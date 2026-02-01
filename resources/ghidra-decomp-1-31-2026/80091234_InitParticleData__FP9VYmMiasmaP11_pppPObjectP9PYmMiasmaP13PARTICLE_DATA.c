// Function: InitParticleData__FP9VYmMiasmaP11_pppPObjectP9PYmMiasmaP13PARTICLE_DATA
// Entry: 80091234
// Size: 872 bytes

/* WARNING: Removing unreachable block (ram,0x80091580) */
/* WARNING: Removing unreachable block (ram,0x80091578) */
/* WARNING: Removing unreachable block (ram,0x80091570) */
/* WARNING: Removing unreachable block (ram,0x80091254) */
/* WARNING: Removing unreachable block (ram,0x8009124c) */
/* WARNING: Removing unreachable block (ram,0x80091244) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void InitParticleData__FP9VYmMiasmaP11_pppPObjectP9PYmMiasmaP13PARTICLE_DATA
               (int param_1,_pppPObject *pppPObject,int param_3,_PARTICLE_DATA *particleData)

{
  uint uVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  uint uStack_54;
  longlong local_50;
  
  uVar3 = rand();
  uStack_54 = uVar3 ^ 0x80000000;
  local_58 = 0x43300000;
  dVar10 = (double)(FLOAT_8033065c *
                   (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330648));
  iVar6 = **(int **)(*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                    *(int *)(param_3 + 4) * 4);
  iVar4 = rand();
  sVar5 = *(short *)(iVar6 + 6);
  uVar1 = (uint)(FLOAT_80330650 * FLOAT_80330654 * (float)((double)FLOAT_80330660 * dVar10) -
                FLOAT_80330664);
  local_50 = (longlong)(int)uVar1;
  sVar5 = (short)iVar4 - (short)(iVar4 / (int)sVar5) * sVar5;
  *(short *)((int)&particleData->m_sizeStart + 2) = sVar5;
  *(short *)&particleData->m_sizeStart = sVar5;
  fVar2 = ppvSinTbl[(int)(uVar1 + 0x4000 & 0xffff) >> 2];
  dVar9 = (double)ppvSinTbl[(int)(uVar1 & 0xffff) >> 2];
  *(short *)&(particleData->m_directionTail).z =
       (short)uVar3 +
       ((short)((ulonglong)((longlong)(int)uVar3 * 0xb60b60b7) >> 0x28) -
       (short)((int)uVar3 / 0x168 + ((int)uVar3 >> 0x1f) >> 0x1f)) * -0x168;
  dVar8 = (double)(float)(dVar10 * (double)*(float *)(param_3 + 0x3c));
  fVar2 = fVar2 * (float)((double)*(float *)(param_1 + 0x1c) + dVar8);
  (particleData->m_matrix).value[0][0] = fVar2;
  (particleData->m_matrix).value[1][0] = fVar2;
  dVar7 = (double)RandF__5CMathFf((double)*(float *)(param_3 + 0x40),&Math);
  (particleData->m_matrix).value[0][1] = (float)dVar7;
  (particleData->m_matrix).value[1][1] = (float)dVar7;
  fVar2 = (float)(dVar9 * (double)(float)((double)*(float *)(param_1 + 0x1c) + dVar8));
  (particleData->m_matrix).value[0][2] = fVar2;
  (particleData->m_matrix).value[1][2] = fVar2;
  local_70 = (particleData->m_matrix).value[1][0];
  local_6c = (particleData->m_matrix).value[1][1];
  local_68 = (particleData->m_matrix).value[1][2];
  pppNormalize__FR3Vec3Vec((particleData->m_matrix).value + 1,&local_70);
  if (Game.game.m_currentSceneId != 7) {
    local_88 = (pppMngStPtr->m_matrix).value[0][3];
    local_84 = (pppMngStPtr->m_matrix).value[1][3];
    local_80 = (pppMngStPtr->m_matrix).value[2][3];
    local_7c = (particleData->m_matrix).value[0][0];
    local_78 = (particleData->m_matrix).value[0][1];
    local_74 = (particleData->m_matrix).value[0][2];
    local_64 = local_88;
    local_60 = local_84;
    local_5c = local_80;
    pppAddVector__FR3Vec3Vec3Vec(particleData,&local_7c,&local_88);
  }
  *(ushort *)((particleData->m_matrix).value[2] + 2) =
       (ushort)*(byte *)(param_3 + 0x48) +
       ((short)uVar3 -
       (short)((int)uVar3 / (int)(uint)*(byte *)(param_3 + 0x49)) *
       (ushort)*(byte *)(param_3 + 0x49));
  *(ushort *)(particleData->m_matrix).value[2] = (ushort)*(byte *)(param_3 + 0x24);
  *(ushort *)((int)(particleData->m_matrix).value[2] + 2) = (ushort)*(byte *)(param_3 + 0x25);
  *(ushort *)((particleData->m_matrix).value[2] + 1) = (ushort)*(byte *)(param_3 + 0x26);
  *(undefined2 *)((int)(particleData->m_matrix).value[2] + 6) = 0;
  *(short *)&(particleData->m_directionTail).x = *(short *)(param_3 + 0x28) >> 7;
  *(ushort *)&(particleData->m_directionTail).x =
       *(short *)&(particleData->m_directionTail).x - (ushort)*(byte *)(param_3 + 0x24);
  *(short *)&(particleData->m_directionTail).x =
       *(short *)&(particleData->m_directionTail).x / *(short *)(param_3 + 0x30);
  *(short *)((int)&(particleData->m_directionTail).x + 2) = *(short *)(param_3 + 0x2a) >> 7;
  *(ushort *)((int)&(particleData->m_directionTail).x + 2) =
       *(short *)((int)&(particleData->m_directionTail).x + 2) - (ushort)*(byte *)(param_3 + 0x25);
  *(short *)((int)&(particleData->m_directionTail).x + 2) =
       *(short *)((int)&(particleData->m_directionTail).x + 2) / *(short *)(param_3 + 0x30);
  *(short *)&(particleData->m_directionTail).y = *(short *)(param_3 + 0x2c) >> 7;
  *(ushort *)&(particleData->m_directionTail).y =
       *(short *)&(particleData->m_directionTail).y - (ushort)*(byte *)(param_3 + 0x26);
  *(short *)&(particleData->m_directionTail).y =
       *(short *)&(particleData->m_directionTail).y / *(short *)(param_3 + 0x30);
  *(short *)((int)&(particleData->m_directionTail).y + 2) = *(short *)(param_3 + 0x2e) >> 7;
  *(ushort *)((int)&(particleData->m_directionTail).y + 2) =
       *(short *)((int)&(particleData->m_directionTail).y + 2) - (ushort)*(byte *)(param_3 + 0x27);
  *(short *)((int)&(particleData->m_directionTail).y + 2) =
       *(short *)((int)&(particleData->m_directionTail).y + 2) / *(short *)(param_3 + 0x30);
  particleData->m_colorDeltaAdd[0] = *(float *)(param_3 + 0x34);
  dVar10 = dVar10 * (double)*(float *)(param_3 + 0x14);
  fVar2 = (float)dVar10;
  uVar1 = (uint)dVar10;
  uVar3 = uVar1 >> 0x1f;
  if ((uVar1 & 1 ^ uVar3) != uVar3) {
    fVar2 = fVar2 * FLOAT_80330668;
  }
  particleData->m_colorDeltaAdd[1] = *(float *)(param_3 + 0x10) + fVar2;
  *(undefined2 *)(particleData->m_colorDeltaAdd + 2) = *(undefined2 *)(param_3 + 0x50);
  *(undefined2 *)((int)particleData->m_colorDeltaAdd + 10) = *(undefined2 *)(param_3 + 0x52);
  *(undefined *)(particleData->m_colorDeltaAdd + 3) = 0;
  return;
}

