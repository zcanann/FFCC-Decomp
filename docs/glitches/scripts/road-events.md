# Road Events (kai_*)

## In short

When your caravan stops on certain world-map roads, a short scene can play
where you meet another caravan: the Alfitaria caravan, Gurdy, the Striped
Brigands, the Black Knight and so on. Each scene is its own script,
`kai_<family>_<n>.cft` ("kai" is short for 街道 *kaidō*, "highway"). The world
script picks which one plays.

The road events are carefully guarded: rewards check for full inventories,
payments check your gil, and pickers can't overdraw. The findings are small:

1. **Amidatty's "you ate it twice" line can never play (confirmed).**
2. **The Leuda caravan's song can only be closed from controller port 1
   (confirmed; the softlock case is a hypothesis).**
3. **Sol's baby gift starts at 1000 gil even if you have less, and confirming
   it empties your purse (confirmed).**
4. **Fum merchants let you raise a rejected offer step by step against the same
   secret price (confirmed).**
5. **Some Fum and Leuda sales only appear to caravans carrying 7,500+ gil,
   because the world script's reference price is 5× the real one (confirmed).**

## How road events trigger

`world` `WM_MoveEnd` calls `encountKaido()` (world source line 1342) whenever a
move ends on a road node (`G61` = 1, 3, 4, 11, 14, 21, 24, 31, 41, 44, 51, 53,
80, 81). `encountKaido` (source lines 145-1017) works in three steps:

1. **Year-locked story steps.** `sysVal0` is the year and `eventWork[9]` the
   total myrrh collected. Each year 1-6 runs one Black Knight step
   (`eventWork[20]`); otherwise one Gurdy step (`eventWork[22]`), the Alfitaria
   intro (cas_7, year 1) or the Brigands' introduction (sma_1, year 2). Gurdy's
   last scene (xxx_4) runs in year 7 or later.
2. **Random encounters,** if no story step fired and the saved budget
   `G358 < (myrrh + 1) × 3` allows. The game rolls 20% (`rand(100) > 80`), picks
   a family with `rand(6)`, and each family has its own chain
   (`eventWork[23..27]`, `[80..82]`) and a 50/50 split between chain steps and
   repeatable events.
3. **Gating before loading.** Merchant and gift events are cancelled if any
   player has a full inventory (64), if a player lacks the gil, or if nobody
   owns the item involved. For these events the world script also picks the
   item (`G357`), a reference price (`G2023`) and the eligible players (`G356`).

| Family | Who | Event IDs (`G2007`) |
|---|---|---|
| cas | Alfitaria caravan (Sol, Lilties) | cas_0-7 = 1-8 |
| wep | Marr's Pass caravan (Lilty smiths) | wep_0-4 = 9-13 |
| fam | Fields of Fum caravan (Clavat farmers) | fam_0-3 = 14-17 |
| mag | Shella caravan (Yukes, Amidatty) | mag_0-4 = 18-22 |
| thi | Leuda caravan (Selkie couple) | thi_0-3 = 23-26 |
| sma | Striped Brigands (*shima*, "stripe") | sma_0-4 = 27-31 |
| bla | Black Knight storyline | bla_0-5 = 32-37 |
| xxx | Gurdy | xxx_0-4 = 38-42 |

Every kai script ends with the same "road event end" macro (source lines
213-325, byte-identical in all 69 copies). It applies one of 14 reward types,
then returns to the world map:

