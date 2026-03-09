import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import transform_dep


class TransformDepTests(unittest.TestCase):
    def _write_dep(self, text: str) -> str:
        tmp = tempfile.NamedTemporaryFile("w", delete=False, suffix=".d", encoding="utf-8")
        tmp.write(text)
        tmp.close()
        return tmp.name

    def test_import_d_file_handles_blank_dependency_line(self):
        dep_path = self._write_dep("build/file.o: \\\n \\\n")
        output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n \\\n")

    def test_import_d_file_keeps_relative_paths_without_crashing(self):
        dep_path = self._write_dep("build/file.o: \\\n\tinclude\\header.h\n")
        output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n\tinclude/header.h\n")

    def test_import_d_file_maps_windows_drive_in_wsl_mode(self):
        dep_path = self._write_dep("build/file.o: \\\n\tC:\\proj\\src\\file.h\n")
        with patch("tools.transform_dep.in_wsl", return_value=True):
            output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n\t/mnt/c/proj/src/file.h\n")

    def test_import_d_file_keeps_drive_relative_paths(self):
        dep_path = self._write_dep("build/file.o: \\\n\tC:proj\\src\\file.h\n")
        with patch("tools.transform_dep.in_wsl", return_value=True):
            output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n\tC:proj/src/file.h\n")

    def test_import_d_file_handles_crlf_continuation_lines(self):
        dep_path = self._write_dep("build\\file.o: \\\r\n\tinclude\\header.h \\\r\n\tmore\\dep.h\r\n")
        output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n\tinclude/header.h \\\n\tmore/dep.h\n")

    def test_import_d_file_handles_crlf_blank_dependency_line(self):
        dep_path = self._write_dep("build/file.o: \\\r\n \\\r\n")
        output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n \\\n")

    def test_import_d_file_preserves_escaped_spaces(self):
        dep_path = self._write_dep("build/file.o: \\\n\tinclude\\my\\ file.h\n")
        output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n\tinclude/my\\ file.h\n")

    def test_import_d_file_preserves_make_escapes_in_windows_path(self):
        dep_path = self._write_dep("build/file.o: \\\n\tC:\\my\\ path\\include\\header.h\n")
        with patch("tools.transform_dep.in_wsl", return_value=True):
            output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n\t/mnt/c/my\\ path/include/header.h\n")

    def test_import_d_file_normalizes_first_line_inline_windows_dependency(self):
        dep_path = self._write_dep("build/file.o: C:\\proj\\include\\a.h \\\n\tC:\\proj\\include\\b.h\n")
        with patch("tools.transform_dep.in_wsl", return_value=True):
            output = transform_dep.import_d_file(dep_path)
        self.assertEqual(
            output,
            "build/file.o: /mnt/c/proj/include/a.h \\\n\t/mnt/c/proj/include/b.h\n",
        )

    def test_import_d_file_normalizes_multiple_dependencies_on_single_line(self):
        dep_path = self._write_dep("build/file.o: \\\n\tC:\\proj\\a.h C:\\proj\\b.h\n")
        with patch("tools.transform_dep.in_wsl", return_value=True):
            output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o: \\\n\t/mnt/c/proj/a.h /mnt/c/proj/b.h\n")

    def test_import_d_file_normalizes_first_line_with_tab_separator(self):
        dep_path = self._write_dep("build/file.o:\tC:\\proj\\a.h \\\n\tC:\\proj\\b.h\n")
        with patch("tools.transform_dep.in_wsl", return_value=True):
            output = transform_dep.import_d_file(dep_path)
        self.assertEqual(
            output,
            "build/file.o: /mnt/c/proj/a.h \\\n\t/mnt/c/proj/b.h\n",
        )

    def test_import_d_file_preserves_target_only_rule_without_extra_space(self):
        dep_path = self._write_dep("build\\file.o:\n")
        output = transform_dep.import_d_file(dep_path)
        self.assertEqual(output, "build/file.o:\n")

    def test_in_wsl_detects_generic_microsoft_kernel_tag(self):
        with patch("tools.transform_dep.uname") as mocked_uname:
            mocked_uname.return_value.release = "5.15.167.4-microsoft"
            self.assertTrue(transform_dep.in_wsl())

    def test_in_wsl_detects_wsl_env_override(self):
        with patch("tools.transform_dep.uname") as mocked_uname:
            mocked_uname.return_value.release = "6.8.0-31-generic"
            with patch.dict("os.environ", {"WSL_DISTRO_NAME": "Ubuntu"}, clear=False):
                self.assertTrue(transform_dep.in_wsl())

    def test_in_wsl_false_on_non_wsl_host(self):
        with patch("tools.transform_dep.uname") as mocked_uname:
            mocked_uname.return_value.release = "6.8.0-31-generic"
            with patch.dict("os.environ", {}, clear=True):
                self.assertFalse(transform_dep.in_wsl())

    def test_winedevices_path_uses_wineprefix_when_set(self):
        with patch.dict("os.environ", {"WINEPREFIX": "/tmp/wine"}, clear=True):
            self.assertEqual(transform_dep._winedevices_path(), "/tmp/wine/dosdevices")

    def test_winedevices_path_falls_back_without_home_env(self):
        with patch.dict("os.environ", {}, clear=True):
            with patch("tools.transform_dep.os.path.expanduser", return_value="/users/test"):
                self.assertEqual(
                    transform_dep._winedevices_path(),
                    "/users/test/.wine/dosdevices",
                )


if __name__ == "__main__":
    unittest.main()
