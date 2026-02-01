// Function: SetDiffuse__9CLightPcsFUl8_GXColorP3Veci
// Entry: 800491f8
// Size: 340 bytes

/* WARNING: Removing unreachable block (ram,0x80049330) */
/* WARNING: Removing unreachable block (ram,0x80049328) */
/* WARNING: Removing unreachable block (ram,0x80049320) */
/* WARNING: Removing unreachable block (ram,0x80049218) */
/* WARNING: Removing unreachable block (ram,0x80049210) */
/* WARNING: Removing unreachable block (ram,0x80049208) */

void SetDiffuse__9CLightPcsFUl8_GXColorP3Veci
               (int param_1,int param_2,undefined4 *param_3,float *param_4,int param_5)

{
  float fVar1;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  undefined4 local_78;
  Vec local_74;
  Mtx MStack_68;
  float fVar2;
  float fVar3;
  
  param_1 = param_1 + param_2 * 0xb0 + 0xbc;
  fVar1 = (float)CameraPcs._244_4_;
  fVar2 = (float)CameraPcs._240_4_;
  fVar3 = (float)CameraPcs._236_4_;
  if (param_5 == 0) {
    fVar1 = param_4[2];
    fVar2 = param_4[1];
    fVar3 = *param_4;
  }
  dVar7 = (double)fVar3;
  dVar6 = (double)fVar2;
  dVar5 = (double)fVar1;
  local_78 = *param_3;
  GXInitLightColor(param_1 + 0x6c,&local_78);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_68);
  dVar4 = (double)FLOAT_8032fc70;
  local_74.x = (float)(dVar4 * -dVar7);
  local_74.y = (float)(dVar4 * -dVar6);
  local_74.z = (float)(dVar4 * -dVar5);
  PSMTXMultVec(&MStack_68,&local_74,&local_74);
  GXInitLightPos((double)local_74.x,(double)local_74.y,(double)local_74.z,param_1 + 0x6c);
  local_74.x = (float)dVar7;
  local_74.y = (float)dVar6;
  local_74.z = (float)dVar5;
  PSMTXMultVecSR(&MStack_68,&local_74,&local_74);
  GXInitLightDir((double)local_74.x,(double)local_74.y,(double)local_74.z,param_1 + 0x6c);
  GXInitLightSpot((double)FLOAT_8032fc74,param_1 + 0x6c,4);
  GXInitLightAttnK((double)FLOAT_8032fc14,(double)FLOAT_8032fc78,(double)FLOAT_8032fc14,
                   param_1 + 0x6c);
  return;
}

