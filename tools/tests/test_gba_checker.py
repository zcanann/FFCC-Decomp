import contextlib
import io
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

# check.py also supports direct execution and imports its sibling preprocessor.
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "gba/tools"))
try:
    from gba.tools import check
finally:
    sys.path.pop(0)


class GbaCheckerTests(unittest.TestCase):
    def test_compile_uses_selected_region_and_preserves_tool_options(self):
        for version in check.VERSIONS:
            for suffix, language, compiler in ((".c", "c", "cc1"), (".cpp", "c++", "cc1plus")):
                with self.subTest(version=version, language=language):
                    with patch.object(check, "preprocess") as preprocess, patch.object(
                        check.subprocess, "run", return_value=subprocess.CompletedProcess([], 0, "", "")
                    ) as run:
                        obj = check.compile_c(Path("sample" + suffix), Path("output"), "mgr",
                                              Path("custom-compilers"), version=version)
                    self.assertEqual(obj, Path("output/a.o"))
                    self.assertEqual(preprocess.call_args.kwargs["defines"], (f"VERSION_{version}",))
                    self.assertEqual(preprocess.call_args.kwargs["language"], language)
                    self.assertEqual(preprocess.call_args.args[0], Path("custom-compilers") / ("gcc2-cpp" + check.EXE))
                    command = run.call_args_list[0].args[0]
                    self.assertEqual(command[0], str(Path("custom-compilers") / (compiler + check.EXE)))
                    self.assertIn("-mthumb-interwork", command)
                    self.assertIn("-O2", command)
                    self.assertIn("-fno-exceptions" if suffix == ".cpp" else "-fno-common", command)
                    self.assertEqual(run.call_args_list[1].args[0][0], check.binutil("as"))

    def test_existing_compile_api_defaults_to_pal(self):
        with patch.object(check, "preprocess") as preprocess, patch.object(
            check.subprocess, "run", return_value=subprocess.CompletedProcess([], 0, "", "")
        ):
            check.compile_c(Path("sample.c"), Path("output"), "cli")
        self.assertEqual(preprocess.call_args.kwargs["defines"], ("VERSION_GCCP01",))
        with patch.object(check, "preprocess") as preprocess:
            with self.assertRaises(ValueError):
                check.compile_c(Path("sample.c"), Path("output"), "cli", version="unknown")
            preprocess.assert_not_called()

    def test_cli_region_routes_both_target_and_compilation(self):
        for requested in (None, *check.VERSIONS):
            for aggregate in (False, True):
                version = requested or "GCCP01"
                with self.subTest(version=requested, aggregate=aggregate), tempfile.TemporaryDirectory() as tmp:
                    root = Path(tmp).resolve()
                    source = root / "gba/src/cli/main/sample.c"
                    source.parent.mkdir(parents=True)
                    source.write_text("void Entry(void) {}\n")
                    target = root / "build" / version / "gba/cli/obj" / ("main.o" if aggregate else "main/sample.o")
                    target.parent.mkdir(parents=True)
                    target.touch()
                    argv = ["check.py", str(source), "Entry", "--gba-compilers", "custom-compilers"]
                    if requested:
                        argv += ["--version", requested]

                    def run(command, **kwargs):
                        if "diff" in command:
                            self.assertEqual(Path(command[command.index("-1") + 1]), target)
                            data = {"left": {"symbols": [{"name": "Entry", "match_percent": 100.0}]},
                                    "right": {"symbols": [{"name": "Entry"}]}}
                            return subprocess.CompletedProcess(command, 0, json.dumps(data), "")
                        self.assertIn("-h", command)
                        self.assertEqual(Path(command[-1]), target)
                        return subprocess.CompletedProcess(command, 0, "", "")

                    with patch.object(check, "ROOT", root), patch.object(sys, "argv", argv), patch.object(
                        check, "compile_c", return_value=root / "compiled.o"
                    ) as compile_c, patch.object(check.subprocess, "run", side_effect=run), contextlib.redirect_stdout(io.StringIO()):
                        check.main()
                    self.assertEqual(compile_c.call_args.kwargs, {"version": version})
                    self.assertEqual(compile_c.call_args.args[3], Path("custom-compilers"))

    def test_missing_region_never_falls_back_to_pal(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp).resolve()
            source = root / "gba/src/cli/main/sample.c"
            source.parent.mkdir(parents=True)
            source.touch()
            pal = root / "build/GCCP01/gba/cli/obj/main/sample.o"
            pal.parent.mkdir(parents=True)
            pal.touch()
            with patch.object(check, "ROOT", root), patch.object(sys, "argv", [
                "check.py", "--version", "GCCE01", str(source)
            ]), patch.object(check, "compile_c") as compile_c:
                with self.assertRaisesRegex(SystemExit, "build GCCE01 first"):
                    check.main()
                compile_c.assert_not_called()


if __name__ == "__main__":
    unittest.main()
