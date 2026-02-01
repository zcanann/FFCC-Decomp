// Function: pppSDrawMatrix
// Entry: 800d25e0
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppSDrawMatrix(_pppPObject *param_1)

{
  PSMTXConcat(&ppvCameraMatrix0,&param_1->m_localMatrix,(Mtx *)(param_1 + 1));
  return;
}

