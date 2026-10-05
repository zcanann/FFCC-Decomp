import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from gba.tools.gbaanalysis import Analysis, EWRAM_BASE, IWRAM_BASE
from gba.tools.split import Emitter, Split, Symbol

ROOT = Path(__file__).resolve().parents[2]
EXE = ".exe" if sys.platform == "win32" else ""
BIN = ROOT / "build/tools/gba-binutils/bin"
if not (BIN / ("arm-none-eabi-ld" + EXE)).is_file():
    system_ld = shutil.which("arm-none-eabi-ld" + EXE)
    if system_ld:
        BIN = Path(system_ld).parent


class GbaDataPointerTests(unittest.TestCase):
    def emitter(self, offset, target=IWRAM_BASE + 16, size=16):
        data = bytearray(range(size))
        struct.pack_into("<I", data, offset, target)
        symbols = [Symbol("stream", ".rodata", EWRAM_BASE, "object", size, raw=True),
                   Symbol("target", ".bss", IWRAM_BASE + 16, "object", 4)]
        ranges = [Split("stream", ".rodata", EWRAM_BASE, EWRAM_BASE + size)]
        return Emitter(Analysis(EWRAM_BASE, bytes(data)), symbols, ranges,
                       data_pointers=[EWRAM_BASE + offset]), data

    @unittest.skipUnless((BIN / ("arm-none-eabi-ld" + EXE)).is_file(), "GBA binutils required")
    def test_packed_pointer_relocates_without_changing_adjacent_bytes(self):
        def tool(name, *args):
            subprocess.run([str(BIN / ("arm-none-eabi-" + name + EXE)), *map(str, args)],
                           check=True, capture_output=True)

        with tempfile.TemporaryDirectory() as tmp:
            work = Path(tmp)
            for offset in range(4, 8):
                with self.subTest(offset=offset):
                    emitter, data = self.emitter(offset)
                    (work / "stream.s").write_text(emitter.emit_unit("stream"))
                    tool("as", "-mcpu=arm7tdmi", "-o", work / "stream.o", work / "stream.s")
                    for target in (IWRAM_BASE + 16, IWRAM_BASE + 48):
                        tool("ld", "--defsym", f"target={target}", "-o", work / "stream.elf", work / "stream.o")
                        tool("objcopy", "-O", "binary", "-j", ".rodata", work / "stream.elf", work / "stream.bin")
                        expected = bytearray(data)
                        struct.pack_into("<I", expected, offset, target)
                        self.assertEqual((work / "stream.bin").read_bytes(), expected)

    def test_unknown_pointer_target_is_rejected(self):
        emitter, _ = self.emitter(5, target=0x12345678)
        with self.assertRaisesRegex(ValueError, "no symbolic target"):
            emitter.emit_unit("stream")

    def test_pointer_crossing_symbol_is_rejected(self):
        emitter, _ = self.emitter(5)
        emitter.by_address[EWRAM_BASE + 7] = [Symbol("inner", ".rodata", EWRAM_BASE + 7, "object", 1)]
        with self.assertRaisesRegex(ValueError, "crosses a boundary"):
            emitter.emit_unit("stream")

    def test_overlapping_pointer_fields_are_rejected(self):
        emitter, _ = self.emitter(5)
        emitter.data_pointers.add(EWRAM_BASE + 6)
        with self.assertRaisesRegex(ValueError, "crosses a boundary"):
            emitter.emit_unit("stream")


if __name__ == "__main__":
    unittest.main()
