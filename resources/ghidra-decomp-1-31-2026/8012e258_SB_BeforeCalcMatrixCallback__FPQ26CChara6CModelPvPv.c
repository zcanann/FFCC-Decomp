// Function: SB_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv
// Entry: 8012e258
// Size: 900 bytes

undefined4
SB_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv(CModel *model,int param_2,int param_3)

{
  float fVar1;
  uint8_t *puVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  float *pfVar6;
  CMesh *pCVar7;
  uint8_t *source;
  Vec local_238;
  Quat QStack_22c;
  Quat QStack_21c;
  Quat QStack_20c;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  Vec local_1f0;
  Vec local_1e4;
  Vec local_1d8;
  Vec local_1cc;
  Vec4d local_1c0;
  Vec4d VStack_1b0;
  Vec local_1a0;
  Vec local_194;
  Vec local_188;
  Mtx MStack_17c;
  Mtx MStack_14c;
  Mtx MStack_11c;
  Mtx MStack_ec;
  Mat4x4 MStack_bc;
  Mtx MStack_7c;
  Mtx MStack_4c;
  
  pfVar6 = *(float **)(param_2 + 0xc);
  local_1e4.x = DAT_801dd4b0;
  local_1e4.y = DAT_801dd4b4;
  local_1e4.z = DAT_801dd4b8;
  local_194.x = (float)CameraPcs._236_4_;
  local_194.y = (float)CameraPcs._240_4_;
  local_194.z = (float)CameraPcs._244_4_;
  local_1a0.x = (float)CameraPcs._224_4_;
  local_1a0.y = (float)CameraPcs._228_4_;
  local_1a0.z = (float)CameraPcs._232_4_;
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_4c);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_bc);
  PSVECCrossProduct(&local_194,&local_1e4,&local_1d8);
  PSVECNormalize(&local_1d8,&local_1d8);
  local_1cc.x = *(float *)(param_2 + 0x18) * local_1d8.x + local_1a0.x;
  local_1cc.y = local_1a0.y;
  local_1cc.z = *(float *)(param_2 + 0x18) * local_1d8.z + local_1a0.z;
  PSMTXMultVec(&MStack_4c,&local_1cc,(Vec *)&VStack_1b0);
  VStack_1b0.w = FLOAT_80331cd0;
  MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math,&MStack_bc,&VStack_1b0,&local_1c0);
  local_188.x = local_1c0.x * local_194.x;
  local_188.y = local_1c0.x * local_194.y;
  local_188.z = local_1c0.x * local_194.z;
  PSVECAdd(&local_1a0,&local_188,&local_188);
  PSMTXInverse(&MStack_4c,&MStack_7c);
  PSMTXConcat(&MStack_7c,&model->m_drawMtx,&model->m_drawMtx);
  fVar1 = FLOAT_80331cc4;
  (model->m_drawMtx).value[0][3] = local_188.x;
  (model->m_drawMtx).value[1][3] = local_188.y;
  (model->m_drawMtx).value[2][3] = local_188.z;
  pCVar7 = model->m_meshes;
  if (*(float *)(param_3 + 0x30) != fVar1) {
    PSVECScale(*(float *)(param_3 + 0x30),(Vec *)(param_3 + 0x20),&local_1f0);
  }
  for (uVar5 = 0; fVar1 = FLOAT_80331cc4, uVar5 < model->m_data->m_meshCount; uVar5 = uVar5 + 1) {
    if (*(char *)(pfVar6 + 0xe) != '\0') {
      puVar2 = model->m_nodes[pCVar7->m_data->m_nodeIndex].unk_0x8_0x43;
      source = puVar2 + 0xc;
      *(float *)(puVar2 + 0x18) = FLOAT_80331cc4;
      *(float *)(puVar2 + 0x28) = fVar1;
      *(float *)(puVar2 + 0x38) = fVar1;
      PSMTXCopy((Mtx *)source,&MStack_ec);
      PSMTXIdentity(&MStack_14c);
      MStack_14c.value[0][3] = pfVar6[9];
      MStack_14c.value[1][3] = pfVar6[10];
      MStack_14c.value[2][3] = pfVar6[0xb];
      PSMTXInverse(&MStack_14c,&MStack_17c);
      local_1fc = pfVar6[6];
      local_1f8 = pfVar6[7];
      local_1f4 = pfVar6[8];
      C_QUATRotAxisRad((double)pfVar6[0xd],&QStack_21c,&local_1fc);
      PSMTXQuat(&MStack_11c,&QStack_21c);
      C_QUATMtx(&QStack_20c,&MStack_ec);
      PSQUATMultiply(&QStack_21c,&QStack_20c,&QStack_22c);
      PSMTXQuat(&MStack_11c,&QStack_22c);
      PSMTXConcat(&MStack_11c,&MStack_14c,(Mtx *)source);
      fVar4 = FLOAT_80331cf4;
      fVar3 = FLOAT_80331cc4;
      pfVar6[3] = pfVar6[3] - *pfVar6;
      fVar1 = pfVar6[0xc];
      pfVar6[4] = pfVar6[1] * fVar1 - fVar4 * *(float *)(param_3 + 0x18) * fVar1 * fVar1;
      pfVar6[5] = pfVar6[5] - pfVar6[2];
      if (*(float *)(param_3 + 0x30) != fVar3) {
        pfVar6[3] = pfVar6[3] + local_1f0.x;
        pfVar6[5] = pfVar6[5] + local_1f0.z;
      }
      pfVar6[0xc] = pfVar6[0xc] + FLOAT_80331cd0;
      local_238.x = MStack_17c.value[0][3];
      local_238.y = MStack_17c.value[1][3];
      local_238.z = MStack_17c.value[2][3];
      PSVECAdd((Vec *)(pfVar6 + 3),&local_238,&local_238);
      MStack_17c.value[0][3] = local_238.x;
      MStack_17c.value[1][3] = local_238.y;
      MStack_17c.value[2][3] = local_238.z;
      PSMTXConcat(&MStack_17c,(Mtx *)source,(Mtx *)source);
    }
    pCVar7 = pCVar7 + 1;
    pfVar6 = pfVar6 + 0xf;
  }
  return 1;
}

