# Dungeon Puzzles

## In short

Per-map puzzle logic lives in each dungeon's `myMapGimmik` class and a few
special classes (carts, bridges, switch spheres, foot switches). No hard
softlock was found. The most useful findings for players:

1. **Mt. Kilanda's first area opens both lava barriers on a timer
   (confirmed).** Wait about 2 min 24 s and 4 min 48 s and the puzzle solves
   itself.
2. **The Mine of Cathuriges cart can be switched onto the wrong rail line
   (logic confirmed, look untested).** This bypasses the second points switch.
3. **Tida's barriers can be worn down with weapons, and each hit can drop an
   item (confirmed, looks intended).** The drop limiter resets every time you
   re-enter the map.
4. **Monsters count as players on some floor switches (confirmed).** A lured
   monster can hold a two-player plate in River Belle Path.
5. **Daemon's Court's log bridge changes Conall Curach (confirmed mechanism,
   intent unknown).** Each time the bridge falls, one more obstacle in the
   second Conall Curach area disappears, for the rest of the save.

## 1. Mt. Kilanda (lava_0): the lava barriers open on a timer

**Status:** Confirmed (bytecode). It may be a deliberate failsafe; either way
it's retail behaviour.
**Applies to:** both.

The two barriers are meant to open when a carried object is thrown into the
matching lava hole (CarryItem state 324 → `send_intLavaHole`, which sets the
barrier bit). The gimmick also counts frames since the map loaded and sets the
same bits on its own:

```c
// lava_0 mainmyMapGimmik
if (this.m17 < 30000) this.m17 += 1;     // 126
if (this.m17 > 7200)  G51[0] |= 1;       // 127: barrier 1
if (this.m17 > 14400) G51[0] |= 2;       // 128: barrier 2
```

`m17` is reset to 0 only in `initmyMapGimmik` (line 94). lava_1 has the same
gimmick without the timer.

**How to trigger:**

1. Enter lava_0.
2. Stay on the map. Idling is enough.
3. After 7200 frames (about 2 min 24 s at 50 fps) barrier 1 erupts and opens.
   After 14400 frames (about 4 min 48 s) barrier 2 opens.

**Consequence:** the lava-hole puzzle can be skipped by waiting. `G51[0]` is a
stage variable, so once opened a barrier stays open on re-entry for the rest of
the dungeon visit. The timer restarts on each entry.

## 2. Mine of Cathuriges (mine_0): the cart jumps to the wrong line

**Status:** Logic Confirmed (constants checked in bytecode). What it looks like
in game is a Hypothesis.
**Applies to:** both.

Every hit on the cart (`Truck`) re-picks which rail line it follows from the
distance travelled so far (`m14`):

```c
// mine_0 onDamageTruck
this.m22 = 10;                                   // 551: south line
if (this.m14 < 500.0)       this.m22 = G51[0] ? 8 : 9;   // 552-553: first switch
else if (this.m14 < 1440.0) this.m22 = G51[1] ? 10 : 8;  // 555-556: second switch
if (posX > 555.5)           this.m22 = 8;        // 558: east line
```

Past distance 1440 the line is forced to 10 (south) unless the cart is already
east of x = 555.5. On the east line (8), x passes 555.5 only at distance ≈1499.
Lines 8 and 10 split at distance ≈1427. Each push moves the cart 208 units
(`mainTruck` lines 511-522: 6.4 + 6.3 + ... + 0.1).

**How to trigger:**

1. Set the second fork east with foot switch 3 (`G51[1] = 0`).
2. Push the cart from the start. The 7th push stops it at ≈1456, inside the
   1440-1499 window.
3. Push it an 8th time. It is put on the south line at distance 1456, toward
   woodbox 9.

**Consequence:** the cart hops tracks (probably a visible jump) and breaks
woodbox 9 with the switch set east, bypassing the second points puzzle. The
break is saved in `G51[2]` and persists for the visit.

Related: line 9, the dead end to woodbox 1, is about 493 long. A cart stopped on
line 8 between distance 483 and 500 that is then switched to the branch fails
the length check on its next hit and teleports back to the start (lines
512-526). That only loses progress.

## 3. Tida (ruin_1): barrier spheres

**Status:** Confirmed. The weapon wear-down looks intentional.
**Applies to:** both.

### Weapons wear barriers down, and hits can drop an item

- Each of the 21 barriers has a budget `m22` of 64 in single player or 32 in
  multiplayer (`resInit` line 104). Magic spends `m5 - 1` per dispel; every
  weapon hit spends 1.
- When the budget reaches 1, the next hit runs the dispel without its particle
  and leaves the barrier permanently down. About 64 weapon hits (32 in
  multiplayer), at most one per ~16 frames, remove a barrier with no magic. A
  strong enough spell does it in one cast.
