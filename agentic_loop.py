import subprocess  # nosec
import time

CMD = ["codex", "exec", "--yolo", "Follow the instructions in AGENTS.MD. NEVER ask the user for input. Simply follow the instructions and make a PR if there is an improvement. Relentlessly push for real improvements, not just tiny patches. Checkpointing with multiple commits before a PR is encouraged. Pay careful attention to any important rules."]
TIMEOUT_SECONDS = 25 * 60
CYCLE_DELAY = 10

while True:
    proc = subprocess.Popen(CMD)  # nosec
    try:
        proc.wait(timeout=TIMEOUT_SECONDS)
    except subprocess.TimeoutExpired:
        subprocess.run(
            ["taskkill", "/F", "/T", "/PID", str(proc.pid)],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            check=False,
        )
    time.sleep(CYCLE_DELAY)
