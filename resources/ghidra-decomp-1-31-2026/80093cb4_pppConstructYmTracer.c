// Function: pppConstructYmTracer
// Entry: 80093cb4
// Size: 80 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmTracer(pppYmTracer *pppYmTracer,UnkC *param_2)

{
  float fVar1;
  float *pfVar2;
  
  fVar1 = FLOAT_803306e8;
  pfVar2 = (float *)((int)(&pppYmTracer->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
  pfVar2[10] = 0.0;
  pfVar2[9] = 0.0;
  pfVar2[8] = 0.0;
  *(undefined2 *)(pfVar2 + 0xb) = 0;
  pfVar2[3] = fVar1;
  pfVar2[2] = fVar1;
  pfVar2[1] = fVar1;
  *pfVar2 = fVar1;
  pfVar2[7] = fVar1;
  pfVar2[6] = fVar1;
  pfVar2[5] = fVar1;
  pfVar2[4] = fVar1;
  *(undefined2 *)((int)pfVar2 + 0x2e) = 0;
  return;
}

