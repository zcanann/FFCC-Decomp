// Function: GBAGetProcessStatus
// Entry: 801a76fc
// Size: 372 bytes

undefined4 GBAGetProcessStatus(int param_1,undefined *param_2)

{
  undefined4 uVar1;
  uint extraout_r4;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  
  param_1 = param_1 * 0x100;
  uVar1 = OSDisableInterrupts();
  if (*(int *)(&DAT_80328374 + param_1) == 0) {
    if (*(int *)(&DAT_8032833c + param_1) == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 2;
    }
  }
  else {
    uVar5 = 2;
    uVar4 = (*(int *)(&DAT_80328394 + param_1) * 100) / *(int *)(&DAT_803283c4 + param_1) & 0xff;
    if (*(int *)(&DAT_8032838c + param_1) != 0 || *(int *)(&DAT_80328388 + param_1) != 0) {
      uVar6 = OSGetTime();
      uVar2 = (uint)uVar6 - *(uint *)(&DAT_8032838c + param_1);
      iVar3 = (int)((ulonglong)uVar6 >> 0x20) -
              ((uint)((uint)uVar6 < *(uint *)(&DAT_8032838c + param_1)) +
              *(int *)(&DAT_80328388 + param_1));
      uVar6 = __div2i(iVar3,uVar2,0,DAT_800000f8 / 4000);
      if (((uint)((ulonglong)uVar6 >> 0x20) ^ 0x80000000) < ((uint)uVar6 < 0x157c) + 0x80000000) {
        __div2i((int)((ulonglong)uVar4 * (ulonglong)uVar2 >> 0x20) + uVar4 * iVar3,uVar4 * uVar2,
                (int)((ulonglong)(DAT_800000f8 / 4000) * 0x157c >> 0x20),
                (DAT_800000f8 / 4000) * 0x157c);
        uVar4 = extraout_r4;
      }
      if (99 < (uVar4 & 0xff)) {
        uVar4 = 100;
      }
    }
    if (param_2 != (undefined *)0x0) {
      *param_2 = (char)uVar4;
    }
  }
  OSRestoreInterrupts(uVar1);
  return uVar5;
}

