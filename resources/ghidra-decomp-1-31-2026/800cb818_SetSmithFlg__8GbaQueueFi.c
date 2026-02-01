// Function: SetSmithFlg__8GbaQueueFi
// Entry: 800cb818
// Size: 168 bytes

void SetSmithFlg__8GbaQueueFi(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  OSSemaphore *osSemaphore;
  
  osSemaphore = (OSSemaphore *)(param_1 + param_2 * 0xc);
  OSWaitSemaphore(osSemaphore);
  bVar1 = (byte)(0x10 << param_2);
  *(byte *)(param_1 + 0x2d38) = *(byte *)(param_1 + 0x2d38) | bVar1;
  OSSignalSemaphore(osSemaphore);
  iVar2 = SetMType__6JoyBusFii(&Joybus,param_2,3);
  if (iVar2 == 0) {
    *(byte *)(param_1 + 0x2d39) = *(byte *)(param_1 + 0x2d39) & ~bVar1;
  }
  else {
    *(byte *)(param_1 + 0x2d39) = *(byte *)(param_1 + 0x2d39) | bVar1;
  }
  return;
}

