# Research Notes

The working state of the glitch investigation: what's established, what's open,
and where to pick up. The finished write-ups are listed in
[README.md](README.md).

## Goal

Find a GBA → GameCube path with a real payoff: player hitbox corruption ("big
chungus", walking through walls), wrong warps, or sequence breaks. The known
glitches (wrong craft, multi-take, multi-sell, CLES, GES, out-of-range
letters) are already documented and give speed, not routing.

## Established

- **Caravan data is static.** Each player's `CCaravanWork` (0xC30 bytes) lives
  in a fixed array of 8. PAL slot 0 is at `0x80220290`, stride `0xC30`. Source:
  [FFCC-GES-Viewer](https://github.com/zcanann/FFCC-GES-Viewer)
  `InventoryViewerViewModel.cs`. EN starts at `0x8021F250` and JP at
  `0x8023BB90`.
- **Write primitives found so far** (see [command-list-oob.md](command-list-oob.md)):
  - **A: `ChgCmdLst`, list index ≥ 8.** Writes a chosen s16 to
    `CCaravanWork + 0x204…0x402`. No GBA trigger known.
  - **B: `DelCmdListAndItem`.** Writes `0xFFFF` to `CCaravanWork + 0xB6 + 2·slot`,
    where slot is any s16 (±64 KB). The write only happens after a successful
    "use". So the 16-bit value already at the target, read as an item ID, must
    have a row kind that uses the item: food `0x17D`/`0x186` via `useItem`. The
    `0x103` random path and kind `0x125` also delete. The target must not
    already be `0xFFFF`.
  - **C: `DeleteItemIdx` / `FGUseItem` / `FGPutItem` with a u8 slot.** Reach
    `+0xB6…+0x2B4` of the caravan block. The GBA sends `slot % 64`, so no
    trigger is known.
- **Items double as attack rows** (see [equipment.md](equipment.md)). This
  explains spell-as-weapon. The lunge distance field is still unidentified.

## Open

1. Where is the player's collision or hitbox size stored? Find the class and
   field, then whether it's in static memory or on the heap. That decides
   whether primitive B can reach it at all.
2. For any candidate target, check its normal value against B's precondition
   (it must read as a usable food or consumable item ID).
3. Is there a GBA path that sends a command-list index ≥ 8 (A) or an item slot
   ≥ 64 (C)?
4. Which field drives the weapon lunge (movement range −1)?
5. What exact frame window lets a letter pause hide menu 11 (joybus state
   machine)?
6. EN character creation: why does a GBA power-off on the last frame build
   the wiped record? Needs the EN `CalcCharaSelect`
   (see [character-creation-disconnect.md](character-creation-disconnect.md)).
7. Guest return power-off: test on hardware
   (see [guest-transfer.md](guest-transfer.md)). Also check whether guests get
   a family in Tipa.
8. Double craft: confirm whether the material loop at gil 4296 trips the GBA's
   30-frame reply timeout (see [wrong-craft-items.md](wrong-craft-items.md)).
9. Meteor Parasite core: what the boss script does if the core dies before
   its later phases (see [weapon-swing.md](weapon-swing.md)).
10. Particles: what a junk particle definition does beyond being drawn.

## Live memory (JP, Dolphin)

- Item table `0x80979FC0`; caravan *n* at `0x8023BBB0 + n × 0xC30`; particle
  slot table `0x802B4600`. JP globals sit about `0x1B900` above PAL's.
- PAL GBA client symbols (`gba/config/cli/symbols.txt`) match the JP client's
  `.bss`, for example `gSession` at `0x03002CA0`.
- Dolphin keeps each GBA's EWRAM and IWRAM in one 0x48000-byte private region,
  tagged `GCCJGC` at +0xAC with the port number at +0xC5.

## Process note

Some analysis steps have been cut off by an automated safety classifier, even
though this is single-player game research. Results go into this file as soon
as they're established, so a cutoff doesn't lose them.
