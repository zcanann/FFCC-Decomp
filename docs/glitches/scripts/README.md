# Event Script Glitches

## In short

Most of what happens in FFCC's maps (puzzles, cutscenes, boss phases, letters,
shops, road events, the memory card check at boot) is not C++ but **CFlat**, a
small scripting language compiled to bytecode. Every map has its own script.
These write-ups come from reading all of the retail PAL scripts, comparing the
many copies of shared code between maps, and checking the interesting cases
against the bytecode and the native code in `src/`.

Highlights:

- The **Slot B format prompt** at boot can format your card when you press B
  to back out (English, French, Italian, Spanish).
- **Mt. Kilanda's lava barriers** open by themselves if you wait about 2½ and
  5 minutes.
- **Meteor Parasite** can be killed before either arena change with one big
  enough hit.
- A **monster-dropped key** you carry back into its area is sent a "pop out of
  the dead carrier" command.
- **Six letters** can never arrive because of duplicate `case` labels.

## How the scripts work

- **Files.** Each map's script is `dvd/cft/<map>.cft`. Most have a
  `<map>.cft.dbg` next to them, written by the script compiler, which maps
  bytecode back to **original source line numbers**. Message text is in
  `dvd/<lang>/cft/<name>.cfd` (`uk`, `fr`, `gr`, `it`, `sp`).
- **Interpreter.** `CFlatRuntime` in
  [cflat_runtime.cpp](../../../src/cflat_runtime.cpp) loads the scripts and runs
  the bytecode (`objectFrame`). System calls and system variables are in
  [cflat_r2system.cpp](../../../src/cflat_r2system.cpp); calls on objects
  (`G452[i].setPRG(...)`, `addItem`, ...) are in
  [cflat_r2class.cpp](../../../src/cflat_r2class.cpp).
- **Objects and PRGs.** Scripts define classes (`Player_for_Battle`,
  `CarryItem`, `HotSpot`, `EventDirector`, ...). Each object runs a `main`
  function, usually a `while (1)` loop with one `wait(1)` per frame, that
  switches on its current program number (PRG, `this.m5`). `setPRG(n)` moves an
  object to state `n`. Event handlers (`onCommand`, `onTalk...`, `send_int...`,
  `onDamage...`) are called by the engine or by other scripts.
- **Shared code.** Many functions are included into every script from common
  source files (the player library, `SPAWN_*`, `INIT_PARTY`, the letter code).
  The same function can appear in 132 scripts, sometimes with small per-map
  differences.

### Maps and dungeons

Stage numbers come from the order of names in `c_system.cfd`, and match the
indices the scripts use (`stageTable`, `incMana`).

| Stage | Dungeon | Scripts |
|---|---|---|
| 0 | River Belle Path | river_0, river_1 (boss) |
| 1 | Goblin Wall | gob_0-2 |
| 2 | Mine of Cathuriges | mine_0-3 |
| 3 | Mushroom Forest | kinoko_0, kinoko_1 |
| 4 | Tida | ruin_0-2 |
| 5 | Moschet Manor | gigas_0-8 |
| 6 | Mount Kilanda | lava_0-2 |
| 7 | Daemon's Court | fort_0, fort_1 |
| 8 | Selepation Cave | cave_0-2 |
| 9 | Veo Lu Sluice | water_0, water_1 |
| 10 | Lynari Desert | desert_0-2 |
| 11 | Conall Curach | swamp_0-3 |
| 12 | Rebena Te Ra | city_0-2 |
| 13 | Mount Vellenge | meteo_0-3 |

Other scripts: `last_0-6` (the Unknown Lands), `world` (world map), towns
(`village_0` Tipa, `castle_*` Alfitaria, `weapon_0` Marr's Pass, `magic_0`
Shella, `thief_*` Leuda, `farm_0` Fum, `port_*`), `festa_0` (festival),
`mog_0` (Mog house), `kai_*` (road events), `stream_*` (miasma streams),
`ffcc_0` (boot card check), `ffcc_2` (game over), `ff44_*`/`ffcc_4` (ending),
`tutorial_0`, and debug maps (`startmap`, `mail`, `miya_*`, `uma_1`,
`map_test`).

## Reading scripts with `tools/cflat/cflat.py`

```sh
python tools/cflat/cflat.py info  <script>                 # classes, functions, globals
python tools/cflat/cflat.py dec   <script> [funcRegex ...] # pseudo-C
python tools/cflat/cflat.py dis   <script> [funcRegex ...] # raw bytecode
python tools/cflat/cflat.py xref  <regex> [--dir <cft dir>]  # functions whose pseudo-C matches
python tools/cflat/cflat.py dump  <out_dir>                # pseudo-C for every script
```

