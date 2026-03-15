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


if __name__ == "__main__":
    unittest.main()
