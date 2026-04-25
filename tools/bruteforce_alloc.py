#!/usr/bin/env python3
"""
Brute-force source mutation tool for alloc.c allocate_from_fixed_pools.

Generates FixBlock_construct variants, compiles, diffs, and reports improvements.
The 6-diff problem: compiler sinks ths->start_=chunk past the loop after inlining.

Mutations target:
  - FixBlock_construct body (statement order, types, expressions, loop forms)
  - FixSubBlock_construct macro formulation
  - Call-site expression variations in allocate_from_fixed_pools
  - Parameter type combinations
"""

import itertools
import json
import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

ALLOC_SRC = "src/MSL_C/PPCEABI/bare/H/alloc.c"
UNIT = "main/MSL_C/PPCEABI/bare/H/alloc"
SYMBOL = "allocate_from_fixed_pools"
BEST_MATCH = 98.24  # current baseline

# Read the original file and split into zones
def read_source():
    with open(ALLOC_SRC) as f:
        return f.read()

def save_source(content):
    with open(ALLOC_SRC, "w") as f:
        f.write(content)

def build():
    """Returns True if build succeeds."""
    result = subprocess.run(["ninja"], capture_output=True, text=True, timeout=120)
    return result.returncode == 0

def diff_symbol():
    """Returns (match_percent, num_diffs, diff_indices) or None on failure."""
    result = subprocess.run(
        ["build/tools/objdiff-cli", "diff", "-p", ".", "-u", UNIT, "-o", "diff_brute.json", SYMBOL],
        capture_output=True, text=True, timeout=60
    )
    if result.returncode != 0:
        return None

    try:
        with open("diff_brute.json") as f:
            data = json.load(f)
        for sym in data.get("left", {}).get("symbols", []):
            if sym["name"] == SYMBOL:
                match_pct = sym.get("match_percent", 0)
                insns = sym.get("instructions", [])
                diffs = [
                    (i, insns[i])
                    for i in range(len(insns))
                    if insns[i].get("diff_kind", "MATCH") != "MATCH"
                ]
                diff_indices = [d[0] for d in diffs]
                return (match_pct, len(diffs), diff_indices)
    except Exception:
        pass
    return None


# ============================================================
# Mutation definitions
# ============================================================

# --- FixBlock_construct body variants ---

