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

Conventions:

- **Confirmed** means the behavior is read directly from decompiled code.
  **Hypothesis** means it fits the code and observed behavior but has not been
  traced end to end.
- Code links point at the decomp. Function names come from symbols. Many GBA
  names and all comments are reconstructions.
