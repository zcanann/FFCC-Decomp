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
