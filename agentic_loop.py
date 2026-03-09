import os
import signal
import subprocess
import time
from datetime import datetime
from typing import Optional

DEFAULT_PROMPT = (
    "Follow the instructions in AGENTS.md. NEVER ask the user for input. "
    "Simply follow the instructions and make a PR if there is an improvement. "
    "Pay careful attention to any important rules."
)


def log(message: str) -> None:
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f"[{timestamp}] {message}", flush=True)


def _read_int_env(var_name: str, default: int, minimum: Optional[int] = None) -> int:
    raw_value = os.getenv(var_name)
    if raw_value is None:
        return default

    try:
        value = int(raw_value)
    except ValueError:
        log(f"invalid integer for {var_name}={raw_value!r}; using default {default}")
        return default

    if minimum is not None and value < minimum:
        log(
            f"invalid integer for {var_name}={raw_value!r}; minimum is {minimum}; "
            f"using default {default}"
        )
        return default

    return value


def _signal_process_tree(proc: subprocess.Popen, sig: int) -> None:
    """Signal the full process tree when possible."""
    if proc.poll() is not None:
        return

    try:
        if os.name == "posix":
            os.killpg(proc.pid, sig)
        else:
            proc.send_signal(sig)
    except ProcessLookupError:
        pass


def _stop_process_tree(proc: subprocess.Popen, grace_seconds: int) -> None:
    _signal_process_tree(proc, signal.SIGTERM)
    try:
        proc.wait(timeout=grace_seconds)
    except subprocess.TimeoutExpired:
        _signal_process_tree(proc, signal.SIGKILL)
        proc.wait()


def _sleep_interruptible(seconds: int) -> bool:
    """Sleep and return False if interrupted by Ctrl+C."""
    try:
        time.sleep(seconds)
        return True
    except KeyboardInterrupt:
        log("keyboard interrupt received; stopping loop")
        return False


def run_agentic_loop(
    prompt: str,
    timeout_seconds: int,
    terminate_grace_seconds: int,
    max_backoff_seconds: int,
) -> None:
    cmd = ["codex", "exec", "--yolo", prompt]
    consecutive_failures = 0

    while True:
        log("starting codex run")
        try:
            proc = subprocess.Popen(
                cmd,
                start_new_session=(os.name == "posix"),
            )
        except OSError as exc:
            consecutive_failures += 1
            backoff = min(2 ** min(consecutive_failures, 8), max_backoff_seconds)
            log(f"failed to launch codex ({exc}); sleeping {backoff}s before retry")
            if not _sleep_interruptible(backoff):
                break
            continue

        try:
            proc.wait(timeout=timeout_seconds)
            if proc.returncode == 0:
                consecutive_failures = 0
                log("codex run completed successfully")
            else:
                consecutive_failures += 1
                backoff = min(2 ** min(consecutive_failures, 8), max_backoff_seconds)
                log(
                    f"codex exited with code {proc.returncode}; "
                    f"sleeping {backoff}s before retry"
                )
                if not _sleep_interruptible(backoff):
                    break
        except subprocess.TimeoutExpired:
            log(f"codex exceeded timeout ({timeout_seconds}s); terminating process")
            _stop_process_tree(proc, terminate_grace_seconds)
            log("codex process stopped after timeout")
            consecutive_failures = 0
        except KeyboardInterrupt:
            log("keyboard interrupt received; stopping loop")
            _stop_process_tree(proc, terminate_grace_seconds)
            break


def main() -> None:
    prompt = os.getenv("AGENTIC_PROMPT", DEFAULT_PROMPT)
    timeout_seconds = _read_int_env("AGENTIC_TIMEOUT_SECONDS", 25 * 60, minimum=1)
    terminate_grace_seconds = _read_int_env(
        "AGENTIC_TERMINATE_GRACE_SECONDS", 10, minimum=0
    )
    max_backoff_seconds = _read_int_env("AGENTIC_MAX_BACKOFF_SECONDS", 300, minimum=1)
    run_agentic_loop(
        prompt=prompt,
        timeout_seconds=timeout_seconds,
        terminate_grace_seconds=terminate_grace_seconds,
        max_backoff_seconds=max_backoff_seconds,
    )


if __name__ == "__main__":
    main()