| Type | Effect | Used by |
|---|---|---|
| 1 | chosen player pays `G2007` gil; if short, gil := 0 | mag_1, xxx_1, xxx_4, cas_6 |
| 2 | every player gets `G2007` gil | mag_1 (refusal) |
| 3 | delete item `G357` from the chosen player | xxx_4 |
| 4 | give `G357` to every player with < 64 items | cas_1, cas_2, fam_1, mag_2 |
| 5 | random material to every player | wep_2 |
| 6 | trade `G357` for `G2016` | mag_0 |
| 7/8 | buy `G357` for `G2007` (8 = two copies) | fam_3, thi_2 |
| 9 | sell `G357` for `G2007` | wep_4 |
| 10 | Brigands steal a random food or material from everyone | sma_0 |
| 11 | everyone loses gil / 10 × 8 | sma_2 |
| 12 | everyone pays 100 gil, no message | thi_3 |
| 13 | tribe-specific Marr weapon to everyone | wep_3 |
| 14 | everyone loses a Striped Apple (item 381) | sma_3 |

Gil is changed through the script helper `addGil` (source lines 63-82), which
returns 0 without paying when a payment exceeds the wallet. Items go through
`CCaravanWork::AddItem`, which silently fails at 64 items.

## 1. Amidatty's "you ate it twice" line never plays

**Status:** Confirmed (bytecode). **Applies to:** both.

In the Shella "world model" sub-story you can eat Amidatty's bannock in mag_2
and again in mag_3. mag_3 has an angry line for eating it a second time, but
the world script overwrites the flag before mag_3 loads.

```c
// kai_mag_2 mainEventDirector, "Eat the bread" ending
eventWork[25] = 2;                                                     // 864

// world encountKaido, lines 719-723
case 1: case 2:
    if (sysVal0 > 5 && eventWork[22] >= 3) { eventWork[25] = 3; G2007 = 21; }  // -> kai_mag_3

// kai_mag_3 state 210, lines 859-867
if (eventWork[25] == 2) dispCubeMes(..., 50);   // never true
else                    dispCubeMes(..., 51);
```

- Message 50: "Wh-What? How dare you! You swallow it not once, but twice? ...
  You are the most disturbing person I have ever met!"
- Message 51: "Why, you odious scoundrel! How dare you eat it! ..."

**Consequence:** message 50 is unreachable, and the choice in mag_2 has no
later effect.

## 2. The Leuda caravan's song only listens to port 1

**Status:** Code Confirmed. The softlock is a Hypothesis.
**Applies to:** multiplayer.

