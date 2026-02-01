// Function: SetBattleCommand__9CRingMenuFiii
// Entry: 800a3340
// Size: 156 bytes

void SetBattleCommand__9CRingMenuFiii
               (CRingMenu *ringMenu,int buttonGroupIndex,int newCommandId,float newRotation)

{
  int iVar1;
  
  if (newCommandId == 0) {
    newCommandId = -1;
  }
  iVar1 = ringMenu->battleButtons[buttonGroupIndex * 2 + 2];
  if (iVar1 == newCommandId) {
    return;
  }
  if (((-1 < iVar1) && (newCommandId < 0)) || ((iVar1 < 0 && (-1 < newCommandId)))) {
    ringMenu->buttonTimers[buttonGroupIndex * 3 + 2] =
         8 - ringMenu->buttonTimers[buttonGroupIndex * 3 + 2];
  }
  ringMenu->battleButtons[buttonGroupIndex * 2 + 3] =
       ringMenu->battleButtons[buttonGroupIndex * 2 + 2];
  ringMenu->battleButtons[buttonGroupIndex * 2 + 2] = newCommandId;
  ringMenu->buttonTimers[buttonGroupIndex * 3 + 1] =
       8 - ringMenu->buttonTimers[buttonGroupIndex * 3];
  ringMenu->buttonTimers[buttonGroupIndex * 3] = 8 - ringMenu->buttonTimers[buttonGroupIndex * 3];
  if (buttonGroupIndex != 2) {
    return;
  }
  ringMenu->rotationPhase = ringMenu->ringRotation;
  ringMenu->ringRotation = newRotation;
  return;
}