def gen_fbc_body(
    p_type="char*",
    np_type="char*",
    k_type="unsigned long",
    start_pos="before_loop",  # before_loop, after_n, after_client, after_link, after_loop, after_fsb_last
    n_alloc_pos="after_loop",  # after_loop, before_loop, after_start
    chunk_expr="chunk",       # chunk, (FixSubBlock*)(ths + 1), cast variants
    p_init="({p_type}){chunk_expr}",  # how p is initialized
    use_np=True,              # whether np temp exists
    loop_form="for_k",       # for_k, for_i_down, while_k
    fsb_macro=True,           # True=macro, False=direct assignments
    fix_size_expr="fix_pool_sizes[index] + 4",  # expression for fixSubBlock_size
    client_size_expr="fix_pool_sizes[index]",   # expression for client_size_
    two_fix_lookups=True,     # True=two lookups, False=one lookup+derive
    extra_cast_p=False,       # cast p in FixSubBlock_construct
    chunk_param_type="FixSubBlock*",  # parameter type for chunk
):
    lines = []

    # Variable declarations
    lines.append(f"    unsigned long fixSubBlock_size;")
    lines.append(f"    unsigned long n;")
    lines.append(f"    {p_type} p;")
    if loop_form == "for_k":
        lines.append(f"    {k_type} k;")
    if use_np:
        lines.append(f"    {np_type} np;")
    lines.append(f"")

    # Link statements (always first)
    lines.append(f"    ths->prev_ = prev;")
    lines.append(f"    ths->next_ = next;")
    lines.append(f"    prev->next_ = ths;")
    lines.append(f"    next->prev_ = ths;")

    if start_pos == "after_link":
        lines.append(f"    ths->start_ = {chunk_expr};")

    # client_size and fixSubBlock_size
    if two_fix_lookups:
        lines.append(f"    ths->client_size_ = {client_size_expr};")
        lines.append(f"    fixSubBlock_size = {fix_size_expr};")
    else:
        lines.append(f"    ths->client_size_ = {client_size_expr};")
        lines.append(f"    fixSubBlock_size = ths->client_size_ + 4;")

    if start_pos == "after_client":
        lines.append(f"    ths->start_ = {chunk_expr};")

    # n calculation
    lines.append(f"    n = chunk_size / fixSubBlock_size;")

    if start_pos == "after_n":
        lines.append(f"    ths->start_ = {chunk_expr};")

    if n_alloc_pos == "before_loop":
        lines.append(f"    ths->n_allocated_ = 0;")

    if start_pos == "before_loop":
        lines.append(f"    ths->start_ = {chunk_expr};")

    # p initialization
    p_init_str = p_init.format(p_type=p_type, chunk_expr=chunk_expr)
    lines.append(f"    p = {p_init_str};")

    # Generate the FixSubBlock_construct call
    def fsb_call(ptr_expr, block_expr, next_expr):
        if fsb_macro:
            if extra_cast_p:
                return f"        FixSubBlock_construct(({p_type}){ptr_expr}, {block_expr}, {next_expr});"
            else:
                return f"        FixSubBlock_construct({ptr_expr}, {block_expr}, {next_expr});"
        else:
            return (
                f"        ((FixSubBlock*)({ptr_expr}))->block_ = {block_expr};\n"
                f"        ((FixSubBlock*)({ptr_expr}))->next_ = {next_expr};"
            )

    # Loop body
    if use_np:
        loop_body = f"        np = p + fixSubBlock_size;\n"
        loop_body += fsb_call("p", "ths", f"(FixSubBlock*)np") + "\n"
        loop_body += f"        p = np;"
    else:
        loop_body = fsb_call("p", "ths", f"(FixSubBlock*)(p + fixSubBlock_size)") + "\n"
        loop_body += f"        p = p + fixSubBlock_size;"

    if loop_form == "for_k":
        lines.append(f"    for (k = 0; k < n - 1; k++) {{")
        lines.append(loop_body)
        lines.append(f"    }}")
    elif loop_form == "for_i_down":
        lines.append(f"    for (k = n - 1; k != 0; k--) {{")
        lines.append(loop_body)
        lines.append(f"    }}")
    elif loop_form == "while_k":
        lines.append(f"    k = 0;")
        lines.append(f"    while (k < n - 1) {{")
        lines.append(loop_body)
        lines.append(f"        k++;")
        lines.append(f"    }}")

    if start_pos == "after_loop":
        lines.append(f"    ths->start_ = {chunk_expr};")

    # Last FixSubBlock_construct (terminator)
    last_fsb = fsb_call("p", "ths", "0").lstrip()
    lines.append(f"    {last_fsb}")

    if start_pos == "after_fsb_last":
        lines.append(f"    ths->start_ = {chunk_expr};")

    if n_alloc_pos == "after_loop" or n_alloc_pos == "after_start":
        lines.append(f"    ths->n_allocated_ = 0;")

    return "\n".join(lines)


def gen_fbc_function(body_code, func_linkage="", chunk_param_type="FixSubBlock*"):
    return (
        f"{func_linkage}void FixBlock_construct(FixBlock* ths, FixBlock* prev, FixBlock* next, "
        f"unsigned long index, {chunk_param_type} chunk, unsigned long chunk_size) {{\n"
        f"{body_code}\n"
        f"}}"
    )


def gen_callsite(chunk_cast="(FixSubBlock*)((char*)block + 0x14)", size_expr="msize - 0x14"):
    return (
        f"        FixBlock_construct((FixBlock*)block, fs->tail_, fs->head_, i, "
        f"{chunk_cast}, {size_expr});"
    )


# --- FixSubBlock_construct macro variants ---
FSB_MACROS = {
    "baseline": (
        '#define FixSubBlock_construct(ths, block, next) \\\n'
        '    (((FixSubBlock*)(ths))->block_ = (block), ((FixSubBlock*)(ths))->next_ = (next))'
    ),
    "no_outer_parens": (
        '#define FixSubBlock_construct(ths, block, next) \\\n'
        '    ((FixSubBlock*)(ths))->block_ = (block), ((FixSubBlock*)(ths))->next_ = (next)'
    ),
    "separate_stmts": (
        '#define FixSubBlock_construct(ths, block, next) do { \\\n'
        '    ((FixSubBlock*)(ths))->block_ = (block); \\\n'
        '    ((FixSubBlock*)(ths))->next_ = (next); \\\n'
        '} while(0)'
    ),
    "reverse_order": (
        '#define FixSubBlock_construct(ths, block, next) \\\n'
        '    (((FixSubBlock*)(ths))->next_ = (next), ((FixSubBlock*)(ths))->block_ = (block))'
    ),
    "void_cast_block": (
        '#define FixSubBlock_construct(ths, block, next) \\\n'
        '    (((FixSubBlock*)(ths))->block_ = (FixBlock*)(void*)(block), ((FixSubBlock*)(ths))->next_ = (next))'
    ),
}


