# Unused, Debug and Cut Content in the Scripts

## In short

The retail scripts still contain developer tools, test maps, cut cutscene
steps and placeholder text. Most of it is reachable only through the debug
start map (`startmap`), which no normal path loads. Everything here is
Confirmed from the scripts unless marked otherwise.

## Debug tools and test maps

- **`startmap`**, the developer start map: character-creation shortcuts
  (`debug_chara_making_1..5`), map jump menus (`debug_jump_dun`, `_kai`, `_num`,
  `_phs`, `_snd`, `_ssr`, `_top`, `_tst`, `_twn`, `_zon`), item test NPCs, a
  player database and party copy helpers. It loads `test.cfd`, which still has
  untranslated Japanese debug strings in the PAL build. It is reached only
  through the `default:` branch of every map's Mog-house return table (an
  unknown `G59`), which no live path hits.
- **Debug bits in `G88`:** 1 = no map exits, 16 = no BGM loading, 32 = no map
  sound, 64 = no stream.
- **`mail.cft`**, a letter test bench reached from startmap: a main menu (MAIL
  CHECK / SYS / CARAVAN / FOOD / JOB / FAMILY / LIKE / FREE ITEM / MAP JUMP), a
  letter menu that calls `addLetter` directly, flag and word editors, food,
  job, family-name and affection editors, an item spawner, a map jump, and a
  `G88 ^= 2` toggle. `printFlag_EVsF` has a duplicate `case 0`.
- **`uma_1.cft`:** a test town with 17 generic NPCs, a shop, a smith and
  `loadCFD('test')`. Its `send_int` still calls `printf` (line 117).
- **`miya_0..3.cft`:** a monster, effect and map viewer on the River Belle map
  (`DrawMenu`: "ACTION MON / SELECT MAGIC / EFFECT NO", monster HP forced to
  16), with `Map_Load_*` for every map. They carry the full player library.
- **`map_test`:** loads map `G83`/`G84`. With no party it builds 8 test
  caravans with random food and names slots 0, 1, 2 and **4** (slot 3 is
  skipped) "1st/2nd/3rd/4th person" in Shift-JIS. Player 2's pad bit `0x100`
  starts a 2000-frame fly-through camera. Its 4-player layouts are dead because
  `G466` is set to 1 first.
- **"Sign of Debug" (`HajimariDebugMenu`)** in village_0 and stream_0: compiled
  but never created with `new`. village_0 places it at (258.8, 10.8, 609.5).
  Its text survives in `village.cfd` 140-146: "You address the Sign of Debug.
  Show all families' data / Advance a year (This year: N) / Change tree to
  cherry cluster tree / Change crop to round corn / Give us a cow / Send wheat
  seeds to farmers / Make a temporary caravan / Jump to a different map /
  Optimal battle gear / Cancel", with a jump list "This map / Festival /
  Departure / Crab boss / Last boss / Ending (B)". The village_0 EventClient has
  no handlers for these options. stream_0's copy holds 1,000,000 gil and item
  grants (source lines 139-167).
- **Debug party.** Every dungeon's `INIT_PARTY` (source lines 17-99) builds a
  test caravan named "Ciaran", "Lu'ge", "Cyadd Gael" and "Ilias" when the map
  is started directly (all four `wmBackupParams` are -1). The language is a
  compile-time `switch (3)`; case 1 holds the Japanese names. A second preset
  is used when `evtFlag[504]` is set.
- **river_0 "no monsters" mode** (`G91`, from the startmap menu): spawning
  returns early, and `initCarryItem` places keys 0-2 next to their locks.
- **Road event launcher:** startmap cases 300+ load each `kai_*` directly with
  `G59 = 123456789`. The shared return macro checks that value and goes back to
  `startmap` instead of the world map.
- **`ff44_3` / `ff44_2` / `ffcc_4` / `ffcc_0`** can be started from startmap.
  `ff44_3` has a fixed fallback party (401/402/403/500) for that case.
