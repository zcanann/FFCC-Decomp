// Function: __dt__9CRingMenuFv
// Entry: 800a5204
// Size: 216 bytes

void __dt__9CRingMenuFv(CRingMenu *ringMenu)

{
  float fVar1;
  
  (**(code **)((int)(ringMenu->menuBase).ref.vtable + 0x10))();
  Create__5CMenuFv(ringMenu);
  ringMenu->animDirection = 0;
  fVar1 = FLOAT_803309c0;
  ringMenu->displayCounter = 0;
  ringMenu->stateFlag = -1;
  ringMenu->transitionTimer = 0x10;
  *(undefined4 *)&ringMenu->field_0x10 = 1;
  ringMenu->battleButtons[0] = 0;
  ringMenu->battleButtons[2] = -1;
  ringMenu->battleButtons[3] = -1;
  ringMenu->buttonTimers[0] = 0;
  ringMenu->buttonTimers[1] = 0;
  ringMenu->buttonTimers[2] = 0;
  ringMenu->battleButtons[1] = 0;
  ringMenu->battleButtons[4] = -1;
  ringMenu->battleButtons[5] = -1;
  ringMenu->buttonTimers[3] = 0;
  ringMenu->buttonTimers[4] = 0;
  ringMenu->buttonTimers[5] = 0;
  ringMenu->battleButtons[2] = 0;
  ringMenu->battleButtons[6] = -1;
  ringMenu->battleButtons[7] = -1;
  ringMenu->buttonTimers[6] = 0;
  ringMenu->buttonTimers[7] = 0;
  ringMenu->_timerRelated = 0;
  ringMenu->ringRotation = -NAN;
  ringMenu->rotationPhase = -NAN;
  ringMenu->spinAccumulator = (int)fVar1;
  ringMenu->gbaConnectedFlag = 0;
  ringMenu->gbaAnimCounter = 0;
  ringMenu->commonFrameCounter = 0;
  ringMenu->timerA = 0;
  ringMenu->timerB = 0;
  ringMenu->currentCommandIndex = 0;
  ringMenu->commandScrollOffset = fVar1;
  return;
}

