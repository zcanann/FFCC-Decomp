"""Addresses and record layouts for the GC/2.5 mwcceppc.exe register allocator.

The allocator routines are instruction-identical matches of the GC/1.3 ones
used by SFA's tracer; field offsets are read from the GC/2.5 simplify/color
loops themselves. Unlike GC/1.3, GC/2.5 only calls its PCode listing hook
(0x500FA0) when listings are enabled, so functions are identified at the
backend driver instead.

InterferenceNode (0x1A-byte header, then int16 neighbors):
  +0x00 next, +0x04 object, +0x10 virtual register, +0x12 degree,
  +0x14 physical register, +0x16 flags, +0x18 neighbor count.
Object names are hash-name nodes; object +0x0A points at one, characters at +0x0A.
"""

import struct

COMPILER_SHA256 = "f68a29252b1f79d820f36184912d2163082d4bb4c394559586bf7276878c6248"

DRIVER = 0x4333F0    # backend per-function driver; arg 2 is the function Object*
SIMPLIFY = 0x508D40
COLOR = 0x508C20
REWRITE = 0x508AF0
HOOK_BYTES = {DRIVER: b"\x53", SIMPLIFY: b"\x53", COLOR: b"\x53", REWRITE: b"\x53"}

GRAPH_TABLE = 0x5EA770      # InterferenceNode** indexed by virtual register
NODE_COUNT = 0x5EAA34       # int[class]: nodes in the active graph
PHYSICAL_COUNT = 0x5EA718   # int[class]: physical registers (first node index)
BLOCKED = 0x5E6B88          # byte[class][32]: physical registers unavailable
REGISTER_CLASS = 0x5EB2D7   # byte: class being allocated
BLOCK_LIST = 0x5EA750       # first PCode basic block of the function being compiled
SPILL_CUTOFF = 0x5E18A8     # int16: nodes at or above it are never chosen to spill

CLASS_NAMES = {3: "fpr", 4: "gpr"}

# PCode opcode -> mnemonic spellings, from SFA's GC/1.3 decoder (tools/tricky_backend_ir.py),
# whose numbering GC/2.5 shares: captured streams align with the emitted objects.
OPCODES = {
    0x00: "b", 0x01: "bl", 0x05: "beq+ beq- bgt+ bgt- blt+ blt- beqlr-",
    0x08: "bge+ bge- ble+ ble- bne+ bne- bgelr-", 0x0B: "bdnz+ bdnz-",
    0x11: "blr", 0x12: "bctr", 0x13: "bctrl", 0x15: "lbz",
    0x17: "lbzx", 0x19: "lhz", 0x1B: "lhzx", 0x1D: "lha", 0x1F: "lhax",
    0x22: "lwz", 0x24: "lwzx", 0x28: "stb", 0x2A: "stbx", 0x2C: "sth", 0x2E: "sthx",
    0x31: "stw", 0x32: "stwu", 0x33: "stwx", 0x3C: "add", 0x3D: "addc", 0x3E: "adde", 0x3F: "addi",
    0x42: "addis", 0x44: "addze", 0x45: "divw", 0x46: "divwu", 0x47: "mulhw", 0x48: "mulhwu", 0x49: "mulli", 0x4A: "mullw", 0x4B: "neg",
    0x4C: "subf", 0x4D: "subfc", 0x4E: "subfe", 0x4F: "subfic", 0x52: "cmpwi", 0x53: "cmpw",
    0x54: "cmplwi", 0x55: "cmplw", 0x56: "andi.", 0x58: "ori", 0x59: "oris", 0x5A: "xori",
    0x5B: "xoris", 0x5C: "and", 0x5D: "or", 0x5E: "xor", 0x62: "andc", 0x64: "extsb",
    0x65: "extsh", 0x66: "cntlzw", 0x67: "clrlwi clrrwi rlwinm rotlwi slwi srwi",
    0x69: "rlwimi", 0x6A: "slw", 0x6B: "srw", 0x6C: "srawi", 0x6D: "sraw", 0x70: "crset", 0x73: "cror",
    0x75: "crclr", 0x78: "mtctr", 0x79: "mtlr", 0x81: "mflr", 0x82: "mfcr",
    0x89: "li", 0x8A: "lis", 0x8B: "mr", 0x8D: "not", 0x8E: "lfs",
    0x90: "lfsx", 0x92: "lfd", 0x96: "stfs", 0x98: "stfsx", 0x9A: "stfd", 0x9E: "fmr", 0x9F: "fabs",
    0xA0: "fneg", 0xA2: "fadd", 0xA3: "fadds", 0xA4: "fsub", 0xA5: "fsubs", 0xA6: "fmul", 0xA7: "fmuls",
    0xA8: "fdiv", 0xA9: "fdivs", 0xAA: "fmadd", 0xAB: "fmadds", 0xAD: "fmsubs", 0xAF: "fnmadds",
    0xB0: "fnmsub", 0xB1: "fnmsubs", 0xB3: "frsqrte", 0xB5: "frsp", 0xB7: "fctiwz",
    0xB8: "fcmpu", 0xB9: "fcmpo", 0x193: "psq_l", 0x195: "psq_lx", 0x197: "psq_st", 0x199: "psq_stx",
}


