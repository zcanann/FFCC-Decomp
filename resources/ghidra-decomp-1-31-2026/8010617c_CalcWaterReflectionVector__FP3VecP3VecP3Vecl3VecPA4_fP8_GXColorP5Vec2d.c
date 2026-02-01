// Function: CalcWaterReflectionVector__FP3VecP3VecP3Vecl3VecPA4_fP8_GXColorP5Vec2d
// Entry: 8010617c
// Size: 700 bytes

/* WARNING: Removing unreachable block (ram,0x8010641c) */
/* WARNING: Removing unreachable block (ram,0x80106414) */
/* WARNING: Removing unreachable block (ram,0x80106194) */
/* WARNING: Removing unreachable block (ram,0x8010618c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcWaterReflectionVector__FP3VecP3VecP3Vecl3VecPA4_fP8_GXColorP5Vec2d
               (Vec *param_1,Vec *param_2,int param_3,int param_4,undefined4 param_5,Mtx *param_6,
               undefined *param_7,float *param_8)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  Vec *source;
  double dVar4;
  double dVar5;
  Vec VStack_d8;
  Vec local_cc;
  Vec local_c0;
  Vec local_b4;
  Mtx MStack_a8;
  Mtx MStack_78;
  
  if (Game.game.m_currentSceneId == 7) {
    local_b4.x = ppvCameraMatrix0.value[0][3];
    local_b4.y = ppvCameraMatrix0.value[1][3];
    local_b4.z = ppvCameraMatrix0.value[2][3];
  }
  else {
    local_b4.x = (float)CameraPcs._224_4_;
    local_b4.y = (float)CameraPcs._228_4_;
    local_b4.z = (float)CameraPcs._232_4_;
  }
  local_c0.x = FLOAT_80331898;
  local_c0.y = FLOAT_80331898;
  local_c0.z = FLOAT_80331898;
  PSMTXCopy(param_6,&MStack_78);
  local_cc.x = MStack_78.value[0][3];
  local_cc.y = MStack_78.value[1][3];
  local_cc.z = MStack_78.value[2][3];
  MStack_78.value[0][3] = local_c0.x;
  MStack_78.value[1][3] = local_c0.y;
  MStack_78.value[2][3] = local_c0.z;
  PSMTXInverse(&MStack_78,&MStack_a8);
  PSVECSubtract(&local_cc,&local_b4,&local_b4);
  PSVECScale(FLOAT_8033189c,&local_b4,&local_b4);
  PSMTXMultVec(&MStack_a8,&local_b4,&local_c0);
  dVar5 = (double)FLOAT_80331898;
  dVar4 = (double)FLOAT_803318a4;
  pfVar3 = param_8;
  source = param_1;
  for (iVar2 = 0; iVar2 < param_4; iVar2 = iVar2 + 1) {
    PSVECSubtract(param_2,&local_c0,&VStack_d8);
    C_VECReflect(&VStack_d8,param_3,source);
    PSMTXMultVec(&MStack_78,source,source);
    PSVECNormalize(source,source);
    if ((double)source->z < dVar5) {
      *param_7 = 0x80;
      fVar1 = FLOAT_803318a0;
      param_7[1] = 0xff;
      param_7[2] = 0x80;
      param_7[3] = 0x7f;
      *pfVar3 = -source->x / (fVar1 - source->z);
      pfVar3[1] = -source->y / (fVar1 - source->z);
    }
    else {
      *param_7 = 0x80;
      fVar1 = FLOAT_803318a0;
      param_7[1] = 0x80;
      param_7[2] = 0xff;
      param_7[3] = 0xbc;
      *pfVar3 = -source->x / (fVar1 + source->z);
      pfVar3[1] = -source->y / (fVar1 + source->z);
    }
    param_2 = param_2 + 1;
    source = source + 1;
    param_3 = param_3 + 0xc;
    param_7 = param_7 + 4;
    *pfVar3 = (float)((double)*pfVar3 * dVar4);
    *pfVar3 = (float)((double)*pfVar3 + dVar4);
    pfVar3[1] = (float)((double)pfVar3[1] * dVar4);
    pfVar3[1] = (float)((double)pfVar3[1] + dVar4);
    pfVar3 = pfVar3 + 2;
  }
  DCFlushRange(param_1,param_4 * 0xc);
  DCFlushRange(param_8,param_4 << 3);
  return;
}

