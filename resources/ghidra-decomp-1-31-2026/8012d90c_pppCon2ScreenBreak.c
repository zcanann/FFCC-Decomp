// Function: pppCon2ScreenBreak
// Entry: 8012d90c
// Size: 36 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppCon2ScreenBreak(pppScreenBreak *pppScreenBreak,UnkC *param_2)

{
  float fVar1;
  float *pfVar2;
  
  fVar1 = FLOAT_80331cc4;
  pfVar2 = (float *)((int)(&pppScreenBreak->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  pfVar2[2] = FLOAT_80331cc4;
  pfVar2[1] = fVar1;
  *pfVar2 = fVar1;
  return;
}

