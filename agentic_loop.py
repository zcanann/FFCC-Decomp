import subprocess

CMD = 'codex exec --yolo "Follow the instructions in AGENTS.MD. NEVER ask the user for input. Simply follow the instructions and make a PR if there is an improvement."'
TIMEOUT_SECONDS = 25 * 60

while True:
    proc = subprocess.Popen(CMD, shell=True)
    try:
        proc.wait(timeout=TIMEOUT_SECONDS)
    except subprocess.TimeoutExpired:
        subprocess.run(
            f"taskkill /F /T /PID {proc.pid}",
            shell=True,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            check=False,
        )
