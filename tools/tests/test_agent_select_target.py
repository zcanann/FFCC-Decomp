import unittest
import tempfile
import json
from pathlib import Path

from tools import agent_select_target


class DeriveFileNameTests(unittest.TestCase):
    def test_derive_object_file_uses_source_path_stem(self):
        unit = {"name": "foo", "metadata": {"source_path": "src/system/player.cpp"}}
        self.assertEqual(agent_select_target.derive_object_file(unit), "player.o")

    def test_derive_object_file_fallback_drops_known_extension(self):
        unit = {"name": "src/system/player.cpp", "metadata": {"source_path": "unknown"}}
        self.assertEqual(agent_select_target.derive_object_file(unit), "player.o")

    def test_derive_source_file_uses_source_path_name(self):
        unit = {"name": "foo", "metadata": {"source_path": "src/system/player.cpp"}}
        self.assertEqual(agent_select_target.derive_source_file(unit), "player.cpp")

    def test_derive_source_file_fallback_drops_known_extension(self):
        unit = {"name": "src/system/player.cpp", "metadata": {"source_path": "unknown"}}
        self.assertEqual(agent_select_target.derive_source_file(unit), "player.cpp")

    def test_derive_source_file_fallback_preserves_c_extension(self):
        unit = {"name": "src/card/CARDOpen.c", "metadata": {"source_path": "unknown"}}
        self.assertEqual(agent_select_target.derive_source_file(unit), "CARDOpen.c")

    def test_derive_source_file_fallback_defaults_to_cpp_without_extension(self):
        unit = {"name": "src/system/player", "metadata": {"source_path": "unknown"}}
        self.assertEqual(agent_select_target.derive_source_file(unit), "player.cpp")


class NumericParsingTests(unittest.TestCase):
    def test_safe_float_returns_default_for_invalid_values(self):
        self.assertEqual(agent_select_target.safe_float("not-a-number"), 0.0)
        self.assertEqual(agent_select_target.safe_float(None, 2.5), 2.5)

    def test_safe_int_returns_default_for_invalid_values(self):
        self.assertEqual(agent_select_target.safe_int("not-a-number"), 0)
        self.assertEqual(agent_select_target.safe_int(None, 7), 7)

    def test_is_viable_target_handles_non_numeric_measures(self):
        unit = {
            "name": "bad-measures",
            "measures": {
                "fuzzy_match_percent": "N/A",
                "matched_code_percent": None,
                "matched_data_percent": "not-set",
            },
            "metadata": {},
        }
        viable, reason = agent_select_target.is_viable_target(unit, [])
        self.assertTrue(viable)
        self.assertEqual(reason, "viable")

    def test_extract_candidates_handles_non_numeric_function_match(self):
        report = {
            "units": [
                {
                    "name": "unitA",
                    "metadata": {"source_path": "src/unitA.cpp"},
                    "measures": {
                        "fuzzy_match_percent": "75.5",
                        "matched_code_percent": "12.3",
                        "matched_data_percent": "5.0",
                        "total_functions": 2,
                        "matched_functions": 0,
                        "matched_functions_percent": "0.0",
                        "total_code": 100,
                        "total_data": 10,
                    },
                    "functions": [
                        {"name": "fn_bad", "fuzzy_match_percent": "N/A", "size": 16},
                        {"name": "fn_good", "fuzzy_match_percent": 50.0, "size": 32},
                    ],
                }
            ]
        }
        with tempfile.TemporaryDirectory() as tmpdir:
            report_path = Path(tmpdir) / "report.json"
            report_path.write_text(json.dumps(report), encoding="utf-8")
            candidates = agent_select_target.extract_candidates(report_path)

        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0]["fuzzy_match"], 75.5)
        self.assertEqual(len(candidates[0]["top_functions"]), 2)
        self.assertEqual(candidates[0]["top_functions"][0]["name"], "fn_bad")
        self.assertEqual(candidates[0]["top_functions"][0]["match"], 0.0)

    def test_extract_candidates_handles_non_numeric_unit_totals(self):
        report = {
            "units": [
                {
                    "name": "unitB",
                    "metadata": {"source_path": "src/unitB.cpp"},
                    "measures": {
                        "fuzzy_match_percent": "40.0",
                        "matched_code_percent": "10.0",
                        "matched_data_percent": "5.0",
                        "total_functions": "N/A",
                        "matched_functions": None,
                        "matched_functions_percent": "0.0",
                        "total_code": "unknown",
                        "total_data": "missing",
                    },
                    "functions": [],
                }
            ]
        }
        with tempfile.TemporaryDirectory() as tmpdir:
            report_path = Path(tmpdir) / "report.json"
            report_path.write_text(json.dumps(report), encoding="utf-8")
            candidates = agent_select_target.extract_candidates(report_path)

        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0]["total_functions"], 0)
        self.assertEqual(candidates[0]["matched_functions"], 0)
        self.assertEqual(candidates[0]["total_code"], 0)
        self.assertEqual(candidates[0]["total_data"], 0)


if __name__ == "__main__":
    unittest.main()
