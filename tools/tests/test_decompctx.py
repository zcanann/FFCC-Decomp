import unittest
import tempfile
from pathlib import Path

from tools import decompctx


class HeaderGuardKeyTests(unittest.TestCase):
    def test_detects_ifndef_on_first_line(self):
        lines = [
            "#ifndef EXAMPLE_H\n",
            "#define EXAMPLE_H\n",
        ]
        self.assertEqual(decompctx.get_header_guard_key("include/example.h", lines), "EXAMPLE_H")

    def test_detects_ifndef_after_banner_comments(self):
        lines = [
            "/*\n",
            " * Copyright header\n",
            " */\n",
            "\n",
            "#ifndef EXAMPLE_H\n",
            "#define EXAMPLE_H\n",
        ]
        self.assertEqual(decompctx.get_header_guard_key("include/example.h", lines), "EXAMPLE_H")

    def test_detects_ifndef_after_single_line_banner_comment(self):
        lines = [
            "/* Copyright header */\n",
            "\n",
            "#ifndef EXAMPLE_H\n",
            "#define EXAMPLE_H\n",
        ]
        self.assertEqual(decompctx.get_header_guard_key("include/example.h", lines), "EXAMPLE_H")

    def test_detects_ifndef_ignoring_trailing_comment(self):
        lines = [
            "#ifndef EXAMPLE_H // guard\n",
            "#define EXAMPLE_H\n",
        ]
        self.assertEqual(decompctx.get_header_guard_key("include/example.h", lines), "EXAMPLE_H")

    def test_detects_if_not_defined_with_parentheses(self):
        lines = [
            "#if !defined(EXAMPLE_H)\n",
            "#define EXAMPLE_H\n",
        ]
        self.assertEqual(decompctx.get_header_guard_key("include/example.h", lines), "EXAMPLE_H")

    def test_detects_if_not_defined_without_parentheses(self):
        lines = [
            "#if !defined EXAMPLE_H\n",
            "#define EXAMPLE_H\n",
        ]
        self.assertEqual(decompctx.get_header_guard_key("include/example.h", lines), "EXAMPLE_H")

    def test_detects_pragma_once_after_comments(self):
        lines = [
            "// generated header\n",
            "\n",
            "#pragma once\n",
            "int x;\n",
        ]
        self.assertEqual(
            decompctx.get_header_guard_key("include/example.h", lines),
            "include/example.h",
        )

    def test_returns_none_without_guard(self):
        lines = [
            "int foo(void);\n",
            "#ifndef EXAMPLE_H\n",
        ]
        self.assertIsNone(decompctx.get_header_guard_key("include/example.h", lines))


class ImportBehaviorTests(unittest.TestCase):
    def setUp(self):
        decompctx.defines.clear()
        decompctx.deps.clear()
        decompctx.active_imports.clear()

    def test_import_c_file_skips_recursive_include_cycle(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            root = Path(tmpdir)
            (root / "a.h").write_text('#include "b.h"\n', encoding="utf-8")
            (root / "b.h").write_text('#include "a.h"\n', encoding="utf-8")

            old_root = decompctx.root_dir
            old_include_dirs = decompctx.include_dirs
            try:
                decompctx.root_dir = str(root)
                decompctx.include_dirs = [str(root)]
                output = decompctx.import_c_file(str(root / "a.h"))
            finally:
                decompctx.root_dir = old_root
                decompctx.include_dirs = old_include_dirs

            self.assertIn("Skipped recursive include", output)
            self.assertEqual(decompctx.active_imports, set())


if __name__ == "__main__":
    unittest.main()
