import unittest

from tools import agent_select_target


class DeriveFileNameTests(unittest.TestCase):
    def test_derive_object_file_uses_source_path_stem(self):
        unit = {"name": "foo", "metadata": {"source_path": "src/system/player.cpp"}}
        self.assertEqual(agent_select_target.derive_object_file(unit), "player.o")

    def test_derive_object_file_fallback_drops_known_extension(self):
        unit = {"name": "src/system/player.cpp", "metadata": {"source_path": "unknown"}}
        self.assertEqual(agent_select_target.derive_object_file(unit), "player.o")

    def test_derive_source_file_uses_source_path_name(self):
        unit = {"name": "foo", "metadata": {"source_path": "src/system/player.cpp"}}
        self.assertEqual(agent_select_target.derive_source_file(unit), "player.cpp")

    def test_derive_source_file_fallback_drops_known_extension(self):
        unit = {"name": "src/system/player.cpp", "metadata": {"source_path": "unknown"}}
        self.assertEqual(agent_select_target.derive_source_file(unit), "player.cpp")


if __name__ == "__main__":
    unittest.main()
