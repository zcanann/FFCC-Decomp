# Keys and Locks

## In short

Dungeon gates are opened by carrying a key item to a pedestal (a `Lock`). Some
keys are dropped by a specific monster. Two script bugs sit in this system:

1. **A key you are holding can be "dropped" again by the monster that carried
   it (script logic confirmed).** The flag that says "a player is holding this
   key" is wiped on every map load before monsters check it. When you bring a
   monster-dropped key back into its original area, the dead carrier sends a
   "pop out of me" command to the key in your hands. What that looks like in
   game hasn't been tested.
2. **Placing a key writes two unrelated globals (confirmed, no visible effect
   found).** A copy-paste slip indexes the "player is carrying" arrays with the
   item class (12) instead of the player number.

There is also no "which key fits which lock" rule: any key opens any lock in
the same dungeon.

See [README](README.md) for the notation (`G<n>`, `this.m<n>`, "line N").

## 1. Held key re-pops from its dead carrier

**Status:** Script logic Confirmed. In-game effect is a Hypothesis (not tested).
**Applies to:** both.

When a monster that carries a key spawns, its `initMonster_Logic` decides
whether it still has the key. It checks two things:

- is the key already on a lock (`G43[lock] == key + 100`)?
- is a player holding it (`G35[key] == 1`)?

If neither, and the monster is already dead (its spawn bit is set), it sends
`send_class(305)` to the key object. That command teleports the key to the
monster's position, gives it a small "pop" impulse and, three frames later,
switches it to the "lying on the ground" state with pickup collision. If the
monster is alive, it is marked as carrying the key again.

`G35[key]` is set to 1 when a player carries a key through a map exit (player
`send_int` 63) or a game over. But every map with locks runs an included macro
while it creates its locks, and that macro clears `G35` inside its search loop.
It runs after the player (and the held key) has been re-created, and before
`spawnMonsters()`:

```c
// city_0 director (macro source lines 6-12, then 267)
SPAWN_PLAYER(1);                              // re-creates the key in your hands
G827[0] = new Lock(0, 26);
for (G1486 = 0; G1486 < 8; G1486 += 1) {      // 10
    G35[G1486] = 0;                           // bytecode 0x0606: load G1486; addr G35[]; pushi 0; st
    if (G43[G1486] == 100) G1486 = 100;
}
...
spawnMonsters();                              // 267
```

```c
// city_0 initMonster_Logic, lines 164-176
if (G35[key] == 1) G1485 = 100;               // 166: never true any more
if (G1485 < 100) {                            // 167
    if (getSpawnBit(G816, this.m0 - 101))     // 168: carrier already killed
        G819[key].send_class(305, classId);   // 170: pop the key out of the carrier
    else
        this.m2 |= 32;                        // 173: carrier "has" the key again
}
```

`G819[key]` is the key object you are holding. `SPAWN_PLAYER` re-creates it in
your hands under the same slot (source line 1386). `send_class` case 305 does
not look at the key's current state (source lines 182-191).