def gen_custom_body(custom_id, v):
    """Generate custom body variants for creative mutations."""
    start_pos = v.get("start_pos", "before_loop")

    if custom_id.startswith("client_from_fixsub_"):
        # client_size_ derived from fixSubBlock_size - 4
        lines = []
        lines.append("    unsigned long fixSubBlock_size;")
        lines.append("    unsigned long n;")
        lines.append("    char* p;")
        lines.append("    unsigned long k;")
        lines.append("    char* np;")
        lines.append("")
        lines.append("    ths->prev_ = prev;")
        lines.append("    ths->next_ = next;")
        lines.append("    prev->next_ = ths;")
        lines.append("    next->prev_ = ths;")
        lines.append("    fixSubBlock_size = fix_pool_sizes[index] + 4;")
        lines.append("    ths->client_size_ = fixSubBlock_size - 4;")
        lines.append("    n = chunk_size / fixSubBlock_size;")
        if start_pos == "before_loop":
            lines.append("    ths->start_ = chunk;")
        lines.append("    p = (char*)chunk;")
        lines.append("    for (k = 0; k < n - 1; k++) {")
        lines.append("        np = p + fixSubBlock_size;")
        lines.append("        FixSubBlock_construct(p, ths, (FixSubBlock*)np);")
        lines.append("        p = np;")
        lines.append("    }")
        if start_pos == "after_loop":
            lines.append("    ths->start_ = chunk;")
        lines.append("    FixSubBlock_construct(p, ths, 0);")
        if start_pos == "after_fsb_last":
            lines.append("    ths->start_ = chunk;")
        lines.append("    ths->n_allocated_ = 0;")
        return "\n".join(lines)

    elif custom_id.startswith("void_temp_start_"):
        # Store chunk to a void* temp first, then assign to start_
        lines = []
        lines.append("    unsigned long fixSubBlock_size;")
        lines.append("    unsigned long n;")
        lines.append("    char* p;")
        lines.append("    unsigned long k;")
        lines.append("    char* np;")
        lines.append("    void* start_tmp;")
        lines.append("")
        lines.append("    ths->prev_ = prev;")
        lines.append("    ths->next_ = next;")
        lines.append("    prev->next_ = ths;")
        lines.append("    next->prev_ = ths;")
        lines.append("    ths->client_size_ = fix_pool_sizes[index];")
        lines.append("    fixSubBlock_size = fix_pool_sizes[index] + 4;")
        lines.append("    n = chunk_size / fixSubBlock_size;")
        lines.append("    start_tmp = (void*)chunk;")
        if start_pos == "before_loop":
            lines.append("    ths->start_ = (FixSubBlock*)start_tmp;")
        lines.append("    p = (char*)start_tmp;")
        lines.append("    for (k = 0; k < n - 1; k++) {")
        lines.append("        np = p + fixSubBlock_size;")
        lines.append("        FixSubBlock_construct(p, ths, (FixSubBlock*)np);")
        lines.append("        p = np;")
        lines.append("    }")
        if start_pos == "after_loop":
            lines.append("    ths->start_ = (FixSubBlock*)start_tmp;")
        lines.append("    FixSubBlock_construct(p, ths, 0);")
        if start_pos == "after_fsb_last":
            lines.append("    ths->start_ = (FixSubBlock*)start_tmp;")
        lines.append("    ths->n_allocated_ = 0;")
        return "\n".join(lines)

    elif custom_id.startswith("local_head_tail_"):
        # Standard body; the "creative" part is caller-side, handled separately
        return gen_fbc_body(
            start_pos=start_pos,
            p_type="char*",
            chunk_expr="chunk",
            p_init="({p_type}){chunk_expr}",
            use_np=True,
            two_fix_lookups=True,
        )

    return None


