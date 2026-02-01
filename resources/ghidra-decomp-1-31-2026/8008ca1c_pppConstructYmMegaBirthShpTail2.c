// Function: pppConstructYmMegaBirthShpTail2
// Entry: 8008ca1c
// Size: 124 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2 *pppYmMegaBirthShpTail2,UnkC *param_2)

{
  float fVar1;
  pppFMATRIX *pppFMtx;
  
  pppFMtx = (pppFMATRIX *)
            ((int)(&pppYmMegaBirthShpTail2->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  pppUnitMatrix__FR10pppFMATRIX(pppFMtx);
  fVar1 = FLOAT_80330560;
  pppFMtx[1].value[0][2] = FLOAT_80330560;
  pppFMtx[1].value[0][1] = fVar1;
  pppFMtx[1].value[0][0] = fVar1;
  pppFMtx[1].value[0][3] = 0.0;
  pppFMtx[1].value[1][0] = 0.0;
  pppFMtx[1].value[1][1] = 0.0;
  pppFMtx[1].value[1][2] = 0.0;
  *(undefined2 *)(pppFMtx[1].value[1] + 3) = 0;
  *(undefined2 *)((int)pppFMtx[1].value[1] + 0xe) = 0;
  *(undefined2 *)(pppFMtx[1].value[1] + 3) = 10000;
  pppUnitMatrix__FR10pppFMATRIX(&MatUnit2);
  return;
}

