# Chalice, Mog and the Shared Player Scripts

## In short

Every dungeon script carries the same player library: picking up and putting
down the chalice and key items, element shrines, the "leave dungeon" prompt,
game over, and Mog. This write-up answers a common question and lists what the
shared code gets wrong.

**Can single-player Mog be used to keep a shrine or menu "locked"?** No. Mog's
carrying is native AI that never runs the script's put-down or pick-up code, so
Mog never places the chalice on a shrine or lifts it off. The shrine message
isn't a blocking menu, and only the human who placed the chalice owns it. The
real locks are a "leave dungeon in progress" flag and a freeze on the chalice
while it sits on a shrine. No way was found to hold a blocking menu open, or to
act during a locked sequence, with a lasting effect.

Findings, most interesting first:

1. **The "leave dungeon" lock has two small gaps (confirmed).** Picking the
   chalice up in the 30 frames after "yes" doesn't cancel the exit, and a
   stored "yes" from a KO'd player fires when they are revived.
2. **The chalice or a key might be grabbed back during its place delay
   (hypothesis).** If the window exists, one key could open two locks.
3. **The "leave dungeon" and "map change" locks don't check each other
   (frame-perfect hypothesis).** In theory the party enters the Moogle house with
   the dungeon's chests and pedestals already reset.
4. **Mog House grooming hides Player 1 instead of the groomer (confirmed,
   multiplayer).**
5. **Letter gifts can be lost to a full inventory (hypothesis).**
6. **The end of the post-boss scene copies one player's display flags onto
   everyone (confirmed, effect unknown).**

Background facts used below (all confirmed):

