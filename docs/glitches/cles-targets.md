# CLES Targets: What Can Be Eaten

## In short

The command-list glitch ([CLES](command-list-oob.md)) lets a command slot point
at any halfword within ±64 KB of a caravan's inventory. Using that command
reads the halfword as an item ID. If the game decides the ID is food, the player
eats it and the game writes `0xFFFF` (`-1`) over the halfword.

Two facts decide what this can do:

1. **The reach is static memory, not heap.** It covers the whole `Game`
   object (saved story state, all nine caravans, all 64 monster work structs)
   and about 60 KB of `.bss`/`.data` before it.
2. **"Food" is a table lookup, not a fixed ID range.** The game reads the item
   row at `itemTable + ID × 0x48` with no range check, and treats the ID as
   food if that row's kind is `0x17D` or `0x186`. IDs 381–392 are food because
   of the real table. Any other ID is food if the heap memory its row lands on
   happens to hold `0x017D` or `0x0186`.

So a **fixed target** (a value you want to turn into `-1`) can be eaten only if
its current value is food. Values 0–1204 point into the fixed item table and
can never become food unless they already are. Values of 1205 and up, or
negative values, point into the heap, and changing what the heap holds at that
address changes whether the target is edible.

Addresses below are PAL (`GCCP01`) unless noted.

## The write (confirmed)

