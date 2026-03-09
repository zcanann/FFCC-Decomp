import os
import subprocess
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import Mock, patch

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

    def test_read_int_env_below_minimum_uses_default_and_logs(self):
        with patch.dict(os.environ, {"AGENTIC_TIMEOUT_SECONDS": "0"}, clear=True):
            with patch("agentic_loop.log") as mock_log:
                self.assertEqual(
                    agentic_loop._read_int_env("AGENTIC_TIMEOUT_SECONDS", 1500, minimum=1),
                    1500,
                )
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

    def test_main_uses_default_prompt_when_env_prompt_is_blank(self):
        env = {
            "AGENTIC_PROMPT": "   ",
            "AGENTIC_TIMEOUT_SECONDS": "1",
            "AGENTIC_TERMINATE_GRACE_SECONDS": "2",
            "AGENTIC_MAX_BACKOFF_SECONDS": "3",
        }
        with patch.dict(os.environ, env, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main()

        mock_run.assert_called_once_with(
            prompt=agentic_loop.DEFAULT_PROMPT,
            timeout_seconds=1,
            terminate_grace_seconds=2,
            max_backoff_seconds=3,
        )

    def test_main_uses_defaults_for_out_of_range_numeric_env(self):
        env = {
            "AGENTIC_PROMPT": "x",
            "AGENTIC_TIMEOUT_SECONDS": "0",
            "AGENTIC_TERMINATE_GRACE_SECONDS": "-1",
            "AGENTIC_MAX_BACKOFF_SECONDS": "0",
        }
        with patch.dict(os.environ, env, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main()

        mock_run.assert_called_once_with(
            prompt="x",
            timeout_seconds=25 * 60,
            terminate_grace_seconds=10,
            max_backoff_seconds=300,
        )

    def test_run_agentic_loop_timeout_applies_backoff_sleep(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=0,
            wait=Mock(side_effect=subprocess.TimeoutExpired(cmd="codex", timeout=1)),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc):
            with patch("agentic_loop._stop_process_tree") as mock_stop:
                with patch("agentic_loop._sleep_interruptible", side_effect=[False]) as mock_sleep:
                    agentic_loop.run_agentic_loop(
                        prompt="x",
                        timeout_seconds=1,
                        terminate_grace_seconds=2,
                        max_backoff_seconds=300,
                    )

        mock_stop.assert_called_once_with(fake_proc, 2)
        mock_sleep.assert_called_once_with(2)


if __name__ == "__main__":
    unittest.main()
