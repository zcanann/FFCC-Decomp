# Guest Transfer

## In short

You can import a character from another save into your game as a **guest**,
then later **return** it home. The game tells the copies apart by a random
**character ID** and the home save's **serial number**. On return, only the
guest's **artifacts** come home.

Two leads come out of the code:

1. **Orphaned guests can return after all (confirmed in code).** "Restore"
   only clears the home character's "away" flag. If you export the character
   again later, an old orphaned guest matches again and can return, bringing
   its artifacts home. You can keep guest copies in several saves and choose
   which one's artifacts to keep.
2. **Power off between the two saves during a return (hypothesis, needs
   testing).** A return writes the home save first and deletes the guest
   second. Turning the console off after the first write should give the home
   character the guest's artifacts while the guest stays in the friend's save.

Artifacts are what a character's stats are built from, so they're what
matters. Max HP is recalculated from the artifact list whenever a save loads
([memorycard.cpp:1398](../../src/memorycard.cpp#L1398)).

## How transfers work (confirmed)

The current game is on Slot A. The save holding the character to import, or
the guest to return, is on Slot B. Both directions use
`CMemoryCardMan::Odekake` ([memorycard.cpp:1984](../../src/memorycard.cpp#L1984)).

**Import** (Slot B character → guest in Slot A):

- copies stats, equipment, artifacts, name, look, job and event flags;
- copies only the inventory items that are equipped;
- copies the character ID and records the Slot B save's serial as the guest's
  origin;
- marks the guest with `m_isGuest`, and marks the original with `m_isAway`.

**Return** (guest in Slot B → original in Slot A):

- finds the original with `GetSameCharaData`
  ([wm_menu.cpp:10301](../../src/wm_menu.cpp#L10301)). The guest's origin
  serial must match the Slot A save, and a character in Slot A must be **away**
  with the same character ID;
- copies the guest's artifact list over the original's (an overwrite, not a
  merge);
- clears `m_isAway` and wipes the guest.

**Restore** is for an away character whose guest never came back. It only sets
`m_isAway = 0` ([goout.cpp:2221](../../src/goout.cpp#L2221)). The character ID
is unchanged. The warning says the transferred data won't be able to return to
this save. That's true only because return requires the original to be away.

Other rules:

- A save can't hold two guests with the same ID and origin
  ([goout.cpp:1737](../../src/goout.cpp#L1737)).
- A character ID is assigned the first time the character is saved
  ([memorycard.cpp:1112](../../src/memorycard.cpp#L1112)). Transfers are
  refused until every character has one ([goout.cpp:1072](../../src/goout.cpp#L1072)).
- A save that is a copy of the current game (same serial and random number) is
  rejected ([goout.cpp:1678](../../src/goout.cpp#L1678)).

## Lead 1: reviving an orphaned guest (confirmed in code)

1. Export character A from home save H to save F. Guest A1 is in F, and A is
   away in H.
2. In H, restore A. A is playable again, and A1 is orphaned in F.
3. Export A from H to a different save G. Guest A2 is in G, and A is away
   again with the **same** ID.
4. From H, return A1 from F. Its origin matches H, and an away character in H
   has its ID, so it succeeds. H's A gets A1's artifact list. A2 is now the
   orphan.

Restore and export again to repeat. You can keep one guest copy of A per save,
in as many saves as you like, and pick which artifact set comes home. Because
return overwrites the list, this chooses between sets, it doesn't add them
together.

## Lead 2: power off during a return (hypothesis)

The transfer writes Slot A, then Slot B
([goout.cpp:1376](../../src/goout.cpp#L1376),
[goout.cpp:1415](../../src/goout.cpp#L1415)). The Slot B write starts only
after the Slot A write reports success
([goout.cpp:1826-1836](../../src/goout.cpp#L1826-L1836)). The message changes
from "Saving data to the Memory Card in Slot A" to "…Slot B" between them.

- **Return:** turn the console off once the Slot B message appears. Slot A
  should already have A back home with the guest's artifacts. Slot B should
  still hold the guest. Combined with lead 1, you could export A somewhere to
  make it away again and repeat. That would sync artifacts home over and over
  without using up the guest.
- **Import:** the same power-off gives a guest in Slot A while the original in
  Slot B isn't marked away. That's no better than an import followed by a
  restore, which the game allows anyway.

What needs testing: whether the Slot A write is fully committed by the time the
Slot B message appears, and whether the game behaves normally after loading
both saves.

## Other guest quirks (confirmed)

- Character creation's duplicate checks for name, look and job skip guests
  ([gbaque.cpp:2836](../../src/gbaque.cpp#L2836),
  [gbaque.cpp:2899](../../src/gbaque.cpp#L2899),
  [gbaque.cpp:2967](../../src/gbaque.cpp#L2967)). A guest can share any of
  them with one of your characters. Whether a guest gets its own family in
  Tipa hasn't been checked.
- A guest arrives with only its equipped items. The home inventory isn't
  changed by either transfer direction.
- A non-guest can't be deleted if it's your last non-guest
  ([goout.cpp:2010](../../src/goout.cpp#L2010)). Guests can be deleted freely,
  which leaves the original away until it is restored.
