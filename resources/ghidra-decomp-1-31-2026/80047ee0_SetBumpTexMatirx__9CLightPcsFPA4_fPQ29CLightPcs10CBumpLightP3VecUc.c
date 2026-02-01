// Function: SetBumpTexMatirx__9CLightPcsFPA4_fPQ29CLightPcs10CBumpLightP3VecUc
// Entry: 80047ee0
// Size: 1180 bytes

/* WARNING: Removing unreachable block (ram,0x80048360) */
/* WARNING: Removing unreachable block (ram,0x80048358) */
/* WARNING: Removing unreachable block (ram,0x80047ef8) */
/* WARNING: Removing unreachable block (ram,0x80047ef0) */

void SetBumpTexMatirx__9CLightPcsFPA4_fPQ29CLightPcs10CBumpLightP3VecUc
               (int param_1,Mtx *param_2,int param_3,float *param_4,char param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  double dVar6;
  Vec local_1a8;
  Vec local_19c;
  Vec local_190;
  Vec local_184;
  Vec local_178;
  Vec local_16c;
  Mtx MStack_160;
  Mtx MStack_130;
  Mtx local_100;
  Mtx local_d0;
  Mtx MStack_a0;
  Mtx local_70;
  
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&local_70);
  if (param_5 == '\0') {
    if ((param_4 == (float *)0x0) ||
       (((FLOAT_8032fc14 == *param_4 && (FLOAT_8032fc14 == param_4[1])) &&
        (FLOAT_8032fc14 == param_4[2])))) {
      PSMTXConcat(&local_70,param_2,&local_d0);
    }
    else {
      PSMTXCopy(param_2,&MStack_160);
      local_19c.x = (float)CameraPcs._224_4_;
      local_19c.y = (float)CameraPcs._228_4_;
      local_19c.z = (float)CameraPcs._232_4_;
      local_1a8.x = MStack_160.value[0][3];
      local_1a8.y = MStack_160.value[1][3];
      local_1a8.z = MStack_160.value[2][3];
      PSVECSubtract(&local_19c,&local_1a8,&local_19c);
      local_19c.x = local_19c.x * *param_4;
      local_19c.y = local_19c.y * param_4[1];
      local_19c.z = local_19c.z * param_4[2];
      PSMTXMultVecSR(&local_70,&local_19c,&local_19c);
      PSMTXConcat(&local_70,&MStack_160,&local_d0);
      local_d0.value[0][3] = local_d0.value[0][3] + local_19c.x;
      local_d0.value[1][3] = local_d0.value[1][3] + local_19c.y;
      local_d0.value[2][3] = local_d0.value[2][3] + local_19c.z;
    }
  }
  else {
    local_16c.x = param_2->value[0][3];
    local_16c.y = param_2->value[1][3];
    local_16c.z = param_2->value[2][3];
    PSMTXMultVec(&local_70,&local_16c,&local_16c);
    if (param_5 == '\x01') {
      local_70.value[0][1] = FLOAT_8032fc14;
      local_70.value[0][0] = FLOAT_8032fc1c;
      local_70.value[0][2] = FLOAT_8032fc14;
      local_70.value[1][0] = FLOAT_8032fc14;
      local_70.value[1][1] = FLOAT_8032fc1c;
      local_70.value[1][2] = FLOAT_8032fc14;
      local_70.value[2][0] = FLOAT_8032fc14;
      local_70.value[2][1] = FLOAT_8032fc14;
      local_70.value[2][2] = FLOAT_8032fc1c;
    }
    else if (param_5 == '\x02') {
      local_184.x = local_70.value[0][1];
      local_184.y = local_70.value[1][1];
      local_184.z = local_70.value[2][1];
      PSVECNormalize(&local_184,&local_184);
      local_178.y = -local_184.x;
      local_70.value[0][1] = local_184.x;
      local_70.value[1][1] = local_184.y;
      local_70.value[2][1] = local_184.z;
      local_178.x = local_184.y;
      local_178.z = FLOAT_8032fc14;
      PSVECNormalize(&local_178,&local_178);
      local_70.value[0][0] = local_178.x;
      local_70.value[1][0] = local_178.y;
      local_70.value[2][0] = local_178.z;
      PSVECCrossProduct(&local_178,&local_184,&local_190);
      PSVECNormalize(&local_190,&local_190);
      local_70.value[0][2] = local_190.x;
      local_70.value[1][2] = local_190.y;
      local_70.value[2][2] = local_190.z;
    }
    PSMTXConcat(&local_70,param_2,&local_d0);
    local_d0.value[0][3] = local_16c.x;
    local_d0.value[1][3] = local_16c.y;
    local_d0.value[2][3] = local_16c.z;
  }
  GXLoadPosMtxImm(&local_d0,0);
  local_100.value[0][0] = local_d0.value[0][0];
  local_100.value[1][0] = local_d0.value[1][0];
  local_100.value[2][0] = local_d0.value[2][0];
  local_100.value[0][1] = local_d0.value[0][1];
  local_100.value[1][1] = local_d0.value[1][1];
  local_100.value[2][1] = local_d0.value[2][1];
  local_100.value[0][2] = local_d0.value[0][2];
  local_100.value[1][2] = local_d0.value[1][2];
  local_100.value[2][2] = local_d0.value[2][2];
  local_100.value[0][3] = FLOAT_8032fc14;
  local_100.value[1][3] = FLOAT_8032fc14;
  local_100.value[2][3] = FLOAT_8032fc14;
  GXLoadNrmMtxImm(&local_100,0);
  if ((param_3 != 0) && (*(char *)(param_3 + 0xb0) != '\0')) {
    if (*(char *)(param_3 + 0xb1) == '\x01') {
      PSMTXTrans(FLOAT_8032fc18,FLOAT_8032fc18,FLOAT_8032fc14,&MStack_a0);
      PSMTXConcat(&MStack_a0,&local_100,(Mtx *)(param_1 + 4));
      PSMTXScale(FLOAT_8032fc20,FLOAT_8032fc20,FLOAT_8032fc20,&MStack_a0);
      PSMTXConcat((Mtx *)(param_1 + 4),&MStack_a0,(Mtx *)(param_1 + 4));
      PSMTXCopy(&local_d0,&MStack_130);
      MStack_130.value[0][3] = FLOAT_8032fc14;
      MStack_130.value[1][3] = FLOAT_8032fc14;
      MStack_130.value[2][3] = FLOAT_8032fc14;
      PSMTXConcat(&MStack_130,&MStack_a0,(Mtx *)(param_1 + 0x34));
    }
    else {
      PSMTXIdentity(&local_100);
      PSMTXTrans(FLOAT_8032fc18,FLOAT_8032fc18,FLOAT_8032fc14,&MStack_a0);
      PSMTXConcat(&MStack_a0,&local_100,(Mtx *)(param_1 + 4));
      PSMTXScale(FLOAT_8032fc20,FLOAT_8032fc20,FLOAT_8032fc20,&MStack_a0);
      PSMTXConcat((Mtx *)(param_1 + 4),&MStack_a0,(Mtx *)(param_1 + 4));
      dVar6 = (double)(float)CameraPcs._224_4_;
      dVar5 = (double)(float)CameraPcs._232_4_;
      PSMTXIdentity((Mtx *)(param_1 + 100));
      fVar4 = FLOAT_8032fc24;
      fVar1 = FLOAT_8032fc14;
      *(float *)(param_1 + 100) = FLOAT_8032fc24;
      fVar2 = FLOAT_8032fc18;
      *(float *)(param_1 + 0x7c) = fVar4;
      fVar3 = FLOAT_8032fc20;
      *(float *)(param_1 + 0x8c) = fVar1;
      *(float *)(param_1 + 0x78) = fVar1;
      *(float *)(param_1 + 0x88) = fVar1;
      *(float *)(param_1 + 0x70) =
           -(fVar4 * (float)(dVar6 + (double)*(float *)(param_3 + 0x2c)) - fVar2);
      *(float *)(param_1 + 0x80) =
           -(fVar4 * (float)(dVar5 + (double)*(float *)(param_3 + 0x30)) - fVar2);
      *(float *)(param_1 + 0x90) = fVar1;
      *(float *)(param_1 + 0xa4) = fVar3;
      *(float *)(param_1 + 0x94) = fVar3;
      *(float *)(param_1 + 0xa8) = fVar1;
      *(float *)(param_1 + 0xa0) = fVar1;
      *(float *)(param_1 + 0x9c) = fVar1;
      *(float *)(param_1 + 0x98) = fVar1;
    }
  }
  return;
}

