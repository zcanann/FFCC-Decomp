// Function: onMapChanging__7CGbaPcsFii
// Entry: 8009782c
// Size: 92 bytes

void onMapChanging__7CGbaPcsFii(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  
  cVar1 = IsThreadRunning__6JoyBusFv(&Joybus);
  if (cVar1 != '\0') {
    SetStageNo__8GbaQueueFii(&GbaQue,param_2,param_3);
  }
  return;
}

