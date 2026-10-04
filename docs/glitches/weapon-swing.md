# Glitched Weapons: Damage, Crashes and Bosses

## In short

When you swing, the game uses your weapon's **item row** as the attack. With
GES or wrong equip, any item can be the weapon, so any row can be the attack:

- **Damage** comes from a few fields: power, damage type, and a kind check.
  Among real items, the best is **power 120** (Firaga +2, Blizzaga +2,
  Thundaga +2). Firaga +2 also casts the spell, because its particles carry a
  hit of their own.
- **Crashes, softlocks and GPU errors** come from the row's **particle**
  fields. The particle bank and number are barely checked, so a junk row can
  spawn particles from the wrong set or past the end of one.
- Rows outside the real table can have huge power. **No stable, positive item
  ID beats Firaga +2**: the strong ones are either negative (wiped when you
  leave the map) or in script memory (different on every map).
- The **Meteor Parasite core** checks its phase thresholds when hit, so one
  big enough hit may kill it before later phases. Mio-Raem and Maggie can't be
  rushed this way.

Item IDs, memory ranges and JP addresses come from
[wrong-craft-items.md](wrong-craft-items.md).

## Damage (confirmed)

`CGCharaObj::onDamage` ([charaobj.cpp:1367](../../src/charaobj.cpp#L1367)
onward) reads the swung row as `SCharaItemRow`
([itemobj.h](../../include/ffcc/itemobj.h)):

- **Kind gate.** For item IDs ≥ 501, field `0x02` must be 1, or the hit does
  no damage. IDs below 501, including negative ones, skip the check.
- **Type** (field `0x08`):
  - **Magic types (0, 1, 4, 0x1C):** damage = (power at `0x06` + Magic) ×
    multiplier − Defence. Type 0 uses the ice resistance, 1 fire, 4 thunder.
  - **Physical types (0x24, 0x25, 0x64, 0x69, 0x6A):** your Strength only. The
    row's power is added only for skill rows (field `0x00` = `0x1F8`).
  - **Anything else:** no damage. The game logs an unknown type.
- Power is loaded unsigned (`lhz`), so `0xFFFF` is 65,535.

### Stats from equipping (`CalcStatus`, [gobjwork.cpp](../../src/gobjwork.cpp))

- **Kind 1:** adds `0x06` as Strength.
- **Kind 0x45:** adds Defence plus an effect.
- **Kind 0x7F:** an effect only.
- **Effect values:**
  - 1–8: element resistances.
  - **19 (0x13):** resistance index 0, which `calcRegist` uses for the
    physical weapon types. That's the **Force Ring** (physical resistance,
    capped at 2).

### Notable items as weapons

| Item | What it is | As a weapon |
|---|---|---|
| Firaga +2 (534) | Spell | Fire, power 120, contact hit plus a Firaga cast. The best stable option. |
| Ultimite, Dark Sphere | Crafting materials (kind 0x12A) | Type `0xFFFF`: no damage. |
| Ultima / Holy magicite | Unused placeholders | No damage. Also deleted with the rest of the magicite. |
| Ribbon | Magic +9 artifact (kind 0xB6, only counts in artifact slots) | Type 0: a weak ice hit, power 9. |
| Force Ring | Accessory: physical resistance | Type 19: no damage. |
| −50 (`0xFFCE`) | Monster-block row | Thunder, power 160. Two-shot a normal mob in testing. No cast. Wiped when you leave the map. |

## What a swing reads (confirmed)

