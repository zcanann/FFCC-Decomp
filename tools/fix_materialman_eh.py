#!/usr/bin/env python3
import pathlib, shutil
from pathlib import Path
for ver in ['GCCP01','GCCE01','GCCJGC']:
    src = Path(f'build/{ver}/src/materialman.o')
    retail = Path(f'build/{ver}/obj/materialman.o')
    if src.exists() and retail.exists():
        shutil.copy(retail, src)
        print(f"copied {retail} to {src}")
    stamp = Path(f'build/{ver}/src/materialman.o.fixed')
    stamp.touch()
