# The Particle System

## In short

Particles (spell effects, weapon trails, hit sparks, map ambience) come from
**particle sets** (`.pdt` files plus `.ptx` textures). The game keeps up to
**32 sets** loaded in a slot table, and up to **384 live particles** at once.

- A particle is spawned by **set slot + particle number**. The game copies that
  particle's definition into a free live entry.
- Every frame, each live entry advances its timeline, moves, tests hits, and
  is drawn by draw pass.
- Spell particles carry the **item ID** that spawned them, so their hits use
  the same item row as a weapon's contact hit. That's how Firaga +2 hits twice
  (see [weapon-swing.md](weapon-swing.md)).

Everything here is confirmed from the decompiled code. JP addresses are from a
live game.

## Set slots

`CPartMng::m_pdtSlots[32]` ([partMng.h](../../include/ffcc/partMng.h)) sits at
`PartMng + 0x22E18` (JP `0x802B4600`; PAL `PartMng` is `0x80275EE8`). Each
0x38-byte slot holds:

- a pointer to the loaded set's data (0 means empty);
- a small environment block;
- the set's name (its file path).

| Slot | Contents | Loaded by |
|---|---|---|
| 0 | The current map and floor's field set | `LoadFieldPdt0` ([p_tina.cpp:1026](../../src/p_tina.cpp#L1026)), on every field load |
| 1–5 | Shared player and spell sets `chobit_0`–`chobit_4` | Startup ([p_tina.cpp:437](../../src/p_tina.cpp#L437)); stay loaded |
| 6 | Location-title effect | `CPartPcs::StartLocationTitle` |
| 7 | Myrrh (Mirura) event effect | `CPartPcs::StartMiruraEvent` |
| 8–31 | Monster and menu sets, first free slot | `LoadMonsterPdt` and the menu loader, via `pppGetFreeDataMng` ([partMng.cpp:3385](../../src/partMng.cpp#L3385)) |

A field load releases slots 0, 6 and 7 before loading the new field set. If no
slot from 8 to 31 is free, the game stops with `OSPanic`.

## What a set contains

`pppLoadPdt` ([partMng.cpp:3301](../../src/partMng.cpp#L3301)) reads
`<name>.pdt` as a chunk file:

- **`RSET`:** models, added to the shared model set.
- **`SSET`:** shapes (2D sprite layouts), added to the shared shape set.
- **`PDTS`:** the particle list. It's copied to the stage heap as:
  - a 0x20-byte header (`_pppDataHead`): particle count, then counts of and
    pointers to cache chunks, models, shapes and shape groups;
  - then **`m_partCount` particle definitions**, 0x60 bytes each
    (`_pppFieldParticleData`).

A particle definition holds:

- **Placement:** position, rotation and scale.
- **Timing:** start delay.
- **Part index:** which **part** (animation program and data) it plays.
- **Culling:** distance, radius and Y offset.
- **Drawing:** draw pass, matrix mode, billboard flag, priority.
- **Attachment:** a map-object index, and a **node name** used to attach to a
  character's bone.

A part's data isn't kept in main RAM all the time. It's fetched by cache index
through `ppvAmemCacheSet` (the ARAM cache), the first time a particle using it
starts.

## Spawning

`pppCreate(slot, number, params)` → `pppCreate0`
([partMng.cpp:3441](../../src/partMng.cpp#L3441)):

1. If the slot has no set, it returns −1 and nothing happens.
2. It takes the free live entry (`_pppMngSt`) from the 384, and copies the
   definition's fields into it.
3. It combines the caller's parameters with the definition:
   - **Position, rotation and scale:** a position is added to the definition's
     offset, a rotation replaces the definition's, and a scale multiplies it.
   - **Hit setup:** hit parameters (including the item ID), hit mask, owner
     slot and "look at" target.
4. **Matrix mode** decides attachment:
   - 2 or 4: follows a map object.
   - 3 or 5–8: binds to the caller's object, and looks up the definition's
     node name in that object's skeleton.
5. It returns the entry index. The owner slot lets the game end or delete all
   of one owner's particles later (`pppEndSlot`, `pppDeleteSlot`).

## The frame loop

`CPartMng::pppPartCalc` ([partMng.cpp:2526](../../src/partMng.cpp#L2526))
walks all 384 entries:

- **Free entries** (`m_baseTime == -0x1000`) are skipped.
- **While the game is paused**, only entries in draw passes 6–7 keep updating.
- **Start delay:** a new entry's timer counts down first. The definition's
  delay is scaled by 25/30. When it runs out, the part's data is fetched from
  the ARAM cache, its program is initialised, and the part starts
  (`_pppStartPart`).
- **Running:** each frame adds `m_deltaTime` (normally `0x1333`, which is 1.2
  in 4.12 fixed point) to an accumulator. For every whole step, it runs one
  part update (`_pppCalcPart`) and one cleanup pass (`_pppDeadPart`), stopping
  early if the particle has finished. So particle timelines run at **1.2 steps
  per game frame**; slot 7 particle 0 can run at 1.0 under one flag.
- **Matrices:** each frame rebuilds the entry's world matrix from its
  position, rotation, scale, and the bound node if any.

Other passes:

- **`pppPartDead`:** frees the objects of entries that finished or hit the
  map.
- **`pppDraw` / `pppDrawPrio`:** draw entries by draw pass. Each one is culled
  against the camera using the definition's cull values.

## Hits

Hit-enabled particles check collisions during their update
([pppPart.cpp:2190](../../src/pppPart.cpp#L2190) onward):

- **Map:** a hit calls `Game.HitParticleBG`.
- **Objects:** for each game object, it checks up to 8 damage colliders. A
  collider only counts if:
  - the object is hittable (`m_bgColMask` bit `0x80000`; the Meteor Parasite
    core sets this when it opens up);
  - the collider's hit mask matches the particle's (`m_objHitMask`);
  - the collider has a radius.

  The test is a capsule against an ellipse. A hit calls the object's
  `HitParticle` with the entry's hit parameters.
- Each particle remembers which objects it has hit, so it hits each object
  **once**, up to **16** objects.

For a weapon's particles, `putParticleFromItem` sets the hit parameters to the
**item ID** and the attacker (`SetParticleWorkParam`), and enables hits for
IDs ≥ 501 (`SetParticleWorkCol`). That's why a spell row equipped as a weapon
casts the spell on top of the contact hit.

## Where this connects to glitches

- **Bank and number:** the slot and particle number in an item row aren't
  range-checked (see [weapon-swing.md](weapon-swing.md)). A bank past 31 reads
  past the slot table. A particle number past the set's count reads beyond
  its definition list.
- **Slot 0 changes with every map**, and slots 8 and up depend on which
  monsters are loaded. Only slots 1–5 are the same everywhere. So a weapon
  that spawns from slot 0 or a monster slot behaves differently from map to
  map.