def c_string(memory, address, limit=512):
    data = memory(address, limit)
    end = data.find(b"\0")
    if end < 0:
        raise ValueError("unterminated compiler string")
    return data[:end].decode("latin-1")


def object_name(memory, address):
    if not address:
        return None
    name_node = int.from_bytes(memory(address + 0x0A, 4), "little")
    return c_string(memory, name_node + 0x0A, 256) if name_node else None


def available_registers(memory, register_class):
    count = int.from_bytes(memory(PHYSICAL_COUNT + 4 * register_class, 4), "little", signed=True)
    blocked = memory(BLOCKED + 32 * register_class, count)
    return [index for index in range(count) if not blocked[index]]


def read_node(memory, address):
    (link, obj, _, spill, virtual, degree, physical, flags, count) = struct.unpack(
        "<IIIihhhHh", memory(address, 0x1A))
    neighbors = list(struct.unpack("<" + "h" * count, memory(address + 0x1A, 2 * count))) if count else []
    return {"address": address, "object": obj, "object_name": object_name(memory, obj),
            "spill_raw": spill, "virtual": virtual, "degree": degree, "physical": physical,
            "flags": flags, "neighbors": neighbors}


def read_graph(memory, register_class):
    table = int.from_bytes(memory(GRAPH_TABLE, 4), "little")
    count = int.from_bytes(memory(NODE_COUNT + 4 * register_class, 4), "little")
    if not 32 <= count <= 8192:
        raise ValueError(f"invalid graph size {count}")
    nodes = []
    for index in range(count):
        node = read_node(memory, int.from_bytes(memory(table + 4 * index, 4), "little"))
        if node["virtual"] != index:
            raise ValueError(f"graph node {index} reports register {node['virtual']}")
        nodes.append(node)
    return nodes


def read_spill_costs(memory, register_class):
    """Per-node spill cost (int at +0x0C), valid once simplify has computed them."""
    table = int.from_bytes(memory(GRAPH_TABLE, 4), "little")
    count = int.from_bytes(memory(NODE_COUNT + 4 * register_class, 4), "little")
    return [int.from_bytes(memory(int.from_bytes(memory(table + 4 * i, 4), "little") + 0x0C, 4), "little", signed=True)
            for i in range(count)]


def read_stack(memory, head):
    """Virtual registers in the order the color routine pops them."""
    order, seen = [], set()
    while head:
        if head in seen:
            raise ValueError("cycle in simplified node stack")
        seen.add(head)
        order.append(int.from_bytes(memory(head + 0x10, 2), "little", signed=True))
        head = int.from_bytes(memory(head, 4), "little")
    return order


def read_pcode(memory):
    """PCode blocks as [[(opcode, [operand, ...]), ...], ...].

    Block: word 0 next block, word 5 first instruction. Instruction: word 0
    next, word 8 opcode | operand count << 16, then 12-byte operands. A register
    operand is kind 0, class byte, int16 number (virtual before rewrite).
    """
    def words(address, count):
        return list(struct.unpack("<" + "I" * count, memory(address, 4 * count)))

    blocks, seen = [], set()
    block = int.from_bytes(memory(BLOCK_LIST, 4), "little")
    while block:
        if block in seen or len(blocks) > 4096:
            raise ValueError("cyclic PCode block chain")
        seen.add(block)
        instructions = []
        address = words(block, 6)[5]
        while address:
            if len(instructions) > 8192:
                raise ValueError("implausible PCode instruction chain")
            header = words(address, 9)
            count = header[8] >> 16
            if count > 64:
                raise ValueError("implausible PCode operand count")
            operands = []
            for index in range(count):
                raw = memory(address + 36 + 12 * index, 12)
                if raw[0] == 0:
                    operands.append({"kind": 0, "class": raw[1],
                                     "number": int.from_bytes(raw[4:6], "little", signed=True)})
                elif raw[0] == 2:
                    operands.append({"kind": 2, "value": int.from_bytes(raw[2:6], "little", signed=True)})
                else:
                    operands.append({"kind": raw[0]})
            instructions.append({"opcode": header[8] & 0xFFFF, "operands": operands})
            address = header[0]
        blocks.append(instructions)
        block = words(block, 1)[0]
    return blocks


def emulate_hook(pc, sp, ebx, word, write_word):
    """Return (esp, eip) after the replaced first instruction of a hook."""
    if not 4 <= sp <= 0xFFFFFFFB:
        raise ValueError("hook stack pointer is outside the 32-bit guest")
    if pc in (DRIVER, SIMPLIFY, COLOR, REWRITE):
        write_word(sp - 4, ebx & 0xFFFFFFFF)
        return sp - 4, pc + 1
    raise ValueError(f"unrecognized compiler hook {pc:#x}")
