// Function: pppDrawMatrix
// Entry: 80065350
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDrawMatrix(_pppPObject *param_1)

{
  PSMTXConcat(&ppvWorldMatrix,&param_1->m_localMatrix,(Mtx *)(param_1 + 1));
  return;
}

