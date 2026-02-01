// Function: pppDrawMatrixNoRot
// Entry: 8008ac30
// Size: 148 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDrawMatrixNoRot(_pppPObject *param_1)

{
  PSMTXScaleApply((pppMngStPtr->m_scale).x,(pppMngStPtr->m_scale).y,(pppMngStPtr->m_scale).z,
                  &param_1->m_localMatrix,(Mtx *)(param_1 + 1));
  param_1[1].m_graphId =
       (int32_t)((param_1->m_localMatrix).value[0][3] * (pppMngStPtr->m_scale).x +
                ppvWorldMatrix.value[0][3]);
  param_1[1].m_localMatrix.value[0][3] =
       (param_1->m_localMatrix).value[1][3] * (pppMngStPtr->m_scale).y + ppvWorldMatrix.value[1][3];
  param_1[1].m_localMatrix.value[1][3] =
       (param_1->m_localMatrix).value[2][3] * (pppMngStPtr->m_scale).z + ppvWorldMatrix.value[2][3];
  return;
}

