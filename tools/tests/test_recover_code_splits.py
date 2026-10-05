import os
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

from tools.recover_code_splits import dol_sections, read_symbols, recover, relocate_code

ROOT = Path(__file__).resolve().parents[2]
BIN = Path(os.environ.get('PPC_BINUTILS', ROOT / 'build/binutils'))
AS = BIN / ('powerpc-eabi-as.exe' if sys.platform == 'win32' else 'powerpc-eabi-as')
LD = BIN / ('powerpc-eabi-ld.exe' if sys.platform == 'win32' else 'powerpc-eabi-ld')
OBJCOPY = BIN / ('powerpc-eabi-objcopy.exe' if sys.platform == 'win32' else 'powerpc-eabi-objcopy')


def dol(body, copies=1, data_only=False):
    result = bytearray(0x100)
    index = 7 if data_only else 0
    struct.pack_into('>I', result, index * 4, 0x100)
    struct.pack_into('>I', result, 0x48 + index * 4, 0x80004000)
    struct.pack_into('>I', result, 0x90 + index * 4, len(body) * copies)
    return bytes(result) + body * copies


class DolTests(unittest.TestCase):
    def test_truncated_and_out_of_bounds(self):
        with self.assertRaisesRegex(ValueError, 'header'):
            dol_sections(b'')
        with self.assertRaisesRegex(ValueError, 'bounds'):
            dol_sections(dol(bytes(16))[:-1])

    def test_branch_range_and_alignment(self):
        for target in (0x84000000, 0x80004002):
            with self.subTest(target=target), self.assertRaisesRegex(ValueError, 'out of range'):
                relocate_code(bytes.fromhex('48000001'), 0x80004000,
                              [dict(offset=0, kind=10, value=target, relative=False)])


@unittest.skipUnless(AS.is_file(), 'PowerPC GNU assembler required')
class RecoveryTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.path = Path(self.temp.name)

    def fixture(self, extra=''):
        source = self.path / 'unit.s'
        source.write_text('''
.text
.global Function
.type Function,@function
Function:
li 3, 17
li 4, 23
li 5, 41
blr
.size Function,.-Function
''' + extra, encoding='utf-8')
        obj = self.path / 'unit.o'
        subprocess.run([str(AS), '-mgekko', '-o', str(obj), str(source)], check=True, capture_output=True)
        return obj.read_bytes(), bytes.fromhex('386000113880001738a000294e800020')

    def test_complete_unit_and_named_anchor(self):
        obj, body = self.fixture()
        known = read_symbols('Function = .text:0x80004000; // type:function size:0x10')
        row = recover('unit.c', obj, dol(body), known)
        self.assertEqual(row['status'], 'verified')
        self.assertEqual(row['verified_bytes'], 16)
        self.assertEqual(row['relocation_count'], 0)
        self.assertIn('end:0x80004010', row['split_snippet'])
        known['Function']['address'] += 4
        self.assertIn('disagrees', recover('unit.c', obj, dol(body), known)['reason'])

    def test_complete_text_and_init_sections(self):
        init_source = '''
.section .init,"ax"
.global Initializer
.type Initializer,@function
Initializer:
li 3, 19
li 4, 29
li 5, 43
blr
.size Initializer,.-Initializer
'''
        obj, body = self.fixture(init_source)
        init = bytes.fromhex('386000133880001d38a0002b4e800020')
        known = read_symbols('Function = .text:0x80004000; // type:function size:0x10\n'
                             'Initializer = .init:0x80004010; // type:function size:0x10')
        row = recover('unit.c', obj, dol(body + init), known)
        self.assertEqual(row['status'], 'verified', row)
        self.assertEqual(row['verified_bytes'], 32)
        self.assertEqual([s['section'] for s in row['sections']], ['.text', '.init'])
        self.assertEqual(len(row['functions']), 2)
        self.assertEqual(row['split_snippet'].count('unit.c:'), 1)
        self.assertIn('.init start:0x80004010 end:0x80004020', row['split_snippet'])
        for image in (dol(body), dol(body + init[:-1] + b'!'), dol(body + init + init)):
            rejected = recover('unit.c', obj, image, known)
            self.assertEqual(rejected['status'], 'rejected', rejected)
            self.assertNotIn('split_snippet', rejected)
        for extra in ('.data\n.word 1\n', '.bss\n.space 4\n', '.comm storage,4,4\n'):
            with self.subTest(storage=extra):
                unverified, _ = self.fixture(init_source + extra)
                rejected = recover('unit.c', unverified, dol(body + init), known)
                self.assertEqual(rejected['status'], 'rejected', rejected)
                self.assertNotIn('split_snippet', rejected)

    def test_rejects_overlapping_code_section_placements(self):
        obj, body = self.fixture('''
.section .init,"ax"
.global Initializer
.type Initializer,@function
Initializer:
li 3, 17
li 4, 23
li 5, 41
blr
.size Initializer,.-Initializer
''')
        row = recover('unit.c', obj, dol(body), {})
        self.assertEqual(row['status'], 'rejected', row)
        self.assertIn('sections overlap', row['reason'])
        self.assertNotIn('split_snippet', row)

    def test_rejects_duplicates_data_only_and_changed_byte(self):
        obj, body = self.fixture()
        self.assertEqual(len(recover('unit.c', obj, dol(body, 2), {})['candidates']), 2)
        for image in (dol(body, data_only=True), dol(body[:-1] + b'!')):
            self.assertEqual(recover('unit.c', obj, image, {})['status'], 'rejected')

    def test_rejects_data_common_and_relocations(self):
        for extra in ('.data\n.word 1\n', '.comm storage,4,4\n', '.text\nbl External\n'):
            obj, body = self.fixture(extra)
            self.assertEqual(recover('unit.c', obj, dol(body), {})['status'], 'rejected')

    def test_rejects_conflicting_named_identity(self):
        obj, body = self.fixture()
        known = read_symbols('Another = .text:0x80004000; // type:function size:0x10')
        self.assertIn('another named', recover('unit.c', obj, dol(body), known)['reason'])

    def test_rejects_overlapping_known_function_and_data_extents(self):
        obj, body = self.fixture()
        for line in (
            'Inside = .text:0x80004004; // type:function size:0xC',
            'Data = .text:0x80004000; // type:object size:0x10',
            'Container = .text:0x80003FFC; // type:function size:0x14',
            'fn_80004000 = .text:0x80004000; // type:function size:0xC',
            'fn_80004000 = .init:0x80004000; // type:function size:0x10',
        ):
            with self.subTest(symbol=line):
                row = recover('unit.c', obj, dol(body), read_symbols(line))
                self.assertEqual(row['status'], 'rejected')
                self.assertIn('overlapping known definition', row['reason'])
                self.assertNotIn('split_snippet', row)

    def test_exact_placeholders_and_unknown_size_starts(self):
        obj, body = self.fixture()
        for name in ('Function', 'fn_80004000'):
            for size in (0, 16):
                with self.subTest(name=name, size=size):
                    known = read_symbols(f'{name} = .text:0x80004000; // type:function size:{size}')
                    known.update(read_symbols('BranchLabel = .text:0x80004004; // type:label'))
                    self.assertEqual(recover('unit.c', obj, dol(body), known)['status'], 'verified')
        for line in (
            'Inside = .text:0x80004004; // type:function size:0',
            'Data = .text:0x80004000; // type:object size:0',
            'fn_real = .text:0x80004000; // type:function size:0x10',
            'fn_80005000 = .text:0x80004000; // type:function size:0x10',
        ):
            with self.subTest(symbol=line):
                self.assertEqual(recover('unit.c', obj, dol(body), read_symbols(line))['status'], 'rejected')