When a command is used, [partyobj.cpp](../../src/partyobj.cpp#L1382) reads the
item ID from the command slot and looks up its kind:

```cpp
const int itemId = caravan->GetCmdListItem(cmdIdx);               // (short)m_inventoryItems[slot]
const unsigned short itemKind = *(u16*)(Game.unkCFlatData0[2] + itemId * 0x48);
switch (itemKind) {
    case 0x186:
    case 0x17D:
        if (useItem(itemId) != 0)
            caravan->DelCmdListAndItem(party.unk6BC, 1);
```

- [`useItem`](../../src/partyobj.cpp#L3502) needs the player to be able to act
  and to have HP above 0. It does not check the ID. Kind `0x17D` heals by the
  food's preference value for IDs 381–388, and by 4 for any other ID. Kind
  `0x186` heals 2.
- [`DelCmdListAndItem`](../../src/gobjwork.cpp#L2158) then writes `0xFFFF` at
  `m_inventoryItems[slot]` unless the halfword is already `0xFFFF`.

The slot is a signed 16-bit index (`short m_commandListInventorySlotRef[8]`), so
negative slots reach backwards.

## Reach (confirmed)

The caravans are `Game.m_caravanWorkArr[9]` at `0x802202B0`, stride `0xC30`
(1,560 slots). The inventory is at `+0xB6`. Each caravan reaches
`inventory − 0x10000` to `inventory + 0xFFFE`:

| Caravan | Reach |
|---|---|
| 0 | `0x80210366`–`0x80230362` |
| `k` | shifted up by `0xC30 × k` |
| 7 | `0x802158B6`–`0x802358B2` |

That covers:

- **Before `Game`:** `.data` constants, vtables, jump tables, boss AI function
  tables (`funcsGiantCrab` … `funcsLKShooter`), menu text tables, DSP code
  (`axDspSlave`), audio tables. These are fixed values; eating one corrupts a
  constant or code pointer.
- **All of `Game`** (`0x8021EEC0`, size `0x11F88`), from caravan 1 up:
  - `m_gameWork`: year, story flags, story counters, myrrh and stage tables,
    chalice element
  - the nine caravans (stats, inventory, equipment, letters)
  - `m_monWorkArr[64]` (monster stats and status timers)
  - party and monster object pointers, map and scene IDs, the next-script
    request, and the loaded script data tables (`m_cFlatDataArr`)
- **The start of `Graphic`** (`0x80230E48`) from caravan 1 up.

Out of reach:

- the script globals `G0`–`G426` (heap, via `CFlat.m_permanentVarValues`)
- the `Memory` object (`0x8023C888`)
- the game objects themselves. They live in static pools far past the window:
  party objects in `m_objParty` (`0x802C8D00`), items such as the chalice in
  `m_objItem` (`0x802BDD80`). Their positions and collision shapes are
  therefore out of reach. Only the per-caravan and per-monster *work* data in
  `Game` is reachable.

[command-list-oob.md](command-list-oob.md#what-a-given-slot-reaches) lists slot
numbers for the main `Game` fields.

## What counts as food

Because the lookup is `itemTable + ID × 0x48` for any signed ID, the set of
edible values is:

- **381–392 (`0x17D`–`0x188`)**, from the real table. 392's row has kind
  `0x186`, so it counts too. These never change.
- **Heap extras:** IDs from 1,205 up, or negative, whose row lands on heap
  memory holding `0x017D` or `0x0186`. These depend on what is loaded, so they
  change with map loads and heap use.

Sample (year 1, `mine_0`, item table at `0x80955BC0`):

| ID | Row address | Kind found |
|---|---|---|
| 381–392 | `0x8095C...` (table) | `0x17D`/`0x186` |
| 9,118 (`0x239E`) | `0x809F6030` | `0x186` |
| 9,229 (`0x240D`) | `0x809F7F68` | `0x186` |
| 18,051 (`0x4683`) | `0x80A93098` | `0x186` |
| −11,039 (`0xD4E1`) | `0x80893B08` | `0x17D` |

## Fixed targets

For a target holding value `T`, the halfword that decides whether it is edible
is at:

```
A(T) = itemTable + (signed)T × 0x48        (PAL item table 0x80955BC0)
```

- **`T` from 0 to 1204:** `A(T)` is inside the item table, loaded from disc.
  If row `T` isn't food, `T` can't become food. This rules out the year (1 in
  year one, row 1 kind `0x0001`), map and scene IDs, slot numbers, small story
  counters and most story-flag byte pairs.
- **`T` of 1205 or more, or negative:** `A(T)` is in the heap. If something
  can be made to hold `0x017D` or `0x0186` at `A(T)`, the target becomes edible.

## The hitbox target ("Big Chungus")

### The chain (confirmed)

A caravan's body radius comes from its character data row:

- The player script sets body radius 0 to `0.01 × csys[-0x175]` (source line
  493 of every map's `Player_for_Battle` code).
- Per-object values `-0x175` to `-0x96` are read through the work struct's
  `m_romWork` pointer ([cflat_r2class.cpp:784](../../src/cflat_r2class.cpp#L784)),
  so the radius is `0.01 × m_romWork[0]`.
- `m_romWork` is at caravan `+0x24`, next to the inventory. It is set in
  [`CCaravanWork::LoadFinished`](../../src/gobjwork.cpp#L281):

  ```cpp
  m_baseDataIndex = (m_id / 100) - 1;
  m_romWork = Game.unkCFlatData0[0] + m_baseDataIndex * 0x1D0 + 0x10;
  ```

  `m_id` is `100 × (row + 1) + appearance`, so the appearance is dropped and
  there are 8 player rows, one per tribe and gender. All 8 hold 500 as the
  first halfword (radius 5.0).

Eating the pointer's **low half** (caravan `+0x26`, slot −72 from that
caravan's own inventory) makes it `0x8093FFFF` in PAL, because all 8 rows share
the high half `0x8093`. The first halfword read from there is `0xFF00`, so the
radius becomes **652.8**. This matches the "huge hitbox" seen when the value
was poked to `-1` by hand.

### The 8 food-check slots (PAL)

The low half `T` is one of 8 fixed values, so whether it is edible depends on 8
fixed heap addresses. They are numbered by ascending address, which is also
row order. They are exactly `0x8280` bytes apart (`0x1D0 × 0x48`).

| Slot | Pointer low half `T` | Food-check address `A(T)` |
|---|---|---|
| 0 | `0xE3D0` | `0x808D6E40` |
| 1 | `0xE5A0` | `0x808DF0C0` |
| 2 | `0xE770` | `0x808E7340` |
| 3 | `0xE940` | `0x808EF5C0` |
| 4 | `0xEB10` | `0x808F7840` |
| 5 | `0xECE0` | `0x808FFAC0` |
| 6 | `0xEEB0` | `0x80907D40` |
| 7 | `0xF080` | `0x8090FFC0` |

The command list aims at the caravan's pointer halfword in `Game`, which is
static and already in reach. What is missing is `0x017D` or `0x0186` at the
slot's address at the moment of eating.

### What occupies the slots (two dumps)

Heap blocks have a 0x40-byte header (magic `0x4B41`, size, links, the source
file and line that allocated it, end magic `0x4D49`), and new memory is filled
with `0xCD`. Walking the headers:

| Slot | `mine_0` | `kinoko_0` |
|---|---|---|
| 0 | Character draw buffer (`chara.cpp:64`, 352 KB), unused tail at `+0x52340` | same |
| 1 | Lighting texture buffer (`p_light.cpp:315`) | same |
| 2 | Free memory | same |
| 3 | Start of a model-load record (`p_chara.cpp:1512`) | same |
| 4 | Start of a model-load record | Header of a texture-load record (`p_chara.cpp:1545`) |
| 5 | Start of a per-object model handle (`gobject.cpp:2561`, `CCharaPcs::CHandle`) | Header of a model handle |
| 6 | Free memory | Start of a model handle |
| 7 | Free memory | Free memory |

Every value seen there is fill, a pointer half, 0, or the block magic.

**Alignment.** The slot addresses, the block headers and every block's data are
all 64-byte aligned. A slot can only be covered by a block header (always
`0x4B41`) or by data at offset 0, `0x40`, `0x80`, … of a block. A small record
can only help if its first field is an item ID; `CLoadModel`'s model ID at
`+0x0E` can never line up.

### Routes that remain (hypothesis)

- **Large data blocks** covering a free slot (2, 7, and 6 on some maps).
  Loaded file buffers hold arbitrary data at 64-byte boundaries, so a
  `0x017D` or `0x0186` could line up on some map.
- **Slot 0 in the draw buffer.** The buffer is rewritten every frame with GPU
  commands, including 16-bit vertex indices. In a scene heavy enough to reach
  `+0x52340`, the halfword there changes frame by frame. A value of 381–392 on
  the right frame would make slot 0 edible for that frame.

Other versions load the rows and item table at different addresses, so their
8 slots need their own dump.

## In-reach values that reach 381–392 on their own

| Field | How it gets into range | Result of `-1` |
|---|---|---|
| Any caravan's inventory (all 8 save slots, not only the party) | Holding food | Item deleted |
| Letter attachments (from caravan `+0x3EC`) | Food gifts | Untested |
| Mio quiz question IDs `eventWork[150–155]` = `(diary & 511) + 19` (up to 530) | Your diary contents | Changes the shown question only; answers are stored separately in `[160–165]` |
| Status timers (39 per caravan and per monster) | Countdowns pass through every value | Becomes 65,535 frames, about 22 minutes |
| 32-bit frame counters (low half) | Every 65,536 frames | Small time skip |

Story flags (`m_eventFlags`) need a byte pair of `01 7D`–`01 88`, which ordinary
progress makes unlikely. The story counters that scripts increment are all
capped well below 381, except `eventWork[9]` (dungeon clears).

## Sample scan (year 1, `mine_0`)

Edible halfwords in the whole reach at that moment:

- **28 halfwords:** food in the inventories of caravans 4–7.
- **5 halfwords:** `.data` constants (shop menu layout, VI timing, DSP code, a
  pitch table, and one `0x0188` in DSP code).
- **1 halfword:** the low half of a heap pointer inside `m_cFlatDataArr[1]`
  (`Game+0xE93A`). Eating it would most likely crash.

None of the heap extras matched an interesting field.

## Tools

[`tools/cles_scan.py`](../../tools/cles_scan.py) (PAL):

```sh
python tools/cles_scan.py dump mem1.bin         # read MEM1 from a running Dolphin (Windows)
python tools/cles_scan.py edible mem1.bin       # every value that is food right now
python tools/cles_scan.py scan mem1.bin         # edible halfwords inside the CLES reach
python tools/cles_scan.py target mem1.bin 0xE3D0  # where a value's row lands and what is there
```

For EN and JP, GES uses item tables at `0x80954B40` (EN) and `0x80979FC0`
(JP), and `Game` is shifted by `-0x1040` (EN) and `+0x1B900` (JP).

## Open leads

- Dump busy maps (towns, boss rooms, many monsters) and record which
  allocations cover the 8 slots, looking for large data blocks on slots 2, 6
  and 7.
- Measure how full the character draw buffer gets in heavy scenes, to see
  whether slot 0 is ever written.
- Dump EN and JP to get their 8 slots.
- Monster work structs have their own `m_romWork` pointers (in reach), giving
  more slots for giant monsters.
- Map the 39 status-timer indices to statuses and durations.
