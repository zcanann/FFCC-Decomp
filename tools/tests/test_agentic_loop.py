import os
import errno
import subprocess
import sys
import tempfile
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

    def test_resolve_agents_filename_prefers_lowercase_when_both_exist(self):
        prev_cwd = os.getcwd()
        with tempfile.TemporaryDirectory() as tmp_dir:
            os.chdir(tmp_dir)
            Path("AGENTS.md").write_text("", encoding="utf-8")
            Path("AGENTS.MD").write_text("", encoding="utf-8")
            try:
                self.assertEqual(agentic_loop._resolve_agents_filename(), "AGENTS.md")
            finally:
                os.chdir(prev_cwd)

    def test_resolve_agents_filename_falls_back_to_uppercase_variant(self):
        prev_cwd = os.getcwd()
        with tempfile.TemporaryDirectory() as tmp_dir:
            os.chdir(tmp_dir)
            Path("AGENTS.MD").write_text("", encoding="utf-8")
            try:
                self.assertEqual(agentic_loop._resolve_agents_filename(), "AGENTS.MD")
            finally:
                os.chdir(prev_cwd)

    def test_resolve_agents_filename_accepts_mixed_case_variant(self):
        prev_cwd = os.getcwd()
        with tempfile.TemporaryDirectory() as tmp_dir:
            os.chdir(tmp_dir)
            Path("Agents.md").write_text("", encoding="utf-8")
            try:
                self.assertEqual(agentic_loop._resolve_agents_filename(), "Agents.md")
            finally:
                os.chdir(prev_cwd)

    def test_resolve_agents_filename_prefers_exact_match_over_mixed_case(self):
        with patch("agentic_loop.os.listdir", return_value=["Agents.md", "AGENTS.MD"]):
            with patch("agentic_loop.Path.is_file", return_value=True):
                self.assertEqual(agentic_loop._resolve_agents_filename(), "AGENTS.MD")

    def test_resolve_agents_filename_defaults_when_missing(self):
        prev_cwd = os.getcwd()
        with tempfile.TemporaryDirectory() as tmp_dir:
            os.chdir(tmp_dir)
            try:
                self.assertEqual(agentic_loop._resolve_agents_filename(), "AGENTS.md")
            finally:
                os.chdir(prev_cwd)

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
            "AGENTIC_MAX_RUNS": "4",
        }
        with patch.dict(os.environ, env, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main()

        mock_run.assert_called_once_with(
            prompt="x",
            timeout_seconds=1,
            terminate_grace_seconds=2,
            max_backoff_seconds=3,
            max_runs=4,
        )

    def test_main_returns_run_agentic_loop_exit_code(self):
        with patch.dict(os.environ, {}, clear=True):
            with patch("agentic_loop.run_agentic_loop", return_value=7):
                rc = agentic_loop.main()
        self.assertEqual(rc, 7)

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
            max_runs=None,
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
            max_runs=None,
        )

    def test_main_cli_arguments_override_environment(self):
        env = {
            "AGENTIC_PROMPT": "env prompt",
            "AGENTIC_TIMEOUT_SECONDS": "11",
            "AGENTIC_TERMINATE_GRACE_SECONDS": "12",
            "AGENTIC_MAX_BACKOFF_SECONDS": "13",
            "AGENTIC_MAX_RUNS": "14",
        }
        with patch.dict(os.environ, env, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main(
                    [
                        "--prompt",
                        "cli prompt",
                        "--timeout-seconds",
                        "1",
                        "--terminate-grace-seconds",
                        "2",
                        "--max-backoff-seconds",
                        "3",
                        "--max-runs",
                        "5",
                    ]
                )

        mock_run.assert_called_once_with(
            prompt="cli prompt",
            timeout_seconds=1,
            terminate_grace_seconds=2,
            max_backoff_seconds=3,
            max_runs=5,
        )

    def test_main_blank_cli_prompt_uses_default(self):
        with patch.dict(os.environ, {}, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main(["--prompt", "   "])

        _, kwargs = mock_run.call_args
        self.assertEqual(kwargs["prompt"], agentic_loop.DEFAULT_PROMPT)

    def test_main_blank_cli_prompt_falls_back_to_env_prompt(self):
        with patch.dict(os.environ, {"AGENTIC_PROMPT": "env prompt"}, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main(["--prompt", "   "])

        _, kwargs = mock_run.call_args
        self.assertEqual(kwargs["prompt"], "env prompt")

    def test_main_trims_cli_prompt(self):
        with patch.dict(os.environ, {}, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main(["--prompt", "  cli prompt  "])

        _, kwargs = mock_run.call_args
        self.assertEqual(kwargs["prompt"], "cli prompt")

    def test_main_trims_env_prompt(self):
        with patch.dict(os.environ, {"AGENTIC_PROMPT": "  env prompt  "}, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main()

        _, kwargs = mock_run.call_args
        self.assertEqual(kwargs["prompt"], "env prompt")

    def test_main_cli_numeric_validation_falls_back_to_defaults(self):
        with patch.dict(os.environ, {}, clear=True):
            with patch("agentic_loop.run_agentic_loop") as mock_run:
                agentic_loop.main(
                    [
                        "--timeout-seconds",
                        "0",
                        "--terminate-grace-seconds",
                        "-1",
                        "--max-backoff-seconds",
                        "0",
                    ]
                )

        mock_run.assert_called_once_with(
            prompt=agentic_loop.DEFAULT_PROMPT,
            timeout_seconds=25 * 60,
            terminate_grace_seconds=10,
            max_backoff_seconds=300,
            max_runs=None,
        )

    def test_main_ignores_invalid_max_runs_env(self):
        env = {
            "AGENTIC_PROMPT": "x",
            "AGENTIC_TIMEOUT_SECONDS": "1",
            "AGENTIC_TERMINATE_GRACE_SECONDS": "2",
            "AGENTIC_MAX_BACKOFF_SECONDS": "3",
            "AGENTIC_MAX_RUNS": "0",
        }
        with patch.dict(os.environ, env, clear=True):
            with patch("agentic_loop.log") as mock_log:
                with patch("agentic_loop.run_agentic_loop") as mock_run:
                    agentic_loop.main()

        mock_log.assert_called_once()
        mock_run.assert_called_once_with(
            prompt="x",
            timeout_seconds=1,
            terminate_grace_seconds=2,
            max_backoff_seconds=3,
            max_runs=None,
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
                        max_runs=None,
                    )

        mock_stop.assert_called_once_with(fake_proc, 2)
        mock_sleep.assert_called_once_with(2)

    def test_run_agentic_loop_stops_at_max_runs_after_success(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=0,
            wait=Mock(return_value=None),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc) as mock_popen:
            with patch("agentic_loop._sleep_interruptible") as mock_sleep:
                agentic_loop.run_agentic_loop(
                    prompt="x",
                    timeout_seconds=1,
                    terminate_grace_seconds=2,
                    max_backoff_seconds=300,
                    max_runs=1,
                )

        mock_popen.assert_called_once()
        mock_sleep.assert_not_called()

    def test_run_agentic_loop_stops_at_max_runs_after_nonzero_exit_without_sleep(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=1,
            wait=Mock(return_value=None),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc) as mock_popen:
            with patch("agentic_loop._sleep_interruptible") as mock_sleep:
                agentic_loop.run_agentic_loop(
                    prompt="x",
                    timeout_seconds=1,
                    terminate_grace_seconds=2,
                    max_backoff_seconds=300,
                    max_runs=1,
                )

        mock_popen.assert_called_once()
        mock_sleep.assert_not_called()

    def test_run_agentic_loop_returns_nonzero_exit_code_on_final_failure(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=3,
            wait=Mock(return_value=None),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc):
            rc = agentic_loop.run_agentic_loop(
                prompt="x",
                timeout_seconds=1,
                terminate_grace_seconds=2,
                max_backoff_seconds=300,
                max_runs=1,
            )

        self.assertEqual(rc, 3)

    def test_run_agentic_loop_maps_signal_termination_to_shell_exit_code(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=-9,
            wait=Mock(return_value=None),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc):
            rc = agentic_loop.run_agentic_loop(
                prompt="x",
                timeout_seconds=1,
                terminate_grace_seconds=2,
                max_backoff_seconds=300,
                max_runs=1,
            )

        self.assertEqual(rc, 137)

    def test_run_agentic_loop_stops_immediately_on_exit_code_130(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=130,
            wait=Mock(return_value=None),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc) as mock_popen:
            with patch("agentic_loop._sleep_interruptible") as mock_sleep:
                rc = agentic_loop.run_agentic_loop(
                    prompt="x",
                    timeout_seconds=1,
                    terminate_grace_seconds=2,
                    max_backoff_seconds=300,
                    max_runs=None,
                )

        self.assertEqual(rc, 130)
        mock_popen.assert_called_once()
        mock_sleep.assert_not_called()

    def test_run_agentic_loop_stops_immediately_on_sigint_return_code(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=-agentic_loop.signal.SIGINT,
            wait=Mock(return_value=None),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc) as mock_popen:
            with patch("agentic_loop._sleep_interruptible") as mock_sleep:
                rc = agentic_loop.run_agentic_loop(
                    prompt="x",
                    timeout_seconds=1,
                    terminate_grace_seconds=2,
                    max_backoff_seconds=300,
                    max_runs=None,
                )

        self.assertEqual(rc, 130)
        mock_popen.assert_called_once()
        mock_sleep.assert_not_called()

    def test_run_agentic_loop_returns_124_when_timeout_reaches_max_runs(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=0,
            wait=Mock(side_effect=subprocess.TimeoutExpired(cmd="codex", timeout=1)),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc):
            with patch("agentic_loop._stop_process_tree"):
                rc = agentic_loop.run_agentic_loop(
                    prompt="x",
                    timeout_seconds=1,
                    terminate_grace_seconds=2,
                    max_backoff_seconds=300,
                    max_runs=1,
                )

        self.assertEqual(rc, 124)

    def test_run_agentic_loop_returns_127_on_missing_codex_binary(self):
        launch_error = OSError(errno.ENOENT, "No such file or directory")
        with patch("agentic_loop.subprocess.Popen", side_effect=launch_error):
            rc = agentic_loop.run_agentic_loop(
                prompt="x",
                timeout_seconds=1,
                terminate_grace_seconds=2,
                max_backoff_seconds=300,
                max_runs=1,
            )

        self.assertEqual(rc, 127)

    def test_run_agentic_loop_stops_at_max_runs_after_timeout_without_sleep(self):
        fake_proc = SimpleNamespace(
            pid=123,
            returncode=0,
            wait=Mock(side_effect=subprocess.TimeoutExpired(cmd="codex", timeout=1)),
            poll=Mock(return_value=None),
        )

        with patch("agentic_loop.subprocess.Popen", return_value=fake_proc) as mock_popen:
            with patch("agentic_loop._stop_process_tree") as mock_stop:
                with patch("agentic_loop._sleep_interruptible") as mock_sleep:
                    agentic_loop.run_agentic_loop(
                        prompt="x",
                        timeout_seconds=1,
                        terminate_grace_seconds=2,
                        max_backoff_seconds=300,
                        max_runs=1,
                    )

        mock_popen.assert_called_once()
        mock_stop.assert_called_once_with(fake_proc, 2)
        mock_sleep.assert_not_called()

    def test_stop_process_tree_uses_kill_signal_constant_after_timeout(self):
        fake_proc = SimpleNamespace(
            wait=Mock(side_effect=[subprocess.TimeoutExpired(cmd="codex", timeout=1), None]),
            poll=Mock(return_value=None),
        )
        with patch("agentic_loop._signal_process_tree") as mock_signal:
            with patch.object(agentic_loop, "KILL_SIGNAL", 12345):
                agentic_loop._stop_process_tree(fake_proc, grace_seconds=1)

        mock_signal.assert_any_call(fake_proc, agentic_loop.signal.SIGTERM)
        mock_signal.assert_any_call(fake_proc, 12345)

    def test_stop_process_tree_logs_and_returns_when_forced_kill_does_not_exit(self):
        fake_proc = SimpleNamespace(
            wait=Mock(
                side_effect=[
                    subprocess.TimeoutExpired(cmd="codex", timeout=1),
                    subprocess.TimeoutExpired(cmd="codex", timeout=agentic_loop.KILL_WAIT_SECONDS),
                ]
            ),
            poll=Mock(return_value=None),
        )
        with patch("agentic_loop._signal_process_tree") as mock_signal:
            with patch("agentic_loop.log") as mock_log:
                agentic_loop._stop_process_tree(fake_proc, grace_seconds=1)

        self.assertEqual(fake_proc.wait.call_count, 2)
        mock_signal.assert_any_call(fake_proc, agentic_loop.signal.SIGTERM)
        mock_signal.assert_any_call(fake_proc, agentic_loop.KILL_SIGNAL)
        mock_log.assert_called_once()

    def test_signal_process_tree_falls_back_to_direct_signal_when_killpg_fails(self):
        fake_proc = SimpleNamespace(
            pid=123,
            poll=Mock(return_value=None),
            send_signal=Mock(),
        )

        with patch("agentic_loop.os.name", "posix"):
            with patch("agentic_loop.os.killpg", side_effect=OSError("no pg")):
                agentic_loop._signal_process_tree(fake_proc, agentic_loop.signal.SIGTERM)

        fake_proc.send_signal.assert_called_once_with(agentic_loop.signal.SIGTERM)

    def test_signal_process_tree_returns_when_process_already_exited(self):
        fake_proc = SimpleNamespace(
            pid=123,
            poll=Mock(return_value=0),
            send_signal=Mock(),
        )

        with patch("agentic_loop.os.killpg") as mock_killpg:
            agentic_loop._signal_process_tree(fake_proc, agentic_loop.signal.SIGTERM)

        mock_killpg.assert_not_called()
        fake_proc.send_signal.assert_not_called()

    def test_normalize_process_return_code_maps_none_or_zero_to_one(self):
        self.assertEqual(agentic_loop._normalize_process_return_code(None), 1)
        self.assertEqual(agentic_loop._normalize_process_return_code(0), 1)

    def test_normalize_process_return_code_keeps_positive_and_maps_negative(self):
        self.assertEqual(agentic_loop._normalize_process_return_code(7), 7)
        self.assertEqual(agentic_loop._normalize_process_return_code(-15), 143)

    def test_is_interrupt_return_code(self):
        self.assertTrue(agentic_loop._is_interrupt_return_code(130))
        self.assertTrue(agentic_loop._is_interrupt_return_code(-agentic_loop.signal.SIGINT))
        self.assertFalse(agentic_loop._is_interrupt_return_code(1))
        self.assertFalse(agentic_loop._is_interrupt_return_code(None))


if __name__ == "__main__":
    unittest.main()
