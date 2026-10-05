import io
from pathlib import Path
import struct
import subprocess
import tempfile
import unittest

from elftools.elf.elffile import ELFFile

from tools.recover_regional_splits import (Section, bss_ownership, constrain, inferred_constraints,
    initialized_map_issues, map_objects, masks, placements, read_object, replay, sda_bases, solve, symbol_records)
from tools.tests.test_recover_code_splits import AS, LD, OBJCOPY, dol


class ConstraintTests(unittest.TestCase):
    def test_conflicting_anchors_are_not_overwritten(self):
        values = {('global', 'same'): 0x80001000}
        with self.assertRaisesRegex(ValueError, 'conflicting'):
            constrain(values, ('global', 'same'), 0x80001004)
        self.assertEqual(values[('global', 'same')], 0x80001000)

    def test_local_symbol_duplicates_survive_without_becoming_global(self):
        rows = symbol_records('local = .bss:0x80001000; // type:object size:4 scope:local\n'
                              'local = .bss:0x80002000; // type:object size:8 scope:local')
        self.assertEqual(len(rows), 2)
        self.assertTrue(all(r['local'] for r in rows))

    def test_map_evidence_ignores_old_addresses_and_preserves_scope(self):
        rows = map_objects('  7] buffer (object,local) found in ax.a unit.c\n'
                           '.bss section layout\n'
                           '  00000100 000020 80340000 32 buffer ax.a unit.c\n')
        self.assertEqual(rows, [dict(section='.bss', size=32, align=32,
                                    name='buffer', owner='unit.c', local=True)])
        self.assertNotIn('address', rows[0])

    def test_masks_preserve_branch_opcode_and_link_bit(self):
        sec = Section(1, '.text', bytes.fromhex('48000001386012344e800020'), 12, 4, False, True, [])
        sec.relocs = [dict(offset=0, kind=10, key=('global', 'Call'), value=0, symbol={})]
        self.assertEqual(masks(sec)[:4], bytes.fromhex('fc000003'))
        target = bytes.fromhex('48000101386012344e800020')
        self.assertEqual(placements(sec, dol(target))[0], [0x80004000])
        for word in ('4c000101', '48000100', '48000103'):
            self.assertEqual(placements(sec, dol(bytes.fromhex(word) + target[4:]))[0], [])

    def test_overlapping_ambiguous_placements_are_reported(self):
        sec = Section(1, '.text', b'1234' * 4, 16, 4, False, True, [])
        self.assertEqual(placements(sec, dol(b'1234' * 5))[0], [0x80004000, 0x80004004])

    def test_sda_replay_preserves_non_relocation_bits(self):
        sec = Section(1, '.text', bytes.fromhex('80600000388000204e800020'), 12, 4, False, True, [])
        sec.relocs = [dict(offset=0, kind=109, key=('section', 2), value=4, symbol={})]
        storage = Section(2, '.sbss', bytes(8), 8, 4, True, False, [])
        bases = {13: 0x80340000, 2: 0x80400000}
        actual = bytes.fromhex('806dffe4388000204e800020')
        constraints = inferred_constraints(sec, 0x80004000, actual, bases)
        self.assertEqual(constraints, [(('section', 2), 0x8033ffe0)])
        self.assertEqual(replay(sec, 0x80004000, dict(constraints), bases, {2: storage}), actual)
        self.assertEqual(masks(sec)[:4], bytes.fromhex('ffe00000'))

    def test_overlapping_sda_windows_use_retail_register_constraint(self):
        sec = Section(1, '.text', bytes.fromhex('80600000388000204e800020'), 12, 4, False, True, [])
        sec.relocs = [dict(offset=0, kind=109, key=('global', 'gx'), value=0, symbol={})]
        bases = {13: 0x80340000, 2: 0x80342000}
        actual = bytes.fromhex('8062ffe0388000204e800020')
        values = dict(inferred_constraints(sec, 0x80004000, actual, bases))
        self.assertEqual(values[('sda_register', 'gx')], 2)
        self.assertEqual(replay(sec, 0x80004000, values, bases, {}), actual)
        with self.assertRaisesRegex(ValueError, 'conflicting'):
            constrain(values, ('sda_register', 'gx'), 13)

    def test_bss_padding_requires_complete_extent_and_alignment_evidence(self):
        symbol = dict(name='buffer', offset=0, size=16, kind='STT_OBJECT', local=True)
        sec = Section(2, '.bss', bytes(32), 32, 4, True, False, [symbol])
        evidence = [dict(section='.bss', name='buffer', owner='unit.c', size=16, local=True, align=4)]
        unsupported, padding = bss_ownership('unit.c', sec, 0x80005000, evidence)
        self.assertIn('unexplained trailing storage', unsupported)
        sec.size = 20
        sec.symbols = [dict(symbol, size=4), dict(symbol, name='next', offset=16, size=4)]
        evidence[0]['size'] = 4
        evidence.append(dict(evidence[0], name='next'))
        self.assertTrue(any('unexplained gap' in s for s in bss_ownership('unit.c', sec, 0x80005000, evidence)[0]))
        evidence[1]['align'] = 16
        self.assertEqual(bss_ownership('unit.c', sec, 0x80005000, evidence),
                         ([], [dict(offset=4, size=12)]))

    def test_function_static_map_counters_do_not_hide_padding_elements(self):
        sym = dict(name='c2r$287', size=40, kind='STT_OBJECT', local=True)
        sec = Section(2, '.data', bytes(40), 40, 8, False, False, [sym])
        evidence = [dict(owner='GXTev.c', name='c2r$194', size=36, section='.data', local=True)]
        issues = initialized_map_issues('gx/GXTev.c', sec, evidence)
        self.assertEqual(len(issues), 1)
        self.assertIn('40 bytes/local differs from MAP layout .data/36 bytes/local', issues[0])
        sym['size'] = 36
        self.assertEqual(initialized_map_issues('gx/GXTev.c', sec, evidence), [])
        self.assertEqual(initialized_map_issues('other.c', sec, evidence), [])


