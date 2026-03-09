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

    def test_load_blacklist_supports_dict_entries_and_deduplicates(self):
        with tempfile.TemporaryDirectory() as tmp_dir:
            state_path = Path(tmp_dir) / ".openclaw/workspace/memory"
            state_path.mkdir(parents=True)
            with open(state_path / "decomp-state.json", "w", encoding="utf-8") as f:
                json.dump(
                    {
                        "recentFailures": [
                            "build/foo.o",
                            {"name": "build/bar.o"},
                            "build/foo.o",
                            {"name": ""},
                            123,
                        ]
                    },
                    f,
                )

            with patch("tools.agent_select_target.Path.home", return_value=Path(tmp_dir)):
                self.assertEqual(
                    agent_select_target.load_blacklist(),
                    ["build/foo.o", "build/bar.o"],
                )

    def test_load_blacklist_prefers_env_configured_state_file(self):
        with tempfile.TemporaryDirectory() as tmp_dir:
            state_path = Path(tmp_dir) / "custom-state.json"
            with open(state_path, "w", encoding="utf-8") as f:
                json.dump({"recentFailures": ["build/from_env.o"]}, f)

            with patch.dict(
                "os.environ",
                {"AGENT_SELECT_TARGET_STATE_FILE": str(state_path)},
                clear=False,
            ):
                self.assertEqual(agent_select_target.load_blacklist(), ["build/from_env.o"])

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

    def test_extract_candidates_ignores_non_dict_unit_rows(self):
        report = {
            "units": [
                "not-a-unit",
                {
                    "name": "build/foo.o",
                    "metadata": {"source_path": "src/foo.cpp"},
                    "measures": {"fuzzy_match_percent": 10, "matched_code_percent": 10, "matched_data_percent": 10},
                    "functions": [],
                },
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
        self.assertEqual(candidates[0]["name"], "build/foo.o")

    def test_extract_candidates_ignores_non_dict_function_rows(self):
        report = {
            "units": [
                {
                    "name": "build/foo.o",
                    "metadata": {"source_path": "src/foo.cpp"},
                    "measures": {"fuzzy_match_percent": 10, "matched_code_percent": 10, "matched_data_percent": 10},
                    "functions": ["bad-func-row", {"name": "f_ok", "fuzzy_match_percent": 50, "size": 8}],
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
        self.assertEqual(len(candidates[0]["top_functions"]), 1)
        self.assertEqual(candidates[0]["top_functions"][0]["name"], "f_ok")

    def test_summarize_symbols_handles_non_dict_payload(self):
        lines = agent_select_target.summarize_symbols("PAL symbols", ["bad-payload"])
        self.assertEqual(lines, ["  PAL symbols: error: unknown error"])

    def test_summarize_symbols_handles_non_string_size_without_crashing(self):
        all_info = {
            "functions": [
                {"parsed": {"symbol": "func_a", "size": 16, "virtual_addr": "0x80000000"}},
            ],
            "globals": [],
        }
        lines = agent_select_target.summarize_symbols("PAL symbols", all_info)
        self.assertEqual(lines[0], "  PAL symbols: 1 funcs, 0 globals (showing up to 5 funcs)")
        self.assertEqual(lines[1], "    - func_a (16b at 0x80000000)")

    def test_parse_args_list_and_per_bucket(self):
        args = agent_select_target._parse_args(["--list", "--per-bucket", "9"])
        self.assertTrue(args.list)
        self.assertEqual(args.per_bucket, 9)

    def test_main_per_bucket_validation(self):
        with patch("builtins.print"):
            with patch("tools.agent_select_target.Path.exists", return_value=True):
                rc = agent_select_target.main(["--per-bucket", "0"])
        self.assertEqual(rc, 1)

    def test_main_per_bucket_overrides_list(self):
        with patch("builtins.print"):
            with patch("tools.agent_select_target.Path.exists", return_value=True):
                with patch(
                    "tools.agent_select_target.extract_candidates", return_value=[{"name": "build/foo.o"}]
                ):
                    with patch(
                        "tools.agent_select_target.build_buckets",
                        return_value={"code": [{"name": "build/foo.o"}], "data": [{"name": "build/foo.o"}]},
                    ) as mock_build:
                        with patch("tools.agent_select_target.print_bucket"):
                            rc = agent_select_target.main(["--list", "--per-bucket", "4"])
        self.assertEqual(rc, 0)
        _, kwargs = mock_build.call_args
        self.assertEqual(kwargs["per_bucket"], 4)


if __name__ == "__main__":
    unittest.main()