def apply_variant(original_source, fbc_func_str, callsite_str, fsb_macro_str=None):
    """Replace the FixBlock_construct function and callsite in the source."""
    src = original_source

    # Replace FixBlock_construct function (find start and end)
    fbc_start_markers = [
        "void FixBlock_construct(",
        "static void FixBlock_construct(",
        "inline void FixBlock_construct(",
    ]

    for marker in fbc_start_markers:
        idx = src.find(marker)
        if idx != -1:
            # Find preceding newline
            line_start = src.rfind("\n", 0, idx)
            if line_start == -1:
                line_start = 0
            else:
                line_start += 1

            # Find the closing brace
            brace_depth = 0
            found_open = False
            end_idx = idx
            while end_idx < len(src):
                if src[end_idx] == '{':
                    brace_depth += 1
                    found_open = True
                elif src[end_idx] == '}':
                    brace_depth -= 1
                    if found_open and brace_depth == 0:
                        end_idx += 1
                        break
                end_idx += 1

            src = src[:line_start] + fbc_func_str + "\n" + src[end_idx:]
            break

    # Replace callsite
    callsite_markers = [
        "        FixBlock_construct((FixBlock*)block,",
    ]
    for marker in callsite_markers:
        idx = src.find(marker)
        if idx != -1:
            end_idx = src.find(";", idx)
            if end_idx != -1:
                src = src[:idx] + callsite_str + src[end_idx + 1:]
            break

    # Replace FixSubBlock_construct macro if given
    if fsb_macro_str is not None:
        old_macro_start = src.find("#define FixSubBlock_construct(")
        if old_macro_start != -1:
            # Find end of macro (last line not ending with \)
            pos = old_macro_start
            while pos < len(src):
                line_end = src.find("\n", pos)
                if line_end == -1:
                    line_end = len(src)
                line = src[pos:line_end]
                if not line.rstrip().endswith("\\"):
                    # This is the last line of the macro
                    src = src[:old_macro_start] + fsb_macro_str + src[line_end:]
                    break
                pos = line_end + 1

    return src