@unittest.skipUnless(AS.is_file(), 'PowerPC GNU assembler required')
class ObjectTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.path = Path(self.temp.name)

    def assemble(self, source, name='source'):
        src, obj = self.path / (name + '.s'), self.path / (name + '.o')
        src.write_text(source)
        subprocess.run([str(AS), '-mgekko', '-o', str(obj), str(src)], check=True, capture_output=True)
        return obj.read_bytes()

    def functions(self, middle='', tail=''):
        return '''.text
.global First
.type First,@function
First:
li 3,17
li 4,23
li 5,41
blr
.size First,.-First
''' + middle + '''
.global Last
.type Last,@function
Last:
li 3,91
li 4,83
li 5,73
blr
.size Last,.-Last
''' + tail

    def test_pal_retained_set_is_tested_against_region(self):
        middle = '.type Unused,@function\nUnused:\nli 3,99\nblr\n.size Unused,.-Unused\n'
        full = self.assemble(self.functions(middle))
        hint = self.assemble(self.functions(), 'hint')
        body = ELFFile(io.BytesIO(hint)).get_section_by_name('.text').data()
        report = solve([dict(unit='unit.c', data=full, pal_object=hint)], dol(body))
        rows = report['objects']
        retained = next(r for r in rows if r['hypothesis'] == 'pal_retained_hint')
        self.assertEqual(retained['status'], 'review_ready')
        self.assertEqual(retained['discarded_functions'], ['Unused'])
        self.assertEqual(retained['initialized_bytes'], 32)
        bad = solve([dict(unit='unit.c', data=full, pal_object=hint)], dol(body[:-1] + b'!'))
        self.assertFalse(any(r['status'] == 'review_ready' for r in bad['objects']))

    def test_kept_reference_to_discarded_function_is_rejected(self):
        source = self.functions('.global Unused\n.type Unused,@function\nUnused:\nblr\n.size Unused,.-Unused\n')
        source = source.replace('li 3,17', 'bl Unused')
        with self.assertRaisesRegex(ValueError, 'discarded function'):
            read_object(self.assemble(source), {'First', 'Last'})

    def test_discarded_data_requires_no_retained_references(self):
        source = self.functions(tail='.section .sdata2,"a"\n.type constant,@object\nconstant:\n.long 0x12345678\n.size constant,4\n')
        obj = self.assemble(source)
        sections, discarded, omitted = read_object(obj, {'First', 'Last'}, {'.text'})
        self.assertEqual(omitted, ['.sdata2'])
        self.assertEqual([s.name for s in sections.values()], ['.text'])
        source = source.replace('li 3,17', 'lis 3,constant@ha')
        with self.assertRaisesRegex(ValueError, 'unsupported relocation target'):
            read_object(self.assemble(source), {'First', 'Last'}, {'.text'})

    def test_unknown_bss_is_never_verified_from_zeros(self):
        obj = self.assemble(self.functions(tail='.bss\n.type buffer,@object\nbuffer:\n.space 16\n.size buffer,16\n'))
        body = ELFFile(io.BytesIO(obj)).get_section_by_name('.text').data()
        row = solve([dict(unit='unit.c', data=obj)], dol(body))['objects'][0]
        self.assertEqual(row['status'], 'hypothesis')
        self.assertEqual(row['sections'][1]['status'], 'unresolved')

    def test_old_mwcc_halfword_sda_offsets(self):
        source = self.functions().replace('li 3,17', 'lwz 3,variable@sda21(0)')
        data = bytearray(self.assemble(source))
        elf = ELFFile(io.BytesIO(data))
        table = next(s for s in elf.iter_sections() if s['sh_type'] == 'SHT_RELA')
        first = next(table.iter_relocations())
        self.assertEqual(first['r_info_type'], 109)
        normal = read_object(bytes(data))[0]
        struct.pack_into('>I', data, table['sh_offset'], first['r_offset'] + 2)
        old = read_object(bytes(data))[0]
        self.assertEqual(next(iter(normal.values())).relocs, next(iter(old.values())).relocs)

    def test_named_overlap_blocks_review_ready(self):
        obj = self.assemble(self.functions())
        body = ELFFile(io.BytesIO(obj)).get_section_by_name('.text').data()
        known = symbol_records('Another = .text:0x80004004; // type:function size:4')
        row = solve([dict(unit='unit.c', data=obj)], dol(body), known)['objects'][0]
        self.assertEqual(row['status'], 'hypothesis')
        self.assertTrue(any('ownership overlaps' in s for s in row['review_issues']))

    def test_cross_object_definitions_resolve_inferred_external_identity(self):
        caller = self.assemble(self.functions().split('.global Last')[0].replace('li 3,17', 'bl Destination'))
        callee_source = '.text\n.global Last' + self.functions().split('.global Last')[1]
        callee = self.assemble(callee_source.replace('Last', 'Destination'), 'callee')
        first = bytearray(ELFFile(io.BytesIO(caller)).get_section_by_name('.text').data())
        first[:4] = bytes.fromhex('48000011')
        last = ELFFile(io.BytesIO(callee)).get_section_by_name('.text').data()
        image = dol(bytes(first) + last)
        alone = solve([dict(unit='caller.c', data=caller)], image)['objects'][0]
        self.assertEqual(alone['inferred_globals'], {'Destination': 0x80004010})
        together = solve([dict(unit='caller.c', data=caller), dict(unit='callee.c', data=callee)], image)
        self.assertTrue(all(r['status'] == 'review_ready' for r in together['objects']))
        self.assertFalse(together['source_linkage_claims'])
        conflict = symbol_records('Another = .text:0x80004014; // type:function size:4')
        blocked = solve([dict(unit='caller.c', data=caller), dict(unit='callee.c', data=callee)], image, conflict)
        self.assertTrue(all(r['status'] == 'hypothesis' for r in blocked['objects']))
        self.assertEqual(blocked['objects'][0]['inferred_globals'], {'Destination': 0x80004010})

    def test_source_optimizer_pragma_prevents_review_ready(self):
        obj = self.assemble(self.functions())
        body = ELFFile(io.BytesIO(obj)).get_section_by_name('.text').data()
        row = solve([dict(unit='unit.c', data=obj, source=b'#pragma dont_inline on\n')], dol(body))['objects'][0]
        self.assertEqual(row['status'], 'hypothesis')
        self.assertTrue(any('optimizer pragmas' in s for s in row['review_issues']))

    def test_conflicting_cross_object_definitions_remain_hypotheses(self):
        first_source = self.functions().split('.global Last')[0]
        one = self.assemble(first_source)
        two = self.assemble(first_source.replace('li 3,17', 'li 3,18'), 'other')
        body = b''.join(ELFFile(io.BytesIO(obj)).get_section_by_name('.text').data() for obj in (one, two))
        report = solve([dict(unit='one.c', data=one), dict(unit='two.c', data=two)], dol(body))
        self.assertEqual(report['conflicts'], {'First': [0x80004000, 0x80004010]})
        self.assertTrue(all(r['status'] == 'hypothesis' for r in report['objects']))

    @unittest.skipUnless(LD.is_file(), 'PowerPC GNU linker required')
    def test_sda_elf_must_match_every_retail_byte_and_zero_padding(self):
        obj = self.assemble(self.functions().split('.global Last')[0])
        linked = self.path / 'linked.elf'
        subprocess.run([str(LD), '-Ttext=0x80004000', '--defsym=_SDA_BASE_=0x80340000',
                        '--defsym=_SDA2_BASE_=0x80342000', '-o', str(linked),
                        str(self.path / 'source.o')], check=True, capture_output=True)
        body = ELFFile(io.BytesIO(obj)).get_section_by_name('.text').data()
        self.assertEqual(sda_bases(linked.read_bytes(), dol(body + bytes(16))),
                         {13: 0x80340000, 2: 0x80342000})
        for image in (dol(body[:-1] + b'!'), dol(body + bytes(15) + b'!'), dol(body + bytes(32))):
            with self.subTest(image=image), self.assertRaises(ValueError):
                sda_bases(linked.read_bytes(), image)

    def test_initialized_data_is_fully_replayed_and_corruption_rejected(self):
        source = self.functions().split('.global Last')[0]
        source = source.replace('li 3,17\nli 4,23', 'lis 3,table@ha\naddi 3,3,table@l')
        source += '.data\n.type table,@object\ntable:\n.long 0x12345678\n.size table,4\n'
        obj = self.assemble(source)
        code = bytes.fromhex('3c6080003863500038a000294e800020')
        image = bytearray(dol(code))
        struct.pack_into('>I', image, 7 * 4, len(image))
        struct.pack_into('>I', image, 0x48 + 7 * 4, 0x80005000)
        struct.pack_into('>I', image, 0x90 + 7 * 4, 4)
        image += bytes.fromhex('12345678')
        row = solve([dict(unit='unit.c', data=obj)], bytes(image))['objects'][0]
        self.assertEqual(row['status'], 'review_ready')
        self.assertEqual(row['initialized_bytes'], 20)
        self.assertEqual(row['relocation_count'], 2)
        mismatched_map = [dict(owner='unit.c', name='table', size=8, section='.data', local=True)]
        contradiction = solve([dict(unit='unit.c', data=obj)], bytes(image), maps=mismatched_map)['objects'][0]
        self.assertEqual(contradiction['initialized_bytes'], 20)
        self.assertEqual(contradiction['status'], 'hypothesis')
        self.assertTrue(any('differs from MAP layout' in s for s in contradiction['review_issues']))
        image[-1] ^= 1
        bad = solve([dict(unit='unit.c', data=obj)], bytes(image))['objects'][0]
        self.assertEqual(bad['status'], 'rejected')

    def test_bss_needs_matching_map_scope_owner_and_extent(self):
        source = self.functions().split('.global Last')[0]
        source = source.replace('li 3,17\nli 4,23', 'lis 3,buffer@ha\naddi 3,3,buffer@l')
        source += '.bss\n.type buffer,@object\nbuffer:\n.space 16\n.size buffer,16\n'
        obj = self.assemble(source)
        image = bytearray(dol(bytes.fromhex('3c6080003863500038a000294e800020')))
        struct.pack_into('>II', image, 0xd8, 0x80005000, 16)
        proof = dict(section='.bss', owner='unit.c', name='buffer', size=16, local=True, align=4)
        good = solve([dict(unit='unit.c', data=obj)], bytes(image), maps=[proof])['objects'][0]
        self.assertEqual(good['status'], 'review_ready')
        self.assertEqual(good['sections'][1]['status'], 'map_supported_bss')
        for key, value in [('owner', 'other.c'), ('size', 12), ('local', False)]:
            wrong = dict(proof, **{key: value})
            row = solve([dict(unit='unit.c', data=obj)], bytes(image), maps=[wrong])['objects'][0]
            self.assertEqual(row['status'], 'hypothesis')
            self.assertEqual(row['sections'][1]['status'], 'unverified_bss')

    def test_truncated_search_cannot_establish_uniqueness(self):
        source = self.functions().split('.global Last')[0].replace('li 3,17', 'bl External')
        obj = self.assemble(source)
        code = ELFFile(io.BytesIO(obj)).get_section_by_name('.text').data()
        pieces = []
        for i in range(33):
            address = 0x80004000 + 16 * i
            target = 0x80005000 if i in (0, 32) else 0x80006000
            pieces.append((0x48000001 | ((target - address) & 0x3fffffc)).to_bytes(4, 'big') + code[4:])
        image = dol(b''.join(pieces))
        records = symbol_records('External = .text:0x80005000; // type:function size:4')
        row = solve([dict(unit='unit.c', data=obj)], image, records)['objects'][0]
        self.assertEqual(row['status'], 'hypothesis')
        self.assertTrue(any('truncated search' in s for s in row['review_issues']))
        records += symbol_records('First = .text:0x80004000; // type:function size:16')
        row = solve([dict(unit='unit.c', data=obj)], image, records)['objects'][0]
        self.assertEqual(row['status'], 'review_ready')

    def test_out_of_bounds_relocation_is_not_silently_discarded(self):
        source = self.functions().replace('li 3,17', 'bl External')
        data = bytearray(self.assemble(source))
        elf = ELFFile(io.BytesIO(data))
        table = next(s for s in elf.iter_sections() if s['sh_type'] == 'SHT_RELA')
        struct.pack_into('>I', data, table['sh_offset'], 32)
        with self.assertRaisesRegex(ValueError, 'relocation extent'):
            read_object(bytes(data), {'First', 'Last'})

    def test_relocation_cannot_straddle_retention_boundary(self):
        source = '''.text
.type First,@function
First: .short 0
.size First,.-First
.type Unused,@function
Unused: .short 0
.size Unused,.-Unused
.type Last,@function
Last: blr
.size Last,.-Last
.reloc 0,R_PPC_ADDR32,External
'''
        with self.assertRaisesRegex(ValueError, 'retained/discarded boundary'):
            read_object(self.assemble(source), {'First', 'Last'})

    def test_circular_external_identities_do_not_certify_each_other(self):
        source = self.functions().split('.global Last')[0]
        one = self.assemble(source.replace('li 3,17', 'bl Second'))
        two = self.assemble(source.replace('First', 'Second').replace('li 3,17', 'bl First').replace('li 5,41', 'li 5,42'), 'other')
        body = bytes.fromhex('48000011') + ELFFile(io.BytesIO(one)).get_section_by_name('.text').data()[4:]
        body += bytes.fromhex('4bfffff1') + ELFFile(io.BytesIO(two)).get_section_by_name('.text').data()[4:]
        rows = solve([dict(unit='one.c', data=one), dict(unit='two.c', data=two)], dol(body))['objects']
        self.assertTrue(all(r['status'] == 'hypothesis' and r['inferred_globals'] for r in rows))

    def test_late_conflict_retracts_dependent_identities(self):
        source = self.functions().split('.global Last')[0]
        specs = [('a.c', 'Shared', None, 41), ('b.c', 'Shared', 'Helper', 42),
                 ('helper.c', 'Helper', None, 43), ('consumer.c', 'Consumer', 'Shared', 44)]
        objects, pieces = [], []
        for i, (unit, name, call, constant) in enumerate(specs):
            text = source.replace('First', name).replace('li 5,41', f'li 5,{constant}')
            if call:
                text = text.replace('li 3,17', 'bl ' + call)
            data = self.assemble(text, name + str(i))
            body = ELFFile(io.BytesIO(data)).get_section_by_name('.text').data()
            if call:
                target = 0x80004020 if call == 'Helper' else 0x80004000
                word = 0x48000001 | ((target - (0x80004000 + 16 * i)) & 0x3fffffc)
                body = word.to_bytes(4, 'big') + body[4:]
            objects.append(dict(unit=unit, data=data))
            pieces.append(body)
        report = solve(objects, dol(b''.join(pieces)))
        self.assertEqual(report['conflicts'], {'Shared': [0x80004000, 0x80004010]})
        consumer = next(r for r in report['objects'] if r['unit'] == 'consumer.c')
        self.assertEqual(consumer['status'], 'hypothesis')
        self.assertEqual(consumer['inferred_globals'], {'Shared': 0x80004000})


if __name__ == '__main__':
    unittest.main()
