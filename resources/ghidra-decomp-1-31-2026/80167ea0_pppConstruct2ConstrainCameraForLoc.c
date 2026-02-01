// Function: pppConstruct2ConstrainCameraForLoc
// Entry: 80167ea0
// Size: 36 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2ConstrainCameraForLoc
               (pppConstrainCameraForLoc *pppConstrainCameraForLoc,UnkC *param_2)

{
  float fVar1;
  float *pfVar2;
  
  fVar1 = FLOAT_803331a8;
  pfVar2 = (float *)((int)(&pppConstrainCameraForLoc->field0_0x0 + 2) +
                    param_2->m_serializedDataOffsets[2]);
  pfVar2[2] = FLOAT_803331a8;
  pfVar2[1] = fVar1;
  *pfVar2 = fVar1;
  return;
}

