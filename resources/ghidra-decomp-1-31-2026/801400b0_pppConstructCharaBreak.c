// Function: pppConstructCharaBreak
// Entry: 801400b0
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructCharaBreak(pppCharaBreak *pppCharaBreak,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80332048;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(undefined4 *)(&pppCharaBreak->field_0x9c + iVar2) = 0;
  *(float *)(&pppCharaBreak->field_0x8c + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x88 + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x84 + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x98 + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x94 + iVar2) = fVar1;
  *(float *)(&pppCharaBreak->field_0x90 + iVar2) = fVar1;
  *(undefined4 *)(&pppCharaBreak->field_0xc4 + iVar2) = 1;
  return;
}

