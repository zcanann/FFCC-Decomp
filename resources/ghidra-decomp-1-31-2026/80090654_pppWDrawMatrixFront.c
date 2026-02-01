// Function: pppWDrawMatrixFront
// Entry: 80090654
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppWDrawMatrixFront(_pppPObject *param_1)

{
  Vec local_18;
  
  PSMTXScaleApply((pppMngStPtr->m_scale).x,(pppMngStPtr->m_scale).y,(pppMngStPtr->m_scale).z,
                  &param_1->m_localMatrix,(Mtx *)(param_1 + 1));
  local_18.x = (param_1->m_localMatrix).value[0][3];
  local_18.y = (param_1->m_localMatrix).value[1][3];
  local_18.z = (param_1->m_localMatrix).value[2][3];
  PSMTXMultVec(&ppvCameraMatrix0,&local_18,&local_18);
  param_1[1].m_graphId = (int32_t)local_18.x;
  param_1[1].m_localMatrix.value[0][3] = local_18.y;
  param_1[1].m_localMatrix.value[1][3] = local_18.z;
  return;
}

