#!/usr/bin/env python3
"""Reader for FFCC CFlat event scripts (dvd/cft/*.cft and *.cft.dbg).

The format and opcode semantics follow the decompiled interpreter:
  - loader:      CFlatRuntime::Create            (src/cflat_runtime.cpp)
  - interpreter: CFlatRuntime::objectFrame/calc  (src/cflat_runtime.cpp)
  - sys values:  CFlatRuntime2::onSystemVal      (src/cflat_r2system.cpp)

Usage:
  cflat.py info   <script>
  cflat.py dis    <script> [func ...]         raw disassembly
  cflat.py dec    <script> [func ...]         pseudo-C
  cflat.py dump   <out_dir> [--dir cft_dir]   pseudo-C for every script
  cflat.py xref   <regex>   [--dir cft_dir]   functions whose pseudo-C matches

<script> is a path or a bare name such as cave_0, looked up in the default
cft directory (orig/GCCP01/files/dvd/cft). Function arguments accept exact
names or regexes (e.g. 'HotSpot$').
A matching .cft.dbg next to the .cft is picked up automatically and adds
original source line numbers.
"""

import argparse
import os
import re
import struct
import sys


# ---------------------------------------------------------------------------
# Chunk file
# ---------------------------------------------------------------------------

def _chunks(data, off, end):
    while off + 16 <= end:
        tag = data[off:off + 4].decode("latin1")
        size, arg0, arg1 = struct.unpack(">III", data[off + 4:off + 16])
        yield tag, off + 16, size, arg0
        off += 16 + ((size + 15) & ~15)


def _cstr(data, off, size):
    return data[off:off + size].split(b"\0")[0].decode("latin1")


def _strtab(data, off, size, count):
    parts = data[off:off + size].split(b"\0")
    return [p.decode("cp1252", "replace") for p in parts[:count]]


class Func:
    def __init__(self, index):
        self.index = index
        self.name = "func_%d" % index
        self.argc = 0
        self.kind = 0
        self.sysidx = 0
        self.reqflag = 0
        self.caller_args = 0
        self.localc = 0
        self.ret = None
        self.code = b""
        self.lines = None  # list of (opcode, line, file) per instruction

    @property
    def kind_name(self):
        return {0: "script", 1: "builtin", 2: "system", 3: "classsystem"}.get(self.kind, "kind%d" % self.kind)


class Class:
    def __init__(self, index):
        self.index = index
        self.name = "class_%d" % index
        self.varc = 0
        self.localc = 0
        self.vtbl = []


