// Function: SIGetType
// Entry: 80185440
// Size: 452 bytes

int SIGetType(uint param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined8 uVar7;
  
  uVar2 = OSDisableInterrupts();
  piVar5 = (int *)(&DAT_80217318 + param_1 * 4);
  iVar4 = *piVar5;
  uVar7 = __OSGetSystemTime();
  piVar6 = (int *)(&DAT_8030c870 + param_1 * 8);
  uVar3 = (uint)uVar7 - *(uint *)(&DAT_8030c874 + param_1 * 8);
  uVar1 = (int)((ulonglong)uVar7 >> 0x20) -
          ((uint)((uint)uVar7 < *(uint *)(&DAT_8030c874 + param_1 * 8)) + *piVar6);
  if ((DAT_80217308 & 0x80 >> (param_1 & 0x3f)) == 0) {
    if (((uint)((DAT_800000f8 / 4000) * 0x32 < uVar3) + (uVar1 ^ 0x80000000) < 0x80000001) &&
       (iVar4 != 8)) {
      OSRestoreInterrupts(uVar2);
      return iVar4;
    }
    if ((uint)((DAT_800000f8 / 4000) * 0x4b < uVar3) + (uVar1 ^ 0x80000000) < 0x80000001) {
      *piVar5 = 0x80;
    }
    else {
      *piVar5 = 0x80;
      iVar4 = 0x80;
    }
  }
  else {
    if (iVar4 != 8) {
      uVar7 = __OSGetSystemTime();
      *(undefined8 *)piVar6 = uVar7;
      OSRestoreInterrupts(uVar2);
      return iVar4;
    }
    *piVar5 = 0x80;
    iVar4 = 0x80;
  }
  uVar7 = __OSGetSystemTime();
  *(undefined8 *)piVar6 = uVar7;
  SITransfer(param_1,&DAT_8032f004,1,piVar5,3,GetTypeCallback,0,(DAT_800000f8 / 500000) * 0x41 >> 3)
  ;
  OSRestoreInterrupts(uVar2);
  return iVar4;
}