@unittest.skipUnless(AS.is_file() and LD.is_file() and OBJCOPY.is_file(), 'PowerPC GNU binutils required')
class RelocationTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.path = Path(self.temp.name)

    def linked_fixture(self, extra='', address=0x80004000):
        source = self.path / 'relocations.s'
        source.write_text('''
.text
.global Function
.type Function,@function
Function:
bl External+4
lis 3,Data@ha
addi 3,3,Data@l
lis 4,Data@h
lis 5,(Data+32)@ha
addi 5,5,(Data+32)@l
lis 6,Function@ha
addi 6,6,Function@l
li 7,41
blr
.size Function,.-Function
''' + extra, encoding='utf-8')
        obj, linked, binary = [self.path / name for name in ('relocations.o', 'linked.elf', 'linked.bin')]
        subprocess.run([str(AS), '-mgekko', '-o', str(obj), str(source)], check=True, capture_output=True)
        subprocess.run([str(LD), '-Ttext', hex(address), '--defsym', 'External=0x80005000',
                        '--defsym', 'Data=0x8033FFF0', '-e', 'Function', '-o', str(linked), str(obj)],
                       check=True, capture_output=True)
        subprocess.run([str(OBJCOPY), '-O', 'binary', '-j', '.text', str(linked), str(binary)],
                       check=True, capture_output=True)
        known = read_symbols('External = .text:0x80005000; // type:function size:0x4\n'
                             'Data = .data:0x8033FFF0; // type:object size:0x40')
        return obj.read_bytes(), binary.read_bytes(), known

    def test_replays_actual_gnu_linker_output(self):
        obj, body, known = self.linked_fixture()
        self.assertEqual(recover('unit.c', obj, dol(body), known)['status'], 'rejected')
        row = recover('unit.c', obj, dol(body), known, allow_relocations=True)
        self.assertEqual(row['status'], 'verified', row)
        self.assertEqual(row['relocation_count'], 8)
        self.assertEqual(row['verified_bytes'], len(body))

    def test_rejects_corrupt_branch_and_address_relocations(self):
        obj, body, known = self.linked_fixture()
        for offset in (3, 7, 11, 15, 19, 23, 27, 31, 35):
            changed = bytearray(body)
            changed[offset] ^= 4
            with self.subTest(offset=offset):
                row = recover('unit.c', obj, dol(changed), known, True)
                self.assertEqual(row['status'], 'rejected', row)
                self.assertNotIn('split_snippet', row)

    def test_rejects_unresolved_or_wrong_external_identity(self):
        obj, body, known = self.linked_fixture()
        known.pop('External')
        self.assertIn('unresolved', recover('unit.c', obj, dol(body), known, True)['reason'])
        known.update(read_symbols('External = .text:0x80005004; // type:function size:0x4'))
        self.assertEqual(recover('unit.c', obj, dol(body), known, True)['status'], 'rejected')

    def test_rejects_unsupported_relocation(self):
        obj, body, known = self.linked_fixture('.long Data\n')
        row = recover('unit.c', obj, dol(body), known, True)
        self.assertIn('unsupported PowerPC relocation', row['reason'])

    def test_rejects_two_fully_relocated_placements(self):
        obj, first, known = self.linked_fixture()
        _, second, _ = self.linked_fixture(address=0x80004000 + len(first))
        row = recover('unit.c', obj, dol(first + second), known, True)
        self.assertEqual(row['status'], 'rejected')
        self.assertEqual(row['candidates'], [0x80004000, 0x80004000 + len(first)])


if __name__ == '__main__':
    unittest.main()
