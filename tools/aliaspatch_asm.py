#!/usr/bin/env python3
"""Assemble the seven register-marshalling stubs that reach AliasPatch.c.

The C blob computes the clause predicates; these stubs stand at the dispatch
sites, hand the query to the right predicate in cdecl form, and act on its
answer -- jumping to the compiler's own "may alias" answer tail on a hit, or
falling through into the compiler's own stock test on a miss. No stock logic is
reassembled here: every miss lands on original bytes.

Only the handful of instruction forms the stubs use are encoded, by a tiny
two-pass assembler keyed on symbolic labels and absolute targets. Each builder
returns raw bytes for a stub placed at a known VA, given the resolved VAs of
the C entry points and the compiler's fixed answer/stock addresses.
"""
import struct


def _rel32(frm_end, to):
    return struct.pack("<i", to - frm_end)


# Fixed VAs in mwcceppc.exe reached by the stubs.
MAY_ALIAS_ANSWER = 0x00512081      # mov ebx,1; jmp epilogue  (may_alias)
STOCK_E0         = 0x00511FF2      # a == b
STOCK_E1_E3      = 0x00511FFF      # a->object == b->object
STOCK_E4         = 0x00512012      # same object and overlapping
VN_STOCK_KILL    = 0x00511A53      # AliasType0 whole-object kill
VN_STOCK_KILL_E1 = 0x00511B0E      # AliasType1 subrange kill
ISLOOPINVARIANT  = 0x00570F60      # CodeMotion isloopinvariant(pcode, loop, vec, f1, f2)


def sched_stub(at, sb_sched_clause, entry, stock_target):
    """may_alias entries 0/1/3/4. esi=a, ebp=b, eax=a->alias, edx=b->alias.
       On a hit -> MAY_ALIAS_ANSWER; on a miss reload eax/edx and jmp stock."""
    b = bytearray()
    b += bytes((0x6A, entry))              # push entry
    b += b"\x55"                           # push ebp   (b)
    b += b"\x56"                           # push esi   (a)
    b += b"\xE8"; b += _rel32(at + len(b) + 4, sb_sched_clause)   # call sb_sched_clause
    b += b"\x83\xC4\x0C"                   # add esp,0xc
    b += b"\x85\xC0"                       # test eax,eax
    b += b"\x0F\x85"; b += _rel32(at + len(b) + 4, MAY_ALIAS_ANSWER)  # jnz answer
    b += b"\x8B\x46\x18"                   # mov eax,[esi+0x18]
    b += b"\x8B\x55\x18"                   # mov edx,[ebp+0x18]
    b += b"\xE9"; b += _rel32(at + len(b) + 4, stock_target)      # jmp stock
    return bytes(b)


def vn_stub(at, sb_vn_store_kill, alias_list_head_va):
    """update_alias_value entry 0. ebx=alias, esi=stored value.
       Load *alias_list_head_va PC-relatively, pass (alias, head). Return 1 ->
       zero esi (clause F). Always fall into the stock kill."""
    b = bytearray()
    b += b"\xE8\x00\x00\x00\x00"           # call $+5
    pop_va = at + len(b)                   # VA of the pop = value left in ecx
    b += b"\x59"                           # pop ecx
    b += b"\x8B\x89"; b += struct.pack("<i", alias_list_head_va - pop_va)   # mov ecx,[ecx+disp]
    b += b"\x51"                           # push ecx   (list_head, arg2)
    b += b"\x53"                           # push ebx   (alias, arg1)
    b += b"\xE8"; b += _rel32(at + len(b) + 4, sb_vn_store_kill)  # call sb_vn_store_kill
    b += b"\x83\xC4\x08"                   # add esp,8
    b += b"\x85\xC0"                       # test eax,eax
    b += b"\x7E\x02"                       # jle +2   (ret 0 or -1 -> no F)
    b += b"\x31\xF6"                       # xor esi,esi   (clause F)
    b += b"\xE9"; b += _rel32(at + len(b) + 4, VN_STOCK_KILL)     # jmp stock kill
    return bytes(b)


def vn_subrange_stub(at, sb_vn_subrange_store, alias_list_head_va):
    """update_alias_value entry 1. ebx=alias, esi=store PCode. Pass (alias,
       store, head). Return 1 -> zero esi (clause S's forwarding half). Always
       fall into the stock subrange kill."""
    b = bytearray()
    b += b"\xE8\x00\x00\x00\x00"           # call $+5
    pop_va = at + len(b)                   # VA of the pop = value left in ecx
    b += b"\x59"                           # pop ecx
    b += b"\x8B\x89"; b += struct.pack("<i", alias_list_head_va - pop_va)   # mov ecx,[ecx+disp]
    b += b"\x51"                           # push ecx   (list_head, arg3)
    b += b"\x56"                           # push esi   (store, arg2)
    b += b"\x53"                           # push ebx   (alias, arg1)
    b += b"\xE8"; b += _rel32(at + len(b) + 4, sb_vn_subrange_store)
    b += b"\x83\xC4\x0C"                   # add esp,0xc
    b += b"\x85\xC0"                       # test eax,eax
    b += b"\x74\x02"                       # jz +2
    b += b"\x31\xF6"                       # xor esi,esi
    b += b"\xE9"; b += _rel32(at + len(b) + 4, VN_STOCK_KILL_E1)   # jmp stock kill
    return bytes(b)


def licm_invariant_stub(at, sb_licm_invariant):
    """Stands in for isloopinvariant at moveinvariantsfromloop's call site
       (0x56f472) only. cdecl: [esp+4] is the pcode and the caller cleans its
       five args, so a bare `ret` hands 0 back. Hit -> return 0 (not
       invariant). Miss -> tail-jump into the stock isloopinvariant with the
       caller's frame untouched."""
    b = bytearray()
    b += b"\x8B\x44\x24\x04"               # mov eax,[esp+4]   (pcode)
    b += b"\x50"                           # push eax
    b += b"\xE8"; b += _rel32(at + len(b) + 4, sb_licm_invariant)   # call sb_licm_invariant
    b += b"\x59"                           # pop ecx
    b += b"\x85\xC0"                       # test eax,eax
    b += b"\x74\x03"                       # jz stock
    b += b"\x31\xC0"                       # xor eax,eax
    b += b"\xC3"                           # ret            (not invariant)
    b += b"\xE9"; b += _rel32(at + len(b) + 4, ISLOOPINVARIANT)     # stock: jmp isloopinvariant
    return bytes(b)
