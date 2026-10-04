import os
import re
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import gba_project
from tools.project import ProjectConfig


class GbaRegionTests(unittest.TestCase):
    def generate(self, work, version, aggregate=False):
        info = gba_project.PROGRAMS[version]["gba_cli"]
        config_dir = work / "gba/config" / info["config"]
        config_dir.mkdir(parents=True)
        unit = "bundle" if aggregate else "main/main"
        (config_dir / "splits.txt").write_text(
            f"{unit}:\n\t.text start:0x02000000 end:0x02000004\n"
            "libgcc/_udivsi3:\n\t.text start:0x02000004 end:0x02000008\n")
        (config_dir / "symbols.txt").write_text(
            "Entry = .text:0x02000000; // type:function size:0x4 thumb\n")
        source_dir = work / "gba/src/cli"
        (source_dir / "main").mkdir(parents=True, exist_ok=True)
        (source_dir / "main/tables.c").write_text("int table[4];\n")
        (source_dir / "settings.cpp").write_text("int setting;\n")
        (source_dir / "unmapped_assets.s").write_text('.incbin "unknown.bin"\n')
        if aggregate:
            (source_dir / "bundle").mkdir()
            (source_dir / "bundle/z.c").write_text("int Entry(void) { return 0; }\n")
            (source_dir / "bundle/a.cpp").write_text("int Other(void) { return 1; }\n")
            (config_dir / "link_order.txt").write_text("bundle:\n\tz.c\n\ta.cpp\n")
        else:
            (source_dir / "main/main.c").write_text("int Entry(void) { return 0; }\n")
        original = work / "orig" / version / "gba/ffcc_cli.bin"
        original.parent.mkdir(parents=True)
        original.write_bytes(bytes(8))
        compilers = work / "compilers"
        compilers.mkdir(exist_ok=True)
        suffix = ".exe" if os.name == "nt" else ""
        for name in ("cc1", "cc1plus", "old_agbcc", "gcc2-cpp"):
            (compilers / (name + suffix)).touch()
        config = ProjectConfig()
        config.version = version
        config.build_dir = Path("build")
        with patch.dict(gba_project.PROGRAMS, {version: {"gba_cli": info}}, clear=True), \
                patch.dict(gba_project.VERSION_COMPLETE, {"GCCP01": gba_project.COMPLETE}, clear=True):
            gba_project.configure_gba(config, Path("binutils"), compilers)
        ninja = (work / "build" / version / "gba/build.ninja").read_text()
        return config, re.sub(r"\$\n\s*", "", ninja)

    def test_regional_layout_uses_shared_source_without_pal_link_claims(self):
        with tempfile.TemporaryDirectory() as tmp:
            work = Path(tmp)
            previous = Path.cwd()
            try:
                os.chdir(work)
                for version in ("GCCE01", "GCCJGC"):
                    with self.subTest(version=version):
                        config, ninja = self.generate(work, version)
                        unit = next(u for u in config.extra_objdiff_units if u["name"] == "gba/cli/main/main")
                        self.assertEqual(unit["metadata"]["source_path"], "gba/src/cli/main/main.c")
                        self.assertEqual(unit["base_path"], f"build/{version}/gba/cli/src/main/main.o")
                        self.assertTrue(all(not u["metadata"]["complete"] for u in config.extra_objdiff_units))
                        self.assertIn(f"gba/config/{version}/cli", ninja)
                        self.assertIn(f"-DVERSION_{version}", ninja)
                        self.assertNotIn("--object ", ninja)
                        self.assertIn(f"build/{version}/gba/cli/cli.elf", ninja)
            finally:
                os.chdir(previous)

    def test_unmapped_cpp_and_c_sources_compile_without_regional_claims(self):
        with tempfile.TemporaryDirectory() as tmp:
            previous = Path.cwd()
            try:
                os.chdir(tmp)
                config, ninja = self.generate(Path(tmp), "GCCE01")
                for unit in ("main/tables", "settings"):
                    obj = f"build/GCCE01/gba/cli/src/{unit}.o"
                    self.assertIn(obj, config.extra_source_inputs)
                    self.assertIn(f"build {obj}: gba_as", ninja)
                    self.assertNotIn("gba/cli/" + unit,
                                     [u["name"] for u in config.extra_objdiff_units])
                link = next(line for line in ninja.splitlines()
                            if line.startswith("build build/GCCE01/gba/cli/cli.elf:"))
                self.assertNotIn("src/main/tables.o", link)
                self.assertNotIn("src/settings.o", link)
                self.assertNotIn("gba/src/cli/unmapped_assets.s", ninja)
            finally:
                os.chdir(previous)

    def test_aggregate_sources_keep_order_without_duplicate_rules(self):
        with tempfile.TemporaryDirectory() as tmp:
            previous = Path.cwd()
            try:
                os.chdir(tmp)
                _, ninja = self.generate(Path(tmp), "GCCE01", aggregate=True)
                base = "build/GCCE01/gba/cli/src/bundle"
                self.assertIn(f"build {base}.o: gba_ld_r {base}/z.o {base}/a.o", ninja)
                self.assertEqual(ninja.count(f"build {base}/z.i: gba_cpp"), 1)
                self.assertEqual(ninja.count(f"build {base}/a.ii: gba_cpp"), 1)
            finally:
                os.chdir(previous)

    def test_pal_retains_proven_source_and_library_link_claims(self):
        with tempfile.TemporaryDirectory() as tmp:
            previous = Path.cwd()
            try:
                os.chdir(tmp)
                config, ninja = self.generate(Path(tmp), "GCCP01")
                self.assertTrue(all(u["metadata"]["complete"] for u in config.extra_objdiff_units))
                self.assertIn("--object main/main=build/GCCP01/gba/cli/src/main/main.o", ninja)
                self.assertIn("--object libgcc/_udivsi3=build/GCCP01/gba/cli/src/libgcc/_udivsi3.o", ninja)
            finally:
                os.chdir(previous)

    def test_regional_claims_are_explicit_and_program_scoped(self):
        claims = {"GCCE01": {"cli": ["libgcc/_udivsi3"]}}
        units = ["libgcc/_udivsi3", "libgcc/_divsi3", "main/main"]
        with patch.dict(gba_project.VERSION_COMPLETE, claims, clear=True):
            self.assertEqual(gba_project._complete_units("GCCE01", "cli", units),
                             {"libgcc/_udivsi3"})
            self.assertEqual(gba_project._complete_units("GCCE01", "mgr", units), set())
            self.assertEqual(gba_project._complete_units("GCCJGC", "cli", units), set())


if __name__ == "__main__":
    unittest.main()
