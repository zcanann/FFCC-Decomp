"""LLDB provider that observes the GC/2.5 register allocator through Wibo.

Loaded by tools/mwcc_trace/regalloc.py inside a private LLDB session. Only that
compiler process is instrumented. The caller compiles the same unit normally
and requires byte-identical output, so a capture never stands in for the real
build.

Hooks (GC/2.5 mwcceppc.exe, SHA-256 in gc25.py), all entered at PUSH EBX:
  DRIVER    0x4333F0  backend per-function driver; arg 2 is the function
  SIMPLIFY  0x508D40  interference graph before simplification
  COLOR     0x508C20  simplified node stack, in coloring order
  REWRITE   0x508AF0  graph after coloring, before operand rewrite

LLDB sees Wibo's host as x86-64 (also under Rosetta), so it cannot single-step
the 32-bit instruction it replaced, so each hook's PUSH EBX is emulated by
writing one stack word.
"""

import json
from pathlib import Path
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import gc25

_state = None


def page_reader(read):
    """Cache guest memory for the duration of one breakpoint callback."""
    pages = {}

    def memory(address, size):
        if address < 0 or size < 0 or address + size > 0x100000000:
            raise ValueError("memory range is outside the 32-bit guest")
        result = bytearray()
        while size:
            page = address & ~4095
            offset = address - page
            count = min(size, 4096 - offset)
            if page not in pages:
                data = read(page, 4096)
                if len(data) != 4096:
                    raise ValueError("short process page read")
                pages[page] = data
            result += pages[page][offset:offset + count]
            address += count
            size -= count
        return bytes(result)

    return memory


class CaptureState:
    def __init__(self, debugger, job):
        import lldb

        self.api = lldb
        self.job = job
        self.target = debugger.GetSelectedTarget()
        self.process = self.target.GetProcess()
        self.wanted = set(job["functions"])
        self.current_name = None
        self.functions = []
        self.events = []
        self.failure = None
        Path(job["pid"]).write_text(str(self.process.GetProcessID()))
        memory = page_reader(self.read)
        for address, expected in gc25.HOOK_BYTES.items():
            if memory(address, 1) != expected:
                raise ValueError(f"unexpected compiler hook byte at {address:#x}")
            breakpoint = self.target.BreakpointCreateByAddress(address)
            breakpoint.SetScriptCallbackFunction("lldb_provider._on_breakpoint")

    def read(self, address, size):
        error = self.api.SBError()
        data = self.process.ReadMemory(address, size, error)
        if error.Fail() or len(data) != size:
            raise ValueError(f"process memory read at {address:#x}: {error}")
        return data

    def write_word(self, address, value):
        error = self.api.SBError()
        count = self.process.WriteMemory(address, struct.pack("<I", value), error)
        if error.Fail() or count != 4:
            raise ValueError("short emulated stack write")

    def stopped(self, frame):
        memory = page_reader(self.read)
        word = lambda address: int.from_bytes(memory(address, 4), "little")
        pc = frame.GetPC()
        sp = frame.FindRegister("rsp").GetValueAsUnsigned()
        if pc == gc25.DRIVER:
            self.current_name = gc25.object_name(memory, word(sp + 8))
            self.functions.append(self.current_name)
        elif self.current_name in self.wanted:
            register_class = memory(gc25.REGISTER_CLASS, 1)[0]
            event = {"name": self.current_name, "register_class": register_class}
            if pc == gc25.SIMPLIFY:
                event["hook"] = "simplify"
                event["available"] = gc25.available_registers(memory, register_class)
                event["graph"] = gc25.read_graph(memory, register_class)
                event["spill_cutoff"] = int.from_bytes(memory(gc25.SPILL_CUTOFF, 2), "little", signed=True)
            elif pc == gc25.COLOR:
                event["hook"] = "color"
                event["order"] = gc25.read_stack(memory, word(sp + 4))
                event["spill_costs"] = gc25.read_spill_costs(memory, register_class)
            elif pc == gc25.REWRITE:
                event["hook"] = "rewrite"
                event["graph"] = gc25.read_graph(memory, register_class)
                event["pcode"] = gc25.read_pcode(memory)
            self.events.append(event)
        sp, pc = gc25.emulate_hook(pc, sp, frame.FindRegister("rbx").GetValueAsUnsigned(), word, self.write_word)
        if not frame.FindRegister("rsp").SetValueFromCString(str(sp)) or not frame.SetPC(pc):
            raise ValueError("cannot emulate 32-bit compiler hook")


def _install(debugger, job_path):
    global _state
    _state = CaptureState(debugger, json.loads(Path(job_path).read_text()))


def _on_breakpoint(frame, location, internal_dict):
    try:
        _state.stopped(frame)
        return False
    except Exception as error:
        _state.failure = f"{type(error).__name__}: {error}"
        print(_state.failure, flush=True)
        return True


def _finish(debugger):
    process = debugger.GetSelectedTarget().GetProcess()
    if (_state is None or _state.failure or process.GetState() != _state.api.eStateExited
            or process.GetExitStatus() != 0):
        process.Kill()
        raise RuntimeError("compiler capture did not exit normally")
    found = {event["name"] for event in _state.events if event["hook"] == "rewrite"}
    if found != _state.wanted:
        raise ValueError(f"no allocation captured for {sorted(_state.wanted - found)}; "
                         f"functions seen: {_state.functions}")
    Path(_state.job["result"]).write_text(json.dumps({"functions": _state.functions, "events": _state.events}))
