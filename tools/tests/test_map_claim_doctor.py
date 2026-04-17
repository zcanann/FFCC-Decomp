import unittest

from tools.map.claim_doctor import AttributionSummary, ProjectSymbol, build_attribution_table, diagnose_section
from tools.map.map_index import load_map_index


class MapIndexParsingTests(unittest.TestCase):
    def test_load_map_index_parses_found_in_and_layout(self):
        with self.subTest("parse mixed PAL-style sample"):
            from pathlib import Path
            import tempfile

            content = """Link map of __start
  1] __start (func,weak) found in os.a __start.c
.bss section layout
  Starting        Virtual
  address  Size   address
  -----------------------
  00000000 000170 802432c0  1 .bss \tfile.o
  00000000 000170 802432c0  4 File \tfile.o
  UNUSED   000030 ........ m$localstatic3$MTXConcatVec__FPA4_fP3VecPA4_f file.o
"""
            with tempfile.TemporaryDirectory() as tmpdir:
                map_path = Path(tmpdir) / "sample.MAP"
                map_path.write_text(content, encoding="utf-8")
                index = load_map_index(map_path, label="sample")

            self.assertEqual(index.object_section_size("file.o", ".bss"), 0x170)
            self.assertEqual(index.layout_records_for_symbol("File", ".bss")[0].object_file, "file.o")
            self.assertEqual(index.layout_records_for_symbol("m$localstatic3$MTXConcatVec__FPA4_fP3VecPA4_f", ".bss")[0].size, 0x30)
            self.assertEqual(index.source_files_for_symbol("__start"), {"__start.c"})


class ClaimDoctorDiagnosisTests(unittest.TestCase):
    def test_build_attribution_table_uses_found_in_object_fallback(self):
        from pathlib import Path
        import tempfile

        content = """Link map of __start
  4] Sound (object,global) found in sound.o
"""
        with tempfile.TemporaryDirectory() as tmpdir:
            map_path = Path(tmpdir) / "sample.MAP"
            map_path.write_text(content, encoding="utf-8")
            index = load_map_index(map_path, label="sample")

        table = build_attribution_table(
            index,
            [ProjectSymbol(name="Sound", section=".bss", address=0x802F26D4, size=0x22DC)],
        )

        self.assertEqual(table["sound.o"][".bss"].bytes, 0x22DC)
        self.assertEqual(table["sound.o"][".bss"].symbols, ["Sound"])

    def test_diagnose_section_prefers_exact_attribution_match(self):
        pal_attr = AttributionSummary()
        pal_attr.add_symbol("MapMng", 0x100)
        diagnosis = diagnose_section(
            source_file="map.cpp",
            object_file="map.o",
            section=".bss",
            compiled_size=0x100,
            claimed_size=0,
            pal_map_total=0x100,
            en_map_total=0x100,
            pal_attr=pal_attr,
            en_attr=AttributionSummary(),
        )

        self.assertEqual(diagnosis.confidence, "medium")
        self.assertIn("direct claim candidate", diagnosis.summary)
        self.assertGreater(diagnosis.score, 100.0)

    def test_diagnose_section_flags_near_old_map_total(self):
        diagnosis = diagnose_section(
            source_file="map.cpp",
            object_file="map.o",
            section=".bss",
            compiled_size=141960,
            claimed_size=0,
            pal_map_total=141948,
            en_map_total=141948,
            pal_attr=AttributionSummary(),
            en_attr=AttributionSummary(),
        )

        self.assertEqual(diagnosis.confidence, "medium")
        self.assertIn("near old-map total", diagnosis.summary)


if __name__ == "__main__":
    unittest.main()