class Script:
    def __init__(self, path):
        self.path = path
        self.name = ""
        self.funcs = []
        self.classes = []
        self.globals = []
        self.strs = []
        self.fstrs = []
        self.vstrs = []
        self.src_path = None
        self._load(open(path, "rb").read())
        dbg = path + ".dbg"
        if os.path.exists(dbg):
            self._load_dbg(open(dbg, "rb").read())

    def _load(self, d):
        for tag, off, size, _ in _chunks(d, 0, len(d)):
            if tag != "CFLT":
                continue
            for tag, o, s, a0 in _chunks(d, off, off + size):
                if tag == "NAME":
                    self.name = _cstr(d, o, s)
                elif tag == "VAL ":
                    self.globals = [struct.unpack(">BBH", d[o + 4 * i:o + 4 * i + 4]) for i in range(a0)]
                elif tag == "CLAS":
                    for btag, bo, bs, _ in _chunks(d, o, o + s):
                        if btag != "BLCK":
                            continue
                        c = Class(len(self.classes))
                        for t, co, cs, ca in _chunks(d, bo, bo + bs):
                            if t == "NAME":
                                c.name = _cstr(d, co, cs)
                            elif t == "INFO":
                                c.varc = struct.unpack(">i", d[co:co + 4])[0]
                            elif t == "VTBL":
                                c.vtbl = list(struct.unpack(">128i", d[co:co + 512]))
                            elif t == "VAL ":
                                c.localc = ca
                        self.classes.append(c)
                elif tag == "FUNC":
                    for btag, bo, bs, _ in _chunks(d, o, o + s):
                        if btag != "BLCK":
                            continue
                        f = Func(len(self.funcs))
                        for t, fo, fs, fa in _chunks(d, bo, bo + bs):
                            if t == "NAME":
                                f.name = _cstr(d, fo, fs)
                            elif t == "INFO":
                                f.argc, f.kind, f.sysidx, f.reqflag, f.caller_args = struct.unpack(">5i", d[fo:fo + 20])
                            elif t == "VAL ":
                                f.localc = fa
                            elif t == "RET ":
                                f.ret = struct.unpack(">BBH", d[fo:fo + 4])
                            elif t == "CODE":
                                f.code = d[fo:fo + fs]
                        self.funcs.append(f)
                elif tag == "STR ":
                    self.strs = _strtab(d, o, s, a0)
                elif tag == "FSTR":
                    self.fstrs = _strtab(d, o, s, a0)
                elif tag == "VSTR":
                    self.vstrs = _strtab(d, o, s, a0)

    def _load_dbg(self, d):
        index = 0
        for tag, off, size, _ in _chunks(d, 0, len(d)):
            if tag != "CFLT":
                continue
            for tag, o, s, _ in _chunks(d, off, off + size):
                if tag == "NAME":
                    self.src_path = _cstr(d, o, s)
                if tag != "FUNC":
                    continue
                for btag, bo, bs, _ in _chunks(d, o, o + s):
                    if btag != "BLCK":
                        continue
                    for t, co, cs, _ in _chunks(d, bo, bo + bs):
                        if t == "CODE" and cs and index < len(self.funcs):
                            recs = []
                            for k in range(cs // 8):
                                op, _b1, _h, line, fid = struct.unpack(">BBHHH", d[co + 8 * k:co + 8 * k + 8])
                                recs.append((op, line, fid))
                            self.funcs[index].lines = recs
                    index += 1

    def find(self, pattern):
        exact = [f for f in self.funcs if f.name == pattern]
        if exact:
            return exact
        rx = re.compile(pattern)
        return [f for f in self.funcs if rx.search(f.name)]

    def classes_of(self, func):
        return [c.name for c in self.classes if func.index in c.vtbl]


# ---------------------------------------------------------------------------
# Instructions
# ---------------------------------------------------------------------------

def instructions(code):
    pc = 0
    while pc < len(code):
        op = code[pc]
        if op < 0x0C:
            yield pc, op, struct.unpack(">I", code[pc + 1:pc + 5])[0]
            pc += 5
        else:
            yield pc, op, None
            pc += 1


def _s32(v):
    return v - (1 << 32) if v & 0x80000000 else v


SYS_NAMES = {
    -0x40: "sysVal0",
    -0x41: "timerA",
    -0x42: "globalTime",
    -0x43: "frameCounter",
    -0x66: "chaliceElement",
    -0x75: "bossArtifactStageIndex",
    -0x76: "playMode",
    -0x77: "soundOption",
    -0x78: "gameOver",
    -0x79: "optionValue",
    -0x7A: "language",
}
SYS_ARRAYS = [
    (-0x47, -0x44, "wmBackupParams"),
    (-0x56, -0x48, "bossArtifactStage"),
    (-0x65, -0x57, "stageTable"),
    (-0x6B, -0x67, "eventHeader"),
    (-0x73, -0x6C, "usbChara"),
]


# Per-object values, from CFlatRuntime2::onClassSystemVal (src/cflat_r2class.cpp).
CSYS_NAMES = {
    -0x1: "posX", -0x2: "posY", -0x3: "posZ", -0x4: "rotTargetY", -0x6: "classId",
    -0xF: "worldParamA", -0x10: "worldParamB",
    -0x40: "maxHp", -0x41: "hp", -0x43: "strength", -0x44: "magic", -0x45: "defense",
    -0x82: "objId",
}
CSYS_ARRAYS = [
    (-0x14, -0x11, "dropItemCodes", 1),
    (-0x79, -0x53, "statusTimers", -1),
    (-0x94, -0x85, "statusValues", 1),
]


def csys_name(idx):
    if idx in CSYS_NAMES:
        return CSYS_NAMES[idx]
    for lo, hi, name, sign in CSYS_ARRAYS:
        if lo <= idx <= hi:
            return "%s[%d]" % (name, idx - lo if sign > 0 else hi - idx)
    return "csys[-0x%X]" % -idx


def sys_name(idx, cls):
    if cls:
        return csys_name(idx)
    if idx <= -0x1000:
        v = -0x1000 - idx
        return "romTable[%d][%d]" % (0x5FF - v % 0x600, v // 0x600)
    if idx <= -500:
        return "evtFlag[%d]" % (idx + 0x9F3)
    if idx <= -200:
        return "eventWork[%d]" % (idx + 0x1C7)
    if idx in SYS_NAMES:
        return SYS_NAMES[idx]
    for lo, hi, name in SYS_ARRAYS:
        if lo <= idx <= hi:
            return "%s[%d]" % (name, idx - lo)
    return "sys[-0x%X]" % -idx


def sys_base(idx, cls):
    """Name for a sys array base that gets a dynamic offset added."""
    if cls:
        return "csys[-0x%X + " % -idx, "]"
    if idx <= -500 and idx > -0x1000:
        return "evtFlag[%d + " % (idx + 0x9F3), "]"
    if idx <= -200 and idx > -0x1000:
        return "eventWork[%d + " % (idx + 0x1C7), "]"
    for lo, hi, name in SYS_ARRAYS:
        if lo <= idx <= hi:
            return "%s[%d + " % (name, idx - lo), "]"
    return "sys[-0x%X + " % -idx, "]"


def var_base(func, arg):
    idx = _s32(arg) >> 8
    if idx < 0:
        return None
    if arg & 8:
        return ("this.m%d" if arg & 0x10 else "G%d") % idx
    if idx < func.argc:
        return "arg%d" % idx
    return "l%d" % idx


BINOPS = {
    0x19: "+", 0x1A: "-", 0x1B: "*", 0x1C: "/", 0x1D: "%", 0x1E: "|", 0x1F: "&",
    0x21: ">>", 0x22: "<<", 0x24: "^",
    0x26: "+.", 0x27: "-.", 0x28: "*.", 0x29: "/.", 0x2A: "%.",
    0x2C: "==", 0x2D: "!=", 0x2E: "<", 0x2F: "<=", 0x30: ">", 0x31: ">=",
    0x32: "==.", 0x33: "!=.", 0x34: "<.", 0x35: "<=.", 0x36: ">.", 0x37: ">=.",
}
UNOPS = {0x20: "-", 0x23: "!", 0x25: "~", 0x2B: "-."}
STORES = {0x0D: "=", 0x0E: "+=", 0x0F: "-=", 0x10: "=", 0x11: "+=", 0x12: "-=",
          0x13: "=", 0x16: "=", 0x14: "+=", 0x17: "+=", 0x15: "-=", 0x18: "-="}
MNEMONIC = {
    0: "load", 1: "addr", 2: "sysref", 3: "pushi", 4: "pushf", 5: "pushs", 6: "objcall",
    7: "jmp", 8: "jz", 9: "jnz", 0x0A: "call", 0x0B: "new",
    0x0C: "pop", 0x0D: "st", 0x0E: "st+", 0x0F: "st-", 0x10: "stf", 0x11: "stf+", 0x12: "stf-",
    0x13: "setsys", 0x14: "setsys+", 0x15: "setsys-", 0x16: "setsys", 0x17: "setsys+", 0x18: "setsys-",
    0x20: "neg", 0x23: "not", 0x25: "bnot", 0x2B: "fneg",
    0x39: "retobj", 0x3A: "dup", 0x3C: "ret", 0x3D: "f2i", 0x3E: "i2f", 0x3F: "push0",
}


def _fmt_float(v):
    s = "%g" % v
    if "." not in s and "e" not in s and "n" not in s:
        s += ".0"
    return s


def _var_text(script, func, op, arg, idx_expr=None):
    """Text for operand of load/addr/sysref; idx_expr is the popped index if any."""
    idx = _s32(arg) >> 8
    cls = bool(arg & 0x10)
    if op == 2 or idx < 0:
        if idx_expr is None:
            return sys_name(idx, cls)
        pre, post = sys_base(idx, cls)
        return pre + idx_expr + post
    base = var_base(func, arg)
    if idx_expr is None:
        return base
    if arg & 4:
        return "%s->[%s]" % (base, idx_expr)
    return "%s[%s]" % (base, idx_expr)


def disassemble(script, func):
    out = []
    lines = func.lines or []
    for n, (pc, op, arg) in enumerate(instructions(func.code)):
        line = ""
        if n < len(lines):
            line = "%5d" % lines[n][1]
        if arg is None:
            name = MNEMONIC.get(op) or BINOPS.get(op) or "op%02X" % op
            text = name
        else:
            name = MNEMONIC[op]
            if op in (0, 1, 2):
                mode = "" if arg & 1 else ("[]" if arg & 2 else ("->[]" if arg & 4 else "?"))
                text = "%s %s%s" % (name, _var_text(script, func, op, arg), mode)
            elif op == 3:
                text = "pushi %d" % _s32(arg)
            elif op == 4:
                text = "pushf %s" % _fmt_float(struct.unpack(">f", struct.pack(">I", arg))[0])
            elif op == 5:
                text = "pushs %d %r" % (arg, script.strs[arg] if arg < len(script.strs) else "?")
            elif op == 6:
                text = "objcall %s" % ("reserve" if (arg >> 16) == 0 else "enter argc=%d" % (arg & 0xFFFF))
            elif op in (7, 8, 9):
                text = "%s %04X%s" % (name, arg & 0xFFFFFF, " (keep)" if arg >> 24 else "")
            elif op == 0x0A:
                g = script.funcs[arg & 0xFFFF]
                text = "call%s %s/%d" % ("" if (_s32(arg) >> 16) < 0 else ".virt", g.name, g.argc)
            elif op == 0x0B:
                text = "new %s" % (script.classes[arg].name if arg < len(script.classes) else arg)
            else:
                text = "%s %08X" % (name, arg)
        out.append("%s  %04X  %s" % (line, pc, text))
    return out


# ---------------------------------------------------------------------------
# Pseudo-C
# ---------------------------------------------------------------------------

class E:
    """Expression on the symbolic stack."""
    __slots__ = ("text", "prec", "effect", "kind", "cmp", "inner")

    def __init__(self, text, prec=100, effect=False, kind=None, cmp=None, inner=None):
        self.text = text
        self.prec = prec
        self.effect = effect
        self.kind = kind
        self.cmp = cmp      # (lhs, op, rhs) for a top-level comparison
        self.inner = inner  # operand of a top-level '!'

    def wrap(self, prec):
        return self.text if self.prec >= prec else "(" + self.text + ")"


PREC = {"*": 13, "/": 13, "%": 13, "+": 12, "-": 12, "<<": 11, ">>": 11,
        "<": 10, "<=": 10, ">": 10, ">=": 10, "==": 9, "!=": 9, "&": 8, "^": 7, "|": 6,
        "&&": 5, "||": 4}
NEG_CMP = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}


def _binprec(sym):
    return PREC.get(sym.rstrip("."), 3)


def negate(e):
    if e.cmp:
        lhs, op, rhs = e.cmp
        base = op.rstrip(".")
        flipped = NEG_CMP[base] + op[len(base):]
        return E("%s %s %s" % (lhs, flipped, rhs), e.prec, e.effect, cmp=(lhs, flipped, rhs))
    if e.inner is not None:
        return e.inner
    return E("!" + e.wrap(14), 14, e.effect, inner=e)


def _const_text(script, op, arg):
    if op == 3:
        return str(_s32(arg))
    if op == 4:
        return _fmt_float(struct.unpack(">f", struct.pack(">I", arg))[0])
    if op == 5:
        return repr(script.strs[arg]) if arg < len(script.strs) else "<str %d>" % arg
    return "0"


def _reachable(insns, index_of):
    seen = set()
    work = [0]
    while work:
        i = work.pop()
        while i < len(insns) and i not in seen:
            seen.add(i)
            pc, op, arg = insns[i]
            if op in (7, 8, 9):
                t = index_of.get(arg & 0xFFFFFF)
                if t is not None:
                    work.append(t)
                if op == 7:
                    break
            if op == 0x3C:
                break
            i += 1
    return seen


def _case_sites(insns):
    """dup; push const; ==; jz T; pop  ->  {index: (const insn, T, body pc)}"""
    sites = {}
    for i in range(len(insns) - 5):
        ops = [insns[i + k][1] for k in range(5)]
        if (ops[0] == 0x3A and ops[1] in (3, 4, 5, 0x3F) and ops[2] in (0x2C, 0x32)
                and ops[3] == 8 and not (insns[i + 3][2] >> 24) and ops[4] == 0x0C):
            sites[i] = (insns[i + 1], insns[i + 3][2] & 0xFFFFFF, insns[i + 5][0])
    return sites


def _switch_groups(insns, index_of, sites):
    """Chains of case sites sharing one subject, with the break target."""
    groups = {}
    targets = {t for (_, t, _) in sites.values()}
    for i in sorted(sites):
        if insns[i][0] in targets:
            continue
        chain = [i]
        while True:
            t = index_of.get(sites[chain[-1]][1])
            if t in sites and t not in chain:
                chain.append(t)
            else:
                break
        ends = []
        for k in chain:
            t = index_of.get(sites[k][1])
            if t is None or t < 2:
                continue
            if insns[t - 1][1] == 7 and insns[t - 2][1] == 7:
                ends.append(insns[t - 2][2] & 0xFFFFFF)
        if ends:
            groups[i] = (chain, max(ends, key=ends.count))
    return groups


def lift(script, func):
    """Bytecode -> flat node list."""
    insns = list(instructions(func.code))
    index_of = {pc: i for i, (pc, _, _) in enumerate(insns)}
    lines = func.lines or []
    line_of = {insns[n][0]: lines[n][1] for n in range(min(len(lines), len(insns)))}
    reach = _reachable(insns, index_of)
    sites = _case_sites(insns)
    groups = _switch_groups(insns, index_of, sites)
    case_body = {sites[k][2] for g in groups.values() for k in g[0]}

    labels = set()
    for pc, op, arg in insns:
        if op == 7 or (op in (8, 9) and not (arg >> 24)):
            labels.add(arg & 0xFFFFFF)

    nodes = []
    stack = []
    live = True
    snapshots = {}
    pending = {}
    switches = []  # active: dict(subject, end, sites)
    targets = []   # objects entered with objcall
    skip_until = -1

    def add(kind, *data, pc=None):
        nodes.append((kind, data, line_of.get(pc)))

    def pop():
        return stack.pop() if stack else E("<underflow>")

    def branch(target):
        if stack and target not in snapshots:
            snapshots[target] = list(stack)

    for i, (pc, op, arg) in enumerate(insns):
        if i < skip_until:
            continue
        if pc in pending:
            for cond, sym, depth in reversed(pending.pop(pc)):
                rhs = stack.pop() if len(stack) > depth else E("<?>")
                p = PREC[sym]
                stack.append(E("%s %s %s" % (cond.wrap(p), sym, rhs.wrap(p + 1)), p, cond.effect or rhs.effect))
        while switches and pc == switches[-1]["end"]:
            add("end")
            switches.pop()
        if i not in reach:
            live = False
            continue
        if pc in labels:
            if not live:
                stack = list(snapshots.get(pc, []))
            add("label", pc)
        live = True

        if i in groups and stack:
            chain, end = groups[i]
            switches.append({"subject": stack[-1], "end": end, "sites": set(chain),
                             "fails": {sites[k][1] for k in chain}})
            add("switch", stack[-1].text, pc=pc)
        sw = switches[-1] if switches else None
        if sw and i in sw["sites"] and stack and stack[-1] is sw["subject"]:
            const, target, _ = sites[i]
            add("case", _const_text(script, const[1], const[2]), pc=pc)
            branch(target)
            stack.pop()
            skip_until = i + 5
            continue
        if sw and op == 0x0C and pc in labels and stack and stack[-1] is sw["subject"]:
            stack.pop()
            add("default", pc=pc)
            continue

        if op == 0:
            idx = pop().text if (not (arg & 1) and (arg & 6)) else None
            stack.append(E(_var_text(script, func, 0, arg, idx)))
        elif op in (1, 2):
            idx = pop().text if (not (arg & 1) and (arg & 6)) else None
            stack.append(E(_var_text(script, func, op, arg, idx), kind="ref"))
        elif op in (3, 4, 5, 0x3F):
            stack.append(E(_const_text(script, op, arg)))
        elif op == 6:
            if (arg >> 16) == 0:
                stack.append(E("<frame>", kind="frame"))
                stack.append(E("<frame>", kind="frame"))
            else:
                base = len(stack) - (arg & 0xFFFF)
                if base >= 3 and stack[base - 1].kind == "frame" and stack[base - 2].kind == "frame":
                    targets.append(stack[base - 3])
                    del stack[base - 3:base]
                else:
                    targets.append(E("<obj>"))
        elif op == 0x0A:
            g = script.funcs[arg & 0xFFFF]
            args = [pop() for _ in range(g.argc)][::-1]
            stack.append(E("%s(%s)" % (g.name, ", ".join(a.text for a in args)), effect=True))
        elif op == 0x39:
            v = pop()
            t = targets.pop() if targets else E("<obj>")
            stack.append(E("%s.%s" % (t.wrap(100), v.text), effect=v.effect, kind=v.kind))
        elif op == 0x0B:
            cls = script.classes[arg] if arg < len(script.classes) else None
            n = 0
            if cls and cls.vtbl and 0 <= cls.vtbl[0] < len(script.funcs):
                n = script.funcs[cls.vtbl[0]].argc
            args = [pop() for _ in range(n)][::-1]
            stack.append(E("new %s(%s)" % (cls.name if cls else arg, ", ".join(a.text for a in args)), effect=True))
        elif op == 0x0C:
            e = pop()
            if e.effect:
                add("stmt", e.text, pc=pc)
        elif op in STORES:
            val = pop()
            ref = pop()
            stack.append(E("%s %s %s" % (ref.text, STORES[op], val.wrap(2)), 1, True))
        elif op in BINOPS:
            rhs = pop()
            lhs = pop()
            sym = BINOPS[op]
            p = _binprec(sym)
            l, r = lhs.wrap(p), rhs.wrap(p + 1)
            cmp = (l, sym, r) if sym.rstrip(".") in NEG_CMP else None
            stack.append(E("%s %s %s" % (l, sym, r), p, lhs.effect or rhs.effect, cmp=cmp))
        elif op in UNOPS:
            v = pop()
            if op == 0x23:
                stack.append(negate(v))
            else:
                stack.append(E(UNOPS[op] + v.wrap(14), 14, v.effect))
        elif op == 0x3A:
            stack.append(stack[-1] if stack else E("<underflow>"))
        elif op in (0x3D, 0x3E):
            v = pop()
            stack.append(E(("(int)" if op == 0x3D else "(float)") + v.wrap(14), 14, v.effect))
        elif op == 0x3C:
            v = pop()
            add("ret", v.text, pc=pc)
            stack = []
            live = False
        elif op == 7:
            tgt = arg & 0xFFFFFF
            branch(tgt)
            if sw and tgt == sw["end"]:
                add("break", pc=pc)
            elif sw and pc in sw["fails"]:
                pass  # last case failed: dispatch to default
            elif sw and tgt in case_body and i + 1 < len(insns) and index_of.get(tgt, -1) == i + 6:
                pass  # fallthrough into the next case body
            else:
                add("goto", tgt, pc=pc)
            stack = []
            live = False
        elif op in (8, 9):
            cond = pop()
            tgt = arg & 0xFFFFFF
            if arg >> 24:
                pending.setdefault(tgt, []).append((cond, "&&" if op == 8 else "||", len(stack)))
            else:
                branch(tgt)
                add("if", negate(cond) if op == 8 else cond, tgt, pc=pc)
        else:
            add("stmt", "/* op%02X */" % op, pc=pc)
    while switches:
        add("end")
        switches.pop()
    return _place_defaults(nodes)


def _place_defaults(nodes):
    """Move 'default: goto D' to label D and drop empty defaults."""
    out = list(nodes)
    k = 0
    while k < len(out):
        if out[k][0] == "default" and k + 1 < len(out) and out[k + 1][0] == "goto":
            d = out[k + 1][1][0]
            del out[k:k + 2]
            for m, n in enumerate(out):
                if n[0] == "label" and n[1][0] == d:
                    out.insert(m + 1, ("default", (), None))
                    break
            k = 0
            continue
        k += 1
    k = 0
    while k < len(out):
        if out[k][0] == "default":
            m = k + 1
            while m < len(out) and out[m][0] == "label":
                m += 1
            if m < len(out) and out[m][0] == "end":
                del out[k]
                continue
        k += 1
    return out


def _find_fors(nodes):
    """Rewrite the compiler's for-loop layout into for/endfor nodes.

    HEAD: if (!cond) goto EXIT; goto BODY; STEP: step...; goto HEAD;
    BODY: body...; goto STEP; EXIT:
    """
    nodes = list(nodes)
    i = 0
    while i + 4 < len(nodes):
        n = nodes
        if not (n[i][0] == "label" and n[i + 1][0] == "if" and n[i + 2][0] == "goto"
                and n[i + 3][0] == "label"):
            i += 1
            continue
        head, step_label = n[i][1][0], n[i + 3][1][0]
        cond, exit_t = n[i + 1][1]
        body_t = n[i + 2][1][0]
        g = i + 4
        while g < len(n) and n[g][0] == "stmt":
            g += 1
        if not (g < len(n) - 1 and n[g][0] == "goto" and n[g][1][0] == head
                and n[g + 1][0] == "label" and n[g + 1][1][0] == body_t):
            i += 1
            continue
        x = next((k for k in range(g + 2, len(n)) if n[k][0] == "label" and n[k][1][0] == exit_t), None)
        if x is None or n[x - 1][0] != "goto" or n[x - 1][1][0] != step_label:
            i += 1
            continue
        steps = [s[1][0] for s in n[i + 4:g]]
        init = ""
        start = i
        if i > 0 and n[i - 1][0] == "stmt" and steps:
            lhs = steps[0].split(" ")[0]
            if n[i - 1][1][0].startswith(lhs + " = "):
                init = n[i - 1][1][0]
                start = i - 1
        loop = ("for", (init, cond, steps, step_label), n[i + 1][2])
        body = n[g + 2:x - 1]
        nodes = n[:start] + [loop] + body + [("label", (step_label,), None), ("endfor", (), None)] + n[x:]
        i = start + 1
    return nodes


def structure(nodes):
    """Flat nodes -> indented pseudo-C lines."""
    nodes = _find_fors(nodes)
    label_at = {}
    refs = {}
    for i, (kind, data, _) in enumerate(nodes):
        if kind == "label":
            label_at[data[0]] = i
        elif kind in ("goto", "if"):
            refs.setdefault(data[-1], []).append(i)
    alive = {t: len(v) for t, v in refs.items()}
    out = []
    last_line = [None]

    def emit(indent, text, line=None):
        tag = ""
        if line is not None and line != last_line[0]:
            tag = "  // %d" % line
            last_line[0] = line
        out.append("    " * indent + text + tag)

    def dest(i):
        while i < len(nodes) and nodes[i][0] == "label":
            i += 1
        return i

    def dest_of(t):
        j = label_at.get(t)
        return None if j is None else dest(j)

    def closed(a, b):
        depth = 0
        for k in range(a, b):
            kind, data, _ = nodes[k]
            if kind in ("switch", "for"):
                depth += 1
            elif kind in ("end", "endfor"):
                depth -= 1
                if depth < 0:
                    return False
            elif kind == "label":
                if any(not (a <= r < b) for r in refs.get(data[0], [])):
                    return False
        return depth == 0

    def find_label(t, lo, hi):
        j = label_at.get(t)
        return j if j is not None and lo <= j < hi else None

    def jump(body, t, line, exit_at, loop, in_switch, cond=None, last=False, nxt=None):
        """Emit a (conditional) jump to label t using break/continue where possible."""
        d = dest_of(t)
        prefix = "" if cond is None else "if (%s) " % cond.text
        if cond is None and ((last and exit_at is not None and d == exit_at) or d == nxt):
            alive[t] -= 1
        elif loop and not in_switch and d == loop[1]:
            emit(body, prefix + "break;", line)
            alive[t] -= 1
        elif loop and not in_switch and d == loop[0]:
            emit(body, prefix + "continue;", line)
            alive[t] -= 1
        else:
            emit(body, prefix + "goto L%04X;" % t, line)

    def walk(lo, hi, indent, in_switch=False, exit_at=None, loop=None):
        body = indent + 1 if in_switch else indent
        i = lo
        while i < hi:
            kind, data, line = nodes[i]
            if kind == "label":
                t = data[0]
                own = refs.get(t, [])
                if i + 1 < hi and nodes[i + 1][0] == "if":
                    _, (cond, exit_t), cline = nodes[i + 1]
                    j = find_label(exit_t, i + 2, hi)
                    if (j is not None and nodes[j - 1][0] == "goto" and nodes[j - 1][1][0] == t
                            and closed(i + 2, j - 1) and all(i <= r < j for r in own)):
                        emit(body, "while (%s) {" % negate(cond).text, cline)
                        alive[t] -= 1
                        alive[exit_t] -= 1
                        walk(i + 2, j - 1, body + 1, exit_at=dest(i), loop=(dest(i), dest(j)))
                        emit(body, "}")
                        i = j
                        continue
                back = [r for r in own if r > i and nodes[r][0] == "goto"]
                if back and max(back) < hi and all(i < r <= max(back) for r in own):
                    g = max(back)
                    if closed(i + 1, g):
                        emit(body, "while (1) {", nodes[i + 1][2] if i + 1 < len(nodes) else None)
                        alive[t] -= 1
                        walk(i + 1, g, body + 1, exit_at=dest(i), loop=(dest(i), dest(g + 1)))
                        emit(body, "}")
                        i = g + 1
                        continue
                if alive.get(t, 0) > 0:
                    out.append("    " * max(body - 1, 0) + "L%04X:" % t)
                i += 1
            elif kind == "if":
                cond, t = data
                j = find_label(t, i + 1, hi)
                if j is None and exit_at is not None and dest_of(t) == exit_at and closed(i + 1, hi):
                    j = hi
                if j is not None and closed(i + 1, j):
                    k = None
                    if j < hi and j - 1 > i and nodes[j - 1][0] == "goto" and len(refs.get(t, [])) == 1:
                        m = nodes[j - 1][1][0]
                        k = find_label(m, j + 1, hi)
                        if k is None and exit_at is not None and dest_of(m) == exit_at and closed(j + 1, hi):
                            k = hi
                        if k is not None and not closed(j + 1, k):
                            k = None
                    emit(body, "if (%s) {" % negate(cond).text, line)
                    alive[t] -= 1
                    if k is not None:
                        alive[nodes[j - 1][1][0]] -= 1
                        after = dest(k) if k < hi else exit_at
                        walk(i + 1, j - 1, body + 1, exit_at=after, loop=loop)
                        emit(body, "} else {")
                        walk(j + 1, k, body + 1, exit_at=after, loop=loop)
                        emit(body, "}")
                        i = k
                    else:
                        walk(i + 1, j, body + 1, exit_at=dest(j) if j < hi else exit_at, loop=loop)
                        emit(body, "}")
                        i = j
                    continue
                jump(body, t, line, exit_at, loop, in_switch, cond=cond)
                i += 1
            elif kind == "goto":
                jump(body, data[0], line, exit_at, loop, in_switch, last=dest(i + 1) >= hi, nxt=dest(i + 1))
                i += 1
            elif kind == "for":
                init, cond, steps, step_label = data
                depth, m = 0, i
                while m < hi:
                    if nodes[m][0] == "for":
                        depth += 1
                    elif nodes[m][0] == "endfor":
                        depth -= 1
                        if depth == 0:
                            break
                    m += 1
                emit(body, "for (%s; %s; %s) {" % (init, negate(cond).text, ", ".join(steps)), line)
                walk(i + 1, m, body + 1, exit_at=dest(label_at[step_label]),
                     loop=(dest(label_at[step_label]), dest(m + 1)))
                emit(body, "}")
                i = m + 1
            elif kind == "switch":
                depth, m = 0, i
                while m < hi:
                    if nodes[m][0] == "switch":
                        depth += 1
                    elif nodes[m][0] == "end":
                        depth -= 1
                        if depth == 0:
                            break
                    m += 1
                emit(body, "switch (%s) {" % data[0], line)
                walk(i + 1, m, body + 1, in_switch=True, exit_at=dest(m + 1), loop=loop)
                emit(body, "}")
                i = m + 1
            elif kind == "case":
                emit(indent, "case %s:" % data[0], line)
                i += 1
            elif kind == "default":
                emit(indent, "default:", line)
                i += 1
            elif kind == "break":
                emit(body, "break;", line)
                i += 1
            elif kind == "ret":
                emit(body, "return %s;" % data[0], line)
                i += 1
            elif kind == "stmt":
                emit(body, data[0] + ";", line)
                i += 1
            else:
                i += 1

    walk(0, len(nodes), 1)
    # labels whose last reference was structured away
    return [l for l in out if not (l.strip().endswith(":") and l.strip().startswith("L")
                                   and alive.get(int(l.strip()[1:-1], 16), 0) <= 0)]


def decompile(script, func):
    if not func.code:
        return []
    return structure(lift(script, func))


def header(script, func):
    owners = script.classes_of(func)
    own = (" [%s]" % ", ".join(owners)) if owners else ""
    params = ", ".join("arg%d" % i for i in range(func.argc))
    return "%s %s(%s)%s" % (func.kind_name, func.name, params, own)


def render(script, func, mode):
    body = decompile(script, func) if mode == "dec" else disassemble(script, func)
    head = header(script, func)
    if not func.code:
        return [head + ";"]
    return [head, "{"] + body + ["}"]


def render_script(script, mode="dec", funcs=None):
    lines = ["// %s" % os.path.basename(script.path)]
    if script.src_path:
        lines.append("// source: %s" % script.src_path)
    lines.append("// %d functions, %d classes, %d globals, %d strings" %
                 (len(script.funcs), len(script.classes), len(script.globals), len(script.strs)))
    for c in script.classes:
        members = [script.funcs[i].name for i in c.vtbl if 0 <= i < len(script.funcs)]
        lines.append("// class %s (%d vars): %s" % (c.name, c.varc, ", ".join(members)))
    lines.append("")
    for f in funcs if funcs is not None else script.funcs:
        if funcs is None and not f.code:
            continue
        lines.extend(render(script, f, mode))
        lines.append("")
    return lines


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

DEFAULT_DIR = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                           "..", "..", "orig", "GCCP01", "files", "dvd", "cft"))


