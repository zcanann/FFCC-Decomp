import os
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


consecutive_failures = 0
while True:
    log("starting codex run")
    proc = subprocess.Popen(CMD)
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
        proc.terminate()
        try:
            proc.wait(timeout=TERMINATE_GRACE_SECONDS)
            log("codex process terminated after timeout")
        except subprocess.TimeoutExpired:
            log("codex process did not terminate gracefully; killing process")
            proc.kill()
            proc.wait()
        consecutive_failures = 0
    except KeyboardInterrupt:
        log("keyboard interrupt received; stopping loop")
        proc.terminate()
        try:
            proc.wait(timeout=TERMINATE_GRACE_SECONDS)
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait()
        break
