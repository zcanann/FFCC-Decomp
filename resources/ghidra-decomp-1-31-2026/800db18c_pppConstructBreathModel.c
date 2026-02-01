// Function: pppConstructBreathModel
// Entry: 800db18c
// Size: 120 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructBreathModel(pppBreathModel *pppBreathModel,UnkC *param_2)

{
  float fVar1;
  Mtx *mtx;
  
  mtx = (Mtx *)((int)(&pppBreathModel->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
  PSMTXIdentity(mtx);
  fVar1 = FLOAT_80330f70;
  mtx[1].value[2][0] = FLOAT_80330f70;
  mtx[1].value[1][3] = fVar1;
  mtx[1].value[1][2] = fVar1;
  mtx[1].value[0][0] = 0.0;
  mtx[1].value[0][1] = 0.0;
  mtx[1].value[0][2] = 0.0;
  mtx[1].value[0][3] = 0.0;
  mtx[1].value[1][0] = 0.0;
  *(undefined2 *)(mtx[1].value[1] + 1) = 10000;
  *(undefined2 *)(mtx[1].value[2] + 1) = 0;
  *(undefined2 *)((int)mtx[1].value[2] + 6) = 0;
  *(undefined *)(mtx[1].value[2] + 2) = 0;
  return;
}

