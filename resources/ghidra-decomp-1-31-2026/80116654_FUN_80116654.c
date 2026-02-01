// Function: FUN_80116654
// Entry: 80116654
// Size: 540 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FUN_80116654(int param_1)

{
  ushort uVar1;
  bool bVar2;
  int iVar3;
  double dVar4;
  undefined auStack_18 [4];
  int local_14 [3];
  
  if (*(char *)(param_1 + 0x6be) != '\0') {
    return;
  }
  bVar2 = false;
  if (*(char *)(param_1 + 0x6bd) == '\0') {
    dVar4 = DOUBLE_80331a18;
    if (Game.game.m_gameWork.m_soundOptionFlag != '\0') {
      dVar4 = DOUBLE_80331a10;
    }
    if ((double)*(float *)(param_1 + 0x5bc) < dVar4) {
      local_14[1] = 0x43300000;
      local_14[2] = (int)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 200);
      FUN_80116870((double)*(float *)(param_1 + 0x1a8),
                   (double)(float)((double)CONCAT44(0x43300000,local_14[2]) - DOUBLE_803319e0),
                   param_1,6,auStack_18,local_14);
      if (-1 < local_14[0]) goto LAB_8011670c;
    }
    local_14[0] = -1;
  }
  else {
    local_14[0] = *(int *)(param_1 + 0x6c4);
  }
LAB_8011670c:
  if (-1 < local_14[0]) {
    iVar3 = *(int *)(param_1 + 0x6d0);
    uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xfe);
    if ((iVar3 == 0) && ((uVar1 & 0x80) != 0)) {
      bVar2 = true;
      SoundBuffer._1252_4_ = 0x32;
    }
    else if ((iVar3 == 0) && ((uVar1 & 0x20) != 0)) {
      bVar2 = true;
      SoundBuffer._1252_4_ = 0x33;
    }
    else if ((iVar3 == 0) &&
            (((uVar1 & 0x40) != 0 || (*(int *)(*(int *)(param_1 + 0x58) + 0x10) == 0x39)))) {
      bVar2 = true;
      SoundBuffer._1252_4_ = 0x34;
    }
  }
  iVar3 = *(int *)(*(int *)(param_1 + 0x58) + 0x10);
  if (iVar3 != 0x70) {
    if (iVar3 < 0x70) {
      if (iVar3 == 0x6a) {
        bVar2 = true;
        SoundBuffer._1252_4_ = 0x35;
      }
      goto LAB_801167ec;
    }
    if (iVar3 != 0x7b) goto LAB_801167ec;
  }
  bVar2 = true;
LAB_801167ec:
  if (bVar2) {
    if (iVar3 == 0x7b) {
      *(undefined4 *)(param_1 + 0x6d8) = 0;
      *(undefined4 *)(param_1 + 0x6dc) = 0;
      *(undefined *)(param_1 + 0x6bb) = 1;
    }
    else if (*(char *)(param_1 + 0x6bd) == '\0') {
      *(undefined4 *)(param_1 + 0x6d8) = 2;
      *(undefined4 *)(param_1 + 0x6dc) = 0;
      *(undefined *)(param_1 + 0x6bb) = 1;
    }
    else {
      *(undefined4 *)(param_1 + 0x6d8) = 2;
      *(undefined4 *)(param_1 + 0x6dc) = 0;
      *(undefined *)(param_1 + 0x6bb) = 1;
    }
    *(int *)(param_1 + 0x6c4) = local_14[0];
  }
  return;
}

