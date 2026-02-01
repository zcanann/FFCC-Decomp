// Function: pppConstructYmLaser
// Entry: 800d3780
// Size: 152 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmLaser(pppYmLaser *pppYmLaser,UnkC *param_2)

{
  float fVar1;
  float *pfVar2;
  double dVar3;
  
  fVar1 = FLOAT_80330dc0;
  dVar3 = (double)FLOAT_80330df0;
  pfVar2 = (float *)((int)(&pppYmLaser->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  *pfVar2 = FLOAT_80330dc0;
  pfVar2[6] = fVar1;
  pfVar2[5] = fVar1;
  pfVar2[4] = fVar1;
  pfVar2[3] = fVar1;
  pfVar2[2] = fVar1;
  pfVar2[1] = fVar1;
  pfVar2[7] = 0.0;
  pfVar2[10] = fVar1;
  pfVar2[9] = fVar1;
  pfVar2[8] = fVar1;
  *(undefined *)(pfVar2 + 0xb) = 0;
  *(undefined *)((int)pfVar2 + 0x2d) = 0;
  *(undefined *)((int)pfVar2 + 0x2e) = 0;
  *(undefined2 *)(pfVar2 + 0xc) = 0;
  *(undefined2 *)(pfVar2 + 0xd) = 0;
  *(undefined2 *)((int)pfVar2 + 0x32) = 0;
  dVar3 = (double)RandF__5CMathFf(dVar3,&Math);
  pfVar2[0xe] = (float)dVar3;
  return;
}

