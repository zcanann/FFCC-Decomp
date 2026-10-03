# Wrong Craft

## In short

In multiplayer, pausing while talking to a blacksmith or tailor can make the
GBA skip the recipe list and open the **"ready to craft"** screen directly.
Since no recipe was chosen, that screen reads whatever data is sitting in a
reused memory buffer and tells the GameCube to craft from it.

Speedrunners fill that buffer on purpose with a letter that starts with a
chosen character name. The name's bytes become the request the GameCube
receives. The request points at the slot where your **gil** is stored, so your
gil amount decides which item gets crafted. The GameCube does not check any of
it: missing materials are ignored and it does not need to be a real recipe.

Three bugs combine to make this work:

1. **Unpausing restores the wrong menu.** The GBA remembers which menu was open
   when you paused, but not whether it was a player menu or a shop menu. After
   unpausing in a shop, index 1 means the forge screen instead of the Command
   List.
2. **Old data lingers.** All of the GBA's menu lists share one buffer. On the
   GameCube, every list is built in the same buffer used for letters, and the
   buy list leaves a few bytes unwritten. Those bytes still hold letter text
   when they are sent.
3. **The GameCube trusts the GBA.** The crafting request carries an inventory
   slot number with no range check. Slot 166 is past the end of the inventory
   and lands on gil.

## Step by step

1. Read a letter that starts with your name, such as `えkk, …`. The GameCube
   builds the letter text in its shared buffer, so it starts with the bytes
   `82 A6 6B 6B`.
2. Open and close a merchant's **Buy** menu. The GameCube builds the buy list in
   the same buffer. It overwrites byte 0 (the item count) but leaves bytes 1–3
   alone, then sends the whole block. The GBA saves it in `LIST_BUF`, so
   `LIST_BUF[1] = 0xA6`.
3. With the GBA on field screen 1 (Command List), pause while talking to the
   smith. The GBA saves "screen 1".
4. Unpause. The smith's mode change reaches the GBA before the unpause message.
   The unpause then restores screen 1 in smith mode, which is the
   **Forge** screen.
5. Confirm the craft. The GBA sends `(slot = LIST_BUF[1] = 166, tribe)`.
6. The GameCube reads "inventory slot 166", which is the low 16 bits of gil.
   It treats that number as an item ID and crafts that item's tribe-specific
   smith result. It also overwrites the low half of gil with `0xFFFF` and
   charges that row's price. Missing materials are skipped.

For example, 423 gil (the setup uses the GBA-only gil desync to reach this
value) selects item row 423. That row's Lilty smith result should be the item
the setup crafts at that point, but this hasn't been checked against the item
table.

## Technical detail

### 1. Screen index is shared across GBA modes (confirmed)

The GBA client has a single `gScreen` index. Each mode reads it through its own
function table. The tables are laid out back to back in `.data` with no bounds
checks ([mode.c](../../gba/src/cli/main/mode.c), `symbols.txt`
`gFieldScreens`…`gSmithScreens`):

| `gScreen` | Field (`MODE_FIELD`) | Shop (`MODE_SHOP`) | Smith (`MODE_SMITH`) |
|---|---|---|---|
| 0 | Radar | Top | Top (recipe list) |
| 1 | Command List | Buy | **Forge** |
| 2 | Items | Sell | Equip |
| 3 | Equip | idle | idle |
| 4–10 | Artifacts … Menu | (overruns into Smith table) | (overruns past Smith table) |
| 11 / 13 | Message screens (11 = pause) | | |