def _open(name):
    if os.path.exists(name):
        return Script(name)
    path = os.path.join(DEFAULT_DIR, name if name.endswith(".cft") else name + ".cft")
    if not os.path.exists(path):
        sys.exit("no script %r (looked in %s)" % (name, DEFAULT_DIR))
    return Script(path)


def _scripts(directory):
    for name in sorted(os.listdir(directory)):
        if name.endswith(".cft"):
            yield Script(os.path.join(directory, name))


def _select(script, patterns):
    if not patterns:
        return None
    sel = []
    for p in patterns:
        found = script.find(p)
        if not found:
            sys.exit("no function matching %r in %s" % (p, script.path))
        sel.extend(found)
    return sel


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("info")
    p.add_argument("file")
    for name in ("dis", "dec"):
        p = sub.add_parser(name)
        p.add_argument("file")
        p.add_argument("funcs", nargs="*")
    p = sub.add_parser("dump")
    p.add_argument("out")
    p.add_argument("--dir", default=DEFAULT_DIR)
    p.add_argument("--dis", action="store_true", help="write disassembly instead of pseudo-C")
    p = sub.add_parser("xref")
    p.add_argument("pattern")
    p.add_argument("--dir", default=DEFAULT_DIR)
    a = ap.parse_args()

    if a.cmd == "info":
        s = _open(a.file)
        print("name: %s  source: %s" % (s.name, s.src_path))
        for c in s.classes:
            print("class %3d %-24s vars=%d" % (c.index, c.name, c.varc))
        for f in s.funcs:
            print("func %4d %-32s %-11s argc=%d sysidx=%d code=%d" %
                  (f.index, f.name, f.kind_name, f.argc, f.sysidx, len(f.code)))
    elif a.cmd in ("dis", "dec"):
        s = _open(a.file)
        print("\n".join(render_script(s, a.cmd, _select(s, a.funcs))))
    elif a.cmd == "dump":
        os.makedirs(a.out, exist_ok=True)
        ext = ".dis.txt" if a.dis else ".c"
        for s in _scripts(a.dir):
            path = os.path.join(a.out, os.path.basename(s.path)[:-4] + ext)
            with open(path, "w", encoding="utf-8", newline="\n") as fh:
                fh.write("\n".join(render_script(s, "dis" if a.dis else "dec")) + "\n")
            print(path)
    elif a.cmd == "xref":
        rx = re.compile(a.pattern)
        for s in _scripts(a.dir):
            for f in s.funcs:
                if not f.code:
                    continue
                body = decompile(s, f)
                hits = [l.strip() for l in body if rx.search(l)]
                if hits:
                    print("%s: %s" % (os.path.basename(s.path), header(s, f)))
                    for h in hits:
                        print("    " + h)


if __name__ == "__main__":
    main()