def generate_variants():
    """Generate all variant parameter combinations."""
    variants = []

    # =========================================
    # Phase 1: Core body variations (most impactful)
    # =========================================
    start_positions = ["before_loop", "after_n", "after_client", "after_link", "after_loop", "after_fsb_last"]
    n_alloc_positions = ["after_loop", "before_loop"]
    p_types = ["char*", "void*", "FixSubBlock*"]
    chunk_exprs = ["chunk", "(FixSubBlock*)(ths + 1)"]
    p_inits = [
        "({p_type}){chunk_expr}",
        "({p_type})ths->start_",
    ]
    use_nps = [True, False]
    two_fix_lookupss = [True, False]

    for start_pos in start_positions:
        for p_type in p_types:
            for chunk_expr in chunk_exprs:
                for p_init in p_inits:
                    for use_np in use_nps:
                        for two_fix in two_fix_lookupss:
                            for n_alloc_pos in n_alloc_positions:
                                variants.append({
                                    "start_pos": start_pos,
                                    "p_type": p_type,
                                    "chunk_expr": chunk_expr,
                                    "p_init": p_init,
                                    "use_np": use_np,
                                    "two_fix": two_fix,
                                    "n_alloc_pos": n_alloc_pos,
                                    "fsb_macro": "baseline",
                                    "chunk_param_type": "FixSubBlock*",
                                    "func_linkage": "",
                                    "callsite_chunk": "(FixSubBlock*)((char*)block + 0x14)",
                                    "callsite_size": "msize - 0x14",
                                    "loop_form": "for_k",
                                })

    # =========================================
    # Phase 2: FSB macro variants × start positions
    # =========================================
    fsb_macros_to_try = ["no_outer_parens", "separate_stmts", "reverse_order", "void_cast_block"]
    for fsb_macro in fsb_macros_to_try:
        for start_pos in start_positions:
            for use_np in [True, False]:
                variants.append({
                    "start_pos": start_pos,
                    "p_type": "char*",
                    "chunk_expr": "chunk",
                    "p_init": "({p_type}){chunk_expr}",
                    "use_np": use_np,
                    "two_fix": True,
                    "n_alloc_pos": "after_loop",
                    "fsb_macro": fsb_macro,
                    "chunk_param_type": "FixSubBlock*",
                    "func_linkage": "",
                    "callsite_chunk": "(FixSubBlock*)((char*)block + 0x14)",
                    "callsite_size": "msize - 0x14",
                    "loop_form": "for_k",
                })

    # =========================================
    # Phase 3: Callsite and linkage variations
    # =========================================
    chunk_param_types = ["FixSubBlock*", "char*", "void*"]
    func_linkages = ["", "static "]
    callsite_chunks = [
        "(FixSubBlock*)((char*)block + 0x14)",
        "(FixSubBlock*)((char*)block + sizeof(FixBlock))",
    ]
    callsite_size_exprs = [
        "msize - 0x14",
        "msize - sizeof(FixBlock)",
    ]
    for chunk_param_type in chunk_param_types:
        for func_linkage in func_linkages:
            for callsite_chunk in callsite_chunks:
                for callsite_size in callsite_size_exprs:
                    for start_pos in start_positions:
                        variants.append({
                            "start_pos": start_pos,
                            "p_type": "char*",
                            "chunk_expr": "chunk",
                            "p_init": "({p_type}){chunk_expr}",
                            "use_np": True,
                            "two_fix": True,
                            "n_alloc_pos": "after_loop",
                            "fsb_macro": "baseline",
                            "chunk_param_type": chunk_param_type,
                            "func_linkage": func_linkage,
                            "callsite_chunk": callsite_chunk,
                            "callsite_size": callsite_size,
                            "loop_form": "for_k",
                        })

    # =========================================
    # Phase 4: Creative / unusual patterns
    # These test ideas not covered by the matrix above
    # =========================================
    creative = []

    # 4a: What if client_size_ is computed from the param, not the array?
    # i.e. fixSubBlock_size = chunk_size_param_related, client_size_ = fixSubBlock_size - 4
    for start_pos in start_positions:
        creative.append({
            "start_pos": start_pos,
            "p_type": "char*",
            "chunk_expr": "chunk",
            "p_init": "({p_type}){chunk_expr}",
            "use_np": True,
            "two_fix": True,  # will be overridden by custom body
            "n_alloc_pos": "after_loop",
            "fsb_macro": "baseline",
            "chunk_param_type": "FixSubBlock*",
            "func_linkage": "",
            "callsite_chunk": "(FixSubBlock*)((char*)block + 0x14)",
            "callsite_size": "msize - 0x14",
            "loop_form": "for_k",
            "custom_body": True,
            "custom_id": f"client_from_fixsub_{start_pos}",
        })

    # 4b: What if the loop uses unsigned int k instead of unsigned long?
    for k_type in ["unsigned int", "int", "long"]:
        for start_pos in ["before_loop", "after_n"]:
            creative.append({
                "start_pos": start_pos,
                "p_type": "char*",
                "chunk_expr": "chunk",
                "p_init": "({p_type}){chunk_expr}",
                "use_np": True,
                "two_fix": True,
                "n_alloc_pos": "after_loop",
                "fsb_macro": "baseline",
                "chunk_param_type": "FixSubBlock*",
                "func_linkage": "",
                "callsite_chunk": "(FixSubBlock*)((char*)block + 0x14)",
                "callsite_size": "msize - 0x14",
                "loop_form": "for_k",
                "k_type_override": k_type,
            })

    # 4c: What if FixSubBlock* chunk param but stored to start_ via a void* temp?
    for start_pos in start_positions:
        creative.append({
            "start_pos": start_pos,
            "p_type": "char*",
            "chunk_expr": "chunk",
            "p_init": "({p_type}){chunk_expr}",
            "use_np": True,
            "two_fix": True,
            "n_alloc_pos": "after_loop",
            "fsb_macro": "baseline",
            "chunk_param_type": "FixSubBlock*",
            "func_linkage": "",
            "callsite_chunk": "(FixSubBlock*)((char*)block + 0x14)",
            "callsite_size": "msize - 0x14",
            "loop_form": "for_k",
            "custom_body": True,
            "custom_id": f"void_temp_start_{start_pos}",
        })

    # 4d: n and fixSubBlock_size as int instead of unsigned long
    for n_type in ["int", "unsigned int"]:
        for start_pos in ["before_loop", "after_n"]:
            creative.append({
                "start_pos": start_pos,
                "p_type": "char*",
                "chunk_expr": "chunk",
                "p_init": "({p_type}){chunk_expr}",
                "use_np": True,
                "two_fix": True,
                "n_alloc_pos": "after_loop",
                "fsb_macro": "baseline",
                "chunk_param_type": "FixSubBlock*",
                "func_linkage": "",
                "callsite_chunk": "(FixSubBlock*)((char*)block + 0x14)",
                "callsite_size": "msize - 0x14",
                "loop_form": "for_k",
                "n_type_override": n_type,
            })

    # 4e: What if the caller stores fs->head_ to a local before passing to construct?
    for start_pos in ["before_loop", "after_n"]:
        creative.append({
            "start_pos": start_pos,
            "p_type": "char*",
            "chunk_expr": "chunk",
            "p_init": "({p_type}){chunk_expr}",
            "use_np": True,
            "two_fix": True,
            "n_alloc_pos": "after_loop",
            "fsb_macro": "baseline",
            "chunk_param_type": "FixSubBlock*",
            "func_linkage": "",
            "callsite_chunk": "(FixSubBlock*)((char*)block + 0x14)",
            "callsite_size": "msize - 0x14",
            "loop_form": "for_k",
            "custom_body": True,
            "custom_id": f"local_head_tail_{start_pos}",
        })

    variants.extend(creative)
    return variants


