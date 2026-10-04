# Bosses and Their Cutscenes

## In short

Boss fights are mostly native code, but the arena, the phase cutscenes, the
intro skip and the victory sequence are scripts. The findings, most
interesting first:

1. **Meteor Parasite can be killed before its arena changes (confirmed in code,
   untested in game).** The script only changes arena when the core reports a
   phase change. A hit that takes the core from above its threshold straight to
   0 HP skips both arena changes, and the normal ending still plays.
2. **Meteor Parasite's arena changes fully heal and revive the party
   (confirmed).**
3. **Killing Gigas Lord during Maggie's entrance hands control back in the
   middle of the victory scene (race confirmed in script, effect untested).**
4. **Moschet Manor's entrance hall re-closes doors you opened (confirmed in
   script).** On later visits a hidden title-cutscene actor still runs its
   timer and slams doors 4-7 shut about 25 seconds after you enter.
5. **Skipping the Moschet Manor title cutscene leaves boss models standing in
   the hall (confirmed in script).**
6. **Skipping the fort_1 boss intro leaves the arena gates drawn open
   (confirmed).**
7. **The post-boss Start skip can run the myrrh-camp step twice (race
   confirmed, effect untested).**
8. **THE END never returns to the title (confirmed).**

## 1. Meteor Parasite: one hit to 0 HP skips the arena changes

**Status:** Confirmed in script and native code. Not tested in game.
**Applies to:** both.

The fight script (`meteo_2`) has no phase counter. `MeteoBattle` watches
`getSysControl(3)`, the native boss state, and plays arena change 1 when it
becomes 1 and arena change 2 when it becomes 2:

```c
// meteo_2 mainMeteoBattle, lines 103-148
switch (getSysControl(3)) {
    case 1: if (G1722 == 0) { G1722 = 1; G1578.setPRG(205); ... }  // arena change 1
    case 2: if (G1722 == 1) { G1722 = 2; G1578.setPRG(207); ... }  // arena change 2
}
```

The win check is the generic boss check, which ignores the phase:

```c
// meteo_2 mainMonster_Logic, lines 454-457
if (this.m1 == 11 && G811 == 1 && hp == 0) setPRG(44);   // -> victory
```

