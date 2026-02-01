// Function: calc__7CGbaPcsFv
// Entry: 8009788c
// Size: 72 bytes

void calc__7CGbaPcsFv(void)

{
  char cVar1;
  
  cVar1 = IsThreadRunning__6JoyBusFv(&Joybus);
  if (cVar1 != '\0') {
    ExecutQueue__8GbaQueueFv(&GbaQue);
    LoadAll__8GbaQueueFv(&GbaQue);
  }
  return;
}