Pause and unpause arrive as "open menu" 11 and 12
([widget.c `Menu_OnOpen`](../../gba/src/cli/main/widget.c#L643)):

```c
if (gScreen == 11) {                       // pause
    if (gMode != MODE_FIELD) { gSavedScreen = 0; gMode = MODE_FIELD; }
    else                       gSavedScreen = prev;
} else if (gScreen == 12) {                // unpause
    gScreen = gSavedScreen;                // gMode is not checked
}
```

`Mode_OnSet` ([window.c](../../gba/src/cli/main/window.c#L2133)) sets
`gScreen = 0` on a mode change while connected, but only clears
`gSavedScreen` while **disconnected**. A field index saved before a mode change
therefore survives it.

If you pause while already in the shop, the GBA zeroes `gSavedScreen`, so
everything returns to screen 0 and the glitch does not happen. The pause has to
land in field mode, after you've started talking but before the shop or smith
mode switch reaches the GBA.

### 2. Unpause and mode change race (confirmed mechanism, timing hypothesis)

On the GameCube, START from a GBA toggles pause
([system.cpp](../../src/system.cpp#L319)):

- **Pause:** `m_scenegraphStepMode = 2`, then `GbaQue.SetPauseMode(1)`.
- **Unpause:** `GbaQue.ClrShopMode()`, then `GbaQue.SetPauseMode(0)`.

The two message types reach the GBA by different routes:

- **Pause and unpause** (menus 11 and 12) are sent **asynchronously**. Each
  player's joybus thread notices the changed `m_pauseMode` on its next poll and
  calls `SendOpenMenu` ([joybus.cpp](../../src/joybus.cpp#L979)).
- **Mode changes** are sent **synchronously** from the main thread. A smith NPC
  runs `CCaravanWork::ShopRequest` case 5, which calls
  `GbaQueue::SetSmithFlg` → `Joybus.SetMType(ch, 3)` → `SendMType`
  ([gobjwork.cpp](../../src/gobjwork.cpp#L1517)).

If the script resumes and opens the smith in the same frame as the unpause, the
mode change is queued first and the unpause arrives after it. The GBA ends up in
`MODE_SMITH` with `gScreen = 1`. The CFlat script timing hasn't been checked
directly, which is why this ordering is still a hypothesis.

### 3. Shared buffers (confirmed)

**GameCube.** `GbaQueue::ExecutQueue` builds every requested list (letter list,
letter body, sell, buy, smith, artifacts) in one buffer,
`Joybus.GetLetterBuffer(channel)` ([gbaque.cpp](../../src/gbaque.cpp#L790)).
The joybus thread then sends `m_letterSizeArr[ch]` bytes of it.

- `MakeLetterData` copies the letter text from offset 0.
- `MakeBuyData` ([gbaque.cpp](../../src/gbaque.cpp#L3374)) writes
  `outData[0] = itemCount` and then jumps to `outData + 4`. Bytes 1–3 are
  never written but are included in the size it sends. The GameCube-side hole
  also covers the 2 bytes skipped after the item IDs when the count is odd.

**GBA.** Bulk types 3 (letter list), 6 (sell), 7 (buy), 8 (smith) and 9
(artifacts) all go to `LIST_BUF` at `0x0203A800`
([xfer.c](../../gba/src/cli/main/xfer.c#L107)). Letter bodies (type 2) go to
`DETAIL_BUF`. That's why opening Sell, Letter or Artifact menus at the wrong
time breaks the setup: each one replaces the primed buy list.

Two other GBA writers can also overwrite `LIST_BUF`:

- `CmdListScreen_BuildCandidates`
  ([cmdlist.c](../../gba/src/cli/main/cmdlist.c#L417)) writes s16
  inventory-slot indices from offset 0, little-endian, so `LIST_BUF[1]`
  becomes `0x00`. It runs locally on the GBA, without the GameCube:
  - whenever the Command List opens;
  - on item updates in field mode;
  - from `Session_OnArtifacts` / `Session_OnTmpArtifact` when `gScreen == 1`
    in **any** mode ([session.c](../../gba/src/cli/main/session.c#L398)).
    The Forge screen is `gScreen == 1`, so an artifact sync that arrives while
    you're on it rebuilds the table over the payload.
- `Scouter_OnInfo` ([session.c](../../gba/src/cli/main/session.c#L570))
  copies 0x200 bytes in whenever scouter info arrives, in any mode.

If the payload is overwritten, the forge sends slot 0. The craft then reads the
item in slot 0 (and deletes it), which is one likely source of "junk" crafts.

### 4. The forge request (confirmed)

The Forge screen normally runs after Smith Top. Only Smith Top requests the
recipe list (`Link_SendRequest(8, 0)`) and resets `sSmithSel`. When the forge
is reached directly, nothing reloads `LIST_BUF`. The confirm path
([smith.c](../../gba/src/cli/main/smith.c#L519)) sends:

```c
p = &LIST_BUF[sSmithSel];
Link_SendEvent(10, p[1], gSession.appearance & 3);   // slot, tribe
```

`sSmithSel` is static and keeps the last real recipe choice, so the byte read is
`LIST_BUF[1 + sSmithSel]`.

### 5. GameCube `SetSmithData` (confirmed)

([gbaque.cpp](../../src/gbaque.cpp#L912)), reached through queue command
`0x14`/10:

```cpp
baseItem  = caravan->m_inventoryItems[slot];          // slot unchecked (u8)
caravan->DeleteItemIdx(slot, 1);
itemRow   = &itemTable[baseItem];                      // baseItem unchecked
smithItem = itemRow->m_smithResults[tribe];
// for each material: search slots 0..63; not found -> foundSlot = 64
//   -> DeleteItemIdx(64): first permanent-artifact slot, usually empty
AddItem(smithItem);                    // failure only sends an error result
AddGil(-itemRow->m_smithPrice * m_shopParam / 100);   // same
SendResult(ok);
```

`CCaravanWork` layout ([gobjwork.h](../../include/ffcc/gobjwork.h#L302)):

| Field | Offset | As `m_inventoryItems[n]` |
|---|---|---|
| `m_inventoryItems[164]` (`short`) | `0x0B6` | n = 0…163 |
| `m_treasureFlags`, `m_moneyFlags` | `0x1FE` | 164 |
| `m_gil` (`int`, big-endian) | `0x200` | 165 = high half, **166 = low half** |

Slot `0xA6` = 166 = the low 16 bits of gil, which is the second byte of
Shift-JIS `え` (`82 A6`). The trailing `kk` bytes fill buffer bytes 2–3 and
aren't used by the forge.

Side effects of a wrong craft:

- `DeleteItemIdx(166)` writes `-1` there, so gil becomes `(high << 16) | 0xFFFF`
  before the price is taken off.
- `m_inventoryItemCount` is decremented even though no real item was removed.
- Nothing is rolled back if `AddItem` or `AddGil` fails.

`SetSmithData` only checks that the caravan exists. It does not check that a
smith is open.

### 6. Letter pause and the GameCube request queue

**Confirmed: a paused GameCube serves no GBA requests.** `ExecutQueue` runs
from `CGbaPcs::calc`, which is registered with flags 0
([p_gba.cpp](../../src/p_gba.cpp#L28)). In step mode 2 the scheduler skips it
([system.cpp](../../src/system.cpp#L400)). The joybus thread keeps running, so
the GBA stays responsive.

**Requests are queued, not dropped.** `SetQueue` keeps up to 64 per player and
`ExecutQueue` runs them in order after unpause. Menus opened during the pause
still rewrite `LIST_BUF`; it just happens at unpause, and the last list request
wins.

**Overflow.** The 65th request sets `m_queueFull[ch]`. After that,
`ExecutQueue` throws away that player's queue every frame, until
`GbaQueue::Init` runs (`ResetQueue` is unused). It's hard to hit in practice,
but the Artifact screen re-requests every 60 frames
([artifact.c](../../gba/src/cli/main/artifact.c#L110)).

**Hypothesis: why the pause screen never appears.** The joybus thread only
sends menu 11 from its idle states. Those states skip everything while
`m_skipProcessingFlag` is set by a transfer handshake
([joybus.cpp](../../src/joybus.cpp#L946)). Pausing on the frame a letter
request starts may hide the 11 inside that window. The GBA would then keep menu
control while the GameCube is paused. This hasn't been traced through the joybus
state machine yet.

## Open questions

- **The CFlat script timing in §2.** Confirm that the smith request is sent
  before the joybus thread's next poll after unpause.
- **The exact letter-pause window in §6.**
- **How the setup reaches screen 1 in smith mode without the Command List
  zeroing `LIST_BUF[1]`.** Candidate explanations are a nonzero `sSmithSel`
  or a route to screen 1 that skips `CmdListScreen_Setup`.
- **The cause of the roughly 50% junk rate.** The leading candidate is the
  artifact-sync rebuild in §3.