- `onCommand(cmd, target)` is called by the native party object
  ([partyobj.cpp:1328](../../../src/partyobj.cpp#L1328),
  [partyobj.cpp:1513](../../../src/partyobj.cpp#L1513)). Before the call it sets
  `commandActive`, which blocks further commands
  ([partyobj.cpp:1115](../../../src/partyobj.cpp#L1115)) until the script calls
  `commandFinished()` ([partyobj.cpp:2990](../../../src/partyobj.cpp#L2990)) or
  the map reloads. Commands: 4 = pick up, 5 = put down, 12 = leave dungeon.
- The chalice is `G452[8]` (CarryItem class 10). An element shrine is a
  `HotSpot` with `worldParamA` 27, switched to 35 while the chalice sits on it.
  A key pedestal is a `Lock` with `worldParamA` 26.
- `classControl(2, v)` sets the native `m_prg` flag
  ([prgobj.cpp:402](../../../src/prgobj.cpp#L402)). With it cleared the
  object's state machine stops ([prgobj.cpp:62](../../../src/prgobj.cpp#L62)).
- `loadCFlat()` only records the next script
  ([cflat_r2system.cpp:1579](../../../src/cflat_r2system.cpp#L1579)); the
  switch happens once per frame. Two calls in the same frame: the later one
  wins.

## 1. Single-player Mog and element shrines

**Status:** Confirmed. **Applies to:** single player (the shrine part applies
to both).

- **Mog is a player object.** In single player, slot 1 is a
  `Player_for_Battle` in "Mog mode" (`m43 = 1`, model 915), created by
  `beginPlayer_for_Battle` (source lines 371-377).
- **At map start the chalice goes to Mog by default** (`beginCarryItem` lines
  355-365, owner = 1 in single player), unless a living player carried it last.
- **Mog's carrying is native.** `CGPartyObj::ghostPartyMog` picks up the
  chalice only when its `m_prg` is set and nobody owns it
  ([partyobj.cpp:4884](../../../src/partyobj.cpp#L4884)), and when ordered to
  drop it, calls `carry(1)` directly without any script
  ([partyobj.cpp:4817](../../../src/partyobj.cpp#L4817)). Mog never runs
  `onCommand(5)` or `onCommand(4)`.
- **Placing the chalice on a shrine is human-only.** `onCommand` case 5 (lines
  96-100) starts the chalice's PRG 307. A few frames later PRG 307 (lines
  656-676) clears the chalice's `m_prg`, flies it onto the shrine, sets the
  shrine to 35 and calls `shrine.send_int(81, placer)`. With `m_prg` cleared,
  Mog's AI won't take the chalice back off.
- **The shrine message doesn't block anything.** `send_intHotSpot` (lines
  850-883) opens window 4 with flags 137 (shown immediately, no input wait),
  sets the new element at once, and nothing waits for the window. Its button
  mask is the placer's port, which in single player is always the human.
- **Taking the chalice off** (`onCommand` case 4, lines 115-145) restores the
  chalice's `m_prg`, sets the shrine back to 27, clears the leave flag `G818`,
  and cancels every player's pending leave prompt.

So the shrine message can always be closed, and Mog can't be used to leave the
chalice "half placed".

Single-player map exits need the human to carry the chalice, or to carry
nothing while Mog carries it (`onPushMapJump` lines 129-145). A human holding a
key while Mog has the chalice can't use exits. That's by design. stream_0 and
stream_1 drop the Mog case entirely; see
[dungeon-puzzles.md](dungeon-puzzles.md#8-stream-exits-need-the-chalice-in-your-hands).

## 2. Gaps in the "leave dungeon" lock

**Status:** Confirmed. **Applies to:** multiplayer.

Choosing "leave" at a shrine runs PRG 86 (`mainPlayer` lines 624-692). On
"yes" it sets `G818 = 1`, waits 30 frames, takes control from everyone, waits
60 more frames, clears the stage variables, spawn bits and opened-chest masks
(`G368`, `G369`), and loads the world map.

- **The exit can't be cancelled.** For the first 30 frames the other players
  still have control. If one of them picks up the chalice, `onCommand` case 4
  clears `G818` and resets the leaver to PRG 11. But the leaver's PRG 86 code
  is already past its check and keeps running. The party still leaves 60
  frames later, with the chalice in someone's hands. No lasting effect.
- **A KO'd player's "yes" is stored.** PRG 86 only acts on
  `G1099 == 1 && hp && G818 == 0` (line 634). If the answering player is KO'd,
  the "yes" waits. Reviving them (Phoenix Down) makes the party leave at that
  moment.

## 3. Picking the chalice or a key up during its place delay

**Status:** Hypothesis. Whether the window exists depends on native animation
timing that couldn't be resolved from the scripts.
**Applies to:** multiplayer for keys. For the chalice, also single player if
Mog's AI is allowed to collect.

Placing works in two steps: the native drop, then the scripted flight, which
starts `G517[tribe]` frames later (3-8, from INIT_PARTY: {3,4,8,8,5,5,4,4}).
The chalice path guards against a pick-up in between (`onCommand` case 4
checks `chalice.m5 != 307`), so the developers expected it. But the guard only
skips script bookkeeping; the native drop has already happened
([partyobj.cpp:1460](../../../src/partyobj.cpp#L1460), before the script call).
Key pedestals have no guard at all.

**How it would work:** player A puts the chalice on a shrine, or a key on a
pedestal. Between the native drop finishing and the script's flight starting,
player B grabs it.

**Expected result if the window exists:**

- **Chalice:** the script still sets up the shrine (element change, message,
  `worldParamA = 35`) and freezes the chalice (`m_prg = 0`) while B carries it.
  The shrine then offers "leave dungeon" with no chalice on it, and Mog won't
  collect the frozen chalice until a scripted pick-up restores it.
- **Key:** PRG 306 still fires and activates the pedestal while B holds the
  key. B can put the same key on a second empty pedestal, and that one
  activates too. One key, two locks.

Evidence: `onCommand` case 5 (lines 76-113) and case 4 (lines 115-145);
`mainCarryItem` cases 306 (lines 620-646) and 307 (lines 656-676).

## 4. The two transition locks don't check each other

**Status:** Hypothesis (needs frame-perfect timing; object order within a frame
unverified). **Applies to:** multiplayer.

Map exits and the Moogle-nest entry check only `G817` (`onPushMapJump` line
124, EventClient PRG 18 line 312). The shrine "leave" prompt checks only `G818`
(`onCommand` case 12, line 47). Two players can start both at once.

The leave sequence clears the stage state (`clearStageVar`, `resetSpawnBit(-1)`,
`G368 = 0`, `G369 = 0`) in the same frame as its `loadCFlat('world')`. If the
Moogle-nest load (`loadCFlat('mog_0')`) is issued later in that same frame, it
wins, and the party goes into the Moogle house with the dungeon progress
already wiped.

**How it would work:** A answers "yes" to leave at frame T (world load at
T + 90). B, with the Moogle-nest prompt open, answers "yes" at exactly T + 40
(Moogle load also at T + 90). Earlier and `mog_0` loads first with nothing
wiped; later and the world map loads.

**Expected result:** back in the dungeon, chests and pedestals are reset and
can be looted and solved again.

## 5. Mog House grooming hides Player 1

**Status:** Confirmed (bytecode). **Applies to:** multiplayer.

When a player grooms a moogle in the Mog House (`mog_0` EventClient case 66),
the script is meant to hide the groomer during the close-up. The index is
hard-coded:

```c
G452[this.m0].setUC(0);       // 248: the groomer
...
G452[0].setUpdate(G593);      // 250: always Player 1
```

The restore at the end un-hides the groomer (`mainCoMogri` case 754, line
2031: `G452[this.m40].setUpdate(3 | G593)`), not Player 1.

**How to trigger:** player 2, 3 or 4 grooms a moogle in the Mog House.

**Consequence:** Player 1's model, weapon and shield stay invisible until the
party leaves the Mog House. The groomer is never hidden and stays in the
close-up. In single player the groomer is Player 1, so nothing goes wrong.

Related (Hypothesis): grooming starts the brushing sound with
`sysControl(14, 1)` (line 244). It is stopped only by the groomer's command 26.
A map exit by another player during grooming may leave the brushing loop
playing.

## 6. Letter gifts lost to a full inventory

**Status:** Hypothesis (the condition that would prevent it couldn't be
confirmed). **Applies to:** both.

When Mog delivers letters after a boss (`mainMogri` PRG 171), letters 76 and
142 also give a tribe-specific item (76 gives item 11/29/45/62, 142 gives
10/28/44/61), but only `if (item count <= 63)`. The letter is marked delivered
either way (`setCaravanEvtFlag(..., 100 + id * 3, 1)`). With 64 items, the gift
is skipped without a message.

Letter selection has an "inventory not full" condition (`checkLetterSub`
condition 24), but it wasn't confirmed that these two letters use it, or that
the inventory can't fill up between selection and delivery.

## 7. Post-boss PRG 190 copies one player's display flags onto everyone

**Status:** Confirmed (bytecode). Visible effect unknown, probably none.
**Applies to:** both.

At the end of the post-boss letter scene each player runs PRG 190, meant to
clear bit `0x400` (fur on) in everyone's display flags:

```c
G452[i].csys[-0x1B] = csys[-0x1B] & -1025;   // source lines 478-483
```

The right-hand side reads the calling player's own flags (see
[the csys pitfall](README.md#cflat-language-pitfalls)), so every player ends
up with the flags of whichever player ran last. In single player that can copy
Mog's `0x800000` bit onto the human, or the human's flags onto Mog. A map load
follows soon after and Mog sets `0x800000` again every frame. The same code is
in every boss-arena script with the post-boss letter scene.

## Minor and design notes

- **Pots vanish through exits.** `SPAWN_PLAYER` re-creates a carried pot on the
  next map only if `G19[idx] == 1`, and `SPAWN_POT` places it only if
  `G19[idx] == 0`. No script ever sets `G19` to non-zero, so a pot carried
  through an exit disappears, and reappears at its original spot when you come
  back. Looks like an unfinished feature.
- **`manaCheck`** initialises `stageTable[0..13]` only, so the 15th entry
  starts at 0 and its artifact counter rises by 1 every 4 myrrh drops. It is
  read only in the Unknown Lands, where every spawn uses the full mask. No
  effect.
- **Game over** records every player's carried items and loads `ffcc_2`. Only
  the ruin copy commits a pending diary entry; the others drop it, but the
  trigger re-arms.
- **`onHit2`** in tutorial_0 writes `G51[0..3]`, which nothing reads.
