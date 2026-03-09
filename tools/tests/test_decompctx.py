import unittest

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


if __name__ == "__main__":
    unittest.main()
