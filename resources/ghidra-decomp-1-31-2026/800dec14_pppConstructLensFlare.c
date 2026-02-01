// Function: pppConstructLensFlare
// Entry: 800dec14
// Size: 72 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructLensFlare(pppLensFlare *pppLensFlare,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80331060;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppLensFlare->field_0x98 + iVar2) = FLOAT_80331060;
  *(float *)(&pppLensFlare->field_0x94 + iVar2) = fVar1;
  *(float *)(&pppLensFlare->field_0x90 + iVar2) = fVar1;
  *(float *)(&pppLensFlare->field_0xa8 + iVar2) = fVar1;
  *(float *)(&pppLensFlare->field_0xa4 + iVar2) = fVar1;
  *(float *)(&pppLensFlare->field_0xa0 + iVar2) = fVar1;
  *(undefined2 *)(&pppLensFlare->field_0xb0 + iVar2) = 0;
  *(undefined2 *)(&pppLensFlare->field_0xae + iVar2) = 0;
  *(undefined2 *)(&pppLensFlare->field_0xac + iVar2) = 0;
  (&pppLensFlare->field_0xb2)[iVar2] = 0;
  *(float *)(&pppLensFlare->field_0xb4 + iVar2) = fVar1;
  return;
}