- Each weapon hit can drop item 256 (`onDamageSwitchSphere` lines 1311-1317):
  chance 2 / (8 + `G51[6]` + barriers already down). There is no drop if
  `checkItem(2, 256)` returns 2 (the attacker already has it). tutorial_0 gives
  item 256 behind the same check, which suggests a magicite.
- `G51[6]` is a per-visit limiter: each drop adds 1 (cap 16), and it decays by
  1 every 1800 frames. `initmyMapGimmik` resets it to 0 on every map load (line
  185).

**How to farm:** hit barriers for drops; when they dry up, leave ruin_1 and come
back. The odds are back to the maximum (25% on the first hit).

### Leaving mid-dispel may keep a barrier down

**Status:** Code path Confirmed. Whether it can be reached in time is a
Hypothesis.

`resFunc` (lines 118-140) sets the barrier's "dispelled" bit in `G51[4]` before
it waits, and clears it only afterwards. `resInit` (lines 105-109) treats a set
bit as permanently dispelled on the next load:

```c
G51[4] |= 1 << arg0;     // 123
wait(30);                // 124
wait(8 * this.m5);       // 128 (+4*m5 more in multiplayer)
/* clear the bit */      // 129
```

If the map unloads inside that window (62-222 frames depending on the spell
and player count), the barrier stays down until you leave the dungeon. The
nearest barriers are about 215 units from an exit, so this may not be
reachable.

## 4. Monsters can hold floor switches

**Status:** Confirmed. Intent unknown.
**Applies to:** both.

River Belle Path (river_0, line 432) and the fort_1 boss arena (line 208)
accept anything that is a player, the chalice, or a monster:

```c
if (arg0.m0 < 8 || arg0.m0 == 10 || arg0.m0 > 100)   // monsters are 101+
```

city_0, city_1 and mine_0 accept only players and the chalice.

- **river_0:** the gates need both plates of a pair held. A monster lured onto
  one plate counts as the second player, so a pair can be solved alone.
- **fort_1:** the switches feed the boss's state (`sysControl(3, G51[3])`).
  The boss or its minions standing on a switch change the boss state.

## 5. Daemon's Court log bridge → Conall Curach obstacles

**Status:** Mechanism Confirmed (bytecode). Intent is a Hypothesis.
**Applies to:** both. The value is per save file.

`eventWork[3]` is saved story work. fort_0 is its only writer and swamp_1 its
only reader:

```c
// fort_0 mainnewLogBridge, each time the log bridge falls
if (eventWork[3] < 6) eventWork[3] += 1;          // 424

// swamp_1 initmyMapGimmik, lines 38-58
switch (eventWork[3]) {
    case 0:  /* both obstacles (BG groups 13, 14) present, GBA marks on */
    case 1:  /* group 13 removed */
    case 2:  /* groups 13 and 14 removed */
    default: /* 13, 14 and 15 removed */
}
```

Native code only saves and loads it. swamp_1 source lines 30-37, just before
the switch, produce no code, which may be removed handling.

