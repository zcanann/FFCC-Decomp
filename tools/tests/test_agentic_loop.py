import os
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

import agentic_loop


class TestAgenticLoop(unittest.TestCase):
    def test_default_prompt_uses_agents_md(self):
        self.assertIn("AGENTS.md", agentic_loop.DEFAULT_PROMPT)
        self.assertNotIn("AGENTS.MD", agentic_loop.DEFAULT_PROMPT)

    def test_read_int_env_returns_default_when_missing(self):
        with patch.dict(os.environ, {}, clear=True):
            self.assertEqual(agentic_loop._read_int_env("AGENTIC_TIMEOUT_SECONDS", 1500), 1500)

    def test_read_int_env_parses_integer(self):
        with patch.dict(os.environ, {"AGENTIC_TIMEOUT_SECONDS": "42"}, clear=True):
            self.assertEqual(agentic_loop._read_int_env("AGENTIC_TIMEOUT_SECONDS", 1500), 42)

    def test_read_int_env_invalid_uses_default_and_logs(self):
        with patch.dict(os.environ, {"AGENTIC_TIMEOUT_SECONDS": "oops"}, clear=True):
            with patch("agentic_loop.log") as mock_log:
                self.assertEqual(agentic_loop._read_int_env("AGENTIC_TIMEOUT_SECONDS", 1500), 1500)
        mock_log.assert_called_once()

    def test_main_reads_env_and_calls_run(self):
        env = {
            "AGENTIC_PROMPT": "x",
            "AGENTIC_TIMEOUT_SECONDS": "1",
            "AGENTIC_TERMINATE_GRACE_SECONDS": "2",
            "AGENTIC_MAX_BACKOFF_SECONDS": "3",
        }
        with patch.dict(os.environ, env, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main()

        mock_run.assert_called_once_with(
            prompt="x",
            timeout_seconds=1,
            terminate_grace_seconds=2,
            max_backoff_seconds=3,
        )


if __name__ == "__main__":
    unittest.main()
