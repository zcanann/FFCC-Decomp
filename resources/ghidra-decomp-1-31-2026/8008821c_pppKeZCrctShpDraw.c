// Function: pppKeZCrctShpDraw
// Entry: 8008821c
// Size: 1148 bytes

/* WARNING: Removing unreachable block (ram,0x80088360) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppKeZCrctShpDraw(_pppPObject *param_1,int param_2)

{
  byte bVar1;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  Vec local_1d8;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  Vec local_1a8;
  Vec VStack_198;
  Vec VStack_188;
  Vec VStack_178;
  Vec local_168;
  Vec local_158;
  Vec local_148;
  Vec local_138;
  Vec local_128;
  pppFMATRIX local_118;
  pppFMATRIX local_e8;
  pppFMATRIX local_b8;
  pppFMATRIX local_88;
  pppFMATRIX pStack_58;
  
  pppGetRowVector__FR10pppFMATRIXR3VecR3VecR3VecR3Vec
            (&param_1->m_localMatrix,&local_138,&local_148,&local_158,&local_168);
  local_1b4 = local_138.x;
  local_1b0 = local_138.y;
  local_1ac = local_138.z;
  pppScaleVector__FR3Vec3Vecf((pppMngStPtr->m_scale).x,&VStack_178,&local_1b4);
  local_1c0 = local_148.x;
  local_1bc = local_148.y;
  local_1b8 = local_148.z;
  pppScaleVector__FR3Vec3Vecf((pppMngStPtr->m_scale).y,&VStack_188,&local_1c0);
  local_1cc = local_158.x;
  local_1c8 = local_158.y;
  local_1c4 = local_158.z;
  pppScaleVector__FR3Vec3Vecf((pppMngStPtr->m_scale).z,&VStack_198,&local_1cc);
  local_1a8.z = FLOAT_803304f8;
  local_1a8.y = FLOAT_803304f8;
  local_1a8.x = FLOAT_803304f8;
  pppSetRowVector__FR10pppFMATRIXR3VecR3VecR3VecR3Vec
            (&pStack_58,&VStack_178,&VStack_188,&VStack_198,&local_1a8);
  local_1d8.x = local_168.x;
  local_1d8.y = local_168.y;
  local_1d8.z = local_168.z;
  pppCopyVector__FR3Vec3Vec(&local_128,&local_1d8);
  local_1fc = local_128.x * *(float *)(param_2 + 0x18);
  local_1f8 = local_128.y * *(float *)(param_2 + 0x1c);
  local_1f4 = local_128.z * *(float *)(param_2 + 0x20);
  bVar1 = *(byte *)(param_2 + 0x28);
  local_128.x = local_1fc;
  local_128.y = local_1f8;
  local_128.z = local_1f4;
  if (bVar1 == 1) {
    local_b8.value[0][0] = ppvWorldMatrix.value[0][0];
    local_b8.value[0][1] = ppvWorldMatrix.value[0][1];
    local_b8.value[0][2] = ppvWorldMatrix.value[0][2];
    local_b8.value[0][3] = ppvWorldMatrix.value[0][3];
    local_b8.value[1][0] = ppvWorldMatrix.value[1][0];
    local_b8.value[1][1] = ppvWorldMatrix.value[1][1];
    local_b8.value[1][2] = ppvWorldMatrix.value[1][2];
    local_b8.value[1][3] = ppvWorldMatrix.value[1][3];
    local_b8.value[2][0] = ppvWorldMatrix.value[2][0];
    local_b8.value[2][1] = ppvWorldMatrix.value[2][1];
    local_b8.value[2][2] = ppvWorldMatrix.value[2][2];
    local_b8.value[2][3] = ppvWorldMatrix.value[2][3];
    local_1f0 = local_1fc;
    local_1ec = local_1f8;
    local_1e8 = local_1f4;
    pppApplyMatrix__FR3Vec10pppFMATRIX3Vec(&local_1a8,&local_b8,&local_1f0);
  }
  else if (bVar1 == 0) {
    local_1e4 = local_1fc + *(float *)(param_2 + 8);
    local_1e0 = local_1f8 + *(float *)(param_2 + 0xc);
    local_1dc = local_1f4 + *(float *)(param_2 + 0x10);
    local_88.value[0][0] = ppvWorldMatrix.value[0][0];
    local_88.value[0][1] = ppvWorldMatrix.value[0][1];
    local_88.value[0][2] = ppvWorldMatrix.value[0][2];
    local_88.value[0][3] = ppvWorldMatrix.value[0][3];
    local_88.value[1][0] = ppvWorldMatrix.value[1][0];
    local_88.value[1][1] = ppvWorldMatrix.value[1][1];
    local_88.value[1][2] = ppvWorldMatrix.value[1][2];
    local_88.value[1][3] = ppvWorldMatrix.value[1][3];
    local_88.value[2][0] = ppvWorldMatrix.value[2][0];
    local_88.value[2][1] = ppvWorldMatrix.value[2][1];
    local_88.value[2][2] = ppvWorldMatrix.value[2][2];
    local_88.value[2][3] = ppvWorldMatrix.value[2][3];
    local_128.x = local_1e4;
    local_128.y = local_1e0;
    local_128.z = local_1dc;
    pppApplyMatrix__FR3Vec10pppFMATRIX3Vec(&local_128,&local_88,&local_1e4);
  }
  else if (bVar1 < 3) {
    local_e8.value[0][0] = (pppMngStPtr->m_matrix).value[0][0];
    local_e8.value[0][1] = (pppMngStPtr->m_matrix).value[0][1];
    local_e8.value[0][2] = (pppMngStPtr->m_matrix).value[0][2];
    local_e8.value[0][3] = (pppMngStPtr->m_matrix).value[0][3];
    local_e8.value[1][0] = (pppMngStPtr->m_matrix).value[1][0];
    local_e8.value[1][1] = (pppMngStPtr->m_matrix).value[1][1];
    local_e8.value[1][2] = (pppMngStPtr->m_matrix).value[1][2];
    local_e8.value[1][3] = (pppMngStPtr->m_matrix).value[1][3];
    local_e8.value[2][0] = (pppMngStPtr->m_matrix).value[2][0];
    local_e8.value[2][1] = (pppMngStPtr->m_matrix).value[2][1];
    local_e8.value[2][2] = (pppMngStPtr->m_matrix).value[2][2];
    local_e8.value[2][3] = (pppMngStPtr->m_matrix).value[2][3];
    pppApplyMatrix__FR3Vec10pppFMATRIX3Vec(&local_1a8,&local_e8,&local_1fc);
    local_208 = *(float *)(param_2 + 8) * (pppMngStPtr->m_scale).x + local_1a8.x;
    local_204 = *(float *)(param_2 + 0xc) * (pppMngStPtr->m_scale).y + local_1a8.y;
    local_200 = *(float *)(param_2 + 0x10) * (pppMngStPtr->m_scale).z + local_1a8.z;
    local_118.value[0][0] = ppvCameraMatrix0.value[0][0];
    local_118.value[0][1] = ppvCameraMatrix0.value[0][1];
    local_118.value[0][2] = ppvCameraMatrix0.value[0][2];
    local_118.value[0][3] = ppvCameraMatrix0.value[0][3];
    local_118.value[1][0] = ppvCameraMatrix0.value[1][0];
    local_118.value[1][1] = ppvCameraMatrix0.value[1][1];
    local_118.value[1][2] = ppvCameraMatrix0.value[1][2];
    local_118.value[1][3] = ppvCameraMatrix0.value[1][3];
    local_118.value[2][0] = ppvCameraMatrix0.value[2][0];
    local_118.value[2][1] = ppvCameraMatrix0.value[2][1];
    local_118.value[2][2] = ppvCameraMatrix0.value[2][2];
    local_118.value[2][3] = ppvCameraMatrix0.value[2][3];
    local_1a8.x = local_208;
    local_1a8.y = local_204;
    local_1a8.z = local_200;
    pppApplyMatrix__FR3Vec10pppFMATRIX3Vec(&local_1a8,&local_118,&local_208);
  }
  return;
}

