"""Run objdiff with symbol deduplication scoped to each linked image.

GameCube and GBA programs may define the same global names independently.
Objdiff 3.6.1 deduplicates names across its entire input project, so give it
one image at a time, preserve its unit results, and combine their measures.
"""

import argparse
import copy
import json
from pathlib import Path
import struct
import subprocess
import tempfile


BYTE_FIELDS = (
    "total_code", "matched_code", "total_data", "matched_data",
    "complete_code", "complete_data",
)
COUNT_FIELDS = ("total_functions", "matched_functions", "total_units", "complete_units")


def f32(value):
    return struct.unpack("f", struct.pack("f", value))[0]


def aggregate(measures):
    """Follow objdiff's Measures addition, including its f32 arithmetic."""
    totals = dict.fromkeys(BYTE_FIELDS + COUNT_FIELDS, 0)
    weighted = 0.0
    for item in measures:
        for key in totals:
            totals[key] += int(item.get(key, 0))
        weighted = f32(weighted + f32(f32(item.get("fuzzy_match_percent", 0))
                                      * f32(int(item.get("total_code", 0)))))
    result = {key: str(value) if key in BYTE_FIELDS else value
              for key, value in totals.items()}
    result["fuzzy_match_percent"] = (f32(weighted / f32(totals["total_code"]))
                                       if totals["total_code"] else 100.0)
    for numerator, denominator in (
        ("matched_code", "total_code"), ("matched_data", "total_data"),
        ("matched_functions", "total_functions"),
        ("complete_code", "total_code"), ("complete_data", "total_data"),
    ):
        result[numerator + "_percent"] = (
            f32(f32(f32(totals[numerator]) / f32(totals[denominator])) * 100.0)
            if totals[denominator] else 100.0
        )
    return result


def image_name(unit):
    parts = unit["name"].split("/")
    # GC units are <DOL-or-REL>/<unit>; GBA units are gba/<program>/<unit>.
    if len(parts) < 2 or (parts[0] == "gba" and len(parts) < 3):
        raise ValueError("Unit has no linked-image prefix: " + unit["name"])
    return "/".join(parts[:2] if parts[0] == "gba" else parts[:1])


def image_projects(project, root):
    project = copy.deepcopy(project)
    # The temporary project directories must resolve exactly the same objects.
    for key in ("target_dir", "base_dir"):
        if project.get(key) is not None:
            project[key] = str((root / project[key]).resolve())
    groups = {}
    for unit in project.get("units", []):
        for key in ("target_path", "base_path"):
            if unit.get(key) is not None:
                unit[key] = str((root / unit[key]).resolve())
        groups.setdefault(image_name(unit), []).append(unit)
    return [{**project, "units": units} for units in groups.values()]


def combine(project, reports):
    if not reports or any(report.get("version") != 2 for report in reports):
        raise ValueError("Expected objdiff version 2 reports")
    units = [unit for report in reports for unit in report["units"]]
    order = {unit["name"]: i for i, unit in enumerate(project["units"])}
    names = [unit["name"] for unit in units]
    if (len(order) != len(project["units"]) or len(set(names)) != len(names)
            or set(names) != order.keys()):
        raise ValueError("Missing, duplicate, or unexpected report units")
    units.sort(key=lambda unit: order[unit["name"]])
    categories = []
    for category in project.get("progress_categories", []):
        category_units = [unit for unit in units if category["id"] in
                          unit.get("metadata", {}).get("progress_categories", [])]
        if category_units:
            categories.append({**category, "measures": aggregate(
                unit["measures"] for unit in category_units)})
    return {"version": 2, "units": units, "categories": categories,
            "measures": aggregate(unit["measures"] for unit in units)}


def generate(objdiff, project_dir, output, args):
    root = project_dir.resolve()
    project = json.loads((root / "objdiff.json").read_text(encoding="utf-8"))
    executable = str(objdiff.resolve())
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="report-", dir=output.parent) as temporary:
        reports = []
        for index, image in enumerate(image_projects(project, root)):
            directory = Path(temporary) / str(index)
            directory.mkdir()
            (directory / "objdiff.json").write_text(json.dumps(image), encoding="utf-8")
            report_path = directory / "report.json"
            subprocess.run([executable, "report", "generate", *args,
                            "-p", str(directory), "-o", str(report_path)], check=True)
            reports.append(json.loads(report_path.read_text(encoding="utf-8")))
        result = combine(project, reports)
        pending = Path(temporary) / "combined.json"
        pending.write_text(json.dumps(result, separators=(",", ":")), encoding="utf-8")
        pending.replace(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--objdiff", type=Path, required=True)
    parser.add_argument("--project", type=Path, default=Path("."))
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("args", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    forwarded = args.args[1:] if args.args[:1] == ["--"] else args.args
    generate(args.objdiff, args.project, args.output, forwarded)


if __name__ == "__main__":
    main()
