import os
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import agentic_loop


class ResolveAgentsFilenameTests(unittest.TestCase):
    def test_prefers_exact_filename_in_cwd(self) -> None:
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp_path = Path(tmp_dir)
            (tmp_path / "AGENTS.md").write_text("", encoding="utf-8")

            with patch("agentic_loop.Path.cwd", return_value=tmp_path):
                self.assertEqual(agentic_loop._resolve_agents_filename(), "AGENTS.md")

    def test_finds_file_in_parent_directory(self) -> None:
        with tempfile.TemporaryDirectory() as tmp_dir:
            root = Path(tmp_dir)
            nested = root / "a" / "b"
            nested.mkdir(parents=True)
            (root / "AGENTS.MD").write_text("", encoding="utf-8")

            with patch("agentic_loop.Path.cwd", return_value=nested):
                self.assertEqual(agentic_loop._resolve_agents_filename(), os.path.join("..", "..", "AGENTS.MD"))

    def test_falls_back_to_case_insensitive_match(self) -> None:
        with tempfile.TemporaryDirectory() as tmp_dir:
            tmp_path = Path(tmp_dir)
            (tmp_path / "Agents.md").write_text("", encoding="utf-8")

            with patch("agentic_loop.Path.cwd", return_value=tmp_path):
                self.assertEqual(agentic_loop._resolve_agents_filename(), "Agents.md")


if __name__ == "__main__":
    unittest.main()
