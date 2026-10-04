# Towns, the World Map and Letters

## In short

Town scripts, the world map, the festival and the post-boss letter selection.
Most interesting first:

1. **Six letters can never arrive (confirmed).** The letter condition code has
   four `case 15:` labels where four different numbers were meant, and four
   letters use a condition type with no case at all.
2. **Tipa families recognise you by occupation, not by character
   (confirmed).** With two characters of the same occupation, visiting the
   other's family counts as visiting your own.
3. **The ship-repair donation can skip its one-year wait (confirmed)** if you
   decline the first offer and pay on the second.
4. **The same donation can be charged to two players (script confirmed,
   simultaneous talk untested).**
5. **The diary stops at 256 entries, and later festivals show no diary
   (confirmed).**
6. **The multiplayer ship prompt only accepts L+R+A from port 1 (confirmed;
   softlock depends on setup).**
7. **The Alfitaria Guard Master can freeze for the visit (logic confirmed,
   multiplayer).**

## 1. Six letters that never arrive

**Status:** Confirmed (bytecode and letter table). The intended labels are a
Hypothesis. **Applies to:** both.

After each boss, the game picks letters for each player. For each candidate it
calls `checkLetterSub`, which switches on the letter's condition type. Four
blocks check "a Selkie / Yuke / Lilty / Clavat is in the party", and all four
are labelled `case 15:`:

```c
// checkLetterSub (identical in all 15 boss scripts and mail.cft)
switch (cond & 255) {                       // 41
    ...
    case 15:  /* Selkie present */          // 101  (bytecode 06C9: pushi 15)
    case 15:  /* Yuke present   (dead) */   // 114  (081A: pushi 15)
    case 15:  /* Lilty present  (dead) */   // 127  (096B: pushi 15)
    case 15:  /* Clavat present (dead) */   // 140  (0ABC: pushi 15)
    case 16: ... case 24: ...
}
return 0;                                   // 263: "not eligible"
```

The switch compares cases in order, so only the first `case 15` can run. The
letter table (`mail_tbl.cfd`, 512 records) uses condition types:

| Type | Letters | Result |
|---|---|---|
| 12 | #116 | no case → never sent |
| 13 | #37 | no case → never sent |
| 0 | #54, #120, #134, #137 | no case → never sent |
| 0 | #501, #502 | given directly by `addLetter` in ruin_1 (fine) |

`checkLetterMain` keeps a candidate only if its score beats the current best,
which starts at 0, so a return of 0 is never picked. No script sends these
letters by other means.

The letters, from `c_system.cfd`:

- #37 (sender 101): "So how's everyone doing? Times must be tough ... your
  friends are always with you."
- #116 (sender 304): "I helped Mother around the house the other day, and she
  gave me a big reward. I'm going to share it with you, Brother!"
- #54: a father's letter ("as your father, I'm happy as long as you have a good
  time").
- #120: "Now I want to join the caravan ... No goblin will stand in my way!"
- #134 (sender 301).
- #137: "I found Father working on some jewels in the middle of the
  night!"

The three type-15 letters (#131-133) are Selkie-themed, which fits the first
label. A likely intent is 15, 14, 13, 12 for Selkie, Yuke, Lilty, Clavat. That
would make #37 need a Lilty and #116 a Clavat in the party. The type-0 letters
may have been cut on purpose, but they have finished text and replies.

## 2. Tipa families: same occupation counts as the same family

**Status:** Confirmed (bytecode). **Applies to:** both. Needs two characters
with the same family occupation.

When you talk to a family member in Tipa (village_0), the script decides "is
this my family?" like this:

```c
// village_0, source line 346
if (arg0.this.m9 == this.m9 && (arg0.csys[...] & 1) == 0)
// player m9 = getCaravanJob(slot)  (line 389)
// NPC    m9 = getCaravanJob(family) (line 79)
```

`m9` is the family occupation, not the character slot (`m10`). Two characters
with the same occupation are each treated as a member of the other's family.

**How to trigger:** create two characters with the same occupation (for
example both Blacksmith). Bring character A to Tipa and talk to character B's
father, mother and siblings.

**Consequence:**

- It sets **A's** "talked to family member k this year" flags (source lines
  353, 512, 594, 635, 664, 703). At the year change, `setHouseGrow` (world
  lines 286-332) rewards those with affection for **A's own** family and counts
  it as a visit, which also suppresses the "never visited and has 10,000+ gil"
  flag.
