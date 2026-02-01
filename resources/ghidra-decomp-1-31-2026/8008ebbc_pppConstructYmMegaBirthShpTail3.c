// Function: pppConstructYmMegaBirthShpTail3
// Entry: 8008ebbc
// Size: 228 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3 *pppYmMegaBirthShpTail3,UnkC *param_2)

{
  float fVar1;
  undefined2 uVar2;
  pppFMATRIX *pppFMtx;
  
  pppFMtx = (pppFMATRIX *)
            ((int)(&pppYmMegaBirthShpTail3->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  pppUnitMatrix__FR10pppFMATRIX(pppFMtx);
  fVar1 = FLOAT_803305a4;
  pppFMtx[1].value[0][2] = FLOAT_803305a4;
  pppFMtx[1].value[0][1] = fVar1;
  pppFMtx[1].value[0][0] = fVar1;
  pppFMtx[1].value[0][3] = 0.0;
  pppFMtx[1].value[1][0] = 0.0;
  pppFMtx[1].value[1][1] = 0.0;
  pppFMtx[1].value[1][2] = 0.0;
  *(undefined2 *)(pppFMtx[1].value[1] + 3) = 0;
  *(undefined2 *)((int)pppFMtx[1].value[1] + 0xe) = 0;
  *(undefined2 *)(pppFMtx[1].value[1] + 3) = 10000;
  uVar2 = rand();
  *(undefined2 *)pppFMtx[2].value[2] = uVar2;
  pppUnitMatrix__FR10pppFMATRIX(&MatUnit3);
  memset(pppFMtx[1].value + 2,0,8);
  memset(pppFMtx[1].value[2] + 2,0,8);
  memset(pppFMtx + 2,0,8);
  memset(pppFMtx[2].value[0] + 2,0,8);
  memset(pppFMtx[2].value + 1,0,8);
  memset(pppFMtx[2].value[1] + 2,0,8);
  return;
}

