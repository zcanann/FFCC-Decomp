import subprocess

PROMPT = (
    "Follow the instructions in AGENTS.MD. NEVER ask the user for input. "
    "Simply follow the instructions and make a PR if there is an improvement. "
    "Pay careful attention to any important rules."
)
CMD = ["codex", "exec", "--yolo", PROMPT]
TIMEOUT_SECONDS = 25 * 60
TERMINATE_GRACE_SECONDS = 10


while True:
    proc = subprocess.Popen(CMD)
    try:
        proc.wait(timeout=TIMEOUT_SECONDS)
    except subprocess.TimeoutExpired:
        proc.terminate()
        try:
            proc.wait(timeout=TERMINATE_GRACE_SECONDS)
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait()
    except KeyboardInterrupt:
        proc.terminate()
        try:
            proc.wait(timeout=TERMINATE_GRACE_SECONDS)
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait()
        break
