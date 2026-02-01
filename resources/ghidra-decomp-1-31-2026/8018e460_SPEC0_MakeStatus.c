// Function: SPEC0_MakeStatus
// Entry: 8018e460
// Size: 372 bytes

void SPEC0_MakeStatus(undefined4 param_1,ushort *param_2,uint *param_3)

{
  ushort uVar1;
  
  uVar1 = 0;
  *param_2 = 0;
  if ((*param_3 >> 0x10 & 8) != 0) {
    uVar1 = 0x100;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x20) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x200;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x100) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x400;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 1) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x800;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x10) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x1000;
  }
  *param_2 = *param_2 | uVar1;
  *(char *)(param_2 + 1) = (char)(param_3[1] >> 0x10);
  *(char *)((int)param_2 + 3) = (char)(param_3[1] >> 0x18);
  *(char *)(param_2 + 2) = (char)param_3[1];
  *(char *)((int)param_2 + 5) = (char)(param_3[1] >> 8);
  *(char *)(param_2 + 3) = (char)(*param_3 >> 8);
  *(char *)((int)param_2 + 7) = (char)*param_3;
  *(undefined *)(param_2 + 4) = 0;
  *(undefined *)((int)param_2 + 9) = 0;
  if (0xa9 < *(byte *)(param_2 + 3)) {
    *param_2 = *param_2 | 0x40;
  }
  if (0xa9 < *(byte *)((int)param_2 + 7)) {
    *param_2 = *param_2 | 0x20;
  }
  *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + -0x80;
  *(char *)((int)param_2 + 3) = *(char *)((int)param_2 + 3) + -0x80;
  *(char *)(param_2 + 2) = *(char *)(param_2 + 2) + -0x80;
  *(char *)((int)param_2 + 5) = *(char *)((int)param_2 + 5) + -0x80;
  return;
}

