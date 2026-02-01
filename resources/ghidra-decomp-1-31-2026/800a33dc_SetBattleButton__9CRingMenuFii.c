// Function: SetBattleButton__9CRingMenuFii
// Entry: 800a33dc
// Size: 28 bytes

void SetBattleButton__9CRingMenuFii(CRingMenu *ringMenu,int buttonIndex,int newValue)

{
  if (ringMenu->battleButtons[buttonIndex] == newValue) {
    return;
  }
  ringMenu->battleButtons[buttonIndex] = newValue;
  return;
}

