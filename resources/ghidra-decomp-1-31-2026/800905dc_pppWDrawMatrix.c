// Function: pppWDrawMatrix
// Entry: 800905dc
// Size: 120 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppWDrawMatrix(_pppPObject *pppPObject)

{
  Vec *inVec;
  
  PSMTXConcat(&ppvCameraMatrix0,&pppPObject->m_localMatrix,(Mtx *)(pppPObject + 1));
  PSVECScale((pppMngStPtr->m_scale).x,(Vec *)(pppPObject + 1),(Vec *)(pppPObject + 1));
  PSVECScale((pppMngStPtr->m_scale).y,(Vec *)&pppPObject[1].m_localMatrix,
             (Vec *)&pppPObject[1].m_localMatrix);
  inVec = (Vec *)(pppPObject[1].m_localMatrix.value + 1);
  PSVECScale((pppMngStPtr->m_scale).z,inVec,inVec);
  return;
}

