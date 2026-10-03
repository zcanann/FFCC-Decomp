# Character Creation Disconnect

## In short

In multiplayer, you create characters on the GBA. Each choice you make is sent
to the GameCube, which keeps a small record per player. When you confirm on the
GBA, the GameCube builds the character from that record.

If a GBA drops off during creation, the GameCube wipes that player's record to
all zeros. A zeroed record, if it were ever built into a character, would be a
**blacksmith in slot 1**: every field takes its first value, including the
target slot.

Observed behavior (reported by players, not reproduced here):

- **EN:** turning the GBA off on the last frame of creation creates a
  blacksmith in slot 1, apparently from a partly copied record. If another slot
  is already a blacksmith, Tipa ends up with two blacksmith families.
- **JP/PAL:** the same input doesn't touch slot 1. With one GBA, it cancels
  the forced character selection instead.

The PAL code explains both PAL's safety and why a blacksmith in slot 1 is
exactly what a wipe would produce. EN has no decomp yet, so what EN changes
is a **hypothesis**.

## What a wiped record becomes (confirmed)

The GameCube's record is a `GbaCMakeInfo` per GBA port. The GBA sends the
name, look, job, birthday and favorite foods as you finish each step
([gbaque.cpp:2755](../../src/gbaque.cpp#L2755) and the functions after it).
The target slot is not sent by the GBA. The GameCube stores it when you pick
an empty slot (`InitCmakeInfo`, [gbaque.cpp:2714](../../src/gbaque.cpp#L2714)).

A disconnect wipes the whole record to zeros (`ClrCmakeInfo`,
[gbaque.cpp:2737](../../src/gbaque.cpp#L2737)). Built by `SetMakeChara`
([wm_menu.cpp:7128](../../src/wm_menu.cpp#L7128)), a zeroed record gives:

| Field | Zeroed result |
|---|---|
| Slot | 0, shown in game as slot 1 |
| Job | 0 (blacksmith, matching what's observed) |
| Tribe, gender, look | first option of each |
| Name | empty |
| Birthday | 0/0 |
| Favorite foods | all eight get the same value |

Any field the GBA sends after the wipe overwrites its zero, so a "partial"
copy is possible. That part hasn't been traced.

### Why two blacksmiths are possible

Duplicate jobs are rejected only when the GBA sends a job choice
(`ChkCMakeJob`, [gbaque.cpp:2930](../../src/gbaque.cpp#L2930)). A zero left
behind by the wipe never goes through that check.

This gives at most **two** blacksmiths. The zeroed slot is always slot 1, so
repeating the trick overwrites slot 1 each time. Any normal creation afterward
has blacksmith rejected because slot 1 now holds one.

## Why PAL is safe (confirmed)

`CMenuPcs::CalcCharaSelect` ([wm_menu.cpp:7191](../../src/wm_menu.cpp#L7191))
runs these steps in order every frame:

1. Read each port's connection state.
2. For each disconnected port, wipe the record **and** clear the "finished"
   flag ([wm_menu.cpp:7283-7285](../../src/wm_menu.cpp#L7283-L7285)).
3. Build a character for each port whose "finished" flag is set
   ([wm_menu.cpp:7356-7360](../../src/wm_menu.cpp#L7356-L7360)).

The "finished" flag is set by the GBA's final message, but only if the
GameCube can still send to that GBA (`CMakeEnd`,
[gbaque.cpp:693](../../src/gbaque.cpp#L693)). If the GBA is gone, creation is
cancelled instead. So in PAL a wiped record never reaches step 3.

### What PAL does instead

On the last frame, the "finished" message arrives while the GBA still counts
as connected, so PAL builds the character from the real record. Once the GBA
is off, each later frame clears that player's confirmed, in-progress and
finished flags ([wm_menu.cpp:7365-7372](../../src/wm_menu.cpp#L7365-L7372)).
The screen only moves on once every connected (or recently disconnected)
player has confirmed ([wm_menu.cpp:7551](../../src/wm_menu.cpp#L7551)). With
one GBA, its only selection was just cleared, so the screen never moves on.
That matches the cancelled selection. Exactly what makes the selection
"forced" hasn't been traced.

### One theoretical PAL gap

`CMakeEnd` runs on the link thread. It first confirms the send to the GBA,
then sets the "finished" flag. If the main loop ran steps 1 and 2 between
those two actions, step 3 of the same frame would build a zeroed record. The
window is microseconds, and the thread priorities haven't been checked.

## EN (hypothesis)

EN builds this code differently. `SetMakeChara` is a separate function in EN
(`0x80116C58`, 576 bytes) but is inlined into `CalcCharaSelect` in PAL. That
suggests the code was changed between versions. The observed EN behavior means
a wiped or half-written record reaches the build step. That would happen if
EN's step 2 runs after step 3, or if EN's step 2 doesn't clear the "finished"
flag. Confirming this needs the EN decomp.
