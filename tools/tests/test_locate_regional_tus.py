import struct
import subprocess
import tempfile
from pathlib import Path
import unittest

from tools.locate_regional_tus import (Locator, annotate_sequence_overlaps, exception_functions, exception_table_hits,
                                     locate_functions, read_code, sequence_proposals, token, words)
from tools.tests.test_recover_code_splits import AS, dol


def instructions(count=64, seed=0):
    # Legal add instructions with varying register triples.
    return [(31 << 26) | (((i + seed) % 31) << 21)
            | (((i + seed) // 3 % 31) << 16)
            | (((i + seed) // 7 % 31) << 11) | (266 << 1)
            for i in range(count)]


def body(raw):
    return struct.pack('>' + 'I' * len(raw), *raw)


def code(raw, functions=()):
    return dict(words=raw, functions=list(functions))


class LocatorTests(unittest.TestCase):
    def test_masks_constants_branches_and_sda_but_keeps_register_shape(self):
        self.assertEqual(token(0x38601234), token(0x38605678))
        self.assertEqual(token(0x48000101), token(0x48001201))
        self.assertNotEqual(token(0x48000101), token(0x48000100))
        self.assertEqual(token(0x80600000), token(0x806D1234))
        self.assertEqual(token(0x80600000), token(0x80625678))
        self.assertNotEqual(token(0x80600000), token(0x80800000))

    def test_locates_whole_window_and_known_identity(self):
        raw = instructions()
        locator = Locator(dol(body([0] * 16 + raw + [0] * 16)))
        known = [dict(name='F', kind='function', address=0x80004040)]
        row = locator.rank(code(raw, [dict(name='F', offset=0, size=256)]), known)
        best = row['candidates'][0]
        self.assertEqual(best['address'], 0x80004040)
        self.assertEqual(best['normalized_match'], 1)
        self.assertEqual(len(best['known_consistent']), 1)
        self.assertEqual(len(best['anchor_bins']), 15)

    def test_runner_up_includes_all_candidates_before_display_limit(self):
        raw = instructions()
        locator = Locator(dol(body(raw + [0] * 16 + raw)))
        row = locator.rank(code(raw), candidates=1)
        self.assertEqual(len(row['candidates']), 1)
        self.assertGreaterEqual(row['candidate_bases_scored'], 2)
        self.assertEqual(row['runner_up_margin'], 0)

    def test_saturated_anchor_is_never_treated_as_unique(self):
        raw = instructions()
        locator = Locator(dol(body(raw + [0] * 8), copies=5))
        self.assertEqual(locator.rank(code(raw))['status'], 'no_anchor')

    def test_excludes_data_and_windows_crossing_section_end(self):
        raw = instructions()
        self.assertEqual(Locator(dol(body(raw), data_only=True)).rank(code(raw))['status'], 'no_anchor')
        row = Locator(dol(body(raw))).rank(code(raw + instructions(8, 500)))
        self.assertEqual(row['status'], 'no_anchor')

    def test_local_names_cannot_anchor_unrelated_unit(self):
        raw = instructions()
        row = Locator(dol(body(raw))).rank(code(raw, [dict(name='F', offset=0, size=256)]),
            [dict(name='F', kind='function', address=0x80009000, local=True)])
        self.assertFalse(row['candidates'][0]['known_conflicts'])

    def test_named_conflict_blocks_strong_function_ranking(self):
        raw = instructions()
        row = locate_functions(Locator(dol(body(raw))), code(raw, [dict(name='F', offset=0, size=256)]),
            [dict(name='F', kind='function', address=0x80009000)])
        self.assertEqual(row['strong_functions'], 0)
        self.assertEqual(len(row['functions'][0]['candidates'][0]['known_conflicts']), 1)

    def test_function_fallback_exposes_insertions(self):
        first, second = instructions(), instructions(seed=700)
        functions = [dict(name='F', offset=0, size=256), dict(name='G', offset=256, size=256)]
        locator = Locator(dol(body(first + [0] * 12 + second)))
        row = locate_functions(locator, code(first + second, functions))
        self.assertEqual(row['strong_functions'], 2)
        self.assertEqual(row['base_hypotheses'], [0x80004000, 0x80004030])
        self.assertEqual(row['ordered_neighbor_pairs'], 1)

    def test_reordering_is_reported_without_claiming_source_order(self):
        first, second = instructions(), instructions(seed=700)
        functions = [dict(name='F', offset=0, size=256), dict(name='G', offset=256, size=256)]
        row = locate_functions(Locator(dol(body(second + first))), code(first + second, functions))
        self.assertEqual(row['strong_functions'], 2)
        self.assertEqual(row['ordered_neighbor_pairs'], 0)

    def test_invalid_extents_and_limits(self):
        raw = instructions()
        locator = Locator(dol(body(raw)))
        with self.assertRaises(ValueError):
            words(b'abc')
        with self.assertRaises(ValueError):
            locator.rank(code(raw), anchors=1)
        with self.assertRaises(ValueError):
            locate_functions(locator, code(raw, [dict(name='F', offset=4, size=256)]))

    def test_replayed_call_destination_checks_independent_function_rankings(self):
        raw = instructions() + instructions(seed=700)
        raw[10] = 0x48000001
        source = code(raw, [dict(name='F', offset=0, size=256), dict(name='G', offset=256, size=256)])
        source['calls'] = [dict(offset=40, target='G', local=True)]
        for delta, consistent in ((216, True), (220, False)):
            retail = raw.copy()
            retail[10] |= delta
            row = locate_functions(Locator(dol(body(retail))), source)
            self.assertEqual(len(row['callgraph_checks']), 1)
            self.assertEqual(row['callgraph_checks'][0]['consistent'], consistent)

    def test_call_site_context_drift_does_not_invent_callgraph_evidence(self):
        raw = instructions() + instructions(seed=700)
        raw[10] = 0x48000001
        source = code(raw, [dict(name='F', offset=0, size=256), dict(name='G', offset=256, size=256)])
        source['calls'] = [dict(offset=40, target='G', local=True)]
        retail = raw.copy()
        retail[9] = 0
        row = locate_functions(Locator(dol(body(retail))), source)
        self.assertFalse(row['callgraph_checks'])

    @unittest.skipUnless(AS.is_file(), 'PowerPC GNU assembler required')
    def test_read_code_accepts_common_and_mixed_data_without_claiming_them(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)
            (path / 'unit.s').write_text('.text\n.global F\n.type F,@function\nF:\nbl External\nblr\n.size F,.-F\n.data\n.long 42\n.comm buffer,64,4\n')
            subprocess.run([str(AS), '-mgekko', '-o', str(path / 'unit.o'), str(path / 'unit.s')],
                           check=True, capture_output=True)
            sections = read_code((path / 'unit.o').read_bytes())
            self.assertEqual(len(sections), 1)
            self.assertEqual(sections[0]['words'], [0x48000001, 0x4e800020])
            self.assertEqual(sections[0]['functions'], [dict(name='F', offset=0, size=8)])


class SequenceTests(unittest.TestCase):
    def fixture(self, second=0x80004040, extra=()):
        pal = code(instructions(32), [dict(name='F', offset=0, size=64), dict(name='G', offset=64, size=64)])
        report = dict(functions=[dict(name=name, strong_ranking=True, candidates=[dict(address=address)])
                                 for name, address in [('F', 0x80004000), ('G', second)]])
        records = [dict(name=f'fn_{address:08X}', kind='function', address=address, size=64)
                   for address in [0x80004000, second]] + list(extra)
        table = struct.pack('>6I', 0x80004000, 64, 0x80004098, second, 64, 0x80004098)
        image = dol(bytes(128) + table + bytes(16))
        return pal, report, records, image

    def test_boundary_votes_and_complete_exception_sequence(self):
        pal, report, records, image = self.fixture()
        row = sequence_proposals(pal, report, records, image, ['F', 'G'])
        best = row['candidates'][0]
        self.assertEqual(best['agreeing_anchors'], 2)
        self.assertEqual(best['exception_table_candidates'], [0x80004080])
        self.assertFalse(best['review_issues'])

    def test_extra_retail_function_exposes_count_drift(self):
        extra = dict(name='fn_80004040', kind='function', address=0x80004040, size=64)
        pal, report, records, image = self.fixture(second=0x80004080, extra=[extra])
        row = sequence_proposals(pal, report, records, image, ['F', 'G'])
        self.assertEqual(len(row['candidates']), 2)
        self.assertTrue(all(c['agreeing_anchors'] == 1 for c in row['candidates']))
        self.assertTrue(all(c['review_issues'] for c in row['candidates']))

    def test_named_conflict_is_not_hidden_by_order_votes(self):
        pal, report, records, image = self.fixture()
        records[0]['name'] = 'DifferentIdentity'
        row = sequence_proposals(pal, report, records, image, ['F', 'G'])
        self.assertEqual(len(row['candidates'][0]['named_conflicts']), 1)

    def test_exception_table_requires_valid_eh_pointers_and_preserves_ambiguity(self):
        _, _, _, image = self.fixture()
        fields = [(0x80004000, 64), (0x80004040, 64)]
        self.assertEqual(exception_table_hits(image, fields), [0x80004080])
        invalid = bytearray(image)
        struct.pack_into('>I', invalid, 0x188, 0)
        self.assertEqual(exception_table_hits(bytes(invalid), fields), [])
        doubled = dol(image[0x100:], copies=2)
        self.assertEqual(len(exception_table_hits(doubled, fields)), 2)

    def test_ambiguous_boundary_alias_is_not_selected_silently(self):
        pal, report, records, image = self.fixture()
        records.append(dict(records[0], name='Alias'))
        row = sequence_proposals(pal, report, records, image, ['F', 'G'])
        self.assertFalse(row['candidates'])

    def test_missing_edge_anchor_is_explicit_even_when_internal_eh_matches(self):
        pal, report, records, image = self.fixture()
        report['functions'][0]['strong_ranking'] = False
        row = sequence_proposals(pal, report, records, image, ['G'])
        self.assertEqual(row['candidates'][0]['unsupported_edges'], [dict(edge='first', name='F')])
        self.assertTrue(row['candidates'][0]['review_issues'])

    def test_complete_exception_table_does_not_prove_unanchored_names(self):
        pal, report, records, image = self.fixture()
        report['functions'][0]['strong_ranking'] = False
        row = sequence_proposals(pal, report, records, image, ['F', 'G'])
        best = row['candidates'][0]
        self.assertEqual(best['exception_table_candidates'], [0x80004080])
        self.assertEqual(best['unanchored_identities'], ['F'])
        self.assertEqual(best['unsupported_edges'], [dict(edge='first', name='F')])
        self.assertTrue(best['review_issues'])

    def test_competing_unit_envelopes_flag_both_owners(self):
        rows = [dict(unit=unit, sections=[dict(name='.text', boundary_sequence=dict(candidates=[
            dict(start=start, end=end, review_issues=[])]))])
                for unit, start, end in [('A', 0, 100), ('B', 80, 120), ('C', 120, 160)]]
        annotate_sequence_overlaps(rows)
        for row, count in zip(rows, [1, 1, 0]):
            candidate = row['sections'][0]['boundary_sequence']['candidates'][0]
            self.assertEqual(len(candidate['competing_unit_envelopes']), count)
            self.assertEqual(bool(candidate['review_issues']), bool(count))

    @unittest.skipUnless(AS.is_file(), 'PowerPC GNU assembler required')
    def test_reads_exception_identity_without_trusting_old_address(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)
            (path / 'unit.s').write_text('.text\n.global F\n.type F,@function\nF:\nblr\n.size F,.-F\n.section extabindex,"a"\n.long F,4,0\n')
            subprocess.run([str(AS), '-mgekko', '-o', str(path / 'unit.o'), str(path / 'unit.s')],
                           check=True, capture_output=True)
            self.assertEqual(exception_functions((path / 'unit.o').read_bytes()), ['F'])


if __name__ == '__main__':
    unittest.main()
