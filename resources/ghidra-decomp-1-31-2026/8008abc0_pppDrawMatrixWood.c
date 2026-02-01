// Function: pppDrawMatrixWood
// Entry: 8008abc0
// Size: 112 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDrawMatrixWood(_pppPObject *param_1)

{
  PSMTXScaleApply((pppMngStPtr->m_scale).x,(pppMngStPtr->m_scale).y,(pppMngStPtr->m_scale).z,
                  &param_1->m_localMatrix,(Mtx *)(param_1 + 1));
  param_1[1].m_graphId = (int32_t)(param_1->m_localMatrix).value[0][3];
  param_1[1].m_localMatrix.value[0][3] = (param_1->m_localMatrix).value[1][3];
  param_1[1].m_localMatrix.value[1][3] = (param_1->m_localMatrix).value[2][3];
  PSMTXConcat(&ppvWorldMatrixWood,(Mtx *)(param_1 + 1),(Mtx *)(param_1 + 1));
  return;
}

