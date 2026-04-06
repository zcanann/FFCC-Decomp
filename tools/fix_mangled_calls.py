#!/usr/bin/env python3
"""
Replace mangled ppp function calls with proper C++ names.
v4 - Ultra-conservative: only safe renames, no type changes, handles extern "C" blocks.

Strategy:
- pppCalcFrameShape: signatures identical, safe rename
- pppSetBlendMode: simple unsigned char, safe rename  
- pppDrawShp (both overloads): signatures identical in header-including files, safe rename
- Deref functions (pppCopyVector, pppUnitMatrix, etc.): safe for files that pass &var args
- pppSetDrawEnv, pppMemAlloc, pppHeapUseRate: SKIPPED (void* vs typed args at call sites)
- pppNormalize, pppVectorLength, pppGetRotMatrixXYZ: SKIPPED (type mismatches)
- Remove redundant variable externs when header provides them
- Remove redundant pppCreatePObject extern when pppPart.h is included
"""

import re
import os
import sys

# Simple renames: mangled → cpp_name
# These have identical signatures between extern "C" and header
SAFE_SIMPLE_RENAMES = {
    'pppCalcFrameShape__FPlRsRsRss': 'pppCalcFrameShape',
    'pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff': 'pppHitCylinderSendSystem',
}

# These also need the extern "C" wrapper removed from blocks
SAFE_EXTERNS_TO_REMOVE_FROM_BLOCKS = set(SAFE_SIMPLE_RENAMES.keys()) | {
    # Also remove these from extern "C" blocks even if we don't rename call sites:
    'pppSetBlendMode',  # unmangled in blocks
}

# Deref renames: call sites use &var style args that naturally deref to reference
DEREF_RENAMES = {
    'pppUnitMatrix__FR10pppFMATRIX': 'pppUnitMatrix',
    'pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX': 'pppCopyMatrix',
    'pppCopyVector__FR3Vec3Vec': 'pppCopyVector',
    'pppAddVector__FR3Vec3Vec3Vec': 'pppAddVector',
    'pppSubVector__FR3Vec3Vec3Vec': 'pppSubVector',
    'pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX': 'pppMulMatrix',
}

# All mangled names we want to remove from extern blocks/declarations
# ONLY include names that we also rename at call sites (or that the included
# header provides), to avoid leaving call sites referencing removed externs.
ALL_REMOVABLE_MANGLED = (
    set(SAFE_SIMPLE_RENAMES.keys()) |
    set(DEREF_RENAMES.keys()) |
    {
        # These are removed from externs AND renamed at call sites
        'pppSetBlendMode__FUc',
    }
)

# Also rename these at call sites (in addition to removing externs)
ALSO_RENAME_CALLSITES = {
    'pppSetBlendMode__FUc': 'pppSetBlendMode',
}

# Files that CANNOT include pppPart.h (local struct conflicts)
CANNOT_ADD_PPPPART = {
    'pppYmDrawMdlTexAnm.cpp',
    'pppYmDeformationMdl.cpp',
    'pppYmDeformationScreen.cpp',
}

PPPPART_FUNCTIONS = {
    'pppUnitMatrix', 'pppCopyMatrix', 'pppCopyVector', 'pppAddVector',
    'pppSubVector', 'pppMulMatrix', 'pppSetBlendMode',
    'pppCreatePObject', 'pppHitCylinderSendSystem',
}

PPPSHAPE_FUNCTIONS = {
    'pppDrawShp', 'pppCalcFrameShape',
}


