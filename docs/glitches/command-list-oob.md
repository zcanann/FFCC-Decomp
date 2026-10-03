# Command List Out-of-Bounds (CLES)

## In short

Each command-list slot stores an **inventory slot number**. The GBA sends the
number and the GameCube stores it without checking it. When you use that
command, the GameCube reads "inventory slot N" even if N is far outside the
inventory. Whatever 16-bit value is there is treated as an item ID:

- If the ID's item-table row is a **weapon**, it gets equipped (equip swap).
- If it's **food**, it gets eaten, and the GameCube then deletes the "item" by
  writing `-1` (`0xFFFF`) to that memory. This is the "eat boss HP and it
  becomes −1" effect.

The slot number is a signed 16-bit value, so it can reach about ±64 KB from the
player's data.

## How a bad slot number gets sent (hypothesis)

The GBA builds the Command List's candidate table (`sCmdCandidates`) directly in
`LIST_BUF`, the same buffer that receives letter, shop, smith and artifact lists
([cmdlist.c](../../gba/src/cli/main/cmdlist.c#L417)). The candidate count is
saved separately, but the values are read back from `LIST_BUF` each time you
assign one:

```c
gSession.cmdSlots[slot] = sCmdCandidates[idx];   // = ((s16 *)LIST_BUF)[idx]
Link_SendCmdSlot(slot, (s16)gSession.cmdSlots[slot]);
```

([cmdlist.c `CmdList_SetSlot`](../../gba/src/cli/main/cmdlist.c#L527))

If a list download or a scouter update (`Scouter_OnInfo`, 0x200 bytes) lands in
`LIST_BUF` while the Command List is open, the candidate rows now contain
arbitrary s16 values from that data. Assigning a row sends the value as-is. The
easiest way to make that happen is to queue list requests while the GameCube is
paused (see the letter pause in [wrong-craft.md](wrong-craft.md#6-letter-pause-and-the-gamecube-request-queue)).
The GameCube serves them at unpause, and the Artifact screen re-requests its
list every 60 frames.

## GameCube side (confirmed)

**Packet** (`0x1F`, built by [link.c `Link_SendCmdSlot`](../../gba/src/cli/main/link.c#L949)):

| Byte | Meaning |
|---|---|
| 0 | `0x1F` |
| 1 | command-list index (u8) |
| 2–3 | inventory slot (s16) |

**Store.** [gobjwork.cpp `ChgCmdLst`](../../src/gobjwork.cpp#L510) does
`m_commandListInventorySlotRef[index] = slot`. Neither value is checked.

**Use.** [gobjwork.cpp `GetCmdListItem`](../../src/gobjwork.cpp#L2065) returns
`m_inventoryItems[ref]` for the selected slot. Then
[partyobj.cpp](../../src/partyobj.cpp#L1432) reads that item's row,
`unkCFlatData0[2] + itemId * 0x48`. Neither the slot nor the item ID is
range-checked. What happens depends on the row's kind field:

| Kind | Effect |
|---|---|
| `1` | Weapon. Queued as the pending weapon (equip swap). |
| `0x17D`, `0x186` | `useItem` (food heal). On success, `DelCmdListAndItem` runs. |
| `0x100`, `0x1F5`, `0xDF`, `0x125` | Cast or ability via `changeStat(2…)`, using the row's `m_fieldA` for some kinds. |

**Write-back.** [gobjwork.cpp `DelCmdListAndItem`](../../src/gobjwork.cpp#L2123):

```cpp
short inventorySlot = m_commandListInventorySlotRef[cmdListIdx];
if (m_inventoryItems[inventorySlot] != -1)
    m_inventoryItems[inventorySlot] = 0xFFFF;   // -1 written at CCaravanWork + 0xB6 + 2*slot
```

### What a given slot reaches

Addresses are relative to the player's `CCaravanWork`, with
`m_inventoryItems` at `+0xB6`:

| Slot | Offset | Field |
|---|---|---|
| 0–163 | `0x0B6`–`0x1FC` | Inventory and artifacts (valid) |
| 165 / 166 | `0x200` / `0x202` | `m_gil` high / low half |
| 167–174 | `0x204` | `m_commandListInventorySlotRef[8]` |
| 183 / 184 | `0x224` / `0x226` | `m_currentCmdListIndex` / `m_weaponIdx` |
| 185–… | `0x228`… | Backup equipment, backup inventory, then letters (`0x3EC`) |
| negative / >~1500 | outside the object | Neighbouring heap objects (for example another entity's HP) |

## A stronger primitive with no known GBA trigger

`ChgCmdLst` doesn't bounds-check the **index** either. That array is
`short[8]`, but the index can be 0–255. A packet with index ≥ 8 would write a
**fully chosen s16 value** anywhere in `CCaravanWork + 0x204` to `+0x402`. That
range includes `m_weaponIdx`, the backup inventory, `m_jobType` and the start
of the letters.

The GBA only sends the cursor row (0–7), and no GBA path that produces a larger
index has been found. If one exists, it would be the most powerful write found
so far.
