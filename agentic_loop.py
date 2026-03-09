import os
import signal
import subprocess
import time
from datetime import datetime

PROMPT = os.getenv(
    "AGENTIC_PROMPT",
    (
        "Follow the instructions in AGENTS.MD. NEVER ask the user for input. "
        "Simply follow the instructions and make a PR if there is an improvement. "
        "Pay careful attention to any important rules."
    ),
)
TIMEOUT_SECONDS = int(os.getenv("AGENTIC_TIMEOUT_SECONDS", str(25 * 60)))
TERMINATE_GRACE_SECONDS = int(os.getenv("AGENTIC_TERMINATE_GRACE_SECONDS", "10"))
MAX_BACKOFF_SECONDS = int(os.getenv("AGENTIC_MAX_BACKOFF_SECONDS", "300"))
CMD = ["codex", "exec", "--yolo", PROMPT]


def log(message: str) -> None:
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f"[{timestamp}] {message}", flush=True)


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


consecutive_failures = 0
while True:
    log("starting codex run")
    try:
        proc = subprocess.Popen(
            CMD,
            start_new_session=(os.name == "posix"),
        )
    except OSError as exc:
        consecutive_failures += 1
        backoff = min(2 ** min(consecutive_failures, 8), MAX_BACKOFF_SECONDS)
        log(f"failed to launch codex ({exc}); sleeping {backoff}s before retry")
        time.sleep(backoff)
        continue

    try:
        proc.wait(timeout=TIMEOUT_SECONDS)
        if proc.returncode == 0:
            consecutive_failures = 0
            log("codex run completed successfully")
        else:
            consecutive_failures += 1
            backoff = min(2 ** min(consecutive_failures, 8), MAX_BACKOFF_SECONDS)
            log(
                f"codex exited with code {proc.returncode}; "
                f"sleeping {backoff}s before retry"
            )
            time.sleep(backoff)
    except subprocess.TimeoutExpired:
        log(f"codex exceeded timeout ({TIMEOUT_SECONDS}s); terminating process")
        _stop_process_tree(proc, TERMINATE_GRACE_SECONDS)
        log("codex process stopped after timeout")
        consecutive_failures = 0
    except KeyboardInterrupt:
        log("keyboard interrupt received; stopping loop")
        _stop_process_tree(proc, TERMINATE_GRACE_SECONDS)
        break
