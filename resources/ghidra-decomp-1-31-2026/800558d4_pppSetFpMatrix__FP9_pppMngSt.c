// Function: pppSetFpMatrix__FP9_pppMngSt
// Entry: 800558d4
// Size: 684 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt *pppMngSt)

{
  Vec local_a8;
  Vec local_9c;
  Vec local_90;
  Vec local_80;
  Vec local_70;
  Vec local_60;
  Vec local_50;
  Mtx MStack_44;
  
  PSMTXCopy(&pppMngStPtr->m_matrix,&MStack_44);
  if (pppMngSt->m_fpBillboard == '\0') {
    PSMTXConcat(&ppvCameraMatrix0,&pppMngStPtr->m_matrix,&ppvWorldMatrix);
    local_50.x = MStack_44.value[0][3];
    local_50.y = MStack_44.value[1][3];
    local_50.z = MStack_44.value[2][3];
    PSMTXMultVec(&ppvCameraMatrix0,&local_50,&local_50);
  }
  else {
    PSMTXConcat(&ppvCameraMatrix0,&pppMngStPtr->m_matrix,&ppvWorldMatrix);
    local_50.x = MStack_44.value[0][3];
    local_50.y = MStack_44.value[1][3];
    local_50.z = MStack_44.value[2][3];
    PSMTXMultVecSR(&ppvCameraMatrix0,&local_50,&local_50);
    local_50.y = local_50.y + (float)CameraPcs._228_4_;
  }
  local_70.x = ppvWorldMatrix.value[0][1];
  local_70.y = ppvWorldMatrix.value[1][1];
  local_90.x = ppvWorldMatrix.value[0][1];
  local_70.z = ppvWorldMatrix.value[2][1];
  local_90.y = ppvWorldMatrix.value[1][1];
  local_90.z = ppvWorldMatrix.value[2][1];
  ppvWorldMatrix.value[0][3] = local_50.x;
  ppvWorldMatrix.value[1][3] = local_50.y;
  ppvWorldMatrix.value[2][3] = local_50.z;
  if (((ppvWorldMatrix.value[0][1] != FLOAT_8032fddc) ||
      (ppvWorldMatrix.value[1][1] != FLOAT_8032fddc)) ||
     (ppvWorldMatrix.value[2][1] != FLOAT_8032fddc)) {
    PSVECNormalize(&local_90,&local_70);
  }
  local_60.x = local_70.y;
  local_9c.y = -local_70.x;
  local_60.z = FLOAT_8032fddc;
  local_9c.x = local_70.y;
  ppvWorldMatrixWood.value[0][1] = local_70.x;
  ppvWorldMatrixWood.value[1][1] = local_70.y;
  ppvWorldMatrixWood.value[2][1] = local_70.z;
  local_9c.z = FLOAT_8032fddc;
  local_60.y = local_9c.y;
  if ((local_70.y != FLOAT_8032fddc) || (local_9c.y != FLOAT_8032fddc)) {
    PSVECNormalize(&local_9c,&local_60);
  }
  ppvWorldMatrixWood.value[0][0] = local_60.x;
  ppvWorldMatrixWood.value[1][0] = local_60.y;
  ppvWorldMatrixWood.value[2][0] = local_60.z;
  PSVECCrossProduct(&local_60,&local_70,&local_80);
  local_a8.x = local_80.x;
  local_a8.y = local_80.y;
  local_a8.z = local_80.z;
  if (((local_80.x != FLOAT_8032fddc) || (local_80.y != FLOAT_8032fddc)) ||
     (local_80.z != FLOAT_8032fddc)) {
    PSVECNormalize(&local_a8,&local_80);
  }
  ppvWorldMatrixWood.value[0][2] = local_80.x;
  ppvWorldMatrixWood.value[1][2] = local_80.y;
  ppvWorldMatrixWood.value[2][2] = local_80.z;
  ppvWorldMatrixWood.value[0][3] = ppvWorldMatrix.value[0][3];
  ppvWorldMatrixWood.value[1][3] = ppvWorldMatrix.value[1][3];
  ppvWorldMatrixWood.value[2][3] = ppvWorldMatrix.value[2][3];
  return;
}

