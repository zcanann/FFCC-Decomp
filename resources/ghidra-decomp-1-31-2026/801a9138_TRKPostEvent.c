// Function: TRKPostEvent
// Entry: 801a9138
// Size: 224 bytes

undefined4 TRKPostEvent(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  TRKAcquireMutex(&DAT_80328720);
  if (DAT_80328724 == 2) {
    uVar2 = 0x100;
  }
  else {
    iVar1 = DAT_80328728 + DAT_80328724 >> 0x1f;
    iVar1 = ((DAT_80328728 + DAT_80328724 & 1U ^ -iVar1) + iVar1) * 0xc;
    TRK_memcpy(iVar1 + -0x7fcd78d4,param_1,0xc);
    *(uint *)(&DAT_80328730 + iVar1) = DAT_80328744;
    DAT_80328744 = DAT_80328744 + 1;
    if (DAT_80328744 < 0x100) {
      DAT_80328744 = 0x100;
    }
    DAT_80328724 = DAT_80328724 + 1;
  }
  TRKReleaseMutex(&DAT_80328720);
  return uVar2;
}

