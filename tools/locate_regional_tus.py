#!/usr/bin/env python3
"""Rank whole-TU PowerPC code placements. Hypotheses only; never edits configs."""

import argparse
from collections import defaultdict
import hashlib
import io
import json
from pathlib import Path
import struct
import time

from elftools.elf.elffile import ELFFile

try:
    from .recover_code_splits import dol_sections
    from .recover_regional_splits import symbol_records
except ImportError:
    from recover_code_splits import dol_sections
    from recover_regional_splits import symbol_records


def words(body):
    if len(body) % 4:
        raise ValueError('code is not an integral number of PPC instructions')
    return list(struct.unpack('>' + 'I' * (len(body) // 4), body))


def token(word):
    """Keep instruction/register shape while tolerating relocated immediates.

    This intentionally also masks ordinary constants. Equal tokens are ranking
    evidence, not relocation replay or proof of instruction equivalence.
    """
    op = word >> 26
    if op == 18:
        return word & 0xFC000003
    if op == 16:
        return word & 0xFFFF0003
    if op in (7, 8, 10, 11, 12, 13, 14, 15, 24, 25, 26, 27, 28, 29) or 32 <= op <= 55:
        # SDA21 resolves RA=0 to r2/r13; treat all three consistently.
        mask = 0xFFFF0000
        if ((word >> 16) & 31) in (0, 2, 13):
            mask &= ~0x001F0000
        return word & mask
    return word


def read_code(data):
    elf = ELFFile(io.BytesIO(data))
    if elf.elfclass != 32 or elf.little_endian or elf['e_machine'] != 'EM_PPC' or elf['e_type'] != 'ET_REL':
        raise ValueError('expected a big-endian PPC ELF32 relocatable object')
    symtab = elf.get_section_by_name('.symtab')
    result = []
    for index, sec in enumerate(elf.iter_sections()):
        if not sec['sh_flags'] & 4 or not sec['sh_size']:
            continue
        if sec['sh_type'] != 'SHT_PROGBITS':
            raise ValueError('executable section is not PROGBITS')
        funcs = [dict(name=s.name, offset=s['st_value'], size=s['st_size'])
                 for s in symtab.iter_symbols()
                 if s['st_shndx'] == index and s['st_info']['type'] == 'STT_FUNC' and s['st_size']] if symtab else []
        calls = []
        for table in elf.iter_sections():
            if table['sh_type'] != 'SHT_RELA' or table['sh_info'] != index:
                continue
            table_symbols = elf.get_section(table['sh_link'])
            for rel in table.iter_relocations():
                if rel['r_info_type'] != 10:
                    continue
                offset = rel['r_offset']
                if offset % 4 or offset + 4 > sec['sh_size']:
                    raise ValueError('invalid REL24 call extent')
                insn = struct.unpack_from('>I', sec.data(), offset)[0]
                if insn >> 26 != 18 or insn & 2:
                    raise ValueError('REL24 is not a relative branch')
                target = table_symbols.get_symbol(rel['r_info_sym'])
                name = target.name
                if target['st_shndx'] == index:
                    fn = next((f for f in funcs if f['offset'] == target['st_value'] + rel['r_addend']), None)
                    if fn:
                        name = fn['name']
                    else:
                        continue
                elif target['st_shndx'] != 'SHN_UNDEF' or rel['r_addend']:
                    continue
                calls.append(dict(offset=offset, target=name, local=target['st_shndx'] == index))
        result.append(dict(name=sec.name, words=words(sec.data()), functions=funcs, calls=calls))
    if not result:
        raise ValueError('object has no executable code')
    return result


class Locator:
    def __init__(self, dol, window=8, max_occurrences=4):
        if window < 4 or max_occurrences < 1:
            raise ValueError('window must be >= 4 and occurrences >= 1')
        self.window, self.max_occurrences = window, max_occurrences
        self.sections, self.index = [], defaultdict(list)
        for sec in dol_sections(dol):
            if sec['index'] >= 7:
                continue
            body = dol[sec['offset']:sec['offset'] + sec['size']]
            raw = words(body)
            normalized = [token(w) for w in raw]
            self.sections.append((sec['address'], raw, normalized))
            for i in range(len(raw) - window + 1):
                key = tuple(normalized[i:i + window])
                hits = self.index[key]
                # Saturated keys are explicitly unusable, not falsely unique.
                if len(hits) <= max_occurrences:
                    hits.append(sec['address'] + 4 * i)

    def rank(self, code, known=(), anchors=1024, candidates=8):
        raw = code['words']
        normalized = [token(w) for w in raw]
        last = len(raw) - self.window
        if last < 0:
            return dict(status='too_small', candidates=[])
        if anchors < 2 or candidates < 1:
            raise ValueError('anchors must be >= 2 and candidates >= 1')
        positions = sorted({round(i * last / (min(anchors, last + 1) - 1))
                            for i in range(min(anchors, last + 1))}) if last else [0]
        votes, distinct = defaultdict(list), 0
        for i in positions:
            hits = self.index.get(tuple(normalized[i:i + self.window]), ())
            if not hits or len(hits) > self.max_occurrences:
                continue
            distinct += 1
            for address in hits:
                votes[address - 4 * i].append(i)
        rows = []
        # Score every base with a distinctive anchor. A limit applies only to
        # displayed results, never to the candidate search or runner-up margin.
        by_name = defaultdict(set)
        for rec in known:
            if rec['kind'] == 'function' and not rec.get('local'):
                by_name[rec['name']].add(rec['address'])
        for base, offsets in votes.items():
            sec = next(((a, r, t) for a, r, t in self.sections
                        if a <= base and base + 4 * len(raw) <= a + 4 * len(r)), None)
            if sec is None:
                continue
            start = (base - sec[0]) // 4
            target = sec[1][start:start + len(raw)]
            tokens = sec[2][start:start + len(raw)]
            equal = sum(a == b for a, b in zip(normalized, tokens))
            opcode = sum(a >> 26 == b >> 26 for a, b in zip(raw, target))
            exact = sum(a == b for a, b in zip(raw, target))
            consistent, conflicts = [], []
            for fn in code['functions']:
                addresses = by_name.get(fn['name'], ())
                if len(addresses) == 1:
                    row = dict(name=fn['name'], predicted=base + fn['offset'], known=next(iter(addresses)))
                    (consistent if row['predicted'] == row['known'] else conflicts).append(row)
            bins = sorted({min(15, i * 16 // len(raw)) for i in offsets})
            rows.append(dict(address=base, end=base + 4 * len(raw), anchor_votes=len(offsets),
                             anchor_bins=bins, anchor_span_bytes=4 * (max(offsets) - min(offsets) + self.window),
                             normalized_match=equal / len(raw), opcode_match=opcode / len(raw),
                             raw_word_match=exact / len(raw), known_consistent=consistent, known_conflicts=conflicts))
        rows.sort(key=lambda r: (r['normalized_match'], len(r['anchor_bins']), r['anchor_votes']), reverse=True)
        margin = rows[0]['normalized_match'] - rows[1]['normalized_match'] if len(rows) > 1 else None
        return dict(status='ranked_hypothesis' if rows else 'no_anchor', sampled_anchors=len(positions),
                    distinctive_anchors=distinct, candidate_bases_scored=len(rows), runner_up_margin=margin,
                    candidates=rows[:candidates])


def locate_functions(locator, code, known=(), anchors=128):
    """Independent function rankings expose internal layout drift and dead code.

    The envelope uses compiled sizes, not proven retail function ends. Even a
    high score cannot establish identity for an unnamed retail function.
    """
    rows = []
    for fn in sorted(code['functions'], key=lambda f: (f['offset'], f['name'])):
        start, size = fn['offset'], fn['size']
        if start % 4 or size % 4 or start < 0 or start + size > len(code['words']) * 4:
            raise ValueError('invalid executable function extent')
        if size < locator.window * 4:
            continue
        fragment = dict(words=code['words'][start // 4:(start + size) // 4],
                        functions=[dict(fn, offset=0)])
        ranking = locator.rank(fragment, known, anchors, candidates=3)
        best = ranking['candidates'][0] if ranking['candidates'] else None
        strong = bool(best and best['normalized_match'] >= 0.80
                      and best['anchor_votes'] >= 2 and len(best['anchor_bins']) >= 8
                      and not best['known_conflicts']
                      and (ranking['runner_up_margin'] is None or ranking['runner_up_margin'] >= 0.10))
        rows.append(dict(fn, strong_ranking=strong, **ranking))
    strong = [r for r in rows if r['strong_ranking']]
    ordered_pairs = sum(a['candidates'][0]['end'] <= b['candidates'][0]['address']
                        for a, b in zip(strong, strong[1:]))
    targets = defaultdict(set)
    for rec in known:
        if rec['kind'] == 'function' and not rec.get('local'):
            targets[rec['name']].add(rec['address'])
    local_targets = defaultdict(set)
    for row in strong:
        local_targets[row['name']].add(row['candidates'][0]['address'])
    call_evidence = []
    for call in code.get('calls', ()):
        source = next((r for r in strong if r['offset'] <= call['offset'] < r['offset'] + r['size']), None)
        addresses = (local_targets if call['local'] else targets).get(call['target'], ())
        if source is None or len(addresses) != 1:
            continue
        site = source['candidates'][0]['address'] + call['offset'] - source['offset']
        sec = next(((a, r) for a, r, _ in locator.sections if a <= site < a + 4 * len(r)), None)
        if sec is None:
            continue
        at = (site - sec[0]) // 4
        original = call['offset'] // 4
        # A fuzzy function can change internally. Only use same-offset call
        # sites whose surrounding instruction shapes still agree.
        if at < 1 or at + 1 >= len(sec[1]) or original < 1 or original + 1 >= len(code['words']):
            continue
        if any(token(sec[1][at + d]) != token(code['words'][original + d]) for d in (-1, 0, 1)):
            continue
        insn = sec[1][at]
        displacement = insn & 0x03FFFFFC
        if displacement & 0x02000000:
            displacement -= 0x04000000
        observed = (site + displacement) & 0xFFFFFFFF
        expected = next(iter(addresses))
        call_evidence.append(dict(source=source['name'], target=call['target'], site=site,
                                  observed=observed, expected=expected, consistent=observed == expected))
    return dict(functions=rows, strong_functions=len(strong),
                strong_compiled_bytes=sum(r['size'] for r in strong),
                ordered_neighbor_pairs=ordered_pairs, neighbor_pairs=max(0, len(strong)-1),
                compiled_extent_envelope=[min(r['candidates'][0]['address'] for r in strong),
                                          max(r['candidates'][0]['end'] for r in strong)] if strong else None,
                base_hypotheses=sorted({r['candidates'][0]['address'] - r['offset'] for r in strong}),
                callgraph_checks=call_evidence)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dol', type=Path, required=True)
    parser.add_argument('--source-dir', type=Path, required=True)
    parser.add_argument('--include', default='*.o', help='Path glob relative to source directory')
    parser.add_argument('--top', type=int, default=30, help='Largest executable-code objects; zero selects all')
    parser.add_argument('--symbols', type=Path)
    parser.add_argument('--window', type=int, default=8)
    parser.add_argument('--anchors', type=int, default=1024)
    parser.add_argument('--functions', action='store_true', help='Also rank functions independently to expose layout drift')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    if args.top < 0 or args.anchors < 2 or args.window < 4:
        parser.error('top must be >= 0, anchors >= 2 and window >= 4')
    started = time.perf_counter()
    objects, rejected = [], []
    for path in args.source_dir.glob(args.include):
        try:
            data = path.read_bytes()
            code = read_code(data)
            objects.append((sum(len(c['words']) * 4 for c in code), path, data, code))
        except (ValueError, OSError) as exc:
            rejected.append(dict(path=str(path), error=str(exc)))
    objects.sort(key=lambda item: (-item[0], str(item[1])))
    if args.top:
        objects = objects[:args.top]
    dol = args.dol.read_bytes()
    locator = Locator(dol, args.window)
    indexed = time.perf_counter()
    known = symbol_records(args.symbols.read_text()) if args.symbols else []
    rows = []
    for size, path, data, sections in objects:
        rows.append(dict(unit=path.relative_to(args.source_dir).as_posix(), code_bytes=size,
                         object_sha256=hashlib.sha256(data).hexdigest(),
                         sections=[dict(name=sec['name'], size=len(sec['words']) * 4,
                                        **locator.rank(sec, known, args.anchors),
                                        **(locate_functions(locator, sec, known) if args.functions else {}))
                                   for sec in sections]))
    result = dict(schema=1, source_linkage_claims=False, placement_claims=False,
                  model='whole_section_same_offset_masked_instruction_anchors',
                  dol_sha256=hashlib.sha256(dol).hexdigest(), window_instructions=args.window,
                  symbols_sha256=hashlib.sha256(args.symbols.read_bytes()).hexdigest() if args.symbols else None,
                  source_directory=str(args.source_dir), include=args.include, top=args.top,
                  whole_section_anchors=args.anchors, function_anchors=128 if args.functions else None,
                  max_anchor_occurrences=locator.max_occurrences,
                  index_seconds=indexed-started, total_seconds=time.perf_counter()-started,
                  objects=rows, rejected=rejected)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(dict(objects=len(rows), code_bytes=sum(r['code_bytes'] for r in rows),
                          seconds=result['total_seconds'], output=str(args.output))))


if __name__ == '__main__':
    main()
