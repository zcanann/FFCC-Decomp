import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from gba.tools.gbaanalysis import Analysis, EWRAM_BASE, IWRAM_BASE
from gba.tools.split import Emitter, Split, Symbol, parse_splits, write_splits

ROOT = Path(__file__).resolve().parents[2]
EXE = ".exe" if sys.platform == "win32" else ""
BIN = ROOT / "build/tools/gba-binutils/bin"
if not (BIN / ("arm-none-eabi-ld" + EXE)).is_file():
    system_ld = shutil.which("arm-none-eabi-ld" + EXE)
    if system_ld:
        BIN = Path(system_ld).parent


class GbaCommonTests(unittest.TestCase):
    def test_common_alignment_survives_config_roundtrip(self):
        ranges = [Split("library", ".common", EWRAM_BASE + 8, EWRAM_BASE + 12, 4)]
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "splits.txt"
            write_splits(path, ranges)
            self.assertEqual(parse_splits(path), ranges)
            emitter = Emitter(Analysis(EWRAM_BASE, bytes(12)),
                              [Symbol("shared", ".common", EWRAM_BASE + 8, "object", 4)], ranges)
            assembly = emitter.emit_unit("library")
            self.assertIn('.section .common,"aw",%nobits', assembly)
            self.assertIn(".balign 4", assembly)
            path.write_text(path.read_text().replace("align:4", "align:3"))
            with self.assertRaises(ValueError):
                parse_splits(path)

    @unittest.skipUnless((BIN / ("arm-none-eabi-ld" + EXE)).is_file(), "GBA binutils required")
    def test_claimed_common_does_not_move_unclaimed_storage(self):
        def tool(name, *args):
            return subprocess.run([str(BIN / ("arm-none-eabi-" + name + EXE)),
                                   *map(str, args)], check=True, capture_output=True, text=True).stdout

        with tempfile.TemporaryDirectory() as tmp:
            work = Path(tmp)
            (work / "owner.s").write_text(".text\n.global Entry\nEntry: .word shared\n"
                                        ".data\n.word 0x55667788\n.bss\n.local scratch\nscratch: .space 4\n.comm shared,4,4\n")
            (work / "other.s").write_text(".text\n.word 0x11223344\n.comm leftover,16,16\n")
            for name in ("owner", "other"):
                tool("as", "-mcpu=arm7tdmi", "-o", work / (name + ".o"), work / (name + ".s"))
            raw = (work / "owner.o").read_bytes()
            tool("ld", "-r", "-d", "-T", ROOT / "gba/tools/common.ld", "-o",
                 work / "view.o", work / "owner.o")
            self.assertEqual((work / "owner.o").read_bytes(), raw)
            self.assertRegex(tool("nm", work / "owner.o"), r" C shared")
            self.assertRegex(tool("nm", work / "view.o"), r" B shared")
            self.assertIn(".common", tool("readelf", "-SW", work / "view.o"))

            for address in (EWRAM_BASE + 12, IWRAM_BASE + 4):
                with self.subTest(address=hex(address)):
                    loaded = address < IWRAM_BASE
                    ranges = [Split("owner", ".text", EWRAM_BASE, EWRAM_BASE + 4),
                              Split("other", ".text", EWRAM_BASE + 4, EWRAM_BASE + 8),
                              Split("owner", ".data", EWRAM_BASE + 8, EWRAM_BASE + 12),
                              Split("owner", ".common", address, address + 4, 4),
                              Split("owner", ".bss", IWRAM_BASE, IWRAM_BASE + 4, 4)]
                    emitter = Emitter(Analysis(EWRAM_BASE, bytes(16 if loaded else 12)), [], ranges)
                    objects = {name: '"' + (work / (name + ".o")).as_posix() + '"'
                               for name in ("owner", "other")}
                    (work / "final.ld").write_text(emitter.linker_script(objects, set(objects)))
                    tool("ld", "-T", work / "final.ld", "-o", work / "final.elf")
                    tool("objcopy", "-O", "binary", "-j", ".text", "-j", ".data",
                         work / "final.elf", work / "final.bin")
                    expected = struct.pack("<III", address, 0x11223344, 0x55667788) + (bytes(4) if loaded else b"")
                    self.assertEqual((work / "final.bin").read_bytes(), expected)
                    symbols = {row.split()[-1]: int(row.split()[0], 16)
                               for row in tool("nm", "--defined-only", work / "final.elf").splitlines()}
                    self.assertEqual(symbols["shared"], address)
                    self.assertEqual(symbols["scratch"], IWRAM_BASE)
                    self.assertEqual(symbols["leftover"], IWRAM_BASE + 16)


if __name__ == "__main__":
    unittest.main()