def variant_key(v):
    """Create a hashable key for deduplication."""
    return tuple(sorted(v.items()))


def main():
    quick_mode = "--quick" in sys.argv
    skip_to = 0
    for arg in sys.argv[1:]:
        if arg.startswith("--skip="):
            skip_to = int(arg.split("=")[1])

    if not os.path.exists(ALLOC_SRC):
        print(f"Error: {ALLOC_SRC} not found. Run from repo root.")
        sys.exit(1)

    original_source = read_source()

    # Backup
    backup_path = ALLOC_SRC + ".bruteforce_backup"
    if not os.path.exists(backup_path):
        shutil.copy2(ALLOC_SRC, backup_path)
        print(f"Backed up to {backup_path}")
    else:
        # Restore from backup to ensure clean state
        with open(backup_path) as f:
            original_source = f.read()
        save_source(original_source)

    variants = generate_variants()

    # Deduplicate
    seen = set()
    unique_variants = []
    for v in variants:
        k = variant_key(v)
        if k not in seen:
            seen.add(k)
            unique_variants.append(v)
    variants = unique_variants

    if quick_mode:
        # Quick mode: only test start_pos and a few key variations
        quick = []
        for v in variants:
            if v.get("custom_id"):
                quick.append(v)
            elif (v["p_type"] == "char*" and v["chunk_expr"] == "chunk" and
                  v["use_np"] and v["two_fix"] and
                  v["fsb_macro"] == "baseline" and
                  v["n_alloc_pos"] == "after_loop" and
                  v["chunk_param_type"] == "FixSubBlock*" and
                  v["func_linkage"] == ""):
                quick.append(v)
        variants = quick
        print(f"Quick mode: {len(variants)} variants")

    print(f"Generated {len(variants)} unique variants to test")
    print(f"Estimated time: {len(variants) * 15 / 60:.0f} minutes at ~15s/variant")
    print(f"Current best: {BEST_MATCH}%")
    if skip_to > 0:
        print(f"Skipping to variant {skip_to}")
    print()

    best_match = BEST_MATCH
    best_variant = None
    results = []
    start_time = time.time()
    build_failures = 0

    try:
        for idx, v in enumerate(variants):
            if idx < skip_to:
                continue

            elapsed = time.time() - start_time
            rate = (idx / elapsed * 60) if elapsed > 0 and idx > 0 else 0
            eta_min = ((len(variants) - idx) / rate) if rate > 0 else 0

            try:
                # Check for custom body
                custom_id = v.get("custom_id")
                if custom_id:
                    body = gen_custom_body(custom_id, v)
                    if body is None:
                        continue
                else:
                    k_type = v.get("k_type_override", "unsigned long")
                    body = gen_fbc_body(
                        p_type=v["p_type"],
                        np_type=v["p_type"],
                        k_type=k_type,
                        start_pos=v["start_pos"],
                        n_alloc_pos=v["n_alloc_pos"],
                        chunk_expr=v["chunk_expr"],
                        p_init=v["p_init"],
                        use_np=v["use_np"],
                        loop_form=v["loop_form"],
                        fsb_macro=True,
                        fix_size_expr="fix_pool_sizes[index] + 4",
                        client_size_expr="fix_pool_sizes[index]",
                        two_fix_lookups=v["two_fix"],
                        chunk_param_type=v["chunk_param_type"],
                    )

                    # Apply n_type override if present
                    n_type = v.get("n_type_override")
                    if n_type:
                        body = body.replace("    unsigned long fixSubBlock_size;",
                                           f"    {n_type} fixSubBlock_size;")
                        body = body.replace("    unsigned long n;",
                                           f"    {n_type} n;")

                func_str = gen_fbc_function(
                    body,
                    func_linkage=v["func_linkage"],
                    chunk_param_type=v["chunk_param_type"],
                )

                # Adjust callsite cast based on chunk_param_type
                cc = v["callsite_chunk"]
                if v["chunk_param_type"] == "char*":
                    cc = "(char*)block + 0x14" if "0x14" in v["callsite_chunk"] else "(char*)block + sizeof(FixBlock)"
                elif v["chunk_param_type"] == "void*":
                    cc = "(void*)((char*)block + 0x14)" if "0x14" in v["callsite_chunk"] else "(void*)((char*)block + sizeof(FixBlock))"

                callsite_str = gen_callsite(
                    chunk_cast=cc,
                    size_expr=v["callsite_size"],
                )

                fsb_macro_str = FSB_MACROS.get(v["fsb_macro"])
                if v["fsb_macro"] == "baseline":
                    fsb_macro_str = None

                src = apply_variant(original_source, func_str, callsite_str, fsb_macro_str)
                save_source(src)

            except Exception as e:
                print(f"[{idx+1}/{len(variants)}] SKIP (gen error: {e})")
                continue

            if not build():
                build_failures += 1
                print(f"[{idx+1}/{len(variants)}] SKIP (build fail) [{rate:.1f}/min, ETA {eta_min:.0f}m]")
                continue

            result = diff_symbol()
            if result is None:
                print(f"[{idx+1}/{len(variants)}] SKIP (diff fail)")
                continue

            match_pct, num_diffs, diff_indices = result
            results.append((match_pct, num_diffs, v))

            marker = ""
            if match_pct > best_match:
                best_match = match_pct
                best_variant = v
                marker = " *** NEW BEST ***"
                shutil.copy2(ALLOC_SRC, ALLOC_SRC + f".best_{match_pct:.2f}")
            elif match_pct > BEST_MATCH:
                marker = " (better than baseline)"

            if match_pct != BEST_MATCH or idx % 50 == 0:
                desc_parts = [f"start={v['start_pos']}", f"p={v['p_type']}"]
                if v.get('custom_id'):
                    desc_parts.append(f"custom={v['custom_id'][:30]}")
                else:
                    desc_parts.extend([f"chunk={v['chunk_expr'][:15]}", f"fix2={v['two_fix']}"])
                if v['fsb_macro'] != 'baseline':
                    desc_parts.append(f"fsb={v['fsb_macro'][:12]}")
                if v['chunk_param_type'] != 'FixSubBlock*':
                    desc_parts.append(f"cptype={v['chunk_param_type']}")
                if v['func_linkage']:
                    desc_parts.append(f"link={v['func_linkage'].strip()}")
                desc = ", ".join(desc_parts)
                print(f"[{idx+1}/{len(variants)}] {match_pct:.2f}% ({num_diffs} diffs) {desc}{marker} [{rate:.1f}/min, ETA {eta_min:.0f}m]")

            if match_pct >= 100.0:
                print(f"\n*** PERFECT MATCH FOUND! ***")
                break

    except KeyboardInterrupt:
        print(f"\n\nInterrupted at variant {idx+1}/{len(variants)}. Resume with --skip={idx}")

    # Restore original
    save_source(original_source)
    print(f"\nRestored original source.")

    # Report
    print(f"\n{'='*60}")
    print(f"RESULTS: Tested {len(results)} variants in {(time.time()-start_time)/60:.1f} minutes")
    print(f"Build failures: {build_failures}")
    print(f"Best match: {best_match:.2f}%")

    if best_variant:
        print(f"Best variant: {best_variant}")
        best_file = ALLOC_SRC + f".best_{best_match:.2f}"
        if os.path.exists(best_file):
            print(f"Best source saved to: {best_file}")

    results.sort(key=lambda x: (-x[0], x[1]))
    seen_pcts = set()
    print(f"\nTop results:")
    for match_pct, num_diffs, v in results:
        if match_pct not in seen_pcts:
            seen_pcts.add(match_pct)
            print(f"  {match_pct:.2f}% ({num_diffs} diffs): {v}")
            if len(seen_pcts) >= 10:
                break


if __name__ == "__main__":
    main()
