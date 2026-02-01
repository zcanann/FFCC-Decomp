// Function: pppDrawMatrixLoc
// Entry: 8016c9e8
// Size: 152 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDrawMatrixLoc(_pppPObject *param_1)

{
  Vec local_38;
  Vec local_2c;
  Vec local_20 [2];
  
  local_2c.z = FLOAT_803331d8;
  local_2c.y = FLOAT_803331d8;
  local_2c.x = FLOAT_803331d8;
  PSMTXCopy(&param_1->m_localMatrix,(Mtx *)(param_1 + 1));
  PSMTXMultVec(&ppvWorldMatrix,&local_2c,&local_2c);
  local_38.x = (float)param_1[1].m_graphId;
  local_38.y = param_1[1].m_localMatrix.value[0][3];
  local_38.z = param_1[1].m_localMatrix.value[1][3];
  PSVECAdd(&local_38,&local_2c,local_20);
  param_1[1].m_graphId = (int32_t)local_20[0].x;
  param_1[1].m_localMatrix.value[0][3] = local_20[0].y;
  param_1[1].m_localMatrix.value[1][3] = local_20[0].z;
  return;
}

