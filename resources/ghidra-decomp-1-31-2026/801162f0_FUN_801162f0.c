// Function: FUN_801162f0
// Entry: 801162f0
// Size: 868 bytes

/* WARNING: Removing unreachable block (ram,0x80116638) */
/* WARNING: Removing unreachable block (ram,0x80116630) */
/* WARNING: Removing unreachable block (ram,0x80116308) */
/* WARNING: Removing unreachable block (ram,0x80116300) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FUN_801162f0(int param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  undefined auStack_38 [4];
  int local_34 [4];
  
  local_34[1] = 0x43300000;
  local_34[2] = (int)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xcc);
  dVar3 = (double)(float)((double)CONCAT44(0x43300000,local_34[2]) - DOUBLE_803319e0);
  dVar2 = (double)PSVECDistance((Vec *)(param_1 + 0x6f8),(Vec *)(param_1 + 0x15c));
  if (*(short *)(param_1 + 0x6e4) == 0) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
  }
  else {
    iVar1 = Game.game.unkCFlatData0[1] +
            ((int)*(short *)(param_1 + 0x6e4) +
            (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) * 0x1d0 + 0x10;
  }
  if ((-1 < *(int *)(param_1 + 0x6c4)) && ((*(ushort *)(iVar1 + 0x102) & 0x20) != 0)) {
    SoundBuffer._1252_4_ = 0;
    memset(param_1 + 0x70c,0,0x34);
    *(undefined4 *)(param_1 + 0x6d8) = 2;
    *(undefined4 *)(param_1 + 0x6dc) = 0;
    *(undefined *)(param_1 + 0x6bb) = 1;
    return;
  }
  if (((*(ushort *)(iVar1 + 0x102) & 0x20) != 0) ||
     (iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x24), (*(ushort *)(iVar1 + 0xfe) & 8) != 0)) {
    SoundBuffer._1252_4_ = 0;
    memset(param_1 + 0x70c,0,0x34);
    *(undefined4 *)(param_1 + 0x6d8) = 0;
    *(undefined4 *)(param_1 + 0x6dc) = 0;
    *(undefined *)(param_1 + 0x6bb) = 1;
    return;
  }
  if (*(short *)(iVar1 + 0x10c) == 1) {
    SoundBuffer._1252_4_ = 0x21;
    if (*(int *)(param_1 + 0x734) != 3) {
      memset(param_1 + 0x70c,0,0x34);
      *(undefined4 *)(param_1 + 0x70c) = 0x806;
      *(undefined4 *)(param_1 + 0x734) = 3;
    }
    *(undefined4 *)(param_1 + 0x718) = *(undefined4 *)(param_1 + 0x6f8);
    *(undefined4 *)(param_1 + 0x71c) = *(undefined4 *)(param_1 + 0x6fc);
    *(undefined4 *)(param_1 + 0x720) = *(undefined4 *)(param_1 + 0x700);
  }
  iVar1 = *(int *)(param_1 + 0x58);
  if (((*(short *)(*(int *)(iVar1 + 0x24) + 0x10c) != 1) || (*(int *)(param_1 + 0x730) < 0x19)) &&
     ((*(short *)(*(int *)(iVar1 + 0x24) + 0x10c) == 1 ||
      ((double)(float)((double)FLOAT_80331a34 * dVar3) <= dVar2)))) goto LAB_801165a0;
  dVar3 = DOUBLE_80331a18;
  if (Game.game.m_gameWork.m_soundOptionFlag != '\0') {
    dVar3 = DOUBLE_80331a10;
  }
  if (dVar3 <= (double)*(float *)(param_1 + 0x5bc)) {
LAB_80116548:
    local_34[0] = -1;
  }
  else {
    local_34[1] = 0x43300000;
    local_34[2] = (int)*(ushort *)(*(int *)(iVar1 + 0x24) + 200);
    FUN_80116870((double)*(float *)(param_1 + 0x1a8),
                 (double)(float)((double)CONCAT44(0x43300000,local_34[2]) - DOUBLE_803319e0),param_1
                 ,6,auStack_38,local_34);
    if (local_34[0] < 0) goto LAB_80116548;
  }
  if (-1 < local_34[0]) {
    *(int *)(param_1 + 0x6c4) = local_34[0];
    if (*(short *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x10c) == 1) {
      *(undefined4 *)(param_1 + 0x6d8) = 2;
      *(undefined4 *)(param_1 + 0x6dc) = 0;
      *(undefined *)(param_1 + 0x6bb) = 1;
      return;
    }
    *(undefined4 *)(param_1 + 0x6d8) = 1;
    *(undefined4 *)(param_1 + 0x6dc) = 0;
    *(undefined *)(param_1 + 0x6bb) = 1;
    return;
  }
LAB_801165a0:
  if ((dVar2 < (double)FLOAT_803319f8) ||
     (iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x24),
     *(uint *)(param_1 + 0x6dc) == (uint)*(ushort *)(iVar1 + 0x1b8))) {
    *(undefined4 *)(param_1 + 0x6f8) = *(undefined4 *)(param_1 + 0x15c);
    *(undefined4 *)(param_1 + 0x6fc) = *(undefined4 *)(param_1 + 0x160);
    *(undefined4 *)(param_1 + 0x700) = *(undefined4 *)(param_1 + 0x164);
    SoundBuffer._1252_4_ = 0;
    memset(param_1 + 0x70c,0,0x34);
    *(undefined4 *)(param_1 + 0x6d8) = 0;
    *(undefined4 *)(param_1 + 0x6dc) = 0;
    *(undefined *)(param_1 + 0x6bb) = 1;
  }
  else if (*(short *)(iVar1 + 0x10c) != 1) {
    SoundBuffer._1252_4_ = 0x1c;
  }
  return;
}