Natively, the core requests state `0x66` when its HP drops below 2/3 (first
core) or 1/3 (second core)
([monobj_boss.cpp:1198](../../../src/monobj_boss.cpp#L1198)). The boss state is
incremented only on frame 0 of state `0x66`
([monobj_boss.cpp:1166](../../../src/monobj_boss.cpp#L1166)). In
[`addHp`](../../../src/charaobj.cpp#L1962), the damage callback runs first and
requests `0x66`, then, because HP is now 0, `changeStat(9)` (death) replaces it
in the same call. State `0x66` never reaches frame 0, the boss state stays 0,
and neither arena change plays.

The victory sequence then runs as normal: director 6 → 7 → 215-219 → 230 →
`loadCFlat('last_5')`. State 215 moves every player to the third-arena
positions (`mainPlayer_for_Battle`, lines 796-851), so the ending plays
correctly from arena 1 or 2.

**How to trigger:** while the core is exposed in arena 1 or 2, deal enough
damage in one hit to take it from above the threshold to 0. That needs damage
far beyond normal play; see [weapon-swing.md](../weapon-swing.md) for glitched
weapon damage.

**Consequence:** both arena changes and their cutscenes are skipped and the
fight ends early. No softlock and no missing flag were found.

**Why it can't advance twice:** states `0x66` and `0x67` clear collision bit
`0x80000`, and both melee hits
([gobject.cpp:2254](../../../src/gobject.cpp#L2254)) and particle hits
([pppPart.cpp:2214](../../../src/pppPart.cpp#L2214)) skip targets without it.
A hit during the retreat can't restart `0x66`.

## 2. Meteor Parasite arena changes heal and revive everyone

**Status:** Confirmed. Probably intended.
**Applies to:** both.

Arena-change cutscenes 205 and 207 set every player's `hp = maxHp`
(`mainPlayer_for_Battle` cases 205/207), without checking for KO. When the
fight resumes, state 4 (source lines 596-605) sends players with HP back to
normal play. A player KO'd before the core crossed 2/3 or 1/3 HP comes back at
full HP. The victory state also sets `hp = maxHp`.

## 3. Gigas Lord: killing him during Maggie's entrance

**Status:** The race is Confirmed in script. The in-game effect is a Hypothesis.
**Applies to:** both. Realistic only with very high burst damage.

Gigas Lord's first damage sets the boss state to 1
(`damagedFuncGigasLoad`). That starts Maggie's entrance in gigas_8
`mainmyMapGimmik` (lines 85-141). The entrance:

- takes control from all players (`setUC(0)`), freezes monster AI
  (`sysControl(12, 7)`) and switches off miasma damage (`sysControl(11, 1)`);
- takes the camera (`G1579.setPRG(230 + n)`);
- waits a fixed 120 + 60 + 90 + 90 = 360 frames (7.2 s);
- then restores everything: camera 0, Maggie's AI on, `setUC(1)` for all four
  players.

It never checks whether the battle is over (no `G811` reference in its
bytecode). Gigas isn't invulnerable during the entrance. If he reaches 0 HP in
those 360 frames, the victory sequence starts (director case 6, which pauses
Maggie and plays a 433-frame pose). When the entrance timer ends, it undoes the
victory setup:

- players get control back during the victory pose;
- the victory camera is replaced by camera 0;
- Maggie's AI is unpaused and she is moved out of her door.

If Gigas dies on the hit that starts the entrance, the entrance camera also
overrides the victory camera at the start.

**How to trigger:** take Gigas Lord from full HP to 0 within about 360 frames
of his first damage. In practice that means a one-shot, or several hits or
spells already in flight landing together in multiplayer.

**Consequence (untested):** a garbled ending with free movement and a live
Maggie. The stage-clear flow runs on its own timer, so a softlock is unlikely.

Checked: Maggie can't drop below 1 HP from a hit
([charaobj.cpp:1962](../../../src/charaobj.cpp#L1962), boss index `0x70`), and
the fight ends only when Gigas reaches 0. Neither boss can be killed early to
skip a phase.

## 4. Moschet Manor entrance hall: doors close themselves on later visits

**Status:** Confirmed in script and bytecode. Whether the closed doors block
movement is a Hypothesis (they exist to block passage).
**Applies to:** both. Easier in multiplayer.

gigas_0 always creates the title-cutscene actors (Gigas, Lamia and three
Tonberries). They are deleted only if `evtFlag[490] == 1 || G59 != 0`
(`initGigas` line 338). On a later visit from the world map only the short
location title plays (`G1007 == 2`), and nothing starts the actors
(`mainLocation_Title` starts them only when `G1007 == 1`, lines 616-624). Their
frame counter still runs. When the Gigas actor's loop times out, its cleanup
closes four doors:

```c
// gigas_0 mainGigas
while (this.m6 < 1250 && G1067 != -2) {   // 348
    ...                                   // 715: this.m6 += 1 every frame
}
G2035[4].send_int(4, 0);                  // 397: door to its "closed" frame
G2035[5].send_int(4, 0);
G2035[6].send_int(4, 0);
G2035[7].send_int(4, 0);                  // 400
```

**How to trigger:**

1. Enter Moschet Manor (gigas_0) from the world map on any visit after the first.
2. Within about 25 seconds (1250 frames), open door 4+5 (race switch 4, north
   end) or door 6 or 7 (race switches 6/7, east side).
3. When the counter runs out, the doors jump to their closed frame with no
   sound.

The race switch that opened them is finished (`mainraceSw` sets `m14 = 2`, and
`onPushraceSw` ignores it, lines 285-288 and 301), so you can't reopen those
doors until you leave the room and come back.

In single player the required tribe changes every 180 frames, so you may wait
up to 540 frames for yours. With mixed tribes in multiplayer someone usually
matches at once.

**Consequence:** a solved race puzzle undoes itself; leaving and re-entering
restores it. Not a permanent softlock.

## 5. Skipping the Moschet Manor title cutscene leaves boss models in the hall

**Status:** Confirmed in script. On-screen result inferred from `setUpdate`.
**Applies to:** both.

In the first-visit cutscene each actor is shown at one frame and hidden (moved
to x = 1000) at a later frame. Every actor loop is
`while (m6 < N && G1067 != -2)`, and START sets `G1067 = -2`
(`mainLocation_Title` line 1215). Skipping ends the loops at once, so the hide
step never runs:

| Actor | Shown at frame | Hidden at frame |
|---|---|---|
| Gigas | 54 | 1166 |
| Lamia | 337 | 633 |
| Tonberry A | 120 | 1207 |
| Tonberry B | 675 | 1166 |
| Tonberry C | 883 | 1066 |

**How to trigger:** on your first entry to Moschet Manor, press START between
frames 340 and 630 of the cutscene. Gigas, Lamia and Tonberry A stay standing
in the hall for the visit.

**Consequence:** cosmetic. They have no collision (radius mask 17). Their
cutscene flags and door-glow particle slots are also left set. fort_0's
`mainLocaLizard` (source line 683) uses the same loop pattern.

## 6. fort_1 boss: skipping the intro leaves the gates open

**Status:** Confirmed (bytecode). Collision follow-through is a Hypothesis.
**Applies to:** both.

The fort_1 intro opens three arena gates during its cutscene (states 202, 203
and 208) and closes them at the end (state 212). The skip path instead calls
`apperEndExtend()`, which sends command 4, and the gate class has no case 4:

```c
// fort_1
script apperEndExtend() {           // run by director state 299
    G2199[0].send_int(4, 0);        // 39
    G2199[1].send_int(4, 0);        // 40
    G2199[2].send_int(4, 0);        // 41
}
classsystem send_intGateAnim(arg0, arg1) {
    switch (arg0) {                 // 250
        case 1: /* animate open */  case 2: /* set closed */  case 3: /* set open */
    }
}
// normal end, director state 212 (lines 1138-1140): G2199[0..2].send_int(2, 0)
```

**How to trigger:** press START to skip the intro after about 475 frames
(9.5 s, when the first gate opens) and before the intro ends. lava_2 and
desert_2 reset their props correctly in `apperEndExtend`.

**Consequence:** the gates stay drawn open for the fight. Gate 0 is the
barrier to the myrrh-tree area, normally opened after victory (source line
1169). Gates are BG map objects, so collision likely follows the animation,
but this hasn't been checked in game.

Related, cosmetic: fort_1 state 299 places guard 102 at x = +22 and guard 103 at
x = -22, the reverse of their intro positions (lines 1909-1914 vs 2062/2067),
and doesn't reset their rotation. After a skip they swap sides and face outward.

## 7. Post-boss Start skip can re-run the myrrh-camp step

**Status:** The race window is Confirmed. The visible effect is a Hypothesis.
**Applies to:** both. Window about 30 frames (0.6 s).

After a boss dies, the myrrh-tree cutscene can be skipped with START while
`G811 == 3`. The shared skip code (Monster_Logic, source lines 464-490 in every
boss map) checks that the director isn't already in PRG 170, then fades out,
waits 30 frames, and only then sets the director to 170:

```c
if (G811 == 3 && G1578.this.m5 != 170) {
    screenFade(1, ..., 30); wait(30);
    G1578.setPRG(0); ... G1578.setPRG(170);
}
// mainEventDirector 1249-1250: PRG 221 moves to 170 by itself at frame 241
if (this.m6 == 241) setPRG(170);
```

If START is pressed in the last ~30 frames of director PRG 221, PRG 170 starts
by itself and the skip then starts it a second time.

PRG 170 (lines 1076-1193) sums every player's counter into a local, adds a
diary entry, runs the letter search, and sets the players, Mog and the letters
to PRG 170 (each does `G1316 += 1`).

**Consequence (untested):**

- a second diary entry for the clear. Locals are zeroed only when a function is
  called ([cflat_runtime.cpp:517](../../../src/cflat_runtime.cpp#L517)), so the
  sum may double and pick a different diary tier;
- the camp letter and Mog scene restart;
- `G1316` overshoots its `G463 + 1` threshold, so the director may move on to
  PRG 171 early.

No duplicate myrrh: myrrh isn't granted in PRG 170. Present in all nine boss
maps checked (cave_2, city_2, desert_2, fort_1, gob_2, kinoko_1, lava_2,
mine_3, river_1).

## 8. THE END never returns to the title

**Status:** Confirmed (bytecode).
**Applies to:** both.

`ffcc_4` shows the end card and then reaches an unconditional loop at source
line 221 (`0315 pushi 1 / jz 032F / ... jmp 0315`, nothing jumps to `032F`):

```c
if (1) { wait(1); goto L0315; }   // 221
// dead, 223-243: wait for A, setNewGame(), clear event work, loadCFlat('world') with G59 = 9999
```

After the staff roll the game stays on THE END and you have to reset. Nothing
is saved in ff44_2, ff44_3 or ffcc_4, so no progress is lost. The dead block
shows the developers once had "press A to return to the title".

## Minor and cosmetic (confirmed unless noted)

- **river_1 Giant Crab adds sit out the intro.** Director case 201 (source
  lines 601-610) only starts the crab's intro. Every other boss director also
  sends PRG 201 to the minions. The one or two monster-94 adds stay in their
  init state during the intro (Hypothesis on how it looks).
- **city_2 Lich minion sound.** Each minion stores its intro sound in the same
  global `G840` (lines 1062-1064), and the skip fades only `G840` (line 1249).
  With 3-4 players, earlier copies may keep playing if that sound loops
  (unverified).
- **city_2 portal animation.** `initPortal` loads `stand` and then `appear_a`
  into the same slot, so PRG 6 loops `appear_a` on the boss's death. The
  portal's PRG 299 (intro skip) does nothing.
- **gigas_0 `stopSe3D(113014)` / `stopSe3D(113015)`** (lines 401-402) pass
  sound IDs, but `StopSe3D` searches by handle. Skipping the title during the
  door rumble lets the sound play to its end.
- **lava_2 destination menu** (Hypothesis, probably unreachable). The post-boss
  menu sets the destination for choices 0/1 only when `eventWork[1]` is 4, 5 or
  6, with no default. Any other value would send the party to world location 0.
  `eventWork[1]` is 0-2 in years 1-3.
- **last_3/last_4 `BossAppearGamenWare`** lacks the re-entry guard the other 15
  copies have (line 122). Its only caller runs once.
