# Wrong Craft: What Each Gil Value Crafts

## In short

In a [wrong craft](wrong-craft.md), the low 16 bits of your gil pick a row of
the **item table**. The game gives you that row's smith result for your tribe.
It doesn't check the row number, the materials, or whether the result is a real
item.

- **Gil 401–493 crafts that recipe directly**, with no materials. The best is
  **492, the Ultima weapon for your tribe** (sword, lance, hammer, maul), which
  normally needs Orichalcum and Ultimite. **493** gives a **Force Ring**.
- **Unused items** appear in rows past the real items. These include **Test 1**,
  **Test 2**, **Equip. 116** and **Equip. 117**; gil values are listed below.
- **Ultimite, the unused magicite (Holy, Ultima, Flare, Meteor…), the
  "Extra" items and designs 94–100 can't be reached** with gil 0–1204.
- **Gil 1205 and up reads past the end of the table, and 32768 and up reads
  before it.** The memory on both sides was mapped live on JP (below): some of
  it is fixed, and some changes with the map.

## Gil after the craft (confirmed)

`SetSmithData` ([gbaque.cpp:894](../../src/gbaque.cpp#L894)) first deletes
"slot 166", which writes `0xFFFF` over the low half of gil. Then it subtracts
the row's smith price times the smith's rate. Gil floors at 0
(`AddGil`, [gobjwork.cpp:822](../../src/gobjwork.cpp#L822)). With under 65,536 gil you
end with **65,535 − price**. For example, gil 492 at a 100% rate leaves
15,535.

## The item table (confirmed)

- **File:** `dvd/<lang>/cft/param.cfd`, `DATA` chunk 2. It has 1,205 rows of
  0x48 bytes (`SItemFlatRow`, [itemobj.h](../../include/ffcc/itemobj.h#L16)).
  The rows are byte-identical in all five PAL languages.
- **Names:** `c_system.cfd`, table 0, five strings per item. Only IDs 0–600
  have names. Rows 601–1204 are attack and spell definitions (see
  [equipment.md](equipment.md)).
- **Smith result:** `u16` at row offset `0x38 + 2 × tribe`, where Clavat = 0,
  Lilty = 1, Yuke = 2, Selkie = 3. In non-recipe rows those bytes mean
  something else, but `SetSmithData` reads them as an item ID anyway.
- **`AddItem` accepts any value** ([gobjwork.cpp:633](../../src/gobjwork.cpp#L633)).
  A result of 0 puts item 0, `DUMMY-US`, in your inventory. That's what most
  off-tribe recipes and many other rows give.

### Recipe rows worth knowing

| Gil | Recipe | Clavat | Lilty | Yuke | Selkie | Price |
|---|---|---|---|---|---|---|
| 407 | Legend. Wpn. | Excalibur | Gungnir | Mystic Hammer | Queen's Heel | 2,500 |
| 408 | Hero's Wpn. | — | Dragoon Spear | — | — | 5,000 |
| 409 | Celestial Wpn. | — | Longinus | — | — | 8,000 |
| 410 | Dark Wpn. | Ragnarok | — | — | — | 5,000 |
| 411 | Lunar Wpn. | — | — | — | Dreamcatcher | 5,000 |
| 425 | Earth Armour | Gaia Plate | Gaia Plate | Gaia Plate | Gaia Plate | 5,000 |
| 474 | Brigandology | — | — | — | Thief's Emblem | 5,000 |
| 491 | Forbid. Tome | — | — | Elemental Soul | — | 5,000 |
| 492 | Greatest Wpn. | Ultima Sword | Ultima Lance | Ultima Hammer | Ultima Maul | 50,000 |
| 493 | Ring of Invin. | Force Ring | Force Ring | Force Ring | Force Ring | 50,000 |

"—" gives `DUMMY-US`. Every row from 401 to 493 works the same way.

### Unused items in rows 0–1204

These come from attack rows (601–1204), whose smith price reads as 1.

| Item | Lilty gil | Selkie gil |
|---|---|---|
| Test 1 (sword) | 636, 724, 727 | 582, 583, 586, 590, 594, 598, 602, 839, 842, 845, 848, 1045 |
| Test 2 (sword) | 665, 668, 737, 738, 743, 749, 781, 785, 816, 995, 1001, 1007, 1023, 1114 | 658, 661, 664, 665, 668, 715, 791, 798, 816, 902, 906, 910, 1023, 1063, 1114, 1117 |
| Equip. 116 | 1117 | — |
| Equip. 117 | 783, 786, 792, 891, 943, 965 | 643, 648, 653, 814, 830, 833, 836, 879, 883, 891, 911, 945, 953, 957, 965, 1097, 1100, 1103 |

Also reachable: Treas. Sword, Fthr. Sword, Marr Sword, Marr Spear and Marr
Hammer (Lilty/Selkie, rows 501–1077). Weapon rows 1–64 give spell rows as
items for Clavat. For example, gil 1–15 gives "Slow" and gil 18–31 gives
"Cure". What those do in the inventory hasn't been tested.

Clavat and Yuke reach almost nothing unusual in this range.

## Gil values outside 0–1204 (confirmed on JP)

### The lookup is signed

Retail `SetSmithData` loads the gil slot with `lha` (sign-extending) and
multiplies by 72 (`mulli`). So gil 32,768–65,535 is rows −32,768 to −1:
memory **before** the table, read backwards. Gil 65,535 is the row just in
front of it. The old GES viewer read forward for these values, so its
"Unlikely to work" entries showed memory the game never reads.

The smith materials are the opposite: they're loaded unsigned (`lhz`), so a
material of `0xFFFF` is 65,535, not −1. Only a material of 0 ends the material
loop.

### What lies around the table

Read from a live JP game (`GCCJGC`) in Dolphin. JP addresses:

- Item table: `0x80979FC0`.
- Caravan member *n*: `0x8023BBB0 + n × 0xC30`. The GES viewer's slot
  addresses point 0x20 bytes earlier.
- Each heap block has a 0x40-byte header that names the source file and line
  that allocated it, so the layout below comes straight from those headers.

| Rows / item IDs | Memory | Stable? |
|---|---|---|
| below about −1,276 | Other heap blocks, including script memory | No |
| about −1,276 to −1 | `param.cfd` chunk 1: **monster base data** (`cflat_data.cpp:69`, 0x16700 bytes) | **Yes.** Loaded once from disc, never freed. |
| 0–1,204 | The item table | Yes |
| 1,206 to about 4,173 | Boot-time text: `c_system` string tables, `MES` text, `mail_tbl`, `newbattle` (`cflat_data.cpp`) | **Yes.** 2,967 of 2,968 rows matched across a town and two dungeon maps. |
| about 4,174 and up | **Script memory** (`cflat_runtime.cpp`) | **No.** It changes per map, and the same data turns up at different offsets on different maps. |

There are two small 0x40-byte blocks (empty string lists) between the monster
block and the table.

So a gil value is only reliable if its **recipe row** sits in a stable range.
The **item** it gives has to sit in a stable range too: its row is read again
every time it's swung or worn.

### Rare items in reach

A full scan of all 65,536 gil values in a town snapshot found every one of
these somewhere: Ultimite, Dark Sphere, all the unused magicite (Holy, Ultima,
Flare, Meteor, Stop, Gravity…), Ribbon, Extra 24–33, designs 94–100,
Equip. 187–210, and the Test swords. Almost all of those gil values read
script memory, so they only hold for the map where the snapshot was taken.
Also note:

- Items 256–292 (all magicite) are deleted by `SafeDeleteTempItem`
  ([gobjwork.cpp:1653](../../src/gobjwork.cpp#L1653)).
- Negative item IDs don't survive leaving a map (below).

### Negative item IDs

`AddItem` stores the result as a signed 16-bit value, so a result of
0x8000–0xFFFE becomes a negative item. Its row is read from before the table,
which for IDs −1 to about −1,276 is the stable monster block.

They get wiped by the sort that runs when you leave a map,
`SortBeforeReturnWorldMap` ([gobjwork.cpp:2305](../../src/gobjwork.cpp#L2305)),
called from the end-of-stage bonus screen. It treats any item ≤ 0 as an empty
slot:

- When it finds a positive item in a later slot, it moves that item into the
  "empty" slot and writes `0xFFFF` behind it.
- Equipment pointers follow the moved item. A negative weapon in slot 0 is
  replaced by whatever slides in, such as Travel Clothes.
- A negative item survives only if no positive item is left after it once the
  sort is done, for example as the last or only item.
- Item 0 (`DUMMY-US`) is wiped the same way.

### Side effect: the item counter

Each wrong craft "deletes" slot 166 (gil), which decrements
`m_inventoryItemCount` without removing an item. One test caravan held 9 items
while the counter read 6.

## The double craft (confirmed on JP)

The [Lilty minimalist guide](https://rentry.co/4gioz) wrong-crafts Firaga +2
at gil 4296 and also gets a free Ultima Lance. On a live JP game, the guide's
values give exactly its items for a Lilty:

| Gil | Lilty result | Price field | Materials | Memory |
|---|---|---|---|---|
| 4296 | Firaga +2 (534) | **0xFFFF** | 3 × `0xFFFF`, counts 3 × `0xFFFF` | script block `cflat_runtime.cpp:158` |
| 4545 | Dreamcatcher (60) | 0 | first material 0 (loop ends) | `cflat_runtime.cpp:217` |
| 4735 | Sun Pendant (231) | 0 | first material 0 | `cflat_runtime.cpp:217` |
| 6554 | **Ultima Lance (31)** | 14,851 | first material 0 | script memory |

**The second item is a normal follow-up craft.**

1. Gil 4296 is first overwritten to 65,535.
2. Row 4296's price of 65,535 at the guide's 90% rate (Crystal Mail cost 450
   rather than 500) is 58,981, which leaves **6,554** gil.
3. A second request then reads row 6554, whose Lilty result is the Ultima
   Lance.

This isn't unique to 4296. In the same snapshot, 6,052 gil values have price
`0xFFFF`, and all of them leave 6,554.

**Why there's a second request (hypothesis).** The GameCube runs each request
once, and the GBA only sends one per A press. So the second craft is another
A press while the confirm window is still up. Row 4296 is the only one of the
guide's rows with a material loop: 3 × 65,535 lookups, each scanning 64
inventory slots, before the GameCube replies. The leading explanation is that
this stalls long enough for the GBA's 30-frame reply timeout. On a timeout the
GBA plays the error sound, keeps the window up, and leaves the cursor on Yes.
A rough estimate puts the stall under 30 frames, so this isn't settled.

Other ways the window can stay up (confirmed in code):

- **Split replies.** A zero-price craft sends an error reply and then a
  success ([gbaque.cpp:946-959](../../src/gbaque.cpp#L946-L959)), because
  `AddGil(0)` returns 0. The GBA keeps only the latest reply
  ([xfer.c:248](../../gba/src/cli/main/xfer.c#L248)). If the error arrives on
  its own frame, the forge stays on the prompt
  ([smith.c:398](../../gba/src/cli/main/smith.c#L398)).
- **Dropped messages.** Each deleted material sends an item update, and the
  send queue silently drops anything past 64 entries
  ([joybus.cpp](../../src/joybus.cpp), `SetSendQueue`).
