// Function: pppConstruct2Laser
// Entry: 801766a8
// Size: 68 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2Laser(pppLaser *pppLaser,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80333428;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppLaser->field_0x98 + iVar2) = FLOAT_80333428;
  *(float *)(&pppLaser->field_0x94 + iVar2) = fVar1;
  *(float *)(&pppLaser->field_0x90 + iVar2) = fVar1;
  *(float *)(&pppLaser->field_0x8c + iVar2) = fVar1;
  *(float *)(&pppLaser->field_0x88 + iVar2) = fVar1;
  *(float *)(&pppLaser->field_0x84 + iVar2) = fVar1;
  *(float *)(&pppLaser->field_0xa8 + iVar2) = fVar1;
  *(float *)(&pppLaser->field_0xa4 + iVar2) = fVar1;
  *(float *)(&pppLaser->field_0xa0 + iVar2) = fVar1;
  (&pppLaser->field_0xac)[iVar2] = 0;
  return;
}

