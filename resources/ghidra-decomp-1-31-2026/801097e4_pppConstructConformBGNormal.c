// Function: pppConstructConformBGNormal
// Entry: 801097e4
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructConformBGNormal(pppConformBGNormal *pppConformBGNormal,UnkC *param_2)

{
  float fVar1;
  float *pfVar2;
  
  fVar1 = FLOAT_80331908;
  pfVar2 = (float *)((int)(&pppConformBGNormal->field0_0x0 + 2) + *param_2->m_serializedDataOffsets)
  ;
  pfVar2[2] = FLOAT_80331908;
  pfVar2[1] = fVar1;
  *pfVar2 = fVar1;
  *(undefined *)(pfVar2 + 3) = 0;
  return;
}

