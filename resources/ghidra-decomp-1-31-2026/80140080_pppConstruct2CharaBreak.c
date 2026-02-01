// Function: pppConstruct2CharaBreak
// Entry: 80140080
// Size: 48 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2CharaBreak(pppCharaBreak *pppCharaBreak,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80332048;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppCharaBreak->field_0x8c + iVar2) = FLOAT_80332048;
  *(float *)(&pppCharaBreak->field_0x88 + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x84 + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x98 + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x94 + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x90 + iVar2) = fVar1;
  return;
}