- It opens the "own family" dialogue: produce gift prompts (paid from your own
  stock, not a dupe) and the family smith/shop at the like-scaled price instead
  of the outsider rate.
- `setHouseGrow` updates the shared shop/smith/gift tiers once per caravan
  slot, so with duplicate occupations a tier can rise twice in one year.

Related (Hypothesis, multiplayer): the job-7 father's yearly gift uses one shared offer and one shared "claimed" flag, checked when the talk
starts but set only after the player accepts (EventClient lines 1594-1601). Two
players talking to two job-7 fathers at the same time might both get the item.

## 3. Leuda ship-repair donation: paying on the second offer skips the wait

**Status:** Confirmed. **Applies to:** both.

The ship-repair chain asks for a 50,000 gil donation at the ferryman (thief_0,
with copies in port_0 and lava_0). Both offers are gated by
`sysVal0 > G371 && eventWork[110] < 50` (line 516):

```c
case 30:                            // first offer
    eventWork[110] = 40;            // 519
    ... if (paid) { eventWork[110] = 50; G371 = sysVal0 + 1; }   // 530-531
case 40:                            // repeat offer after declining
    ... if (paid) { eventWork[110] = 50; }                      // 549: G371 not set
// castle_0, lines 2255-2257
if (sysVal0 > G371) { G371 = sysVal0; /* advance to the Alfitaria step */ }
```

**How to trigger:** after delivering both ship parts and waiting a year,
decline the 50,000 gil prompt, talk to the ferryman again and pay. Then go to
Alfitaria in the same year.

**Consequence:** the Alfitaria follow-up is available in the same year instead
of the next. The same omission is in port_0 (lines 629 vs 648) and lava_0 (507
vs 526). Nothing breaks.

## 4. The donation can be charged twice

**Status:** Script Confirmed. Whether two players can be in the dialogue at once
is a Hypothesis. **Applies to:** multiplayer.

Each player's EventClient runs the ferryman branch separately. The first talker
at `eventWork[110] == 30` sets it to 40 before the prompt. A second player who
talks while that prompt is open lands in `case 40` and gets the same prompt.
`onTalkFERRYMAN` (lava_0 lines 368-395) never turns a second talker away. Each
"yes" calls `addGil(player, -50000)`.

**Consequence:** both players pay 50,000 gil for one repair.

## 5. The diary stops at 256 entries

**Status:** Confirmed. **Applies to:** both.

Diary entries are stored in the saved array `G99[256]`, with the count in
`G355`. `addDiary` (world lines 109-143) refuses once the count reaches 256,
and nothing removes or rotates entries:

```c
if (G355 < 256) { G99[G355++] = ...; return 1; }
return 0;
```

At the festival, `DiaryView` counts this year's entries (festa_0 lines
474-552). With a full diary that count is 0, so both the "Diary from Year N"
pages and the year-end summary page are skipped.

**How to trigger:** play long enough to log 256 diary events. At about 10-20 a
year that takes roughly 13-25 years.

**Consequence:** long games silently stop recording, and later festivals show
no diary. The per-character memory counter still goes up (lines 112-115 run
before the size check).

## 6. Multiplayer ship prompt only listens to port 1

**Status:** Code Confirmed. The softlock is a Hypothesis (depends on a GameCube
controller being present in multiplayer). **Applies to:** multiplayer.

Before a ship voyage, `wmShipPadCheck` looks for a plain GameCube controller.
In multiplayer it shows message 334 ("To play multiplayer mode, please connect a
Game Boy Advance ... You can proceed by pressing the L + R + A Buttons
simultaneously.") and reads each port into its own variable, but all four
checks test port 1's:

```c
// world wmShipPadCheck
this.m30 = getPad(1);                                   // 1237
if (this.m29 & 64 && this.m29 & 32 && this.m29 & 256)   // 1238: m29, not m30
...                                                     // same for m31 (1244-1245), m32 (1251-1252)
```

**How to trigger:** in multiplayer, have a GameCube controller in port 2, 3 or
4 for a present player and take a ship. L+R+A on that controller does nothing.

**Consequence:** the world map waits on the prompt. Unplugging the controller
ends the loop. The single-player branch is correct.

## 7. Alfitaria Guard Master can freeze

**Status:** Logic Confirmed (bytecode). Timing is a Hypothesis.
**Applies to:** multiplayer.

At the end of each patrol leg the Guard Master (castle_0) tells the guards there
to report (`setPRG(1000)`), sets `m20 = 1` and waits (lines 1883-1904). He only
resumes when a guard answers with `setPRG(1500)` or `1550`. A guard that is
mid-conversation does nothing (lines 1701-1735). Only guard 1 has a fallback.
Legs 7, 8 and 10 go to pairs of guards.

**How to trigger:** two players each talk to one guard of a pair (for example
the two gate guards) and stay in the dialogue until the Guard Master arrives.

**Consequence:** he stops patrolling and can't be talked to (`onTalkGuardMaster`
needs `m20 == 0`, line 2000) for the rest of the visit. Talking to him is a
step in the Fiona side quest (line 2003), so that step waits until the map
reloads.