def split_args(s):
    args, depth, cur = [], 0, []
    for ch in s:
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        if ch == ',' and depth == 0:
            args.append(''.join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if cur:
        args.append(''.join(cur).strip())
    return [a for a in args if a]


def deref_arg(arg):
    """Convert &x → x, ptr → *ptr."""
    arg = arg.strip()
    if arg.startswith('&') and not arg.startswith('&&'):
        return arg[1:]
    if arg.startswith('*'):
        return arg
    return '*' + arg


def find_matching_paren(text, pos):
    depth, i = 1, pos + 1
    while i < len(text) and depth > 0:
        if text[i] == '(':
            depth += 1
        elif text[i] == ')':
            depth -= 1
        i += 1
    return i if depth == 0 else -1


def is_in_decl_context(text, pos):
    line_start = text.rfind('\n', 0, pos)
    line_start = 0 if line_start == -1 else line_start + 1
    prefix = text[line_start:pos].lstrip()
    return prefix.startswith(('extern', '//', '#', 'void ', 'void*', 'int ', 'float '))


def rename_call_sites(content, mangled, cpp_name, deref=False):
    """Replace call sites of mangled → cpp_name."""
    result = content
    pos = 0
    while True:
        idx = result.find(mangled, pos)
        if idx == -1:
            break
        if is_in_decl_context(result, idx):
            pos = idx + len(mangled)
            continue
        after = idx + len(mangled)
        ws = after
        while ws < len(result) and result[ws] in ' \t\n':
            ws += 1
        if ws >= len(result) or result[ws] != '(':
            # Not a call, just rename
            result = result[:idx] + cpp_name + result[after:]
            pos = idx + len(cpp_name)
            continue
        paren_end = find_matching_paren(result, ws)
        if paren_end == -1:
            pos = after
            continue
        if not deref:
            new = cpp_name + result[after:paren_end]
        else:
            args = split_args(result[ws + 1:paren_end - 1])
            new_args = [deref_arg(a) for a in args]
            new = cpp_name + '(' + ', '.join(new_args) + ')'
        result = result[:idx] + new + result[paren_end:]
        pos = idx + len(new)
    return result


def should_remove_from_block(line, all_mangled):
    """Check if a line in an extern "C" block should be removed.
    Only remove if the mangled name is in our removable set."""
    stripped = line.strip()
    if not stripped or stripped == '}' or stripped == '{':
        return False
    for m in all_mangled:
        if m in stripped:
            return True
    # Also check for unmangled function names that we provide via included headers
    # ONLY the ones we actually rename at call sites
    safe_unmangled = [
        r'^void\s+pppSetBlendMode\s*\(',
        r'^void\s+pppCalcFrameShape\s*\(',
        r'^void\s+pppUnitMatrix\s*\(',
        r'^void\s+pppCopyMatrix\s*\(',
        r'^void\s+pppCopyVector\s*\(',
        r'^void\s+pppAddVector\s*\(',
        r'^void\s+pppSubVector\s*\(',
        r'^void\s+pppMulMatrix\s*\(',
        r'^void\s+pppHitCylinderSendSystem\s*\(',
    ]
    for p in safe_unmangled:
        if re.match(p, stripped):
            return True
    return False


def remove_mangled_from_extern_blocks(content, all_mangled):
    """Remove mangled declarations from extern "C" { } blocks."""
    pattern = r'extern\s+"C"\s*\{'
    result = content
    search_from = 0

    while True:
        m = re.search(pattern, result[search_from:])
        if not m:
            break
        m_start = search_from + m.start()
        m_end = search_from + m.end()
        
        block_start = m_start
        brace_start = m_end - 1
        depth = 1
        i = brace_start + 1
        while i < len(result) and depth > 0:
            if result[i] == '{':
                depth += 1
            elif result[i] == '}':
                depth -= 1
            i += 1
        if depth != 0:
            break
        block_end = i

        block_content = result[brace_start + 1:block_end - 1]
        lines = block_content.split('\n')
        kept_lines = []
        skip_continuation = False

        for line in lines:
            if skip_continuation:
                if ';' in line:
                    skip_continuation = False
                continue
            if should_remove_from_block(line, all_mangled):
                if ';' not in line and line.strip():
                    skip_continuation = True
                continue
            kept_lines.append(line)

        remaining = '\n'.join(kept_lines).strip()
        if not remaining:
            line_start = result.rfind('\n', 0, block_start)
            line_start = 0 if line_start == -1 else line_start
            result = result[:line_start] + result[block_end:]
            search_from = line_start
        else:
            new_block = f'extern "C" {{\n{remaining}\n}}'
            result = result[:block_start] + new_block + result[block_end:]
            search_from = block_start + len(new_block)

    return result


def remove_single_line_externs(content, all_mangled):
    """Remove single-line extern declarations with mangled names."""
    lines = content.split('\n')
    new_lines = []
    skip = False
    for line in lines:
        if skip:
            if ';' in line:
                skip = False
            continue
        stripped = line.strip()
        remove = False
        if stripped.startswith('extern'):
            for m in all_mangled:
                if m in stripped:
                    remove = True
                    if ';' not in line:
                        skip = True
                    break
            # Also check for non-"C" externs with demangled names
            # ONLY for functions we actually rename at call sites
            if not remove:
                nonc_patterns = [
                    r'^extern\s+void\s+pppSetBlendMode\s*\(',
                    r'^extern\s+void\s+pppDrawShp\s*\(',
                    r'^extern\s+void\s+pppCalcFrameShape\s*\(',
                    r'^extern\s+_pppPObject\*\s+pppCreatePObject\s*\(',
                ]
                for p in nonc_patterns:
                    if re.match(p, stripped):
                        remove = True
                        if ';' not in stripped:
                            skip = True
                        break
        if stripped == 'class CMaterialSet;':
            remove = True
        if not remove:
            new_lines.append(line)
    return '\n'.join(new_lines)


def remove_redundant_var_externs(content, has_partmng_or_ppppart):
    if not has_partmng_or_ppppart:
        return content
    lines = content.split('\n')
    new_lines = []
    for line in lines:
        s = line.strip()
        if re.match(r'extern\s+_pppEnvSt\*\s+pppEnvStPtr\s*;', s):
            continue
        if re.match(r'extern\s+_pppMngSt\*\s+pppMngStPtr\s*;', s):
            continue
        if re.match(r'extern\s+Mtx\s+ppvCameraMatrix0\s*;', s):
            continue
        new_lines.append(line)
    return '\n'.join(new_lines)


def add_include(content, inc):
    if inc in content:
        return content
    lines = content.split('\n')
    last_ffcc = -1
    for i, l in enumerate(lines):
        if '#include "ffcc/' in l:
            last_ffcc = i
    if last_ffcc >= 0:
        lines.insert(last_ffcc + 1, inc)
    else:
        for i, l in enumerate(lines):
            if '#include' in l:
                lines.insert(i + 1, inc)
                break
        else:
            lines.insert(0, inc)
    return '\n'.join(lines)


def process_file(filepath, dry_run=False):
    with open(filepath, 'r') as f:
        content = f.read()
    original = content
    basename = os.path.basename(filepath)
    can_add_ppppart = basename not in CANNOT_ADD_PPPPART

    has_ppppart = '#include "ffcc/pppPart.h"' in content
    has_pppshape = '#include "ffcc/pppShape.h"' in content
    has_partmng = '#include "ffcc/partMng.h"' in content

    needs_ppppart = False
    needs_pppshape = False

    # Determine which renames will be applied
    all_renames = {}
    all_renames.update(SAFE_SIMPLE_RENAMES)
    all_renames.update(ALSO_RENAME_CALLSITES)
    
    for mangled, cpp_name in all_renames.items():
        if mangled in content:
            if cpp_name in PPPPART_FUNCTIONS:
                needs_ppppart = True
            if cpp_name in PPPSHAPE_FUNCTIONS:
                needs_pppshape = True

    deref_to_apply = {}
    if can_add_ppppart:
        for mangled, cpp_name in DEREF_RENAMES.items():
            if mangled in content:
                deref_to_apply[mangled] = cpp_name
                if cpp_name in PPPPART_FUNCTIONS:
                    needs_ppppart = True

    # Step 1: Remove from extern "C" blocks
    content = remove_mangled_from_extern_blocks(content, ALL_REMOVABLE_MANGLED)

    # Step 2: Remove single-line externs
    content = remove_single_line_externs(content, ALL_REMOVABLE_MANGLED)

    # Step 3: Simple renames at call sites
    for mangled, cpp_name in all_renames.items():
        if mangled in content:
            content = rename_call_sites(content, mangled, cpp_name, deref=False)

    # Step 4: Deref renames at call sites (only for compatible files)
    for mangled, cpp_name in deref_to_apply.items():
        if mangled in content:
            content = rename_call_sites(content, mangled, cpp_name, deref=True)

    # Step 5: Add includes
    will_have = has_partmng or has_ppppart
    if needs_ppppart and not has_ppppart and can_add_ppppart:
        content = add_include(content, '#include "ffcc/pppPart.h"')
        will_have = True
        if has_partmng:
            lines = content.split('\n')
            content = '\n'.join(l for l in lines if l.strip() != '#include "ffcc/partMng.h"')
    if needs_pppshape and not has_pppshape:
        content = add_include(content, '#include "ffcc/pppShape.h"')

    # Step 6: Remove redundant variable externs
    content = remove_redundant_var_externs(content, will_have)

    # Step 7: Remove redundant CMaterialSet forward decl
    if '#include "ffcc/pppShape.h"' in content:
        lines = content.split('\n')
        content = '\n'.join(l for l in lines if l.strip() != 'class CMaterialSet;')

    # Step 8: Clean blanks
    while '\n\n\n' in content:
        content = content.replace('\n\n\n', '\n\n')

    if content != original:
        if not dry_run:
            with open(filepath, 'w') as f:
                f.write(content)
        return True
    return False


def main():
    dry_run = '--dry-run' in sys.argv
    src_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'src')
    changed = []
    for root, dirs, files in os.walk(src_dir):
        for fname in sorted(files):
            if not (fname.endswith('.cpp') or fname.endswith('.c')):
                continue
            fp = os.path.join(root, fname)
            with open(fp) as f:
                c = f.read()
            # Quick check
            hit = any(m in c for m in ALL_REMOVABLE_MANGLED)
            if not hit:
                for pat in [r'extern\s+_pppEnvSt\*\s+pppEnvStPtr\s*;',
                            r'extern\s+_pppMngSt\*\s+pppMngStPtr\s*;',
                            r'extern\s+_pppPObject\*\s+pppCreatePObject']:
                    if re.search(pat, c):
                        hit = True
                        break
            if not hit:
                continue
            if process_file(fp, dry_run):
                changed.append(fp)
                pfx = '[DRY] ' if dry_run else ''
                print(f"{pfx}Changed: {os.path.relpath(fp, os.path.dirname(src_dir))}")
    print(f"\nTotal: {len(changed)} files {'would be ' if dry_run else ''}changed")


if __name__ == '__main__':
    main()
