import struct
import subprocess
import tempfile
from pathlib import Path
import unittest

from tools.locate_regional_tus import Locator, locate_functions, read_code, token, words
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


if __name__ == '__main__':
    unittest.main()
