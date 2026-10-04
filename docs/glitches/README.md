# Glitch Investigations

Explanations of known FFCC glitches, traced through the decompiled GameCube
(`src/`) and GBA client (`gba/src/cli/`) sources. Each write-up starts with a
plain-language summary and gets more technical as it goes.

| Write-up | Summary |
|---|---|
| [Research Notes](research-notes.md) | Working state: established facts, open questions, where to resume. |
| [GBA → GameCube Trust](gba-gc-trust.md) | **Start here.** Every command the GBA can send, what the GameCube fails to check, and the ranked leads. |
| [Command List OOB (CLES)](command-list-oob.md) | Command-list slots store unchecked inventory indices. Using one reads any value within ±64 KB as an item, and eating it writes `-1` there. |
| [Wrong Equip (GES)](equipment.md) | Equip slots accept any inventory slot. Items double as attack definitions, so a spell "weapon" swings with the spell's attack row. |
| [Wrong Craft](wrong-craft.md) | Pausing at the right moment makes the GBA open the blacksmith's "ready to craft" screen with no recipe selected. That screen then sends the GameCube a byte left behind by a letter, which the GameCube uses as an inventory slot. Slot 166 is your gil, so your gil amount picks what gets crafted. |
| [Wrong Craft: Items](wrong-craft-items.md) | What each gil value crafts. Gil 401–493 crafts any recipe with no materials (492 = Ultima weapon). Where the item table lives, unused items in reach, and what lies past either end. |
| [Glitched Weapons](weapon-swing.md) | How a swung item row deals damage, why junk weapons crash (unchecked particle bank and number), what stable items exist, and how boss HP hooks react to huge hits. |
| [Particle System](particles.md) | How particle sets are loaded into 32 slots, how particles spawn, update, draw and hit, and which slots change per map. |
| [Character Creation Disconnect](character-creation-disconnect.md) | A GBA disconnect wipes that player's creation record to zeros, which would build a blacksmith in slot 1. PAL clears the record before it can be used; EN apparently doesn't (hypothesis). |
| [Guest Transfer](guest-transfer.md) | Guests return only their artifacts, matched by character ID. "Restore" just clears the away flag, so orphaned guests can come back later. Powering off between the two saves during a return may sync artifacts while keeping the guest (hypothesis). |

Conventions:

- **Confirmed** means the behavior is read directly from decompiled code.
  **Hypothesis** means it fits the code and observed behavior but has not been
  traced end to end.
- Code links point at the decomp. Function names come from symbols. Many GBA
  names and all comments are reconstructions.
