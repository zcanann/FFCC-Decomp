// Function: pppRyjMegaBirthCon
// Entry: 800822f4
// Size: 124 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRyjMegaBirthCon(pppRyjMegaBirth *pppRyjMegaBirth,UnkC *param_2)

{
  float fVar1;
  Mtx *mtx;
  
  mtx = (Mtx *)((int)(&pppRyjMegaBirth->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  PSMTXIdentity(mtx);
  fVar1 = FLOAT_80330448;
  mtx[1].value[0][2] = FLOAT_80330448;
  mtx[1].value[0][1] = fVar1;
  mtx[1].value[0][0] = fVar1;
  mtx[1].value[0][3] = 0.0;
  mtx[1].value[1][0] = 0.0;
  mtx[1].value[1][1] = 0.0;
  mtx[1].value[1][2] = 0.0;
  *(undefined2 *)(mtx[1].value[1] + 3) = 0;
  *(undefined2 *)((int)mtx[1].value[1] + 0xe) = 0;
  *(undefined2 *)(mtx[1].value[1] + 3) = 10000;
  PSMTXIdentity(&MatUnit);
  return;
}

