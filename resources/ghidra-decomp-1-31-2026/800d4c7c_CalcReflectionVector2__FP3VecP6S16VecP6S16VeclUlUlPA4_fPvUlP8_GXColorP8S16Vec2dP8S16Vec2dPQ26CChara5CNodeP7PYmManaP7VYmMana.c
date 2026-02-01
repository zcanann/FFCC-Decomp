// Function: CalcReflectionVector2__FP3VecP6S16VecP6S16VeclUlUlPA4_fPvUlP8_GXColorP8S16Vec2dP8S16Vec2dPQ26CChara5CNodeP7PYmManaP7VYmMana
// Entry: 800d4c7c
// Size: 1120 bytes

/* WARNING: Removing unreachable block (ram,0x800d50c0) */
/* WARNING: Removing unreachable block (ram,0x800d50b8) */
/* WARNING: Removing unreachable block (ram,0x800d50b0) */
/* WARNING: Removing unreachable block (ram,0x800d50a8) */
/* WARNING: Removing unreachable block (ram,0x800d50a0) */
/* WARNING: Removing unreachable block (ram,0x800d4cac) */
/* WARNING: Removing unreachable block (ram,0x800d4ca4) */
/* WARNING: Removing unreachable block (ram,0x800d4c9c) */
/* WARNING: Removing unreachable block (ram,0x800d4c94) */
/* WARNING: Removing unreachable block (ram,0x800d4c8c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcReflectionVector2__FP3VecP6S16VecP6S16VeclUlUlPA4_fPvUlP8_GXColorP8S16Vec2dP8S16Vec2dPQ26CChara5CNodeP7PYmManaP7VYmMana
               (int param_1,int param_2,int param_3,int param_4,undefined4 param_5,
               undefined4 param_6,Mtx *param_7,ushort *param_8,int param_9,int param_10,int param_11
               ,int param_12,int param_13)

{
  float fVar1;
  byte bVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  uint uVar9;
  Vec *source;
  ushort *puVar10;
  ushort *puVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  float local_238;
  float local_234;
  float local_230;
  float local_22c;
  S16Vec local_228;
  S16Vec local_220;
  float local_218;
  float local_214;
  Vec VStack_210;
  Vec VStack_204;
  Vec VStack_1f8;
  Vec local_1ec;
  Vec local_1e0;
  Vec local_1d4;
  Vec local_1c8;
  Mtx MStack_1bc;
  Mtx MStack_18c;
  Mtx MStack_15c;
  Mtx MStack_12c;
  Mtx MStack_fc;
  Mtx MStack_cc;
  
  local_1c8.x = (float)CameraPcs._224_4_;
  local_1c8.y = (float)CameraPcs._228_4_;
  local_1c8.z = (float)CameraPcs._232_4_;
  PSMTXCopy(param_7,&MStack_12c);
  PSMTXCopy((Mtx *)(param_13 + 0x14),&MStack_18c);
  PSMTXCopy((Mtx *)(param_13 + 0x6c),&MStack_1bc);
  local_1d4.x = MStack_1bc.value[0][3];
  local_1d4.y = MStack_1bc.value[1][3];
  local_1d4.z = MStack_1bc.value[2][3];
  local_1e0.x = MStack_12c.value[0][3];
  local_1e0.y = MStack_12c.value[1][3];
  local_1e0.z = MStack_12c.value[2][3];
  PSVECAdd(&local_1d4,&local_1e0,&local_1ec);
  PSMTXCopy(&MStack_1bc,&MStack_fc);
  PSMTXRotRad(FLOAT_80330e48,&MStack_15c,0x79);
  MStack_fc.value[0][3] = local_1ec.x;
  MStack_fc.value[1][3] = local_1ec.y;
  MStack_fc.value[2][3] = local_1ec.z;
  PSMTXCopy(&MStack_fc,&MStack_cc);
  dVar14 = (double)FLOAT_80330e4c;
  dVar15 = (double)FLOAT_80330e58;
  MStack_cc.value[0][3] = FLOAT_80330e4c;
  dVar16 = (double)FLOAT_80330e5c;
  MStack_cc.value[1][3] = FLOAT_80330e4c;
  dVar17 = (double)FLOAT_80330e60;
  MStack_cc.value[2][3] = FLOAT_80330e4c;
  puVar10 = (ushort *)((int)param_8 + param_9);
  dVar18 = (double)FLOAT_80330e64;
  while (param_8 < puVar10) {
    bVar2 = *(byte *)param_8;
    uVar3 = *(ushort *)((int)param_8 + 1);
    iVar5 = IsHasDrawFmtDL__5CUtilFUc((CUtil *)&DAT_8032ec70,(uint)bVar2);
    if (iVar5 == 0) break;
    param_8 = (ushort *)((int)param_8 + 3);
    for (iVar5 = 0; iVar5 < (int)(uint)uVar3; iVar5 = iVar5 + 1) {
      uVar9 = (uint)*param_8;
      uVar4 = param_8[1];
      puVar11 = param_8 + 4;
      if ((bVar2 & 7) == 2) {
        puVar11 = param_8 + 5;
      }
      puVar8 = (undefined4 *)(param_2 + uVar9 * 6);
      local_220._0_4_ = *puVar8;
      local_220.z = *(short *)(puVar8 + 1);
      ConvI2FVector__5CUtilFR3Vec6S16Vecl((CUtil *)&DAT_8032ec70,&VStack_204,&local_220,param_5);
      puVar8 = (undefined4 *)(param_3 + (uint)uVar4 * 6);
      local_228._0_4_ = *puVar8;
      local_228.z = *(short *)(puVar8 + 1);
      ConvI2FVector__5CUtilFR3Vec6S16Vecl((CUtil *)&DAT_8032ec70,&VStack_210,&local_228,param_6);
      PSMTXMultVec(&MStack_fc,&VStack_204,&VStack_204);
      PSMTXMultVec(&MStack_cc,&VStack_210,&VStack_210);
      PSVECSubtract(&VStack_204,&local_1c8,&VStack_1f8);
      source = (Vec *)(param_1 + uVar9 * 0xc);
      C_VECReflect(&VStack_1f8,&VStack_210,source);
      iVar6 = strcmp(&DAT_80330e50,0x8022b6b4);
      if (iVar6 == 0) {
        PSMTXMultVec(&MStack_15c,source,source);
      }
      if ((double)source->z < dVar14) {
        puVar7 = (undefined *)(param_10 + uVar9 * 4);
        *puVar7 = 0;
        puVar7[1] = 0;
        puVar7[2] = 0;
        puVar7[3] = 0;
      }
      else {
        puVar7 = (undefined *)(param_10 + uVar9 * 4);
        *puVar7 = 0xff;
        puVar7[1] = 0xff;
        puVar7[2] = 0xff;
        puVar7[3] = 0xff;
      }
      fVar1 = (float)(dVar15 + (double)source->z);
      dVar13 = (double)(float)((double)(float)((double)(-source->x / fVar1) * dVar16) + dVar16);
      dVar12 = (double)(float)((double)(float)((double)(-source->y / fVar1) * dVar16) + dVar16);
      local_230 = -(float)(dVar18 * (double)(float)(dVar17 * (double)(float)(dVar13 - dVar16)) -
                          dVar13);
      local_22c = -(float)(dVar18 * (double)(float)(dVar17 * (double)(float)(dVar12 - dVar16)) -
                          dVar12);
      local_218 = local_230;
      local_214 = local_22c;
      ConvF2IVector2d__5CUtilFR8S16Vec2d5Vec2dl
                ((CUtil *)&DAT_8032ec70,(S16Vec2d *)(param_11 + uVar9 * 4),&local_230,0xc);
      fVar1 = (float)(dVar15 - (double)source->z);
      dVar13 = (double)(float)((double)(float)((double)(-source->x / fVar1) * dVar16) + dVar16);
      dVar12 = (double)(float)((double)(float)((double)(-source->y / fVar1) * dVar16) + dVar16);
      local_238 = -(float)(dVar18 * (double)(float)(dVar17 * (double)(float)(dVar13 - dVar16)) -
                          dVar13);
      local_234 = -(float)(dVar18 * (double)(float)(dVar17 * (double)(float)(dVar12 - dVar16)) -
                          dVar12);
      local_218 = local_238;
      local_214 = local_234;
      ConvF2IVector2d__5CUtilFR8S16Vec2d5Vec2dl
                ((CUtil *)&DAT_8032ec70,(S16Vec2d *)(param_12 + uVar9 * 4),&local_238,0xc);
      param_8 = puVar11;
    }
  }
  iVar5 = param_4 << 2;
  DCFlushRange(param_11,iVar5);
  DCFlushRange(param_12,iVar5);
  DCFlushRange(param_10,iVar5);
  DCFlushRange(param_1,param_4 * 0xc);
  return;
}

