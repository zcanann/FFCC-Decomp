# Glitch Investigations

Explanations of known FFCC glitches, traced through the decompiled GameCube
(`src/`) and GBA client (`gba/src/cli/`) sources. Each write-up starts with a
plain-language summary and gets more technical as it goes.

| Write-up | Summary |
|---|---|
| [Wrong Craft](wrong-craft.md) | Pausing at the right moment makes the GBA open the blacksmith's "ready to craft" screen with no recipe selected. That screen then sends the GameCube a byte left behind by a letter, which the GameCube uses as an inventory slot. Slot 166 is your gil, so your gil amount picks what gets crafted. |

Conventions:

- **Confirmed** means the behavior is read directly from decompiled code.
  **Hypothesis** means it fits the code and observed behavior but has not been
  traced end to end.
- Code links point at the decomp. Function names come from symbols. Many GBA
  names and all comments are reconstructions.
