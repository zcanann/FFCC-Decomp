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
  before it.** What's there depends on the heap layout. It's probably the same
  every boot, but it needs a memory dump to confirm.

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

## What's next to the table (partly confirmed)

The table is copied into the **main heap stage** (`Game.m_mainStage`,
0x106000 bytes) by `CFlatData::Create`
([cflat_data.cpp:71](../../src/cflat_data.cpp#L71)). This happens once, at
the first real script load (`CGame::loadCfd`,
[game.cpp:807](../../src/game.cpp#L807)), and it's never freed. The allocator
is first-fit. It rounds each size up to 0x40 and puts a 0x40-byte header in
front ([memory.cpp:945](../../src/memory.cpp#L945)).

Allocation order:

1. `param.cfd` chunk 0: player base data (3,712 bytes).
2. `param.cfd` chunk 1: monster base data (91,872 bytes, `CRomWork`).
3. **The item table** (86,760 bytes).
4. `c_system.cfd` string tables, then `mail_tbl.cfd`, then `newbattle.cfd`.

Each `DATA` chunk also allocates two empty 0x40-byte string blocks. Those can
fill earlier holes in the heap, so the exact gap between neighbours is
unknown.

- **Gil 32768–65535 (negative rows)** most likely read **monster base data**.
  It's the same in every PAL language, so it would be repeatable. But the hits
  move with the gap. Two plausible gaps (0x60 or 0x160 bytes) both give unused items
  around gil 64,000–65,500, such as Holy magicite, Equip. 195/205/210,
  design 100 and Extra 24/33. Those exact values aren't reliable.
- **Gil 1205 and up** reads leftover padding, block headers (heap pointers and
  the source name `cflat_data.cpp`), then language-specific text. It won't
  carry over between languages.

**To settle the layout:** dump MEM1 in Dolphin after loading a save. Find the
item table by its first row and read the block headers on either side. Each
header names its source file and line, so the neighbours are easy to
identify.
