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

**Example: a 32-bit float.** A float halfword is a large value. 5.0 is
`0x40A00000`; its high half `0x40A0` (16,544) has `A = 0x80A788C0`, which held
`0x4B12` in the sample. Eating a float's high half gives `0xFFFFxxxx`, a NaN.
This fits the reported "huge hitbox" result from eating player data with
`-1`. The exact field behind that result has not been identified in the decomp
yet. It has to be in the caravan or monster work data in `Game`, because the
party objects that hold the collision shapes are out of reach.

### Making a fixed target edible (hypothesis)

1. Read the target's value `T` and compute `A(T)`
   (`tools/cles_scan.py target`).
2. Dump memory on different maps and in different states, and check what lives
   at `A(T)` each time. Heap allocations repeat in a fixed order per map, so
   the same kind of object tends to land there again.
3. Look for heap objects that hold item IDs and can be steered:
   - item objects for food on the ground (`m_objItem` is a static pool, so
     this only helps if the item's ID is copied into heap data)
   - monster drop lists (`CGObject::m_dropItemCodes`)
   - treasure and shop lists built at map load
   - other loaded tables that list food IDs

   If one of them puts a Striped Apple (`0x017D`) or Spring Water (`0x0186`) on
   `A(T)`, the target becomes edible.

The sample `A(0x40A0)` value is a single snapshot. Whether any steerable object
ever lands on a useful `A(T)` is untested.

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
python tools/cles_scan.py target mem1.bin 0x40A0  # where a value's row lands and what is there
```

For EN and JP, GES uses item tables at `0x80954B40` (EN) and `0x80979FC0`
(JP), and `Game` is shifted by `-0x1040` (EN) and `+0x1B900` (JP).

## Open leads

- Identify the field behind the reported "huge hitbox" result and compute
  `A(T)` for each of its halfwords on each caravan.
- Dump several maps and states and track what occupies those `A(T)` addresses.
- Check whether any steerable heap object (dropped food, drop lists, shop
  stock) can be placed on a chosen `A(T)`.
- Map the 39 status-timer indices to statuses and durations.