## 8. Shella: one NPC hint wipes the other players' flags

**Status:** Code Confirmed (bytecode). In-game effect untested.
**Applies to:** multiplayer.

Npc_MAG_06's hint in magic_0 (EventClient case 121, era `eventWork[1] == 5`,
repeatable) freezes all players, then restores the non-talkers with:

```c
G452[i].this.m2 = G452[i].this.m2 & (~this.m2 & 16384);   // 3014
```

`this.m2` is the EventClient's own flags, which don't have bit `0x4000`, so
this is `player.m2 &= 0x4000`: every other flag bit is cleared. The players are
then put in talk state 75, which they leave only when `0x4000` is set. They
keep a heavier collision weight (150 instead of 50) until they next talk to
something. In single player this only matters if Mog occupies slot 1, where it
clears Mog's `0x800000` "Mog as player" bit.

## 9. Mount Vellenge's world-map bubble never shows its myrrh tree

**Status:** Code Confirmed. Whether it's intentional is a Hypothesis.
**Applies to:** both.

```c
// world WM_mapInfoDispOn
globalTime = arg0;            // 919: stage number (scratch use of a system variable)
if (globalTime < 13) {        // 921
    setWorldParam(1, stageTable[arg0] == 100);   // ripe or not
    setWorldParam(2, arg1 | 512);                // 512 = show the tree
} else { ... no tree ... }
```

Mount Vellenge is stage 13 (`WM_mapInfoDispOn(13, 0, 3, ...)`, line 4219). Its
myrrh tree is tracked like the others (`incMana(13)` in meteo_2/3,
`stageTable[13]`), but its bubble never shows the tree icon.

## 10. Lost dialogue

**Status:** Confirmed. Cosmetic. **Applies to:** both.

- **Marr's Pass resident (weapon_0 `resident_F`).** `switch (rand(4))` case 2
  sets line 36 ("That lady in front of the inn is the mistress. She's a bright
  and capable woman!") but has no `break` (source lines 1305-1312). It falls
  into case 3, which always overwrites it. Line 36 never shows, and case 3's
  lines appear half the time.
- **Amidatty's "twice" line** in the mag_3 road event: see
  [road-events.md](road-events.md#1-amidattys-you-ate-it-twice-line-never-plays).

## Hypotheses

- **Yuke kid quest reward re-arms.** One swamp_2 monster spawns with a different
  parameter while `eventWork[28] == 20`. It is reset only on world-map entry,
  and only if a party member holds item 364 **and** has caravan flag 60
  (world `mainBasha` lines 344-351). Flag 60 is set only on the character who
  started the quest (magic_0 line 3204). If someone else carries the reward, or
  the starter isn't in the party, the special spawn keeps coming back. What the
  different parameter does wasn't traced.
- **port_1 tutorial choice has no guards.** The "go to the tutorial" answer
  (EventClient case 31, lines 353-368) loads `tutorial_0` after 50 frames
  without the usual checks (map change in progress, game over, a player
  shopping) that village_0's version has (line 1321). A partner's map exit in
  those 50 frames could race it.

## Minor (confirmed, no visible effect)

- **`setForgot`** clears `evtFlag[600..850]` but sets `evtFlag[600..851]`
  (world lines 412-419). Flag 851 is never cleared; no NPC uses it.
- **World-map arrow:** `mainArrow` has two `case 26:` labels (lines 5748-5774);
  arrow 4 never shows at that node.
- **Festival party fill** reads `wmBackupParams[4..7]` once all four slots are
  filled (festa_0 lines 2061-2071). Reads only; nothing changes.

## Checked and clean

The year change and festival, `incMana`, the diary indexing, the world-map
element shrines, Fum's cow race and its bets, ferry fares (checked for every
player before anyone pays), the Mog house stamps and race prize, village shop
and smith tiers, the hidden town moogles (flag set before the gift), the
farewell scenes, the tutorial entry and exit, and the reply effects of the Yuke
kid letters.
