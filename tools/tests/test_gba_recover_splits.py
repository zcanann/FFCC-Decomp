import shutil
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from gba.tools.recover_splits import BASE, audit, read_object
from gba.tools.split import Split, Symbol

ROOT = Path(__file__).resolve().parents[2]
EXE = '.exe' if sys.platform == 'win32' else ''
BIN = ROOT / 'build/tools/gba-binutils/bin'
if not (BIN / ('arm-none-eabi-as' + EXE)).is_file():
    system_as = shutil.which('arm-none-eabi-as' + EXE)
    if system_as:
        BIN = Path(system_as).parent


@unittest.skipUnless((BIN / ('arm-none-eabi-ld' + EXE)).is_file(), 'GBA binutils required')
class RecoveryTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.work = Path(self.temp.name)

    def tool(self, name, *args):
        return subprocess.run([str(BIN / ('arm-none-eabi-' + name + EXE)),
                               *map(str, args)], check=True, capture_output=True, text=True).stdout

    def assemble(self, name, source):
        path = self.work / (name + '.s')
        path.write_text(source, encoding='utf-8')
        obj = path.with_suffix('.o')
        self.tool('as', '-mcpu=arm7tdmi', '-o', obj, path)
        return obj

    def image(self, objects, script):
        linker = self.work / 'link.ld'
        linker.write_text(script, encoding='utf-8')
        elf = self.work / 'linked.elf'
        self.tool('ld', '-T', linker, '-o', elf, *objects)
        output = self.work / 'image.bin'
        self.tool('objcopy', '-O', 'binary', elf, output)
        return output.read_bytes()

    def fixture(self, duplicate_pointer=False):
        source = '''
.text
.thumb
.global Entry
.type Entry,%function
.thumb_func
Entry:
push {lr}
bl External
ldr r0, pool
mov r2, #17
mov r3, #23
pop {r1}
bx r1
.align 2
pool: .word blob
.size Entry, .-Entry
.section .rodata,"a"
.global blob
.type blob,%object
blob: .ascii "Unique initialized object data"
.size blob, .-blob
'''
        if duplicate_pointer:
            source = source.replace('pool: .word blob', 'pool: .word blob, blob')
        obj = self.assemble('owner', source)
        other = self.assemble('other', '''
.section .external,"ax"
.thumb
.global External
.type External,%function
.thumb_func
External: bx lr
.size External, .-External
''')
        data = self.image([obj, other], '''SECTIONS {
 .text 0x02000000 : { *(.text) }
 .rodata 0x02000080 : { *(.rodata) }
 .external 0x02000100 : { *(.external) }
}''')
        _, sections, _ = read_object(obj)
        text = next(s for s in sections.values() if s.name == '.text')
        pool = next(s['value'] for s in text.symbols if s['name'] == '$d')
        symbols = [Symbol('Entry', '.text', BASE, 'function', pool, True),
                   Symbol('External', '.text', BASE + 0x100, 'function', 2, True),
                   Symbol('false_pool_function', '.text', BASE + pool, 'function', 4)]
        splits = [Split('owner', '.text', BASE, BASE + text.size),
                  Split('regional_data', '.rodata', BASE + 0x80, BASE + 0xA0)]
        return obj, data, symbols, splits, text

    def test_real_relocations_mapping_data_and_reviewable_edits(self):
        obj, image, symbols, splits, text = self.fixture()
        result = audit([('owner', obj)], image, symbols, splits)
        sections = result['objects'][0]['sections']
        self.assertTrue(all(s['status'] == 'verified' for s in sections))
        code = next(s for s in sections if s['section'] == '.text')
        self.assertEqual(code['verified_bytes'], text.size)
        self.assertEqual({r['type'] for r in code['relocations']}, {2, 10})
        edits = code['proposal']['symbol_edits']
        self.assertTrue(any(e['action'] == 'remove_function_boundary'
                            and e['name'] == 'false_pool_function' for e in edits))
        self.assertTrue(any('size:0x' + format(text.size, 'X') in e.get('line', '') for e in edits))
        data = next(s for s in sections if s['section'] == '.rodata')
        self.assertEqual(data['address'], BASE + 0x80)
        self.assertTrue(any(e['action'] == 'add_range' and e['unit'] == 'regional_data'
                            for e in data['proposal']['split_edits']))
        self.assertFalse(result['source_linkage_claims'])
        self.assertEqual(result, audit([('owner', obj)], image, symbols, splits))

    def test_unknown_call_does_not_validate_its_referenced_data(self):
        obj, image, symbols, splits, _ = self.fixture()
        symbols = [s for s in symbols if s.name != 'External']
        rows = audit([('owner', obj)], image, symbols, splits)['objects'][0]['sections']
        text = next(s for s in rows if s['section'] == '.text')
        data = next(s for s in rows if s['section'] == '.rodata')
        self.assertEqual(text['status'], 'unresolved')
        self.assertIn('unresolved relocation', text['reason'])
        self.assertEqual(data['status'], 'conditional')
        self.assertNotIn('proposal', data)

    def test_changed_relocation_bytes_are_not_accepted_as_masked_bytes(self):
        obj, image, symbols, splits, text = self.fixture()
        image = bytearray(image)
        rel = next(r for r in text.relocations if r['type'] == 10)
        image[rel['offset'] + 2] ^= 1
        rows = audit([('owner', obj)], bytes(image), symbols, splits)['objects'][0]['sections']
        code = next(s for s in rows if s['section'] == '.text')
        self.assertEqual(code['status'], 'unresolved')
        self.assertEqual(code['reason'], 'relocated bytes differ from retail')

    def test_disagreeing_data_references_do_not_claim_the_only_matching_copy(self):
        import struct
        obj, image, symbols, splits, text = self.fixture(duplicate_pointer=True)
        image = bytearray(image)
        rel = [r for r in text.relocations if r['type'] == 2][-1]
        struct.pack_into('<I', image, rel['offset'], BASE + 0xA0)
        rows = audit([('owner', obj)], bytes(image), symbols, splits)['objects'][0]['sections']
        code = next(s for s in rows if s['section'] == '.text')
        data = next(s for s in rows if s['section'] == '.rodata')
        self.assertEqual(code['status'], 'unresolved')
        self.assertEqual(data['status'], 'conditional')
        self.assertEqual(data['candidates'], [BASE + 0x80])
        self.assertNotIn('proposal', data)

    def test_duplicate_bodies_and_overlapping_objects_block_proposals(self):
        obj = self.assemble('simple', '''
.arm
.global Simple
.type Simple,%function
Simple: mov r0, #29
mov r1, #31
mov r2, #37
bx lr
.size Simple, .-Simple
''')
        data = self.image([obj], 'SECTIONS { .text 0x02000000 : { *(.text) } }')
        row = audit([('simple', obj)], data + data, [], [])['objects'][0]['sections'][0]
        self.assertEqual(row['status'], 'ambiguous')
        self.assertEqual(row['candidates'], [BASE, BASE + len(data)])
        rows = audit([('first', obj), ('second', obj)], data, [], [])['objects']
        for row in rows:
            self.assertEqual(row['sections'][0]['proposal']['blocked'], 'overlapping object proposals')

    def test_thumb_abs32_odd_addend_matches_gnu_and_rejects_even_pointer(self):
        import struct
        obj = self.assemble('pointer', '''
.text
.thumb
.global Target
.type Target,%function
.thumb_func
Target: mov r0,#47
mov r1,#53
mov r2,#59
mov r3,#61
add r0,r1
bx lr
.size Target, .-Target
.section .rodata,"a"
.global pointers
.type pointers,%object
pointers: .word Target+1, odd_data
.size pointers, .-pointers
.data
.byte 0x12
.global odd_data
.type odd_data,%object
odd_data: .byte 0x34,0x56,0x78
.size odd_data, .-odd_data
''')
        image = self.image([obj], '''SECTIONS {
 .text 0x02000000 : { *(.text) }
 .rodata 0x02000040 : { *(.rodata) }
 .data 0x02000080 : { *(.data) }
}''')
        symbols = [Symbol('Target', '.text', BASE, 'function', 12, True),
                   Symbol('pointers', '.rodata', BASE + 0x40, 'object', 8)]
        rows = audit([('pointer', obj)], image, symbols, [])['objects'][0]['sections']
        self.assertTrue(all(s['status'] == 'verified' for s in rows))
        self.assertEqual(struct.unpack_from('<II', image, 0x40), (BASE | 1, BASE + 0x81))
        data = next(s for s in rows if s['section'] == '.data')
        self.assertEqual(data['address'], BASE + 0x80)
        corrupted = bytearray(image)
        struct.pack_into('<I', corrupted, 0x40, BASE + 2)
        rejected = audit([('pointer', obj)], bytes(corrupted), symbols, [])
        self.assertTrue(all(s['status'] != 'verified' for s in rejected['objects'][0]['sections']))
        self.assertEqual(rejected['batch_split_edits'], [])

    def test_batch_carves_each_original_range_once_and_has_no_overlaps(self):
        from gba.tools.recover_splits import batch_split_edits
        rows = [dict(unit='first', sections=[dict(status='verified', address=BASE + 8,
                size=8, section='.rodata', alignment=4, proposal={'split_edits': []})]),
                dict(unit='second', sections=[dict(status='verified', address=BASE + 24,
                size=8, section='.rodata', alignment=4, proposal={'split_edits': []})])]
        original = Split('regional_data', '.rodata', BASE, BASE + 40)
        edits = batch_split_edits(rows, [original])
        self.assertEqual(sum(e['action'] == 'remove_range' for e in edits), 1)
        added = sorted((e['start'], e['end']) for e in edits if e['action'] == 'add_range')
        self.assertEqual(added, [(BASE, BASE + 8), (BASE + 8, BASE + 16),
                                (BASE + 16, BASE + 24), (BASE + 24, BASE + 32),
                                (BASE + 32, BASE + 40)])

    def test_blocked_code_ownership_blocks_dependent_data_claim(self):
        obj, image, symbols, splits, _ = self.fixture()
        result = audit([('different_owner', obj)], image, symbols, splits)
        rows = result['objects'][0]['sections']
        code = next(s for s in rows if s['section'] == '.text')
        data = next(s for s in rows if s['section'] == '.rodata')
        self.assertEqual(code['proposal']['blocked'], 'range overlaps another named unit')
        self.assertEqual(data['proposal']['blocked'], 'referenced ownership is unverified')
        self.assertEqual(result['batch_split_edits'], [])

    def test_project_discovery_uses_whole_objects_not_common_or_temporary_views(self):
        from gba.tools.recover_splits import objects_from_project
        for name in ('unit.o', 'unit.common.o', 'unit.temporary.o', 'other.o'):
            (self.work / name).touch()
        project = self.work / 'objdiff.json'
        project.write_text(json.dumps({'units': [
            {'name': 'gba/cli/main/unit', 'base_path': 'unit.common.o'},
            {'name': 'gba/mgr/other', 'base_path': 'other.o'},
            {'name': 'gba/cli/fallback', 'target_path': 'retail.o'},
        ]}), encoding='utf-8')
        self.assertEqual(objects_from_project(project, 'cli'), [('main/unit', self.work / 'unit.o')])
        (self.work / 'unit.o').unlink()
        with self.assertRaisesRegex(ValueError, 'source object missing'):
            objects_from_project(project, 'cli')

    def constructor_fixture(self, external=False):
        obj = self.assemble('constructor', '''
.text
.thumb
.global Init
.type Init,%function
.thumb_func
Init: mov r0,#47
mov r1,#53
mov r2,#59
mov r3,#61
add r0,r1
bx lr
.size Init, .-Init
.section .ctors,"aw"
.align 2
.word ''' + ('Missing' if external else 'Init') + '\n')
        image = self.image([obj], '''Missing = 0x02000101; SECTIONS {
 .text 0x02000000 : { *(.text) }
 .ctors 0x02000080 : { *(.ctors) }
}''')
        symbols = [Symbol('Init', '.text', BASE, 'function', 12, True)]
        splits = [Split('constructor', '.text', BASE, BASE + 12),
                  Split('regional_data', '.rodata', BASE + 0x80, BASE + len(image))]
        return obj, image, symbols, splits

    def test_relocation_only_constructor_table_has_unique_verified_placement(self):
        obj, image, symbols, splits = self.constructor_fixture()
        result = audit([('constructor', obj)], image, symbols, splits)
        ctor = next(s for s in result['objects'][0]['sections'] if s['section'] == '.ctors')
        self.assertEqual(ctor['status'], 'verified')
        self.assertEqual(ctor['fixed_bytes'], 0)
        self.assertEqual(ctor['placement_method'], 'resolved_absolute_relocations')
        self.assertEqual(ctor['address'], BASE + 0x80)
        self.assertEqual(ctor['dependencies'], ['.text'])
        self.assertTrue(any(e['action'] == 'add_range' and e['section'] == '.ctors'
                            for e in result['batch_split_edits']))

    def test_relocation_only_search_preserves_ambiguity_and_definition_dependency(self):
        obj, image, symbols, splits = self.constructor_fixture()
        duplicated = image + image[-4:]
        result = audit([('constructor', obj)], duplicated, symbols, splits)
        ctor = next(s for s in result['objects'][0]['sections'] if s['section'] == '.ctors')
        self.assertEqual(ctor['status'], 'ambiguous')
        self.assertEqual(ctor['candidates'], [BASE + 0x80, BASE + 0x84])
        self.assertNotIn('proposal', ctor)
        corrupt = bytearray(image)
        corrupt[0] ^= 1
        result = audit([('constructor', obj)], bytes(corrupt), symbols, splits)
        ctor = next(s for s in result['objects'][0]['sections'] if s['section'] == '.ctors')
        self.assertEqual(ctor['status'], 'conditional')
        self.assertEqual(ctor['unverified_dependencies'], ['.text'])
        self.assertNotIn('proposal', ctor)

    def test_relocation_only_search_does_not_infer_unknown_external_targets(self):
        obj, image, symbols, splits = self.constructor_fixture(external=True)
        result = audit([('constructor', obj)], image, symbols, splits)
        ctor = next(s for s in result['objects'][0]['sections'] if s['section'] == '.ctors')
        self.assertEqual(ctor['status'], 'unresolved')
        self.assertEqual(ctor['candidates'], [])
        self.assertNotIn('proposal', ctor)

    def test_numeric_objects_remain_raw_while_pointer_objects_keep_relocations(self):
        from gba.tools.split import Emitter, analyze, parse_symbols
        obj = self.assemble('tables', '''
.text
.arm
.global Entry
.type Entry,%function
Entry: bx lr
.size Entry, .-Entry
.data
.global NumericWords, PointerWords
.type NumericWords,%object
NumericWords: .word 0x02000000, 0x02000004
.size NumericWords, .-NumericWords
.type PointerWords,%object
PointerWords: .word Entry, NumericWords
.size PointerWords, .-PointerWords
''')
        image = self.image([obj], '''SECTIONS {
 .text 0x02000000 : { *(.text) }
 .data 0x02000040 : { *(.data) }
}''')
        symbols = [Symbol('Entry', '.text', BASE, 'function', 4),
                   Symbol('NumericWords', '.data', BASE + 0x40, 'object', 1, raw=True),
                   Symbol('PointerWords', '.data', BASE + 0x48, 'object', 1, raw=True)]
        splits = [Split('tables', '.text', BASE, BASE + 4),
                  Split('regional_data', '.data', BASE + 0x40, BASE + 0x50)]
        rows = audit([('tables', obj)], image, symbols, splits)['objects'][0]['sections']
        self.assertTrue(all(s['status'] == 'verified' for s in rows))
        lines = [e['line'] for s in rows for e in s['proposal']['symbol_edits']
                 if e['action'] in ('replace_symbol', 'define_symbol')]
        self.assertIn('data:byte', next(s for s in lines if s.startswith('NumericWords ')))
        self.assertNotIn('data:byte', next(s for s in lines if s.startswith('PointerWords ')))
        config = self.work / 'symbols.txt'
        config.write_text('\n'.join(lines) + '\n', encoding='utf-8')
        recovered = parse_symbols(config)
        owned = [Split('tables', s.section, s.start, s.end) for s in splits]
        emitter = Emitter(analyze(image, recovered), recovered, owned)
        assembly = emitter.emit_unit('tables')
        target = self.assemble('recovered', assembly)
        _, source_sections, _ = read_object(obj)
        _, target_sections, _ = read_object(target)
        source = next(s for s in source_sections.values() if s.name == '.data')
        result = next(s for s in target_sections.values() if s.name == '.data')
        self.assertEqual(result.data, source.data)
        self.assertEqual([(r['offset'], r['type'], r['symbol']['name']) for r in result.relocations],
                         [(r['offset'], r['type'], r['symbol']['name']) for r in source.relocations])

    def test_mixed_numeric_pointer_word_blocks_metadata_not_byte_proof(self):
        from gba.tools.split import Emitter, analyze
        obj = self.assemble('mixed', '''
.text
.arm
.global Entry
.type Entry,%function
Entry: bx lr
.size Entry, .-Entry
.data
.global Mixed
.type Mixed,%object
Mixed: .word Entry, 0x02000000
.size Mixed, .-Mixed
''')
        image = self.image([obj], '''SECTIONS {
 .text 0x02000000 : { *(.text) }
 .data 0x02000040 : { *(.data) }
}''')
        symbols = [Symbol('Entry', '.text', BASE, 'function', 4),
                   Symbol('Mixed', '.data', BASE + 0x40, 'object', 8)]
        splits = [Split('mixed', '.text', BASE, BASE + 4),
                  Split('regional_data', '.data', BASE + 0x40, BASE + 0x48)]
        # The same linked value denotes a pointer and an integer. Removing the
        # object's raw flag would make the splitter invent a second relocation.
        owned = [Split('mixed', s.section, s.start, s.end) for s in splits]
        unsafe = self.assemble('unsafe', Emitter(analyze(image, symbols), symbols, owned).emit_unit('mixed'))
        _, source_sections, _ = read_object(obj)
        _, target_sections, _ = read_object(unsafe)
        source = next(s for s in source_sections.values() if s.name == '.data')
        target = next(s for s in target_sections.values() if s.name == '.data')
        self.assertEqual([r['offset'] for r in source.relocations], [0])
        self.assertEqual([r['offset'] for r in target.relocations], [0, 4])
        result = audit([('mixed', obj)], image, symbols, splits)
        row = next(s for s in result['objects'][0]['sections'] if s['section'] == '.data')
        self.assertEqual(row['status'], 'verified')
        self.assertEqual(row['verified_bytes'], 8)
        self.assertEqual(row['proposal'], dict(
            blocked='nonrelocated pointer-like word in mixed object',
            conflicts=[dict(symbol='Mixed', offset=4, address=BASE + 0x44, value=BASE)]))
        self.assertNotIn('symbol_edits', row['proposal'])
        self.assertFalse(any(e['section'] == '.data' for e in result['batch_split_edits']))

    def test_mixed_object_with_nonpointer_integer_remains_accepted(self):
        obj = self.assemble('mixed_small', '''
.text
.arm
.global Entry
.type Entry,%function
Entry: bx lr
.size Entry, .-Entry
.data
.global Mixed
.type Mixed,%object
Mixed: .word Entry, 1234, 0
.size Mixed, .-Mixed
''')
        image = self.image([obj], '''SECTIONS {
 .text 0x02000000 : { *(.text) }
 .data 0x02000040 : { *(.data) }
}''')
        symbols = [Symbol('Entry', '.text', BASE, 'function', 4),
                   Symbol('Mixed', '.data', BASE + 0x40, 'object', 12),
                   Symbol('AbsoluteZero', '.abs', 0, 'object', 0)]
        splits = [Split('mixed_small', '.text', BASE, BASE + 4),
                  Split('regional_data', '.data', BASE + 0x40, BASE + 0x4C)]
        result = audit([('mixed_small', obj)], image, symbols, splits)
        row = next(s for s in result['objects'][0]['sections'] if s['section'] == '.data')
        self.assertEqual(row['status'], 'verified')
        self.assertNotIn('blocked', row['proposal'])
        self.assertNotIn('data:byte', row['proposal']['symbol_edits'][0]['line'])

    def test_mixed_word_bootstrap_without_configured_symbols_or_ranges(self):
        obj = self.assemble('mixed_bootstrap', '''
.text
.arm
.global Entry
.type Entry,%function
Entry:
mov r0, #17
mov r1, #23
mov r2, #41
bx lr
.size Entry, .-Entry
.data
.global Mixed
.type Mixed,%object
Mixed: .word Entry, 0x02000000
.size Mixed, .-Mixed
''')
        image = self.image([obj], '''SECTIONS {
 .text 0x02000000 : { *(.text) }
 .data 0x02000040 : { *(.data) }
}''')
        result = audit([('mixed_bootstrap', obj)], image, [], [])
        row = next(s for s in result['objects'][0]['sections'] if s['section'] == '.data')
        self.assertEqual(row['status'], 'verified')
        self.assertEqual(row['proposal']['blocked'], 'nonrelocated pointer-like word in mixed object')
        self.assertEqual(row['proposal']['conflicts'][0]['value'], BASE)
        self.assertFalse(result['batch_split_edits'])

    def test_known_function_placements_must_agree(self):
        obj = self.assemble('two', '''
.arm
.global First, Second
.type First,%function
First: mov r0,#1
bx lr
.size First, .-First
.type Second,%function
Second: mov r0,#2
bx lr
.size Second, .-Second
''')
        data = self.image([obj], 'SECTIONS { .text 0x02000000 : { *(.text) } }')
        symbols = [Symbol('First', '.text', BASE, 'function', 8),
                   Symbol('Second', '.text', BASE + 12, 'function', 8)]
        row = audit([('two', obj)], data, symbols, [])['objects'][0]['sections'][0]
        self.assertEqual(row['status'], 'unresolved')
        self.assertIn('placements disagree', row['reason'])

    def test_unsupported_relocation_and_nobits_extents_stay_unverified(self):
        unsupported = self.assemble('unsupported', '''
.text
.global Entry
.type Entry,%function
Entry: .word External - .
.word 0x12345678, 0x9ABCDEF0, 0x31415926
.size Entry, .-Entry
''')
        symbols = [Symbol('Entry', '.text', BASE, 'function', 16)]
        row = audit([('unsupported', unsupported)], bytes(16), symbols, [])['objects'][0]['sections'][0]
        self.assertEqual(row['status'], 'unresolved')
        self.assertIn('unsupported relocation 3', row['reason'])
        obj = self.assemble('storage', '''
.text
.global Entry
.type Entry,%function
Entry: .word scratch
.word 0x12345678, 0x9ABCDEF0, 0x31415926
.size Entry, .-Entry
.bss
.align 2
scratch: .space 12
.comm common,8,4
''')
        image = self.image([obj], 'SECTIONS { .text 0x02000000 : { *(.text) } .bss 0x03000000 (NOLOAD) : { *(.bss) *(COMMON) } }')
        result = audit([('storage', obj)], image, symbols, [])['objects'][0]
        self.assertEqual(result['sections'][0]['status'], 'conditional')
        bss = next(s for s in result['sections'] if s['section'] == '.bss')
        self.assertEqual(bss['status'], 'unverified_storage_extent')
        self.assertEqual(bss['references'], [0x03000000])
        self.assertEqual(result['common'][0]['status'], 'unverified_storage_extent')


if __name__ == '__main__':
    unittest.main()
