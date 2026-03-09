import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import agent_select_target


class AgentSelectTargetTests(unittest.TestCase):
    def test_module_imports_with_package_relative_extract_symbols(self):
        self.assertTrue(hasattr(agent_select_target, "extract_candidates"))

    def test_derive_object_file_avoids_double_o_suffix(self):
        unit = {"name": "build/foo.o", "metadata": {"source_path": "unknown"}}
        self.assertEqual(agent_select_target.derive_object_file(unit), "foo.o")

    def test_derive_source_file_keeps_existing_source_suffix(self):
        unit = {"name": "src/sample/file.c", "metadata": {"source_path": "unknown"}}
        self.assertEqual(agent_select_target.derive_source_file(unit), "file.c")

    def test_load_blacklist_returns_empty_for_invalid_recent_failures_type(self):
        with tempfile.TemporaryDirectory() as tmp_dir:
            state_path = Path(tmp_dir) / ".openclaw/workspace/memory"
            state_path.mkdir(parents=True)
            with open(state_path / "decomp-state.json", "w", encoding="utf-8") as f:
                json.dump({"recentFailures": "not-a-list"}, f)

            with patch("tools.agent_select_target.Path.home", return_value=Path(tmp_dir)):
                self.assertEqual(agent_select_target.load_blacklist(), [])

    def test_load_blacklist_returns_empty_for_non_object_json_root(self):
        with tempfile.TemporaryDirectory() as tmp_dir:
            state_path = Path(tmp_dir) / ".openclaw/workspace/memory"
            state_path.mkdir(parents=True)
            with open(state_path / "decomp-state.json", "w", encoding="utf-8") as f:
                json.dump(["bad-root"], f)

            with patch("tools.agent_select_target.Path.home", return_value=Path(tmp_dir)):
                self.assertEqual(agent_select_target.load_blacklist(), [])

    def test_extract_candidates_handles_malformed_measure_values(self):
        report = {
            "units": [
                {
                    "name": "build/foo.o",
                    "metadata": {"source_path": "src/foo.cpp"},
                    "measures": {
                        "fuzzy_match_percent": "unknown",
                        "matched_code_percent": None,
                        "matched_data_percent": "bad",
                        "total_functions": "nope",
                        "matched_functions": "",
                        "matched_functions_percent": "???",
                        "total_code": "not-int",
                        "total_data": "still-not-int",
                    },
                    "functions": [{"name": "func_a", "fuzzy_match_percent": "88.5", "size": 32}],
                }
            ]
        }
        with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False) as report_file:
            json.dump(report, report_file)
            report_path = Path(report_file.name)

        try:
            with patch("tools.agent_select_target.load_blacklist", return_value=[]):
                candidates = agent_select_target.extract_candidates(report_path)
        finally:
            report_path.unlink()

        self.assertEqual(len(candidates), 1)
        candidate = candidates[0]
        self.assertEqual(candidate["fuzzy_match"], 0.0)
        self.assertEqual(candidate["matched_data_percent"], 0.0)
        self.assertEqual(candidate["total_functions"], 0)
        self.assertEqual(candidate["top_functions"][0]["match"], 88.5)

    def test_extract_candidates_skips_units_without_name(self):
        report = {
            "units": [
                {
                    "metadata": {"source_path": "src/no_name.cpp"},
                    "measures": {"fuzzy_match_percent": 10},
                }
            ]
        }
        with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False) as report_file:
            json.dump(report, report_file)
            report_path = Path(report_file.name)

        try:
            with patch("tools.agent_select_target.load_blacklist", return_value=[]):
                candidates = agent_select_target.extract_candidates(report_path)
        finally:
            report_path.unlink()

        self.assertEqual(candidates, [])

    def test_extract_candidates_handles_function_missing_name(self):
        report = {
            "units": [
                {
                    "name": "build/foo.o",
                    "metadata": {"source_path": "src/foo.cpp"},
                    "measures": {
                        "fuzzy_match_percent": 20,
                        "matched_code_percent": 20,
                        "matched_data_percent": 20,
                    },
                    "functions": [{"fuzzy_match_percent": "50.0", "size": 16}],
                }
            ]
        }
        with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False) as report_file:
            json.dump(report, report_file)
            report_path = Path(report_file.name)

        try:
            with patch("tools.agent_select_target.load_blacklist", return_value=[]):
                candidates = agent_select_target.extract_candidates(report_path)
        finally:
            report_path.unlink()

        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0]["top_functions"][0]["name"], "unknown")

    def test_is_viable_target_handles_null_metadata(self):
        unit = {
            "name": "main/foo",
            "metadata": None,
            "measures": {
                "fuzzy_match_percent": 10,
                "matched_code_percent": 10,
                "matched_data_percent": 10,
            },
        }
        viable, reason = agent_select_target.is_viable_target(unit, [])
        self.assertTrue(viable)
        self.assertEqual(reason, "viable")

    def test_extract_candidates_handles_null_metadata(self):
        report = {
            "units": [
                {
                    "name": "main/foo",
                    "metadata": None,
                    "measures": {
                        "fuzzy_match_percent": 20,
                        "matched_code_percent": 20,
                        "matched_data_percent": 20,
                    },
                    "functions": [],
                }
            ]
        }
        with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False) as report_file:
            json.dump(report, report_file)
            report_path = Path(report_file.name)

        try:
            with patch("tools.agent_select_target.load_blacklist", return_value=[]):
                candidates = agent_select_target.extract_candidates(report_path)
        finally:
            report_path.unlink()

        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0]["source_file"], "unknown")


if __name__ == "__main__":
    unittest.main()