**What drops the bridge:** switch sphere 28000 sits next to the map's only Bomb
(monster 4). In `onHitParticleSwitchSphere` (lines 1177-1188), only particle 595
(the Bomb's self-destruct explosion) counts. Player spells and weapons don't.
If you kill the Bomb before it explodes beside the sphere, or lure it away, the
bridge doesn't fall that visit.

**Consequence:** how open the second Conall Curach area (swamp_1) is depends on
how many separate runs dropped the fort_0 bridge. The cap of 6 and the
`default` case suggest a deliberate cross-dungeon link, but two designers
reusing the same index can't be ruled out.

fort_0 also has `G51[7] = 1` (bridge falls) in monster PRG 82 (source lines
264-276), but nothing ever puts a monster in PRG 82. It looks like an older
"any Bomb explosion drops the bridge" design.

## 6. Rebena Te Ra (city_1): leaving during the orb window deletes an orb

**Status:** Confirmed. **Applies to:** multiplayer (needs two players).

Orbs 30103 and 30104 must both be hit within a short window. A hit sets a saved
bit in `G51[6]`, cleared about 91 frames later if the partner orb wasn't hit
(`resFunc` lines 467-478). If the map unloads first, `resInit` (lines 397-412)
sees one bit without its partner on re-entry, shows the barrier and deletes
that orb. The bit stays set, so hitting the other orb alone later opens
barrier 1.

**How to trigger:** one player hits an orb; within about 41 frames the chalice
carrier steps into a map exit (exits fire after 50 frames). The orbs are far
from the exits, so it takes two players.

**Consequence:** one orb is gone for the visit. Not a useful shortcut.

## 7. Lynari Desert multiplayer quirks

**Status:** Logic Confirmed. Effects are minor.
**Applies to:** multiplayer.

- **Quicksand exit, last player decides.** `mainmyMapGimmik` (desert_0 line
  104, desert_1 lines 63-76) loops over the players and overwrites one flag per
  player, so only the highest-numbered present player decides whether the
  sink-and-pull animation plays. In desert_1 the check is outside the `hp`
  test: if that player is KO'd, the animation doesn't play. In desert_0 the
  sink point may come from a stale player. The map change itself still
  happens.
- **KO'd players hold the descent waves.** desert_2 advances a tier when
  "players with posY < 112 + chalice == players + 1" (lines 92-111). A KO'd
  player counts by position only, so one KO'd upstairs holds the next tier
  until revived.

## 8. Stream exits need the chalice in your hands

**Status:** Confirmed. Probably intentional. **Applies to:** single player.

Normally a single-player exit also fires when Mog holds the chalice
(`onPushMapJump` lines 140-142). stream_0 and stream_1 leave that branch out,
and their stage-23 guard (`G468 == 0 && 23 != 23`) is always false. In single
player you must carry the chalice yourself to leave a miasma stream map.

## Overlapping gate cutscenes

**Status:** Confirmed. Cosmetic or minor. **Applies to:** multiplayer.

Key placements (river_0, city_0/1, fort_0 and others), foot-switch gates
(river_0 lines 224-282, cave_0 lines 214-272) and water_0's switch spheres run
their cutscene inside the triggering object:

```c
G1461.setPRG(20x); sysControl(11, 1); sysControl(12, mask);   // freeze
wait(60..100);
sysControl(11, 0); sysControl(13, mask); G1461.setPRG(0);     // unfreeze
```

If two are triggered within that window, the first to finish resets the camera
and unfreezes players and monsters while the second is still playing. fort_0
guards its reset with `if (G1461.m5 == 20x)` (lines 983, 1001); the others
don't. Nothing persists past a map change.

cave_1's gate cutscene (lines 107-131) never calls the freeze pair at all, so
players keep control during it.

## 9. meteo_1 vent taint can leave a particle running

**Status:** Confirmed. Cosmetic. **Applies to:** both.

When the chalice touches a vent (`onPushSwitchSphere` lines 1338-1344), the
game turns on "miasma everywhere" (`sysControl(10, 1)`) and starts that vent's
particle. Breaking *any* vent (`resFunc` lines 606-620) cures it but ends only
the broken vent's particle. Touch vent A and break vent B, and A's particle
keeps playing. Broken vents can't re-taint the chalice.

## 10. stream_0 current only reads exact D-pad directions

**Status:** Hypothesis, needs an in-game test. **Applies to:** both.

stream_0 `mainTeikou` (source lines 433-1007) reads only digital direction
bits, mapped to a fixed axis per stream. It changes speed only when the exact
"toward" or "away" bit is held, and pushes back only when no direction is held.
Holding a perpendicular direction keeps the previous frame's speed, possibly
the boosted retreat speed, and suppresses the push-back. stream_1 rewrote this
with analog input. Backstops (a forced 150-frame push-back at the stream edges
with the wrong element) make a clean crossing unlikely.

## Minor and cosmetic (confirmed unless noted)

- **city_1 barrier 2 hum is inverted.** `if ((G51[6] & 32) == 0) { } else
  { playSe3D(120014, ...); }` (lines 67-69; the then-branch is a bare jump in
  bytecode). Barrier 2 is silent while closed and hums after it opens. The
  dissolve sound also replays for each solved barrier on every re-entry.
- **lava_0 title skip doesn't skip the ship.** The skip sends the ferry PRG 766
  (line 1250), but in the same tick `send_class(0)` (line 1283) restarts its
  arrival. Skipping still plays the whole ship arrival with players locked.
- **desert_0 hidden shrine setup runs every frame** after the puzzle is solved
  (`mainHotSpot` lines 946-962). Same net state each frame; no visible effect.
- **swamp SinkQuads:** swamp_3 quads 1-3 share splash particles 54/55 while
  swamp_1/2 give each quad its own pair (Hypothesis: copy-paste). All quads
  write the same footstep/splash globals each frame, so the last one wins.
- **swamp_2 ambient particle** is started with `putParticleTmpPos` but stopped
  with `endFieldParticle(63)`, which does nothing (Hypothesis: slot leak).
- **lava_2:** a pot thrown into a suppressed lava hole goes to PRG 325, which
  has no handler; the pot is wasted.
- **fort_0 chest** at (-481.38, 60.47, -374.71) (source line 1681) carries the
  upper-area flag although it sits outside the upper area. Its twin (line
  1677) doesn't (Hypothesis on any visible effect).
- **water_0 one-frame race** (Hypothesis, very unlikely): a switch-sphere talk
  and a magic hit landing in the same frame can leave miasma damage off and
  monsters frozen until the map changes (EventClient case 20 lines 372-373,
  `resFunc` line 212).
