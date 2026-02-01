// Function: pppWDrawMatrixLoop
// Entry: 800c4dd8
// Size: 120 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppWDrawMatrixLoop(_pppPObject *param_1)

{
  Vec *inVec;
  
  PSMTXConcat(&ppvCameraMatrix0,&param_1->m_localMatrix,(Mtx *)(param_1 + 1));
  PSVECScale((pppMngStPtr->m_scale).x,(Vec *)(param_1 + 1),(Vec *)(param_1 + 1));
  PSVECScale((pppMngStPtr->m_scale).y,(Vec *)&param_1[1].m_localMatrix,
             (Vec *)&param_1[1].m_localMatrix);
  inVec = (Vec *)(param_1[1].m_localMatrix.value + 1);
  PSVECScale((pppMngStPtr->m_scale).z,inVec,inVec);
  return;
}