- **Debug text overlays:** `ffcc_5` prints `mVal3=%d` / `mVal4=%d` every frame
  (lines 342-343), mine_3's tree prints `TIME=%3d`. `dispPrintf` only draws
  when a debug-menu flag is set
  ([p_graphic.cpp:722](../../../src/p_graphic.cpp#L722)), so players never see
  it.

## Boot, title and system

- **NTSC progressive-scan prompt.** `ffcc_0` case 700 (lines 259-326) is a
  complete "Display in Progressive Scan Mode?" flow (hold B at boot) using
  messages 0-2. Nothing enters state 700, and PAL forces 50 Hz. The text
  survives in all five PAL languages.
- **`LightEditor` (ffcc_2):** a full live lighting editor (ambient, three
  diffuse lights, map shade, fog, shadow X/Y) with an on-screen HUD. Never
  created. Its help text is probably `ffcc.cfd` message 44 ("... Press START to
  open debug menu."), which no script uses.
- **`KeyCheck` (ffcc_2):** waits for START on any pad and sets `G2007`, which
  nothing reads.
- **Unused `ffcc.cfd` messages:** 23-25 (logo cards for Nintendo, Game
  Designers Studio and Square Enix), **26 (a "Start / Continue / Debug" title
  menu)**, 27 (copyright line), 39-42 ("Single-Player Mode", "Multiplayer
  Mode", "OK", "Checking... 1P= 2P= 3P= 4P="), 43 (opening narration), 44, and
  **49-50, a build stamp ("Local Complied on 10/31 19:51", "Friday")**. Native
  code may use some of these; that wasn't ruled out.
- **`ffcc_0` logo region:** `onDraw` case 1 draws the top 448×104 of
  `crp_logo`, but `G2004` is only ever 0 or 2.
- **THE END's "return to title" code** is dead; see
  [bosses.md](bosses.md#8-the-end-never-returns-to-the-title).
- **`Liquidate`** (all 15 boss maps, line 485):
  `if (getElfType() == 2 && 0 == 1) loadCFlat('ffcc_2')`, a disabled jump.

## Dungeons

- **mine_3 myrrh-tree camera test.** Only mine_3's ManaTree has a talk handler
  (`onTalkManaTree`, line 216). It triggers three spline camera sweeps over the
  arena (300 + 300 + 600 frames) printing `TIME=%3d`. The tree never gets a
  talkable collision mask, so it's probably unreachable.
- **castle_1 `AnimTestQuad`:** door trigger zones at castle_0's door
  positions, never created.
- **castle_1 cut Fiona steps:** a second `case 207:` (line 1032) that can't
  run, `send_intEventDirector` cases 208-218 that nothing sends, and
  `mainPrincess` PRG 209.
- **lava_0 `forEffect`:** never created. It would ride the ferry projecting a
  60-unit miasma-safe bubble, perhaps a cut "chalice protection on the ferry".
- **lava_0 ship trigger:** the location title waits for frame 1630 to start
  the ship (PRG 699, `G65 |= 64`), but its counter stops at 470. Dead.
- **river_1 `BossQuad`:** four push zones that count players into `G2204[]`,
  which nothing reads. Never created. Possibly a cut Giant Crab mechanic.
- **river_0 sign cameras:** EventCamera 201/207/208/209 pan to the four
  signposts and are never requested (`singleEventCamera()` has no callers).
  river_0 also has unused GBA marks 2-4 on its locked gates.
- **Daemon's Court (fort_0) monster PRG 82** drops the log bridge, but no
  script sets it; see
  [dungeon-puzzles.md](dungeon-puzzles.md#5-daemons-court-log-bridge--conall-curach-obstacles).
- **ruin_0:** unreachable copies of ruin_1's barrier helpers, and a `G367`
  branch (native-set, possibly an attract mode) with a reduced setup: one lock,
  no moogle, no shrines, a single key carrier.
- **Moschet Manor (gigas):**
  - gigas_1 line 73: `if (G599[0].hp == 0) G51[0] = G51[0];` is a no-op copy of
    the Tonberry kill tracker, on a map with no monsters.
  - gigas_0 creates race switches 0-4 and 6-9 but not 5 (source line 889 is
    missing); switch 4 also opens door 5, which has no sound.
  - gigas_8, the boss arena, reuses the gigas_0 hall geometry.
  - Map exits contain a dead `if (5 == 15 && evtFlag[81] ...)` warp to
    `farewell_1`.
- **stream_1 Carbuncle close-up** can't play: the trigger is checked once
  before the loop, and `G2005`/`G2006` are never written. A placement branch
  for the wrong element is also dead.
- **tutorial_0:** the "leave dungeon" prompt reloads the tutorial or shows
  message 98. Director program 1024 has two `case 1024:` blocks (lines 994 and
  1010), and nothing sets 1024.
- **gob_2** checks lock 3, which gob_2 doesn't have (line 128).
- **Unfinished pot carrying** between maps: see
  [chalice-and-mog.md](chalice-and-mog.md#minor-and-design-notes).
- **NTSC-only branches** `if (0.833333 == 1.0)` in lava_1 and lava_2 are dead
  on PAL.
- **Compiled-out blocks:** `if (0) { ... loadMergeFile ... }` in directors (for
  example cave_0 lines 196-257), `if (0)` camera calls in thief_1, and a
  `G59 = G59` no-op in GameOver.
- Never-created classes: port_2's MogSu, `Tegami` in mail/meteo_2/meteo_3,
  `BossAppearGamenWare` in meteo_3. MogSu wander states 552-555 are
  unreachable.
- Empty or stub functions: `onTalkLock`, `onTalkHotSpot`,
  `onDamageCarryItem`, `DEBUG_BG_GROUP_COLOR()` (fort_0/1), `resLoop()` in
  meteo_0, `onPushMagicBridgeQuad` in magic_0. `TreasureBox.m20` (a timer) is
  computed but never read, and every chest passes 0.

## The Unknown Lands and the ending

- **The memory quiz was cut from 10 doors to 7.** last_1 advances
  `eventWork[100]` 4 → 5 → **7** and last_2 7 → 8 → **10**. The `== 6` and
  `== 9` branches, and their dispatcher entries, are dead. `G2042 = 10 -
  eventWork[100]` is still computed for message 248, but the English text
  ("Prepare yourself.") doesn't show it.
- **Placeholder question:** last_0 state 251 and last_1 state 208 show
  `last.cfd` 188/189: "It was in Year ??... (Question)" / "What were you doing
  at that time? Answer A (Right) / Answer B (Wrong)". Neither state is entered.
- **`last.cfd` leftovers:** 247 "That's all I've got. Sorry." and 286-301, two
  runs of "8/8" ... "1/8".
- **last_4 `Omoide_Capsule_Appear`** only writes `G2041`, which nothing reads.
- **Staff roll:** `ff44_3` classes `fa084` and `fa094` (actors with timed moves
  at frames 2500 and 2583) are never created.

## Towns and letters

- **Letters with condition type 0** (#54, #120, #134, #137) have text and
  replies but can't be sent; see
  [towns-and-letters.md](towns-and-letters.md#1-six-letters-that-never-arrive).
- **`mog_0` Mogri case 35** (shop, falls through into `default`) is dead: no
  `m30 = 35` exists.
- **Hidden moogle gift table** (EventClient case 1110): item 390 appears for
  entries 10, 22 and 23 (entry 21 gives 389). Possibly a copy-paste slip; may
  be intended.
- Both MogSu NPCs in cave_0 and city_1 use ID 136 and share a flag. No effect.
- The mog-house jump copies in gigas_3 and ruin_1 can't be triggered.

## Road events

- **`kai_fam.cfd` message 48:** "Viewable debug mode. You must complete the
  event or the event flag will be corrupted. ▸Year 3 version. / Year 6
  version." A debug selector for fam_2's two variants.
- **`kai_sma.cfd` 48, 49, 62:** "M-Moogles are too cute to hurt, kupo!", "I
  said, moogles are—", "Ngah...". Cut lines from the Brigands' charge-through
  scene.
- **Every `kai_*.cfd`, messages 10-12:** "Monster attack info. Dummy", "Monster
  material info. Dummy", and an item selector with "Cancel". An unused shared
  template.

## Placeholder text

- `world.cfd` 330 "Your element is bugged." (unreachable default case).
- Diary placeholders, `world.cfd` 53/63/91 and `festa.cfd` 59/69/97: "Not used.
  If found, it's a bug.", "This shouldn't appear. Report this bug if found.",
  "If this appears, it's a bug." These are the default slots of three road
  events that always record a different entry. Diaries 123-131 are blank.
- Build stamps: `world.cfd` 314 and `festa.cfd` 320 ("2003/12/10 17:49/18:02
  Wednesday master").
- `mog.cfd` 34 "Aw, there's a bug, kupo!" is unreferenced.
- `c_system.cfd` 16/17 "Letter body test" / "Reply test" (letter #0) and 1078
  "Test message".
- Message 0 of `farm`, `magmell`, `mog`, `port` and `tutorial` is
  "Dummy."/"Dummy!". `weapon.cfd` 0-1: "Dummy message! Will not be used." and
  "welcome to the weapon town. You're now reading a dummy message.".
- Joke that does show: river_0 sign message 26, "Right: Lots of Monsters /
  Left: Lots of Monsters".
