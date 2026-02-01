// Function: __EXIProbe
// Entry: 8018289c
// Size: 372 bytes

undefined4 __EXIProbe(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint *puVar3;
  int *piVar4;
  int extraout_r4;
  uint uVar5;
  undefined8 uVar6;
  
  if (param_1 == 2) {
    uVar1 = 1;
  }
  else {
    uVar1 = 1;
    uVar2 = OSDisableInterrupts();
    puVar3 = &DAT_cc006800 + param_1 * 5;
    uVar5 = *puVar3;
    if ((FatalContext[param_1 * 0x10 + 0x29a] & 8) == 0) {
      if ((uVar5 & 0x800) != 0) {
        *puVar3 = *puVar3 & 0x7f5 | 0x800;
        FatalContext[param_1 * 0x10 + 0x29f] = 0;
        (&DAT_800030c0)[param_1] = 0;
      }
      if ((uVar5 & 0x1000) == 0) {
        FatalContext[param_1 * 0x10 + 0x29f] = 0;
        (&DAT_800030c0)[param_1] = 0;
        uVar1 = 0;
      }
      else {
        uVar5 = DAT_800000f8 / 4000;
        uVar6 = OSGetTime();
        uVar6 = __div2i((int)((ulonglong)uVar6 >> 0x20),(int)uVar6,0,uVar5);
        __div2i((int)((ulonglong)uVar6 >> 0x20),(int)uVar6,0,100);
        piVar4 = &DAT_800030c0 + param_1;
        if (*piVar4 == 0) {
          *piVar4 = extraout_r4 + 1;
        }
        if ((extraout_r4 + 1) - *piVar4 < 3) {
          uVar1 = 0;
        }
      }
    }
    else if (((uVar5 & 0x1000) == 0) || ((uVar5 & 0x800) != 0)) {
      FatalContext[param_1 * 0x10 + 0x29f] = 0;
      (&DAT_800030c0)[param_1] = 0;
      uVar1 = 0;
    }
    OSRestoreInterrupts(uVar2);
  }
  return uVar1;
}