The spawn bit is set natively when a non-respawning monster dies
([monobj.cpp:2774](../../../src/monobj.cpp#L2774)). It persists until you leave
the dungeon. For a monster that respawns, the bit is never set, so it is marked
as carrying the key again and pops it when you kill it a second time.

**How to trigger** (example: Goblin Wall, gob_1):

1. Kill monster 159 near (610, 125, -471). It drops key 0. Pick the key up.
2. Without placing it, take one of the exits back to gob_0.
3. Come back into gob_1 holding the key.

The same layout exists in city_0 (monster 72/73, key 0, exits to city_1),
mine_1 (monster 52, key 0, exits to mine_0/mine_2), ruin_0 (keys 0/1, exits to
ruin_1) and river_0 (keys 0-2). In river_0 the reload can also come from
choosing "Return to River Belle Path" at an exit, the Moogle house, or a game
over and continue, none of which clear spawn bits. The macro is present in all
twelve lock maps: city_0/1, fort_0, gob_1/2, mine_1, river_0, ruin_0/1/2,
tutorial_0, water_0.

**Consequence (untested):** the script side is certain. What you see depends on
the native carry code, which may keep the key attached to your hand and ignore
the `setPos`. Two outcomes fit:

- the key jumps out of your hands to where its carrier died, or
- the key stays in your hands but is now flagged as a free ground item with
  pickup collision, which might let another player pick up "the same" key.

There is still only one key object, so this can't create a second key.

## 2. Placing a key writes `G18` and `G19[3]`

**Status:** Confirmed (bytecode). No visible effect found.
**Applies to:** both.

When a key lands on a pedestal, CarryItem PRG 306 clears "this player is
carrying something". It indexes with `this.m0`, which in CarryItem is the item
class (12 for keys), instead of `this.m16` (the player):

```c
// mainCarryItem case 306, lines 626-629, identical in all 132 scripts
G10[this.m0] = 0;   // G10 is 4 slots (10-13); [12] is slot 22 = G19[3]
G6[this.m0]  = 0;   // G6 is 4 slots (6-9);   [12] is slot 18 = G18
```

Script arrays have no bounds check
([cflat_runtime.cpp:640](../../../src/cflat_runtime.cpp#L640)). The global
layout is the same in every script: G6 = slots 6-9, G10 = 10-13, G14 = 14-17,
G18 = 18, G19 = 19-34. The player's own entries are cleared correctly elsewhere
(`onCommand` case 5, lines 110-111).

`G18` is the spawn-condition mask that `SPAWN_MONSTER` rebuilds at the start of
every map load. After a pedestal is filled it is read only in a few places that
don't care (gob_1's per-frame BG mask refresh, gob_2 boss checks that run
earlier, kinoko_0's camera, which has no pedestals). No script ever sets `G19`
to non-zero. So the write is latent: any future check of `G18` after a key is
placed would see 0.

## 3. Picking a key up again during its placement delay

Placing an item is two steps: the native drop, then a scripted flight to the
pedestal that starts a few frames later. Pedestal items have no guard against
being picked up in between. If that window exists, one key could open two
locks. This is a Hypothesis; see
[chalice-and-mog.md](chalice-and-mog.md#3-picking-the-chalice-or-a-key-up-during-its-place-delay)
for the full analysis, which covers the chalice too.

## 4. Any key opens any lock

**Status:** Confirmed. Design note, not a bug.
**Applies to:** both.

The placement check is only `target.worldParamA == 26 && carried.m0 == 12`. It
then writes `G43[lock] = key + 100`, and gates test `G43[i] != 0`. Keys are
interchangeable inside a dungeon, including across its maps (for example a
ruin_0 key on a ruin_1 lock). There are as many keys as locks, so this can't
softlock.

Two players placing keys on the same pedestal in the same frame can't both
succeed: the first `onCommand` reserves the pedestal (`m2 = 3`) in the same
call.

## Minor and latent

- **gob_2 reuses `G51[7]`.** Key placements set bits 1 and 2 in `G51[7]`, and
  gates open on `!= 0` and `== 3`. The director resets `G51[7] = 0` on every
  load without rebuilding it from the locks (source line 492), and the shared
  Iron Giant callback `onProgram(10, 0)` decrements the same slot. This would
  softlock a half-filled gob_2, but gob_2 can't be re-entered (its exits are
  empty and a game over goes to the Continue screen). Not reachable.
- **gob_2 checks a lock that doesn't exist:** `if (G43[3] == 103)` (source
  line 128). gob_2 only has locks 1 and 2. Copy-paste leftover.
- **fort_0 sound slots.** The lock fountains and `JochuSE` both use
  `G934[5]`/`G934[6]` for looping sounds. Placing key 0 or 1 overwrites the
  ambience handles, so the old loop can't be faded by handle afterwards
  (audible effect untested).
- **Lock cutscenes can cut each other short** in multiplayer. See
  [dungeon-puzzles.md](dungeon-puzzles.md#overlapping-gate-cutscenes).
