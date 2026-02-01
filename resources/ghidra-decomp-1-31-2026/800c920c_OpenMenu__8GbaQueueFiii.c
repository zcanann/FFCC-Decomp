// Function: OpenMenu__8GbaQueueFiii
// Entry: 800c920c
// Size: 476 bytes

void OpenMenu__8GbaQueueFiii(OSSemaphore *param_1,int param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  OSSemaphore *pOVar3;
  int iVar4;
  int iVar5;
  
  if (param_3 == 999) {
    iVar4 = 0;
    pOVar3 = param_1;
    do {
      OSWaitSemaphore(pOVar3);
      iVar4 = iVar4 + 1;
      pOVar3 = pOVar3 + 1;
    } while (iVar4 < 4);
    *(undefined *)((int)&param_1[0x3c7].count + 3) = 1;
    iVar4 = 0;
    do {
      OSSignalSemaphore(param_1);
      iVar4 = iVar4 + 1;
      param_1 = param_1 + 1;
    } while (iVar4 < 4);
    iVar4 = 0;
    do {
      iVar5 = 0;
      do {
        iVar2 = SetMType__6JoyBusFii(&Joybus,iVar4,4);
        if (iVar2 == 0) break;
        iVar5 = iVar5 + 1;
      } while (iVar5 < 10);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
  }
  else {
    iVar4 = 0;
    do {
      iVar5 = SetOpenMenu__6JoyBusFic(&Joybus,param_2,(char)param_3);
      if (iVar5 == 0) break;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 10);
    pOVar3 = GbaQue.accessSemaphores + param_2;
    OSWaitSemaphore(pOVar3);
    uVar1 = countLeadingZeros(1 - (char)GbaQue._11606_1_);
    OSSignalSemaphore(pOVar3);
    if ((uVar1 >> 5 & 0xff) == 0) {
      iVar4 = 0;
      do {
        iVar5 = SetCtrlMode__6JoyBusFii(&Joybus,param_2,param_4);
        if (iVar5 == 0) {
          return;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 10);
    }
    else {
      OSWaitSemaphore(pOVar3);
      uVar1 = countLeadingZeros(1 - (char)GbaQue._11606_1_);
      OSSignalSemaphore(pOVar3);
      if ((((uVar1 >> 5 & 0xff) == 0) && (param_2 == 1)) && (param_3 == 0)) {
        iVar4 = 0;
        do {
          iVar5 = SetCtrlMode__6JoyBusFii(&Joybus,1,0);
          if (iVar5 == 0) {
            return;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < 10);
      }
    }
  }
  return;
}