`<script>` is a path or a bare name such as `cave_0` (looked up in
`orig/GCCP01/files/dvd/cft`). Function arguments are names or regexes, for
example `dec lava_0 '^mainmyMapGimmik$'`. The matching `.cft.dbg` is picked up
automatically, and each pseudo-C line ends with `// N`, the original source
line.

Always confirm surprising lines with `dis`.

## Notation in these write-ups

- **"line N"** is the original source line from the `.dbg` file (the `// N`
  comment), not a line in the pseudo-C output. Lines from included files keep
  their own numbering, so the same number can appear in different functions.
- **`G<n>`** is script global `n`. Numbering is per script: the same variable
  can be `G1504` in one map and `G1637` in another.
- **`this.m<n>`** is member `n` of the current object. `m5` is the current PRG
  and `m6` usually a frame counter.
- **`csys[-0x..]`** reads a native field of an object through a system
  variable (for example `csys[-0x1B]`, the display/update flags).
- **`evtFlag[n]`, `eventWork[n]`** are saved story flags and story counters.
  `sysVal0` is the year.
- Common globals: `G452[0..3]` players (`G452[8]` is the chalice), `G2[i]`
  "player i present", `G463` player count, `playMode` single-player mode (Mog
  is player slot 1), `G811` boss fight state, `G817` "map change in progress",
  `G818` "leave dungeon in progress", `G51[]` per-dungeon puzzle state.
- Frame counts are PAL, 50 frames per second.

## CFlat language pitfalls

These look like ordinary C in the pseudo-C but behave differently. The first
two are traps for the original developers too.

### A store leaves the old value