In thi_3 ("How about a song ... Just 100 gil will do"), choosing "Yes, please"
starts a dance that loops until someone presses A. The prompt ("Press the A
Button to leave") is shown to everyone, but only pad 0 is read:

```c
// kai_thi_3, each dance state (lines 687, 695, 703, 711, 742)
if (getPadDown(0) & 256) setPRG(212);
// other kai scripts, e.g. xxx_*, bla_5 lines 1299-1307:
// (G1512[0] | G1512[1] | G1512[2] | G1512[3]) & 256
```

**Consequence:** only the port-1 player can end the song. If a multiplayer
session can run with nobody in port 1, the event never ends. The scripts test
`G2[0]` (port 1 present) everywhere, which suggests that's possible, but it
wasn't confirmed. Separately, reward type 12 charges **every** player 100 gil
without a message, although only one player answered.

**Trigger:** year 4 or later, every player has at least 100 gil, and the
random roll picks thi_3.

## 3. Sol's baby gift can empty your purse

**Status:** Confirmed (bytecode). **Applies to:** both. In multiplayer the
chooser is random.

"Send a gift" in cas_6 opens an amount picker that starts at 1000 gil for anyone
with more than 100 gil. The Up button is capped at your gil; the starting value
isn't.

```c
// kai_cas_6 mainEventDirector
G2008 = 1000; G2011 = 100;                          // 510-511: start 1000, step 100
G2006 = getCaravanGil(...); G2007 = G2008;          // 512-513: your gil; amount = 1000
if (G452[G2004].gil > 100) { G2012 = 1; ... }       // 786-788: picker shown
if (G2007 + G2011 <= G2006) G2007 += G2011;         // 546/558: Up is capped, start isn't

// payment macro, type 1, lines 225-227
if (addGil(G2004, -G2007) == 0) G452[G2004].gil = 0;
```

**How to trigger:**

1. Year 8 or later, with the Alfitaria chain at `eventWork[23] == 4`. You get
   cas_6 ("Did you hear about Sol?").
2. Pick **Send a gift** with the chosen player holding 101-999 gil.
3. Press A without lowering the amount.

**Consequence:** `addGil` refuses the 1000 gil payment, and the macro sets your
gil to 0. The screen said 1000, you lose whatever you had, and Sol's caravan
says "I'll make sure he gets it." Gurdy's xxx_4 clamps its own starting value to
your wallet (line 1221), so the case was known elsewhere.

## 4. Fum merchants: raise your offer against a fixed price

**Status:** Confirmed. **Applies to:** both.

fam_3 rolls a secret price once: `G2008 = base ± up to 50%` (state 203, lines
497-501). Too low an offer gets "that's too little", and **Hold on!** returns
you to the picker with the same secret price and no penalty (state 205, lines
688-690). The accept check (state 204, lines 659-670):

- `price > offer` → rejected;
- `price × 2 > offer` → one item;
- otherwise → two items.

**How to use:** offer the minimum; when rejected, choose "Hold on!" and add one
step at a time. You pay the lowest accepted price, within one step (10% of
base). Overshooting 2× the secret price gives the bonus second copy.

## 5. Merchant price gate uses 5× the real price

**Status:** Confirmed. **Applies to:** both.

The world script decides whether a Fum or Leuda sale can happen from a
reference price. For items 308-318 it uses 5000 (world source lines 139-154);
the merchants themselves ask 1000 (fam_3 and thi_2, source lines 467-474). The
gate requires a player with more than 1.5 × 5000 = 7,500 gil. Other items use
the same price in both tables.

**Consequence:** Magma Rock, Chilly Gel, Thunderball, Holy Water, Heavenly
Dust, Blue Silk, Fiend's Claw and Faerie's Tear are offered far less often than
their price suggests, and never to poor caravans.

## Intended, but worth knowing

- **Shella fortune-teller (mag_1):** answering "No, thanks" to "Would you buy
  the wisdom of the Yukes for ten gil?" gives **every** player 10 gil and
  decrements the encounter counter (`eventWork[81]`, line 687), so it never
  runs out. Unlimited but tiny gil.
- **Leuda "Could you buy this?" (thi_2):** the offer can go down to one step
  (10% of base) and is always accepted (lines 791-799). Any item they sell can
  be bought for 10% of its base price; the diary text ("haggling their prices
  way down") shows this is intended.
- **Story chains are year-locked.** Each Black Knight and Gurdy step needs its
  predecessor and a myrrh count (world lines 154-225). A year that ends without
  that step firing on a road move leaves the chain stuck for good, and mag_2-4,
  xxx_4 and sma_4 depend on these chains. In normal play the step almost
  always fires.
- **Road event budget.** `G358` is saved and never reset. It caps random road
  events at 3 × (myrrh + 1) for the whole save.
- **Brigand theft (sma_0)** is the default case, so it can happen before their
  introduction and after Meh Gaj's death. The script hides the old man in the
  second case (line 243), so both look handled on purpose.

## Checked and clean

- Every item-giving event is cancelled on the world map if any player has 64
  items, and the chain flag is rolled back when it is.
- Ownership-gated events (mag_0, wep_4, xxx_4, sma_3) only pick players who own
  the item, and delete it before paying.
- Yes/No windows use a cancel entry of -1, so B can't produce an unhandled
  value ([mesmenu.cpp:1012](../../../src/mesmenu.cpp#L1012)).
- The same event can't fire twice in a row (`G361 != G2007`).
- In single player Mog can receive type 2/4/5/13 rewards; they go to a
  temporary caravan record, so nothing is gained or lost.

Unused text and the debug launcher for road events are listed in
[unused-content.md](unused-content.md#road-events).
