#!/usr/bin/env python3
"""The AliasPatch blob: checked-in artefact first, AliasPatch.c as the truth.

The compiler patch's predicates are written in C (AliasPatch.c, in the local
mwcc-gc CodeWarrior-decompilation repo) and compiled with that repo's own
Metrowerks mwcc.exe. A bare bfbb checkout has neither, so the LINKED BLOB is
checked in as tools/aliaspatch_blob.py and is what patch_compiler.py derives
from -- blob_for() below. When the mwcc-gc repo IS present (its location comes
from the MWCC_GC environment variable, defaulting to the path here), blob_for()
also recompiles AliasPatch.c and asserts the fresh link equals the artefact
byte-for-byte, so a stale artefact fails the build loudly instead of silently
shipping old predicates. The C never becomes optional; it just stops being
required to build.

To refresh the artefact after changing AliasPatch.c:

    python tools/aliaspatch_link.py --refresh

then update PATCHED_SHA1 in tools/patch_compiler.py (build once to see the new
hash) and re-measure with tools/patchcost.py -- a changed blob is a changed
compiler.

Link mechanics: mwcc emits one COMDAT `.text` section per function. link()
concatenates them at a caller-chosen base VA and resolves the x86 relocations.
The blob is fully PIC: every relocation is IMAGE_REL_I386_REL32 (0x14) --
inter-function calls and the one external call to killmemory -- so nothing
needs a base relocation and the sjiswrap rebase leaves it correct. If a build
ever emits an absolute IMAGE_REL_I386_DIR32 (0x6), link() raises, because that
would need .reloc surgery this injector deliberately avoids. External symbols
resolve to fixed VAs in the GC/2.0 binary; only killmemory is referenced (the
alias-list head is passed in by the stub).
"""
import os
import struct
import subprocess
import sys
import tempfile

MWCC_GC = os.environ.get("MWCC_GC", r"C:\Users\joeyj\Documents\Git\mwcc-gc")
MWCC = os.path.join(MWCC_GC, "CodeWarrior", "Other Metrowerks Tools",
                    "Command Line Tools", "mwcc.exe")
SRC = os.path.join(MWCC_GC, "src", "compiler_and_linker", "BackEnd", "PowerPC",
                   "GlobalOptimizer", "AliasPatch.c")
ARTIFACT = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                        "aliaspatch_blob.py")
# -opt space: the injected block must fit the executable tail of .text (the
# padding below the next section's page); speed there is irrelevant and the
# smaller code leaves margin. Behaviour is identical to any opt level.
CFLAGS = ["-c", "-opt", "l=4,space", "-enum", "min", "-nosyspath", "-inline", "off"]

# Undefined externals -> absolute VAs in mwcceppc.exe (GC/2.0 / p1 identical here)
EXTERNS = {"_killmemory": 0x0050A2C0}

# The exported predicates the stubs call.
EXPORTS = ("_sb_sched_clause", "_sb_vn_store_kill", "_sb_licm_invariant",
           "_sb_vn_subrange_store")

REL32 = 0x14
DIR32 = 0x06


def compile_obj(out_path):
    subprocess.run([MWCC, SRC, "-o", out_path, *CFLAGS], check=True)
    return open(out_path, "rb").read()


def _parse(data):
    mach, nsec, ts, symoff, nsym, optsz, ch = struct.unpack_from("<HHIIIHH", data, 0)
    strtab = symoff + 18 * nsym
    secs = []
    for i in range(nsec):
        o = 20 + 40 * i
        name = bytes(data[o:o + 8]).rstrip(b"\0").decode("latin1")
        vsz, va, rsz, rptr, relptr, lnptr, nrel, nln, flags = \
            struct.unpack_from("<IIIIIIHHI", data, o + 8)
        secs.append(dict(name=name, rsz=rsz, rptr=rptr, relptr=relptr, nrel=nrel))

    def symname(o):
        if struct.unpack_from("<I", data, o)[0] == 0:
            so = struct.unpack_from("<I", data, o + 4)[0]
            e = data.index(b"\0", strtab + so)
            return data[strtab + so:e].decode("latin1")
        return bytes(data[o:o + 8]).rstrip(b"\0").decode("latin1")

    syms = []
    i = 0
    while i < nsym:
        o = symoff + 18 * i
        nm = symname(o)
        val, secnum, typ, cls, naux = struct.unpack_from("<IhHBB", data, o + 8)
        syms.append(dict(name=nm, val=val, secnum=secnum))  # secnum is 1-based
        syms.extend([None] * naux)
        i += 1 + naux
    return secs, syms


