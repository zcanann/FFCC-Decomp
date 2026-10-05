import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

from gba.tools.recover_functions import BASE, audit
from gba.tools.recover_splits import audit as audit_sections, read_object
from gba.tools.split import Split, Symbol

ROOT = Path(__file__).resolve().parents[2]
EXE = '.exe' if sys.platform == 'win32' else ''
BIN = ROOT / 'build/tools/gba-binutils/bin'
if not (BIN / ('arm-none-eabi-as' + EXE)).is_file():
    system_as = shutil.which('arm-none-eabi-as' + EXE)
    if system_as:
        BIN = Path(system_as).parent


@unittest.skipUnless((BIN / ('arm-none-eabi-ld' + EXE)).is_file(), 'GBA binutils required')
class FunctionRecoveryTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.work = Path(self.temp.name)

    def tool(self, name, *args):
        return subprocess.run([str(BIN / ('arm-none-eabi-' + name + EXE)), *map(str, args)],
                              check=True, capture_output=True, text=True).stdout

    def assemble(self, name, source):
        path = self.work / (name + '.s')
        path.write_text(source, encoding='utf-8')
        obj = path.with_suffix('.o')
        self.tool('as', '-mcpu=arm7tdmi', '-o', obj, path)
        return obj

    def image(self, objects, script='SECTIONS { .text 0x02000000 : { *(.text) } }'):
        linker = self.work / 'link.ld'
        linker.write_text(script, encoding='utf-8')
        elf, output = self.work / 'image.elf', self.work / 'image.bin'
        self.tool('ld', '-T', linker, '-o', elf, *objects)
        self.tool('objcopy', '-O', 'binary', elf, output)
        return output.read_bytes()

    def function(self, name='Entry', body=None):
        return f'''
.text
.thumb
.align 2
.global {name}
.type {name},%function
.thumb_func
{name}:
{body or 'mov r0,#17; mov r1,#23; mov r2,#31; mov r3,#41; add r0,r1; bx lr'}
.size {name}, .-{name}
'''

    def functions(self, result):
        return {name: f for o in result['objects'] for f in o['functions'] for name in f['names']}

    def test_region_inserts_function_and_moves_named_pooled_data(self):
        first = self.function('First', 'push {lr}; bl Second; ldr r0,pool; mov r2,#17; pop {r1}; bx r1; .align 2; pool: .word blob+2')
        second = self.function('Second')
        data = '.section .rodata,"a"\n.type blob,%object\nblob: .ascii "abcdef"\n.size blob,.-blob\n'
        source = self.assemble('source', first + second + data)
        target = self.assemble('target', first + self.function('Added', 'mov r0,#99; bx lr') + second + '.section .rodata,"a"\n.space 16\n' + data)
        image = self.image([target], 'SECTIONS { .text 0x02000000 : { *(.text) } .rodata 0x02000100 : { *(.rodata) } }')
        _, sections, _ = read_object(target)
        text = next(s for s in sections.values() if s.name == '.text')
        second_at = BASE + next(s['value'] & ~1 for s in text.symbols if s['name'] == 'Second')
        symbols = [Symbol('First', '.text', BASE, 'function', 20, True),
                   Symbol('Second', '.text', second_at, 'function', 12, True),
                   Symbol('blob', '.rodata', BASE + 0x110, 'object', 6, local=True)]
        splits = [Split('owner', '.text', BASE, BASE + text.size),
                  Split('owner', '.rodata', BASE + 0x110, BASE + 0x116)]
        self.assertNotEqual(audit_sections([('owner', source)], image, symbols, splits)['objects'][0]['sections'][0]['status'], 'verified')
        functions = self.functions(audit([('owner', source)], image, symbols, splits))
        self.assertEqual(functions['First']['status'], 'verified')
        self.assertEqual(functions['Second']['address'], second_at)
        self.assertEqual(functions['Second']['status'], 'verified')
        relocation = next(r for r in functions['First']['candidates'][0]['relocations'] if r['type'] == 2)
        self.assertEqual(relocation['symbol'], 'blob')
        self.assertEqual(relocation['target'], BASE + 0x110)

    def test_masked_relocations_do_not_accept_wrong_or_unknown_callee(self):
        source = self.assemble('caller', self.function(body='push {lr}; bl External; mov r0,#17; mov r1,#23; mov r2,#31; pop {r3}; bx r3'))
        external = self.assemble('external', self.function('External'))
        image = self.image([source, external])
        unknown = self.functions(audit([('caller', source)], image, [], []))['Entry']
        self.assertEqual(unknown['status'], 'unresolved')
        self.assertEqual(unknown['candidates'][0]['unresolved_references'][0]['symbol'], 'External')
        wrong = [Symbol('External', '.text', BASE + 0x100, 'function', 12, True)]
        row = self.functions(audit([('caller', source)], image, wrong, []))['Entry']
        self.assertEqual(row['status'], 'unmatched')
        self.assertEqual(row['candidates'][0]['reason'], 'relocation replay differs from retail')

    def test_independent_function_identity_resolves_later_round(self):
        source = self.assemble('both', self.function('Caller', 'push {lr}; bl Callee; mov r0,#42; mov r1,#43; mov r2,#44; pop {r3}; bx r3') + self.function('Callee'))
        image = self.image([source])
        result = self.functions(audit([('both', source)], image, [], []))
        self.assertEqual({r['status'] for r in result.values()}, {'verified'})
        self.assertEqual(result['Caller']['candidates'][0]['relocations'][0]['symbol'], 'Callee')

    def test_duplicates_and_candidate_limit_remain_ambiguous(self):
        source = self.assemble('one', self.function())
        image = self.image([source])
        doubled = image + image
        row = self.functions(audit([('one', source)], doubled, [], []))['Entry']
        self.assertEqual(row['status'], 'ambiguous')
        self.assertEqual(len(row['candidates']), 2)
        row = self.functions(audit([('one', source)], doubled, [], [], limit=1))['Entry']
        self.assertEqual(row['status'], 'ambiguous')
        self.assertIn('candidate limit exceeded', row['reason'])

    def test_tiny_function_needs_identity_and_aliases_share_one_extent(self):
        source = self.assemble('tiny', self.function(body='bx lr') + '.global Alias\n.thumb_set Alias,Entry\n')
        image = self.image([source])
        unknown = self.functions(audit([('tiny', source)], image, [], []))['Entry']
        self.assertEqual(unknown['status'], 'unresolved')
        known = [Symbol('Entry', '.text', BASE, 'function', 2, True)]
        result = audit([('tiny', source)], image, known, [])
        self.assertEqual(len(result['objects'][0]['functions']), 1)
        self.assertEqual(result['objects'][0]['functions'][0]['names'], ['Alias', 'Entry'])
        self.assertEqual(result['objects'][0]['functions'][0]['status'], 'verified')

    def test_identity_ownership_and_batch_conflicts_are_explicit(self):
        source = self.assemble('one', self.function())
        image = self.image([source])
        symbols = [Symbol('Entry', '.text', BASE + 0x100, 'function', 12, True)]
        splits = [Split('another', '.text', BASE, BASE + 12)]
        result = audit([('one', source), ('two', source)], image, symbols, splits)
        for obj in result['objects']:
            row = obj['functions'][0]
            self.assertEqual(row['status'], 'verified')
            self.assertEqual({c['kind'] for c in row['conflicts']}, {'identity', 'ownership', 'candidate_overlap'})
        self.assertFalse(result['configuration_edits'])
        self.assertFalse(result['source_linkage_claims'])

    def test_conflicting_batch_identity_does_not_resolve_callers(self):
        caller = self.assemble('caller', self.function('Caller', 'push {lr}; bl Callee; mov r0,#42; mov r1,#43; mov r2,#44; pop {r3}; bx r3'))
        callee = self.assemble('callee', self.function('Callee'))
        image = self.image([caller, callee])
        result = self.functions(audit([('caller', caller), ('callee', callee), ('duplicate', callee)], image, [], []))
        self.assertEqual(result['Caller']['status'], 'unresolved')
        self.assertEqual(result['Callee']['identity_status'], 'conflicting')

    def test_ambiguous_regional_name_never_becomes_a_callee_anchor(self):
        caller = self.assemble('caller', self.function('Caller', 'push {lr}; bl Callee; mov r0,#42; mov r1,#43; mov r2,#44; pop {r3}; bx r3'))
        callee = self.assemble('callee', self.function('Callee'))
        image = self.image([caller, callee])
        symbols = [Symbol('Callee', '.text', BASE + 16, 'function', 12, True),
                   Symbol('Callee', '.text', BASE + 100, 'function', 12, True)]
        result = audit([('caller', caller), ('callee', callee)], image, symbols, [])
        self.assertEqual(self.functions(result)['Caller']['status'], 'unresolved')
        self.assertIn('Callee', result['objects'][0]['ambiguous_regional_identities'])

    def test_thumb_literal_alignment_phase_is_preserved(self):
        source = self.assemble('phase', self.function(body='ldr r0,pool; mov r1,#23; mov r2,#31; mov r3,#41; add r0,r1; bx lr; .align 2; pool: .word 0x12345678'))
        image = self.image([source])
        row = self.functions(audit([('phase', source)], b'\0\0' + image, [], []))['Entry']
        self.assertEqual(row['status'], 'unmatched')

    def test_arm_relocations_and_bios_calls_replay(self):
        source = self.assemble('arm', '''
.text
.arm
.global Caller
.type Caller,%function
Caller: push {lr}
bl Callee
mov r0,#42
mov r1,#43
pop {lr}
bx lr
.size Caller,.-Caller
.global Callee
.type Callee,%function
Callee: mov r0,#17
mov r1,#23
svc #0x60000
bx lr
.size Callee,.-Callee
''')
        image = self.image([source])
        result = self.functions(audit([('arm', source)], image, [], []))
        self.assertEqual({f['status'] for f in result.values()}, {'verified'})
        self.assertEqual(result['Caller']['candidates'][0]['relocations'][0]['type'], 28)
        self.assertNotIn('reason', result['Caller'])

    def test_code_match_in_configured_data_is_an_identity_conflict(self):
        source = self.assemble('data', self.function())
        image = self.image([source])
        symbols = [Symbol('numeric_table', '.rodata', BASE, 'object', len(image))]
        result = self.functions(audit([('data', source)], image, symbols, []))['Entry']
        self.assertEqual(result['status'], 'verified')
        self.assertEqual(result['identity_status'], 'conflicting')
        self.assertEqual(result['conflicts'][0]['kind'], 'code_overlaps_configured_object')

    def test_known_bss_pointer_never_certifies_storage(self):
        source = self.assemble('storage', self.function(body='ldr r0,pool; mov r1,#23; mov r2,#31; mov r3,#41; add r0,r1; bx lr; .align 2; pool: .word scratch') + '.bss\n.type scratch,%object\nscratch: .space 12\n.size scratch,.-scratch\n.comm common,8,4\n')
        image = self.image([source], 'SECTIONS { .text 0x02000000 : { *(.text) } .bss 0x03000000 (NOLOAD) : { *(.bss) *(COMMON) } }')
        symbols = [Symbol('scratch', '.bss', 0x03000000, 'object', 12, local=True)]
        splits = [Split('storage', '.bss', 0x03000000, 0x0300000C)]
        result = audit([('storage', source)], image, symbols, splits)
        self.assertEqual(self.functions(result)['Entry']['status'], 'verified')
        self.assertEqual(result['objects'][0]['unverified_storage'], [{'section': '.bss', 'size': 12}])
        self.assertEqual(result['objects'][0]['common'][0]['name'], 'common')
        self.assertFalse(result['storage_extent_claims'])
        # An unrelated global with a coincidentally identical spelling is not
        # evidence for this object's local storage.
        symbols[0].local = False
        self.assertEqual(self.functions(audit([('storage', source)], image, symbols, []))['Entry']['status'], 'unresolved')

    def test_unrelocated_outgoing_branch_needs_target_identity(self):
        source = self.assemble('branch', self.function('First', 'mov r0,#17; mov r1,#23; mov r2,#31; mov r3,#41; add r0,r1; b Second') + self.function('Second', 'bx lr'))
        image = self.image([source])
        result = self.functions(audit([('branch', source)], image, [], []))
        self.assertEqual(result['First']['status'], 'unresolved')
        symbols = [Symbol('Second', '.text', BASE + 12, 'function', 2, True)]
        result = self.functions(audit([('branch', source)], image, symbols, []))
        self.assertEqual(result['First']['status'], 'verified')

    def test_unsupported_relocation_and_crossing_extent_are_rejected(self):
        source = self.assemble('rel32', self.function(body='mov r0,#17; mov r1,#23; mov r2,#31; mov r3,#41; add r0,r1; bx lr; .word External-.'))
        row = self.functions(audit([('rel32', source)], bytes(32), [], []))['Entry']
        self.assertEqual(row['status'], 'unsupported')
        self.assertIn('unsupported relocation 3', row['reason'])
        crossing = self.assemble('crossing', self.function(body='bx lr; .word External').replace('.size Entry, .-Entry', '.size Entry, 4'))
        row = self.functions(audit([('crossing', crossing)], bytes(32), [], []))['Entry']
        self.assertEqual(row['status'], 'unsupported')
        self.assertIn('crosses function boundary', row['reason'])

    def test_cli_project_discovery_uses_original_common_object(self):
        source = self.assemble('owner', self.function())
        image = self.image([source])
        (self.work / 'image.bin').write_bytes(image)
        (self.work / 'symbols.txt').write_text('', encoding='utf-8')
        (self.work / 'splits.txt').write_text('', encoding='utf-8')
        project = self.work / 'objdiff.json'
        project.write_text(json.dumps({'units': [{'name': 'gba/cli/owner', 'base_path': 'owner.common.o'}]}), encoding='utf-8')
        output = self.work / 'result.json'
        subprocess.run([sys.executable, str(ROOT / 'gba/tools/recover_functions.py'), '--image', str(self.work / 'image.bin'),
                        '--config', str(self.work), '--project', str(project), '--program', 'cli', '--output', str(output)], check=True, capture_output=True)
        result = json.loads(output.read_text())
        self.assertEqual(result['summary'], {'verified': 1})
        self.assertTrue(result['objects'][0]['object'].endswith('owner.o'))
        self.assertIn('sha256', result['configuration']['symbols.txt'])


if __name__ == '__main__':
    unittest.main()
