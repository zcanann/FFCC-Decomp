import argparse
import shlex
import subprocess
import time

TIMEOUT_SECONDS = 25 * 60
CYCLE_DELAY = 10
BASE_PROMPT = (
    "Follow the instructions in AGENTS.MD. NEVER ask the user for input. "
    "Simply follow the instructions and make a PR if there is an improvement. "
    "Relentlessly push for real improvements, not just tiny patches. "
    "Checkpointing with multiple commits before a PR is encouraged. "
    "Pay careful attention to any important rules."
)


def parse_args():
    parser = argparse.ArgumentParser(
        description="Continuously run Codex agents against FFCC-Decomp targets.",
    )
    parser.add_argument(
        "bucket_arg",
        nargs="?",
        help="optional WORK_SPLIT bucket shorthand, e.g. B3",
    )
    parser.add_argument(
        "--bucket",
        dest="bucket_opt",
        help="optional WORK_SPLIT bucket, e.g. B3",
    )
    parser.add_argument(
        "--bucket-file",
        default="WORK_SPLIT.md",
        help="bucket definition markdown file passed to agent_select_target.py",
    )
    return parser.parse_args()


def build_prompt(bucket, bucket_file):
    if not bucket:
        return BASE_PROMPT

    selector_cmd = (
        f"python3 tools/agent_select_target.py --bucket {shlex.quote(bucket)} "
        f"--bucket-file {shlex.quote(bucket_file)}"
    )
    return (
        f"{BASE_PROMPT} Restrict target selection to WORK_SPLIT bucket {bucket}. "
        f"When selecting a target, run `{selector_cmd}`. "
        "The bucket is only a narrowing filter; still respect recent-failure and "
        "permanent blacklists."
    )


def main():
    args = parse_args()
    bucket = args.bucket_opt or args.bucket_arg
    prompt = build_prompt(bucket, args.bucket_file)
    cmd = ["codex", "exec", "--yolo", prompt]

    while True:
        proc = subprocess.Popen(cmd)
        try:
            proc.wait(timeout=TIMEOUT_SECONDS)
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait()
        time.sleep(CYCLE_DELAY)


if __name__ == "__main__":
    main()