def link(base_va, obj_path):
    """Place the blob at base_va. Returns (blob_bytes, {export_name: va})."""
    data = compile_obj(obj_path)
    secs, syms = _parse(data)

    # Assign each .text section a place in the blob, 4-byte aligned,
    # deterministic in section-table order. The COFF asks for 16; x86 does not
    # need it.
    text_idx = [i for i, s in enumerate(secs) if s["name"] == ".text" and s["rsz"]]
    place = {}      # section index (0-based) -> base VA
    blob = bytearray()
    for i in text_idx:
        while len(blob) % 4:
            blob.append(0)
        place[i] = base_va + len(blob)
        s = secs[i]
        blob += data[s["rptr"]:s["rptr"] + s["rsz"]]

    # Symbol -> VA. Defined symbols live in a placed .text section; undefined
    # externals map to their fixed binary VAs.
    def sym_va(sym):
        if sym["secnum"] > 0:
            si = sym["secnum"] - 1
            if si in place:
                return place[si] + sym["val"]
            raise KeyError(f"symbol {sym['name']} in non-.text section {si}")
        if sym["name"] in EXTERNS:
            return EXTERNS[sym["name"]]
        raise KeyError(f"unresolved external {sym['name']}")

    # Apply relocations per section.
    for i in text_idx:
        s = secs[i]
        secbase = place[i]
        blob_off = secbase - base_va
        for r in range(s["nrel"]):
            ro = s["relptr"] + 10 * r
            va, symidx, rtype = struct.unpack_from("<IIH", data, ro)
            if rtype == DIR32:
                raise RuntimeError("AliasPatch produced an absolute DIR32 "
                                   "relocation; the blob must stay PIC")
            if rtype != REL32:
                raise RuntimeError(f"unexpected relocation type {rtype:#x}")
            target = sym_va(syms[symidx])
            patch_at = blob_off + va
            addend = struct.unpack_from("<i", blob, patch_at)[0]
            value = target + addend - (secbase + va + 4)
            struct.pack_into("<i", blob, patch_at, value)

    exports = {}
    for sym in syms:
        if sym and sym["name"] in EXPORTS and sym["secnum"] > 0:
            exports[sym["name"]] = sym_va(sym)
    for e in EXPORTS:
        if e not in exports:
            raise KeyError(f"export {e} not found")

    return bytes(blob), exports


def source_available():
    return os.path.exists(MWCC) and os.path.exists(SRC)


def _fresh_link(base_va):
    with tempfile.TemporaryDirectory(prefix="aliaspatch_") as td:
        return link(base_va, os.path.join(td, "AliasPatch.obj"))


def load_artifact():
    """(base_va, blob, exports) from the checked-in tools/aliaspatch_blob.py."""
    ns = {}
    with open(ARTIFACT) as f:
        exec(compile(f.read(), ARTIFACT, "exec"), ns)
    return ns["BASE_VA"], bytes.fromhex(ns["BLOB_HEX"]), dict(ns["EXPORTS"])


def blob_for(base_va):
    """The blob to inject: the checked-in artefact, verified against a fresh
    compile of AliasPatch.c whenever the mwcc-gc repo is present."""
    abase, blob, exports = load_artifact()
    if abase != base_va:
        sys.exit(f"{ARTIFACT} was linked for base {abase:#x}, the injector "
                 f"wants {base_va:#x}; run tools/aliaspatch_link.py --refresh")
    if source_available():
        fresh_blob, fresh_exp = _fresh_link(base_va)
        if fresh_blob != blob or fresh_exp != exports:
            sys.exit(
                f"AliasPatch.c no longer matches the checked-in blob "
                f"{ARTIFACT}.\nIf the C change is intended, refresh it:\n"
                f"    python tools/aliaspatch_link.py --refresh\n"
                f"then update PATCHED_SHA1 in tools/patch_compiler.py and "
                f"re-measure with tools/patchcost.py."
            )
    return blob, exports


def refresh():
    if not source_available():
        sys.exit(f"cannot refresh: mwcc-gc repo not found at {MWCC_GC} "
                 f"(set MWCC_GC to its location)")
    from patch_compiler import BLOB_VA   # the one home of the base VA
    blob, exports = _fresh_link(BLOB_VA)
    import hashlib
    src_sha = hashlib.sha1(open(SRC, "rb").read()).hexdigest()
    hexs = blob.hex()
    lines = "\n".join(f'    "{hexs[i:i + 64]}"' for i in range(0, len(hexs), 64))
    body = f'''"""GENERATED -- do not edit. The linked AliasPatch blob.

Produced by `python tools/aliaspatch_link.py --refresh` from AliasPatch.c in
the mwcc-gc repo (source sha1 {src_sha}). patch_compiler.py injects these
bytes; when the mwcc-gc repo is present the build recompiles the C and refuses
to run if it no longer produces exactly this blob. After refreshing, update
PATCHED_SHA1 in tools/patch_compiler.py and re-measure with
tools/patchcost.py.
"""

BASE_VA = {BLOB_VA:#x}
SRC_SHA1 = "{src_sha}"
BLOB_HEX = (
{lines}
)
EXPORTS = {{
''' + "".join(f'    "{k}": {v:#x},\n' for k, v in sorted(exports.items())) + "}\n"
    with open(ARTIFACT, "w") as f:
        f.write(body)
    print(f"wrote {ARTIFACT}: {len(blob)} bytes at {BLOB_VA:#x}, "
          f"source sha1 {src_sha}")
    print("now update PATCHED_SHA1 in tools/patch_compiler.py (build once to "
          "see the new hash) and re-measure with tools/patchcost.py")


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "--refresh":
        refresh()
        sys.exit(0)
    base = int(sys.argv[1], 16) if len(sys.argv) > 1 else 0x57F000
    blob, exp = _fresh_link(base)
    print(f"blob {len(blob)} bytes at {base:#x}")
    for k, v in exp.items():
        print(f"  {k} = {v:#x}")
