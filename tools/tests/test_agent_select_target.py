import unittest
import tempfile
import json
from pathlib import Path
from unittest.mock import patch

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

    def test_safe_int_parses_hex_and_float_strings(self):
        self.assertEqual(agent_select_target.safe_int("0x20"), 32)
        self.assertEqual(agent_select_target.safe_int("-0x10"), -16)
        self.assertEqual(agent_select_target.safe_int("12.0"), 12)

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

    def test_extract_candidates_skips_units_without_name(self):
        report = {
            "units": [
                {
                    "metadata": {"source_path": "src/nameless.cpp"},
                    "measures": {
                        "fuzzy_match_percent": "10.0",
                        "matched_code_percent": "0.0",
                        "matched_data_percent": "0.0",
                    },
                    "functions": [],
                },
                {
                    "name": "unitC",
                    "metadata": {"source_path": "src/unitC.cpp"},
                    "measures": {
                        "fuzzy_match_percent": "20.0",
                        "matched_code_percent": "0.0",
                        "matched_data_percent": "0.0",
                    },
                    "functions": [],
                },
            ]
        }
        with tempfile.TemporaryDirectory() as tmpdir:
            report_path = Path(tmpdir) / "report.json"
            report_path.write_text(json.dumps(report), encoding="utf-8")
            candidates = agent_select_target.extract_candidates(report_path)

        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0]["name"], "unitC")

    def test_extract_candidates_defaults_missing_function_name(self):
        report = {
            "units": [
                {
                    "name": "unitD",
                    "metadata": {"source_path": "src/unitD.cpp"},
                    "measures": {
                        "fuzzy_match_percent": "50.0",
                        "matched_code_percent": "10.0",
                        "matched_data_percent": "0.0",
                        "total_functions": 1,
                        "matched_functions": 0,
                        "matched_functions_percent": "0.0",
                        "total_code": 100,
                        "total_data": 0,
                    },
                    "functions": [
                        {"fuzzy_match_percent": "12.0", "size": 8},
                    ],
                }
            ]
        }
        with tempfile.TemporaryDirectory() as tmpdir:
            report_path = Path(tmpdir) / "report.json"
            report_path.write_text(json.dumps(report), encoding="utf-8")
            candidates = agent_select_target.extract_candidates(report_path)

        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0]["top_functions"][0]["name"], "unknown")


class BlacklistLoadingTests(unittest.TestCase):
    def _state_path(self, home):
        return home / ".openclaw/workspace/memory/decomp-state.json"

    def test_load_blacklist_returns_empty_when_state_file_missing(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            home = Path(tmpdir)
            with patch("tools.agent_select_target.Path.home", return_value=home):
                self.assertEqual(agent_select_target.load_blacklist(), [])

    def test_load_blacklist_returns_empty_for_malformed_json(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            home = Path(tmpdir)
            state_path = self._state_path(home)
            state_path.parent.mkdir(parents=True, exist_ok=True)
            state_path.write_text("{not-json", encoding="utf-8")

            with patch("tools.agent_select_target.Path.home", return_value=home):
                self.assertEqual(agent_select_target.load_blacklist(), [])

    def test_load_blacklist_returns_empty_for_unreadable_state_path(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            home = Path(tmpdir)
            state_path = self._state_path(home)
            state_path.parent.mkdir(parents=True, exist_ok=True)
            state_path.mkdir(parents=False, exist_ok=True)

            with patch("tools.agent_select_target.Path.home", return_value=home):
                self.assertEqual(agent_select_target.load_blacklist(), [])

    def test_load_blacklist_returns_recent_failures(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            home = Path(tmpdir)
            state_path = self._state_path(home)
            state_path.parent.mkdir(parents=True, exist_ok=True)
            state_path.write_text(
                json.dumps({"recentFailures": ["unitA", "unitB"]}),
                encoding="utf-8",
            )

            with patch("tools.agent_select_target.Path.home", return_value=home):
                self.assertEqual(agent_select_target.load_blacklist(), ["unitA", "unitB"])

    def test_load_blacklist_returns_empty_for_non_list_recent_failures(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            home = Path(tmpdir)
            state_path = self._state_path(home)
            state_path.parent.mkdir(parents=True, exist_ok=True)
            state_path.write_text(
                json.dumps({"recentFailures": "unitA"}),
                encoding="utf-8",
            )

            with patch("tools.agent_select_target.Path.home", return_value=home):
                self.assertEqual(agent_select_target.load_blacklist(), [])

    def test_load_blacklist_filters_non_string_recent_failures(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            home = Path(tmpdir)
            state_path = self._state_path(home)
            state_path.parent.mkdir(parents=True, exist_ok=True)
            state_path.write_text(
                json.dumps({"recentFailures": ["unitA", 42, None, "unitB"]}),
                encoding="utf-8",
            )

            with patch("tools.agent_select_target.Path.home", return_value=home):
                self.assertEqual(agent_select_target.load_blacklist(), ["unitA", "unitB"])


class SymbolSummaryTests(unittest.TestCase):
    def test_summarize_symbols_accepts_integer_size(self):
        info = {
            "functions": [
                {"parsed": {"symbol": "fnA", "size": 32, "virtual_addr": "0x80001000"}},
            ],
            "globals": [],
        }

        lines = agent_select_target.summarize_symbols("PAL symbols", info)

        self.assertEqual(lines[0], "  PAL symbols: 1 funcs, 0 globals (showing up to 5 funcs)")
        self.assertEqual(lines[1], "    - fnA (0x20b at 0x80001000)")

    def test_summarize_symbols_stringifies_unexpected_size_type(self):
        info = {
            "functions": [
                {"parsed": {"symbol": "fnB", "size": None, "virtual_addr": "0x80002000"}},
            ],
            "globals": [],
        }

        lines = agent_select_target.summarize_symbols("EN symbols", info)

        self.assertEqual(lines[0], "  EN symbols: 1 funcs, 0 globals (showing up to 5 funcs)")
        self.assertEqual(lines[1], "    - fnB (Noneb at 0x80002000)")


if __name__ == "__main__":
    unittest.main()
