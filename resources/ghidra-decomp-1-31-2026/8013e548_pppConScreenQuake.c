// Function: pppConScreenQuake
// Entry: 8013e548
// Size: 60 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConScreenQuake(pppScreenQuake *pppScreenQuake,UnkC *param_2)

{
  float fVar1;
  float *pfVar2;
  
  fVar1 = FLOAT_80331fc8;
  pfVar2 = (float *)((int)(&pppScreenQuake->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
  pfVar2[2] = FLOAT_80331fc8;
  pfVar2[1] = fVar1;
  *pfVar2 = fVar1;
  pfVar2[5] = fVar1;
  pfVar2[4] = fVar1;
  pfVar2[3] = fVar1;
  pfVar2[8] = fVar1;
  pfVar2[7] = fVar1;
  pfVar2[6] = fVar1;
  return;
}

