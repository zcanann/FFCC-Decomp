// Function: pppParMoveLine
// Entry: 800906dc
// Size: 232 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppParMoveLine(_pppPObject *param_1,int param_2)

{
  _pppMngSt *pppMngSt;
  float fVar1;
  Vec VStack_28;
  Vec local_1c;
  
  pppMngSt = pppMngStPtr;
  PSVECSubtract(&pppMngStPtr->m_paramVec0,&pppMngStPtr->m_savedPosition,&local_1c);
  fVar1 = FLOAT_80330638;
  (pppMngSt->m_previousPosition).x = (pppMngSt->m_position).x;
  (pppMngSt->m_previousPosition).y = (pppMngSt->m_position).y;
  (pppMngSt->m_previousPosition).z = (pppMngSt->m_position).z;
  if (((fVar1 != local_1c.x) || (fVar1 != local_1c.y)) || (fVar1 != local_1c.z)) {
    PSVECNormalize(&local_1c,&VStack_28);
    PSVECScale(*(float *)(param_2 + 4) * pppMngSt->m_paramC,&VStack_28,&local_1c);
    PSVECAdd(&local_1c,&pppMngSt->m_position,&pppMngSt->m_position);
  }
  (pppMngStPtr->m_matrix).value[0][3] = (pppMngSt->m_position).x;
  (pppMngStPtr->m_matrix).value[1][3] = (pppMngSt->m_position).y;
  (pppMngStPtr->m_matrix).value[2][3] = (pppMngSt->m_position).z;
  pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
  return;
}

