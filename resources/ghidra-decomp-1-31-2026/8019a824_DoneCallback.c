// Function: DoneCallback
// Entry: 8019a824
// Size: 804 bytes

void DoneCallback(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined4 chan;
  byte local_58 [4];
  undefined auStack_54 [68];
  
  chan = 0;
  puVar8 = &DAT_80327540;
  if (param_1 != -0x7fcd8a90) {
    chan = 1;
    puVar8 = &DAT_80327650;
    if (param_1 != -0x7fcd8980) {
      chan = 2;
      puVar8 = &DAT_80327650;
    }
  }
  uVar9 = *(uint *)((puVar8[0x20] + 0x2f & 0xffffffe0) + 0x20);
  iVar2 = DummyLen();
  iVar3 = ReadArrayUnlock(chan,(uVar9 ^ puVar8[0xb]) & 0xffff0000,auStack_54,iVar2,1);
  if (iVar3 < 0) {
    EXIUnlock(chan);
    __CARDMountCallback(chan,0xfffffffd);
  }
  else {
    uVar4 = 0;
    uVar1 = puVar8[0xb];
    uVar6 = iVar2 + puVar8[5] + 4;
    iVar2 = uVar6 * 8;
    uVar7 = iVar2 + 1;
    if (uVar7 != 0) {
      if ((8 < uVar7) && (uVar6 = uVar6 & 0x1fffffff, iVar2 != 7)) {
        do {
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar4 = uVar4 + 8;
          uVar6 = uVar6 - 1;
        } while (uVar6 != 0);
      }
      iVar2 = uVar7 - uVar4;
      if (uVar4 < uVar7) {
        do {
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
    }
    puVar8[0xb] = uVar1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1f;
    uVar5 = DummyLen();
    iVar2 = ReadArrayUnlock(chan,(uVar9 << 0x10 ^ puVar8[0xb]) & 0xffff0000,auStack_54,uVar5,1);
    if (iVar2 < 0) {
      EXIUnlock(chan);
      __CARDMountCallback(chan,0xfffffffd);
    }
    else {
      iVar2 = __CARDReadStatus(chan,(char *)local_58);
      iVar3 = EXIProbe(chan);
      if (iVar3 == 0) {
        EXIUnlock(chan);
        __CARDMountCallback(chan,0xfffffffd);
      }
      else {
        if ((iVar2 == 0) && ((local_58[0] & 0x40) == 0)) {
          EXIUnlock(chan);
          iVar2 = -5;
        }
        __CARDMountCallback(chan,iVar2);
      }
    }
  }
  return;
}