`CGCharaObj::statAttack` ([charaobj.cpp:931](../../src/charaobj.cpp#L931)):

1. **Model**, when equipped: `LoadWeapon(field 0x02 & 0xFFF, field 0x02 >> 12)`.
2. **Particles**, on the first frame: four `putParticleFromItem` calls, one
   per entry.
3. **Sounds**, at the frames given in fields `0x38`–`0x3E`.
4. **For IDs ≥ 501:** each particle also gets a hit area
   (`SetParticleWorkCol`). That's the spell-as-weapon second hit.

### Particles

`putParticleFromItem` ([charaobj.cpp:1006](../../src/charaobj.cpp#L1006)) and
`CPartMng::pppCreate0` ([partMng.cpp](../../src/partMng.cpp)):

- **Bank** (field `0x12`, loaded unsigned):
  - 253 or 255: no particle.
  - 254: the character's own set.
  - **Anything else is used as an index into a 32-entry slot table, with no
    bounds check.**
- **Entries** (fields `0x14`–`0x1A`, four of them):
  - `0xFFFF`: none.
  - Otherwise the low byte is the particle number. Bits `0x1000`/`0x2000`/
    `0x4000` force bank 1, 2 or 3.
- **Empty slot:** the spawn is quietly skipped.
- **Loaded slot:** the particle number is **not checked** against the set's
  particle count (`m_partCount`). A number past the end reads whatever follows
  as a particle definition.

On JP the slot table is at `0x802B4600` (`PartMng` + 0x22E18; PAL `PartMng`
is `0x80275EE8`). On the first map of the final dungeon:

| Slot | Contents |
|---|---|
| 0 | **This stage's own set** (`stage031/fp000`, 58 particles) |
| 1–5 | Shared player and spell sets `chobit_0`–`chobit_4` |
| 8–11 | This map's monster sets |
| others | Empty |

### Why weapons crash or not

| Result | Cause |
|---|---|
| Works | No particles; real particles in slots 1–5; or an out-of-range bank that lands on a zero word, so it's skipped. |
| GPU "invalid instruction" spam | A junk particle definition gets drawn. |
| Softlock or hard crash | A junk definition or pointer. Particles from the stage's set (slot 0) crashed both times they were tested. |

Tested items:

| Item | Particles | Result |
|---|---|---|
| Firaga / Blizzaga / Thundaga +2 | Bank 2 (shared set), real particles | Works |
| −50 | Bank 2,200 (reads 0 here, so skipped) and bank 2 #15 | Works on this map |
| −810 | Bank 0 (stage set) #0 ×4 | Crashes |
| 7256 | Bank 0 (stage set) #0, #6, #0, #0 | Crashes on swing or map entry |
| −523, −1045, −117 | Bank 65,535 (garbage pointer) and bank 1 #242 (past 127) | Predicted crash |

Particles from slots 1–5 with a valid number are the only ones known to be
safe on every map. What a junk particle definition does beyond being drawn
hasn't been traced.

## Searching for a better weapon

Scans of live JP memory (a town and two maps of the final dungeon) for rows
that pass the kind gate, have a magic type and beat power 120:

- **Stable negative rows** (monster block): many with power 65,535, such as
  −523 (fire). All the ones found have broken particles, and negative items
  are wiped on leaving a map.
- **Positive rows in script memory:** strong candidates exist on each map,
  such as 6450 (fire, 15,360). But none of them matched between maps, so the
  stats change with the map.
- **The stable positive range** (IDs 1,206–4,173, boot-time text): only 11
  rows pass the kind gate, and none is usable.

So for every boss, the ceiling is still the real table, with Firaga +2 the
pick. An item that's only strong in one arena could still be carried
unequipped and equipped there.

## Bosses and big hits (confirmed in code, untested)

`CGCharaObj::addHp` ([charaobj.cpp](../../src/charaobj.cpp)) special-cases
three monsters by base-data index. HP never goes below 0. When a hit takes it
to 0, the boss's own damage hook runs first, then the death state.

| Index | Monster | Rule |
|---|---|---|
| 0x70 | Maggie | HP can't drop below 1 from a hit. |
| 0x88 | Meteor Parasite core | Damage also adds to a counter in the shared boss data. |
| 0x9A | Mio-Raem | While `m_actionBranch` is 0, damage only adds to a counter; HP doesn't change. |

**Meteor Parasite core** (`damagedFuncMeteoParasiteC`,
[monobj_boss.cpp:1198](../../src/monobj_boss.cpp#L1198)):

- **Phase 0:** advances to the next phase below 2/3 HP.
- **Phase 1:** advances below 1/3 HP.
- **Phase 2:** dies at 0.
- **Every 50 damage** on the counter, the core retreats for 375 frames.

A single hit that takes it from above the threshold to 0 should start the
death state in phase 0 or 1, skipping the remaining phases. What the
(undecompiled) boss script does with an early death, when its phase counter is
lower than expected, is the open question.

Maggie's and Mio-Raem's endings are decided by script, so damage can't skip
them.