The store opcode writes the new value and leaves the **old** one on the stack
(`objectFrame` case `0x0D`,
[cflat_runtime.cpp:900](../../../src/cflat_runtime.cpp#L900)). `+=` and `-=`
work the same way. So in CFlat, unlike C, the value of an assignment is what
the variable held before. The tool prints such uses as `x++`, `x--` or
`postassign(x = v)`.

- **Chained assignment in `get_treasure`** (132 scripts, source line 15):

  ```c
  arg2->[0] = arg3->[0] = arg4->[0] = arg5->[0] = 0;
  ```

  Only the last output is zeroed; each of the others receives the previous
  value of the next one. **No effect in retail:** the outputs are four
  per-map globals passed in by `SPAWN`, `SPAWN_TBOX` and
  `SPAWN_SWITCH_SPHERE`, and every branch of the switch that follows assigns
  all four, for every cycle index `getIdxSet()` can return (0-7), and in the
  default case.
- **`if (x = v)` tests the old value.** Three places do this:
  - kai_bla_0 line 233 and kai_bla_3 line 231:
    `if (this.m12 = rand(4) + 23)`. `m12` is the caravan member's ID (23-26),
    so the test is always true either way, and the ID is overwritten with a
    random one. It was probably meant as `==` (a 1-in-4 idle animation). No
    visible effect was found.
  - kai_cas_6 lines 348 and 364: `if (G2050 = 1)`. In C this would always be
    true. In CFlat it is true only if `G2050` was already 1, which is set when
    Sol turns away in state 209. So it behaves like the intended `== 1`.

### Assigning a system variable on another object reads your own

In a statement like

```c
G452[i].csys[-0x1B] = csys[-0x1B] | 1024;
```

the address is taken inside the target object, but the right-hand side is
evaluated after the interpreter has switched back to the calling object
(`retobj`, opcode `0x39`,
[cflat_runtime.cpp:1081](../../../src/cflat_runtime.cpp#L1081)). It reads the
**caller's** flags, so the loop copies the caller's flags onto every player.
This happens in:

- the location title of 14 dungeon-entry maps (source lines 1435-1438): every
  player gets the title object's flags plus `0x800000` for the ready-wait, and
  line 1484 repairs them. Visual only.
- the fur on/off macro in the boss-intro player code of 14 boss maps (for
  example river_1).
- the post-boss PRG 190; see
  [chalice-and-mog.md](chalice-and-mog.md#7-post-boss-prg-190-copies-one-players-display-flags-onto-everyone).

### Other things to know

- **Ternaries.** `a ? b : c` compiles to a branch. Older versions of the tool
  printed it as an empty if/else followed by a constant store; the current
  version recovers it.
- **No bounds checks.** `G6[12]` on a 4-slot array silently reads or writes
  another global ([cflat_runtime.cpp:640](../../../src/cflat_runtime.cpp#L640)).
- **Locals are zeroed on every call**
  ([cflat_runtime.cpp:517](../../../src/cflat_runtime.cpp#L517)), and so are
  the members of a new object.
- **Permanent globals.** Globals flagged `0x20` in the script's table survive
  map loads and are saved with the game
  ([cflat_runtime.cpp:464](../../../src/cflat_runtime.cpp#L464)). The rest are
  reset on each script load.
- **`loadCFlat()` is deferred.** It only records the next script; the switch
  happens once per frame. Two calls in the same frame: the later one wins.
- **`switch` with duplicate `case` labels compiles.** Cases are compared in
  order, so only the first can match. See
  [towns-and-letters.md](towns-and-letters.md#1-six-letters-that-never-arrive).

## Write-ups

| Write-up | Summary |
|---|---|
| [Keys and Locks](keys-and-locks.md) | A key you carry back into its area is sent a "pop out of the dead carrier" command, because the "held by a player" flag is wiped before monsters check it. Placing a key writes two unrelated globals. Any key fits any lock. |
| [Memory Card Format](memory-card-format.md) | On the Slot B "Proceed?" prompt, B doesn't cancel in English, French, Italian and Spanish: with the cursor on Yes it formats the card. Cards with odd sector sizes stall the check. |
| [Bosses](bosses.md) | Meteor Parasite can be one-shot past both arena changes; its arena changes heal and revive. Gigas Lord killed during Maggie's entrance hands control back mid-victory. Moschet Manor's doors re-close on later visits. fort_1 intro skip leaves gates open. THE END never returns to the title. |
| [Dungeon Puzzles](dungeon-puzzles.md) | Mt. Kilanda's barriers open on a timer. The Cathuriges cart can jump to the wrong line. Tida barriers can be worn down and farmed for drops. Monsters hold floor switches. Daemon's Court's log bridge opens Conall Curach. Cutscene overlaps. |
| [Chalice and Mog](chalice-and-mog.md) | How single-player Mog interacts with shrines (it can't place or remove the chalice). Gaps in the "leave dungeon" lock, the place-delay window, a frame-perfect transition race, Mog House grooming hiding Player 1, lost letter gifts. |
| [Road Events](road-events.md) | How `kai_*` road encounters are picked and rewarded. A line that can't play, a song only port 1 can end, Sol's gift emptying your purse, haggling tricks. |
| [Towns and Letters](towns-and-letters.md) | Six letters that never arrive, Tipa families confused by shared occupations, the ship-repair donation skip and double charge, the 256-entry diary cap, the port-1-only ship prompt, the Guard Master freeze. |
| [Unused Content](unused-content.md) | Debug maps and menus, the Sign of Debug, the light editor, an NTSC prompt, cut quiz doors in the Unknown Lands, placeholder and build-stamp text. |

## Open leads (need in-game testing)

- **Held key re-pop** ([keys](keys-and-locks.md#1-held-key-re-pops-from-its-dead-carrier)):
  does the key leave your hands, and can a second player then take it?
- **Format prompt** ([memory card](memory-card-format.md)): confirm on Dolphin
  or hardware; check whether B on the Slot A prompt is also unsafe.
- **Meteor Parasite one-shot** and **Gigas Lord during Maggie's entrance**
  ([bosses](bosses.md)): need a glitched weapon or stacked spells.
- **Place-delay window** ([chalice](chalice-and-mog.md#3-picking-the-chalice-or-a-key-up-during-its-place-delay)):
  measure the frames between the native drop and the scripted flight; if there
  is a gap, one key may open two locks.
- **Leave/Moogle-nest race** ([chalice](chalice-and-mog.md#4-the-two-transition-locks-dont-check-each-other)):
  frame-perfect, multiplayer.
- **Cathuriges cart** ([puzzles](dungeon-puzzles.md#2-mine-of-cathuriges-mine_0-the-cart-jumps-to-the-wrong-line)):
  what the line switch looks like, and whether it saves time.
- **Moschet Manor doors** and **fort_1 gates**: does the door state also change
  collision?
- **Post-boss Start skip** ([bosses](bosses.md#7-post-boss-start-skip-can-re-run-the-myrrh-camp-step)):
  does a second diary entry or a doubled tier appear?
- **Multiplayer port-1 issues:** the Leuda song with nobody on port 1, the ship
  prompt with a GameCube controller on ports 2-4.
- **Donation double charge, Guard Master freeze:** need two players talking at
  once.
- **Letters 76 and 142 with a full inventory**, the **stream_0 current** with
  perpendicular input, and **leaving Tida mid-dispel**.
