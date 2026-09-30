import itertools
import unittest

from tools.mine_function_order import analyze, plan_moves


def side(names):
    return {"symbols": [{"name": name, "address": i * 4, "size": "4",
                         "instructions": [], "match_percent": 100.0}
                        for i, name in enumerate(names)]}


class FunctionOrderTests(unittest.TestCase):
    def test_three_independent_lighting_moves(self):
        wanted = ["parent", "child", "insert", "calc", "destroy", "quit", "init", "sinit"]
        current = ["child", "parent", "insert", "destroy", "calc", "init", "quit", "sinit"]
        result = analyze({"left": side(wanted), "right": side(current)}, "lighting")
        self.assertEqual(result["minimum_moves"], 3)
        self.assertEqual(result["size_differences"], [])

    def test_aliases_are_not_move_candidates(self):
        left = side(["a", "alias", "b"])
        left["symbols"][1]["address"] = 0
        right = side(["b", "a", "alias"])
        right["symbols"][2]["address"] = 4
        result = analyze({"left": left, "right": right}, "aliases")
        self.assertEqual(result["minimum_moves"], 0)
        self.assertEqual(result["common_functions"], 1)
        self.assertEqual(result["ignored_aliases"], {"retail": 2, "compiled": 2})

    def test_missing_extra_and_size_changes_stay_visible(self):
        left, right = side(["a", "b", "missing"]), side(["b", "a", "extra"])
        right["symbols"][0]["size"] = "8"
        result = analyze({"left": left, "right": right}, "incomplete")
        self.assertEqual(result["missing_functions"], ["missing"])
        self.assertEqual(result["extra_functions"], ["extra"])
        self.assertEqual(result["size_differences"], ["b"])
        self.assertEqual(result["minimum_moves"], 1)

    def test_generated_destructor_order_requires_review(self):
        wanted = ["__dt__ParentFv", "array_ctor", "array_dtor", "sinit"]
        current = ["array_ctor", "array_dtor", "__dt__ParentFv", "sinit"]
        moves = plan_moves(current, wanted)
        self.assertEqual(moves, [{"function": "__dt__ParentFv", "before": "array_ctor",
                                 "special_member_or_runtime": True}])

    def test_all_small_permutations_have_minimal_executable_plans(self):
        wanted = list("abcde")
        for permutation in itertools.permutations(wanted):
            current = list(permutation)
            # Independent brute-force subsequences verify the minimum move count.
            longest = max(len(part) for count in range(6)
                          for part in itertools.combinations(current, count)
                          if list(part) == sorted(part))
            moves = plan_moves(current, wanted)
            self.assertEqual(len(moves), 5 - longest)
            for move in moves:
                current.remove(move["function"])
                anchor = move["before"]
                current.insert(current.index(anchor) if anchor is not None else len(current), move["function"])
            self.assertEqual(current, wanted)


if __name__ == "__main__":
    unittest.main()
