import os
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

from tools.recover_code_splits import dol_sections, read_symbols, recover

ROOT = Path(__file__).resolve().parents[2]
BIN = Path(os.environ.get('PPC_BINUTILS', ROOT / 'build/binutils'))
AS = BIN / ('powerpc-eabi-as.exe' if sys.platform == 'win32' else 'powerpc-eabi-as')


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


if __name__ == '__main__':
    unittest.main()
