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


if __name__ == "__main__":
    unittest.main()
