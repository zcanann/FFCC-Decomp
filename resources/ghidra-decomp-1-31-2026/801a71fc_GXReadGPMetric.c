// Function: GXReadGPMetric
// Entry: 801a71fc
// Size: 424 bytes

void GXReadGPMetric(uint *param_1,int *param_2)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  short sVar6;
  uint uVar5;
  int iVar7;
  int iVar8;
  
  sVar6 = *(short *)(DAT_8032f2ec + 0x42);
  do {
    sVar2 = *(short *)(DAT_8032f2ec + 0x42);
    bVar1 = sVar2 != sVar6;
    sVar6 = sVar2;
  } while (bVar1);
  uVar5 = CONCAT22(sVar2,*(undefined2 *)(DAT_8032f2ec + 0x40));
  sVar6 = *(short *)(DAT_8032f2ec + 0x46);
  do {
    sVar2 = *(short *)(DAT_8032f2ec + 0x46);
    bVar1 = sVar2 != sVar6;
    sVar6 = sVar2;
  } while (bVar1);
  sVar6 = *(short *)(DAT_8032f2ec + 0x4a);
  do {
    sVar3 = *(short *)(DAT_8032f2ec + 0x4a);
    bVar1 = sVar3 != sVar6;
    sVar6 = sVar3;
  } while (bVar1);
  iVar7 = CONCAT22(sVar3,*(undefined2 *)(DAT_8032f2ec + 0x48));
  sVar6 = *(short *)(DAT_8032f2ec + 0x4e);
  do {
    sVar3 = *(short *)(DAT_8032f2ec + 0x4e);
    bVar1 = sVar3 != sVar6;
    sVar6 = sVar3;
  } while (bVar1);
  iVar8 = CONCAT22(sVar3,*(undefined2 *)(DAT_8032f2ec + 0x4c));
  iVar4 = *(int *)(DAT_80333828 + 0x4e4);
  if (iVar4 == 10) {
    *param_1 = (uint)(CONCAT22(sVar2,*(undefined2 *)(DAT_8032f2ec + 0x44)) * 1000) / uVar5;
    goto LAB_801a72fc;
  }
  if (iVar4 < 10) {
    if (-1 < iVar4) {
LAB_801a72e0:
      *param_1 = uVar5;
      goto LAB_801a72fc;
    }
  }
  else {
    if (iVar4 == 0x23) {
      *param_1 = 0;
      goto LAB_801a72fc;
    }
    if (iVar4 < 0x23) goto LAB_801a72e0;
  }
  *param_1 = 0;
LAB_801a72fc:
  switch(*(undefined4 *)(DAT_80333828 + 0x4e8)) {
  case 0:
    *param_2 = iVar8 << 2;
    return;
  case 1:
  case 2:
  case 3:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x15:
    *param_2 = iVar8;
    return;
  case 4:
    *param_2 = iVar7 + iVar8 * 2;
    return;
  case 5:
    *param_2 = iVar7 * 3 + iVar8 * 4;
    return;
  case 6:
    *param_2 = iVar7 * 5 + iVar8 * 6;
    return;
  case 7:
    *param_2 = iVar7 * 7 + iVar8 * 8;
    return;
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
    *param_2 = iVar7;
    return;
  case 0x16:
    *param_2 = 0;
    return;
  default:
    *param_2 = 0;
    return;
  }
}

