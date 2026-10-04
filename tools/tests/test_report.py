import unittest
from pathlib import Path

from tools.report import aggregate, combine, image_projects


class ImageReportTests(unittest.TestCase):
    def test_images_keep_duplicate_names_in_separate_objdiff_inputs(self):
        units = [
            {"name": "main/a", "target_path": "obj/a.o"},
            {"name": "gba/cli/a", "target_path": "obj/cli.o"},
            {"name": "main/b", "base_path": "src/b.o"},
            {"name": "gba/mgr/a", "target_path": "obj/mgr.o"},
        ]
        project = {"units": units, "options": {"functionRelocDiffs": "none"}}
        root = Path("project").resolve()
        groups = image_projects(project, root)
        self.assertEqual([[u["name"] for u in g["units"]] for g in groups],
                         [["main/a", "main/b"], ["gba/cli/a"], ["gba/mgr/a"]])
        self.assertEqual(groups[0]["units"][0]["target_path"], str(root / "obj/a.o"))
        self.assertEqual(groups[0]["units"][1]["base_path"], str(root / "src/b.o"))
        self.assertEqual(project["units"][0]["target_path"], "obj/a.o")
        self.assertEqual(groups[1]["options"], project["options"])

    def test_combine_preserves_units_and_counts_each_image(self):
        units = []
        reports = []
        for name, size, complete in (("main/memcpy", 80, True),
                                     ("gba/cli/memcpy", 96, False),
                                     ("gba/mgr/memcpy", 96, False)):
            category = name.rsplit("/", 1)[0]
            unit = {"name": name, "metadata": {"complete": complete,
                    "progress_categories": [category, "all_images"]},
                    "functions": [{"name": "memcpy", "size": str(size)}],
                    "measures": aggregate([{"total_code": str(size),
                        "matched_code": str(size), "total_functions": 1,
                        "matched_functions": 1, "total_units": 1,
                        "complete_code": str(size if complete else 0),
                        "complete_units": int(complete), "fuzzy_match_percent": 100}])}
            units.append(unit)
            reports.append({"version": 2, "units": [unit]})
        project = {"units": units, "progress_categories": [
            {"id": name, "name": name} for name in ("main", "gba/cli", "gba/mgr", "all_images")]}
        result = combine(project, list(reversed(reports)))
        self.assertEqual(result["units"], units)
        self.assertEqual(result["measures"]["total_code"], "272")
        self.assertEqual(result["measures"]["complete_code"], "80")
        self.assertEqual(result["measures"]["complete_units"], 1)
        self.assertEqual(result["categories"][-1]["measures"], result["measures"])
        self.assertEqual(result["categories"][1]["measures"]["complete_code_percent"], 0)

    def test_duplicate_units_and_unknown_report_versions_are_rejected(self):
        project = {"units": [{"name": "main/a"}]}
        report = {"version": 2, "units": [{"name": "main/a", "measures": {}}]}
        with self.assertRaises(ValueError):
            combine(project, [report, report])
        with self.assertRaises(ValueError):
            combine(project, [{**report, "version": 3}])

    def test_weighted_match_and_zero_sized_units(self):
        result = aggregate([{"total_code": "4", "fuzzy_match_percent": 25},
                            {"total_code": "12", "fuzzy_match_percent": 75}])
        self.assertEqual(result["fuzzy_match_percent"], 62.5)
        self.assertEqual(aggregate([])["complete_code_percent"], 100)
        self.assertEqual(aggregate([])["complete_code"], "0")

    def test_missing_units_cannot_silently_reduce_the_denominator(self):
        project = {"units": [{"name": "main/a"}, {"name": "main/b"}]}
        report = {"version": 2, "units": [{"name": "main/a", "measures": {}}]}
        with self.assertRaises(ValueError):
            combine(project, [report])


if __name__ == "__main__":
    unittest.main()
