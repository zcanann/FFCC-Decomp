# Memory Card Check at Boot

## In short

Before the title screen, the boot script `ffcc_0` checks both memory card
slots and offers to format a card it reports as corrupted. Two problems come
out of the script:

1. **Pressing B on the Slot B "Proceed?" prompt can format the card (confirmed
   in script and data, not tested on hardware).** In the English, French,
   Italian and Spanish text, that prompt has no cancel entry. B then leaves the
   answer on whatever is highlighted, and the script treats a B press like A.
   With the cursor on Yes, backing out with B formats Slot B.
2. **A card with a non-8 KB sector size leaves the check stuck (script gap
   confirmed; which cards do this is a hypothesis).** The script has no case
   for that status, so nothing appears and the game doesn't continue.

## 1. B on the Slot B format prompt formats the card

**Status:** Confirmed from the script, the message data and the native menu
code. Not tested on hardware or an emulator.
**Applies to:** both (boot). PAL English, French, Italian and Spanish. German
is not affected.

**How to trigger:**

1. Boot with no usable card in Slot A, and a card in Slot B that the game
   reports as corrupted. The check treats `CARD_RESULT_BROKEN` and
   `CARD_RESULT_ENCODING` as corrupted. A card formatted on a Japanese console
   reports `ENCODING`.
2. At "The Memory Card in Slot B is corrupted ... Do you want to format?",
   choose **Yes**.
3. At "The Memory Card in Slot B will be formatted. All data on the Memory Card
   will be lost. Proceed?", move the cursor up to **Yes**.
4. Press **B** to back out. Slot B is formatted.

**Why.** A Yes/No menu is written in the message text as
`FF A7 <default> <cancel>`, each value as two nibble characters
([mes.cpp:39](../../../src/mes.cpp#L39), case 7 at
[mes.cpp:940](../../../src/mes.cpp#L940)). In `uk/cft/ffcc.cfd`:

| Message | Text | Code | Default | Cancel entry |
|---|---|---|---|---|
| 13 | Slot A will be formatted ... Proceed? | `20 21 20 21` | No | No |
| 14 | Slot B will be formatted ... Proceed? | `20 21 2F 2F` | No | none (-1) |

fr, it and sp match uk. The German file (`gr`) has `20 21 20 21` for message
14, like message 13.

The menu reacts to B like this
([mesmenu.cpp:1012](../../../src/mesmenu.cpp#L1012)):

```c
} else if ((downMask & 0x200) != 0) {      // B
    if (altCursor >= 0) cursor = altCursor; // jump to the cancel entry
    else /* buzz */;                        // no cancel entry: cursor stays
}
...
if (altCursor >= 0 && cursor == altCursor) cursor = -1;
m_mes.SetValue(0, cursor);                  // value = highlighted entry
```

The script accepts A or B and only looks at the value:

```c
// ffcc_0 mainEventDirector, case 811 (lines 561-578), message 14 on screen
if (getPadDown(0) & 768) {                  // 0x100 A or 0x200 B
    closeCubeMes(4);
    if (getCubeMesValue(4, 0) == 0) {       // 0 = "Yes"
        playSe(2);
        this.m18 = 815;                     // 815: setWorldParam(16, 1) -> format Slot B
    } else { ... }                          // back to "Begin the game anyway?"
}
```

With no cancel entry, B leaves the value at 0 when Yes is highlighted, so the
script formats.

**Consequence:** every save on the Slot B card is erased although the player
pressed the cancel button.

**Open question (Slot A):** the Slot A copy (case 804, lines 823-840) has a
cancel entry, so B sets the value to -1, but only once the menu has processed
the press. If the script runs before the menu in that frame, it still reads 0
and formats Slot A as well. The per-frame order of the two wasn't resolved.

## 2. Cards with a non-8 KB sector size stall the check

**Status:** Script gap Confirmed. Which real cards trigger it is a Hypothesis.
**Applies to:** both (boot).

`CMemoryCardMan::McChkConnect`
([memorycard.cpp:1908](../../../src/memorycard.cpp#L1908)) returns -2 when
`CARDProbeEx` succeeds but the sector size isn't `0x2000`. The script receives
that as status 2 for the slot. `ffcc_0` state 900 handles Slot A statuses
{7, 0, 3, 6, 1} and Slot B statuses {7, 3, 6, 1, 0}, but never 2.

**How to trigger:** boot with such a card in Slot A, or with Slot A empty and
such a card in Slot B. Official 59, 251 and 1019 block cards all use 8 KB
sectors, so this would take a large third-party card.

**Consequence:** no message and no progress. The script polls every frame until
the card is removed or swapped. If a message was already up (for example "No
Memory Card found." before the card was inserted), it stays, and A/B do
nothing.

## Other notes (confirmed, harmless)

- **Pressing twice on a format prompt** before its cursor appears would read the
  previous message's value. These prompts open instantly, so a second press on
  the next frame isn't possible by hand. Theoretical only.
- **"Begin the game anyway?" → No** runs `setPRG(950); setPRG(900);` (source
  lines 185-189). The first call (start the game) is overridden at once by the
  second (go back to the card check). It looks like "No" once started the game
  and was patched by adding a line.
- The boot script also contains a complete, unreachable NTSC progressive-scan
  prompt. See [unused-content.md](unused-content.md#boot-title-and-system).
