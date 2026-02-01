// Function: DestroyCache__13CAmemCacheSetFi
// Entry: 8001d468
// Size: 576 bytes

void DestroyCache__13CAmemCacheSetFi(CAmemCacheSet *amemCacheSet,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)(*(int *)&amemCacheSet->field_0x58 + param_2 * 0x1c);
  if (*(char *)((int)piVar3 + 0x1a) == '\0') {
    iVar2 = piVar3[1];
    if (iVar2 == 0) goto LAB_8001d680;
    if (iVar2 != 0) {
      if (*(short *)(iVar2 + -0x40) == 0x4b41) {
        if (*(short *)(iVar2 + -2) != 0x4d49) goto LAB_8001d5c0;
      }
      else {
LAB_8001d5c0:
        Printf__7CSystemFPce
                  (&System,&DAT_801d6648,iVar2,iVar2 + -0x26,*(undefined2 *)(iVar2 + -0x28));
      }
      *(byte *)(iVar2 + -0x3e) = *(byte *)(iVar2 + -0x3e) & 0xfb;
      if ((*(byte *)(*(int *)(iVar2 + -0x38) + 2) & 4) == 0) {
        *(int *)(iVar2 + -0x30) =
             *(int *)(*(int *)(iVar2 + -0x38) + 0x10) + *(int *)(iVar2 + -0x30) + 0x40;
        *(int *)(*(int *)(*(int *)(iVar2 + -0x38) + 8) + 4) = iVar2 + -0x40;
        *(undefined4 *)(iVar2 + -0x38) = *(undefined4 *)(*(int *)(iVar2 + -0x38) + 8);
      }
      iVar1 = *(int *)(iVar2 + -0x3c);
      if ((*(byte *)(iVar1 + 2) & 4) == 0) {
        *(int *)(iVar1 + 0x10) = *(int *)(iVar2 + -0x30) + *(int *)(iVar1 + 0x10) + 0x40;
        *(undefined4 *)(*(int *)(iVar2 + -0x3c) + 8) = *(undefined4 *)(iVar2 + -0x38);
        *(undefined4 *)(*(int *)(iVar2 + -0x38) + 4) = *(undefined4 *)(iVar2 + -0x3c);
      }
      *(int *)(*(int *)(iVar2 + -0x34) + 0x124) = *(int *)(*(int *)(iVar2 + -0x34) + 0x124) + -1;
    }
    *piVar3 = 0;
    piVar3[1] = 0;
    goto LAB_8001d680;
  }
  iVar2 = *piVar3;
  if (iVar2 != 0) {
    if (iVar2 != 0) {
      if (*(short *)(iVar2 + -0x40) == 0x4b41) {
        if (*(short *)(iVar2 + -2) != 0x4d49) goto LAB_8001d4c0;
      }
      else {
LAB_8001d4c0:
        Printf__7CSystemFPce
                  (&System,&DAT_801d6648,iVar2,iVar2 + -0x26,*(undefined2 *)(iVar2 + -0x28));
      }
      *(byte *)(iVar2 + -0x3e) = *(byte *)(iVar2 + -0x3e) & 0xfb;
      if ((*(byte *)(*(int *)(iVar2 + -0x38) + 2) & 4) == 0) {
        *(int *)(iVar2 + -0x30) =
             *(int *)(*(int *)(iVar2 + -0x38) + 0x10) + *(int *)(iVar2 + -0x30) + 0x40;
        *(int *)(*(int *)(*(int *)(iVar2 + -0x38) + 8) + 4) = iVar2 + -0x40;
        *(undefined4 *)(iVar2 + -0x38) = *(undefined4 *)(*(int *)(iVar2 + -0x38) + 8);
      }
      iVar1 = *(int *)(iVar2 + -0x3c);
      if ((*(byte *)(iVar1 + 2) & 4) == 0) {
        *(int *)(iVar1 + 0x10) = *(int *)(iVar2 + -0x30) + *(int *)(iVar1 + 0x10) + 0x40;
        *(undefined4 *)(*(int *)(iVar2 + -0x3c) + 8) = *(undefined4 *)(iVar2 + -0x38);
        *(undefined4 *)(*(int *)(iVar2 + -0x38) + 4) = *(undefined4 *)(iVar2 + -0x3c);
      }
      *(int *)(*(int *)(iVar2 + -0x34) + 0x124) = *(int *)(*(int *)(iVar2 + -0x34) + 0x124) + -1;
    }
    *piVar3 = 0;
  }
  if (piVar3[1] != 0) {
    piVar3[1] = 0;
  }
LAB_8001d680:
  *(undefined2 *)(piVar3 + 6) = 0;
  *(undefined2 *)(piVar3 + 3) = 0;
  *(undefined *)((int)piVar3 + 0xe) = 0;
  return;
}

