# What the GameCube Trusts from the GBA

## In short

In multiplayer, the GBA runs the menus and sends the GameCube small 4-byte
commands such as "equip slot X", "drop item Y" or "buy row Z". The GameCube
assumes the GBA only sends sensible values. Nearly every handler uses those
bytes directly as array indices or amounts, without range, ownership or
affordability checks.

The GBA's own menus normally keep the values sensible. The glitches come from
making the GBA work from **stale data**:

- a menu list left over from an earlier download (`LIST_BUF`, `DETAIL_BUF`);
- a GBA inventory or gil that no longer matches the GameCube's;
- a GameCube paused in the middle of an exchange.

Any of these makes the GBA send a value the GameCube would never produce
itself.

## Input table

Packets reach `GbaQueue::ExecutQueue`
([gbaque.cpp](../../src/gbaque.cpp#L738)). The only check common to all of them
is that the player's `CCaravanWork` exists. "u8 slot" means the byte is used
directly as `m_inventoryItems[slot]`. Slots 0–163 are valid, slot 166 is gil's
low half, and see [command-list-oob.md](command-list-oob.md#what-a-given-slot-reaches)
for the rest.

| Command | Handler | Unchecked input | Effect of a bad value |
|---|---|---|---|
| `0x14`/10 Craft | `SetSmithData` | u8 slot; item row; materials; price | Crafts from any value, including gil. Missing materials are free. See [wrong-craft.md](wrong-craft.md). |
| `0x1F` Command List | `ChgCmdLst` | u8 list index (array is `[8]`); s16 slot | OOB slot: on use, reads any ±64 KB value as an item and writes `-1` back. OOB index: chosen s16 written to `+0x204…+0x402`. See [command-list-oob.md](command-list-oob.md). |
| `0x1E` Equip | `ChgEquipPos` | s8 equip index; s8 slot; item category | Equips any slot's contents as weapon, armor and so on. See [equipment.md](equipment.md). |
| `0x17`/1 Use | `FGUseItem` | u8 slot | `useItem(m_inventoryItems[slot])`, then writes `-1` there. |
| `0x17`/2 Drop | `FGPutItem` | u8 slot; item ID | Spawns a pickup of **any** item ID. `putItem` doesn't validate it. |
| `0x17`/3 Discard | `DeleteItemIdx` | u8 slot | Writes `-1` at the slot (slot 165/166 overwrites a gil half). |
| `0x14`/8 Sell | `SetSellData` | u8 slot; whether the slot holds anything | Pays a quarter of `itemTable[m_inventoryItems[slot]].m_price`. An empty slot reads row −1. Repeating it while paused at a shop is **multi-sell** (known). |
| `0x14`/9 Buy | `SetBuyData` | u8 row into `m_shopList[16]`; u8 quantity; affordability | Items are always granted. Gil is clamped to 0, so missing gil isn't charged. |
| `0x1A` Drop gil | `ChgMoneyData` → `FGPutGil` | 32-bit amount vs. balance | Spawns a pickup of the full amount, then clamps gil at 0. This is the GameCube side of the GBA gil desync. |
| `0x14`/0,1 Take attachment | `MoveLetterItem` | u8 letter index (`m_letters[100]`); claimed flag | Grants the attachment again on every request (known as **multi-take**). Index ≥ 100 reads later fields as a "letter" and sets a claimed bit inside them. |
| `0x0C`/2 Open letter | `MakeLetterData` / `FGLetterOpen` | u8 letter index | Out-of-bounds letter "open" (**known**). |
| `0x14`/6 Birthday | `CMakeBarthday` | 2 bytes | Stored as-is. Character creation only. |

The GBA's own menus usually keep these in range. For example, item operations
use `% 64` ([item.c](../../gba/src/cli/main/item.c#L307)), sell is limited to
the 64-slot list, and buy is limited to the downloaded count. But the GBA's
checks run against **its own copy** of inventory and gil (`gSession`), which
can go out of sync.

## Why stale GBA state is easy to get

1. **A paused GameCube doesn't answer.** `ExecutQueue` doesn't run while
   paused, so requests queue up (up to 64) and run together at unpause. Any
   check the GBA would have made after a reply never happens. Multi-take works
   this way: the GBA only marks an attachment as taken after a reply
   ([letter.c](../../gba/src/cli/main/letter.c#L1005)), so each A press while
   paused queues another grant, and `MoveLetterItem` never checks
   `m_attachmentClaimed`.
2. **Shared buffers.** `LIST_BUF` holds every downloaded list and also the
   Command List candidates. `DETAIL_BUF` holds the letter body, equip
   candidates and command-list item info. A screen reached without its own
   download step reads whatever is left there.
3. **The inventory count can wrap.** `m_inventoryItemCount` is an unsigned
   short. Every delete path decrements it whenever it removes a non-`-1` value,
   including out-of-range "items" such as gil halves. It never checks for 0.
   Once it wraps to 65535, `AddItem`'s `>= 0x40` check fails forever, so you
   can't receive any more items. This is the "bad things at count 0" after
   multi-sell.
4. **Unchecked GBA-side stores.** `Session_OnCmdSlot` stores raw values, and
   `Mode_OnSet` / `Menu_OnOpen` restore screens without checking the mode.

## Leads, ranked

1. **Drop an arbitrary item (`0x17`/2).** `putItem` creates a pickup for any
   ID. A drop request with slot 166 would drop "item number = gil" (which is
   easy to control) for anyone to pick up. The GBA sends `idx % 64`, so this
   needs a GBA path that produces a slot ≥ 64. None found yet. Command-list
   refs don't go through it.
2. **Command-list index ≥ 8 (`0x1F`).** A chosen 16-bit value written to
   `m_weaponIdx`, the backup inventory, `m_jobType` and so on. Needs a GBA path
   that sends an index ≥ 8. `CmdList_SetSlot` only sends the cursor row.
3. **Sell an emptied slot.** If the GBA still shows an item that the GameCube
   has already removed (for example, a drop queued during a pause and then a
   sell), the sale reads `itemTable[-1].m_price`. That's the 0x48 bytes before
   the item table. Its value decides whether this pays out, and it hasn't been
   checked.
4. **Buy beyond your gil.** If the GBA's gil is higher than the GameCube's,
   `SetBuyData` grants every item and only clamps gil to 0. With the gil desync,
   this means free items.
5. **Letter index ≥ 100.** `MoveLetterItem` reads `m_evtState`, the event flags
   and later fields as letters. A non-zero "attachment" there is granted (gil
   up to 51100, or items outside 1–0x9E) and sets a claimed bit inside event
   data. That's an event-flag write. Probably the same mechanism as the known
   out-of-bounds letters.
