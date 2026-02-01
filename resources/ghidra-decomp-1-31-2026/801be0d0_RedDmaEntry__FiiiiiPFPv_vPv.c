// Function: RedDmaEntry__FiiiiiPFPv_vPv
// Entry: 801be0d0
// Size: 356 bytes

undefined4
RedDmaEntry__FiiiiiPFPv_vPv
          (uint param_1,int param_2,int param_3,int param_4,int param_5,void *param_6,void *param_7)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  uVar1 = OSDisableInterrupts();
  if ((param_1 & 0xffff7fff) == 0) {
    puVar4 = (undefined4 *)&DAT_8032c660;
    puVar5 = (undefined4 *)0x8032f3e4;
  }
  else {
    puVar5 = &DAT_8032f3e0;
    puVar4 = &DAT_8032b860;
  }
  puVar7 = (undefined4 *)*puVar5;
  uVar2 = GetMyEntryID__Fv();
  uVar6 = param_5 + 0x1fU & 0xffffffe0;
  if ((DAT_8032f43c == 0) && ((param_1 & 0x8000) == 0)) {
    *puVar7 = uVar2;
    puVar7[1] = param_2;
    puVar7[2] = param_3;
    puVar7[3] = param_4;
    puVar7[4] = uVar6;
    puVar7[5] = param_6;
    puVar7[6] = param_7;
    puVar8 = puVar7 + 7;
    if (puVar4 + 0x380 <= puVar7 + 7) {
      puVar8 = puVar4;
    }
    *puVar5 = puVar8;
  }
  else {
    do {
      uVar3 = uVar6;
      if (0x40000 < (int)uVar6) {
        uVar3 = 0x40000;
      }
      *puVar7 = uVar2;
      uVar6 = uVar6 - uVar3;
      puVar7[1] = param_2;
      puVar7[2] = param_3;
      param_3 = param_3 + uVar3;
      puVar7[3] = param_4;
      param_4 = param_4 + uVar3;
      puVar7[4] = uVar3;
      puVar7[6] = param_7;
      if ((int)uVar6 < 1) {
        puVar7[5] = param_6;
      }
      else {
        puVar7[5] = 0;
      }
      puVar7 = puVar7 + 7;
      if (puVar4 + 0x380 <= puVar7) {
        puVar7 = puVar4;
      }
    } while (0 < (int)uVar6);
    *puVar5 = puVar7;
  }
  OSSignalSemaphore((OSSemaphore *)&DAT_8032ddd8);
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

