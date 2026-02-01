// Function: pppConstruct2YmLaser
// Entry: 800d373c
// Size: 68 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2YmLaser(pppYmLaser *pppYmLaser,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80330dc0;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppYmLaser->field_0x98 + iVar2) = FLOAT_80330dc0;
  *(float *)(&pppYmLaser->field_0x94 + iVar2) = fVar1;
  *(float *)(&pppYmLaser->field_0x90 + iVar2) = fVar1;
  *(float *)(&pppYmLaser->field_0x8c + iVar2) = fVar1;
  *(float *)(&pppYmLaser->field_0x88 + iVar2) = fVar1;
  *(float *)(&pppYmLaser->field_0x84 + iVar2) = fVar1;
  *(float *)(&pppYmLaser->field_0xa8 + iVar2) = fVar1;
  *(float *)(&pppYmLaser->field_0xa4 + iVar2) = fVar1;
  *(float *)(&pppYmLaser->field_0xa0 + iVar2) = fVar1;
  (&pppYmLaser->field_0xac)[iVar2] = 0;
  return;
}

