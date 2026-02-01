// Function: pppFrameChangeBGColor
// Entry: 8012d3fc
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameChangeBGColor(pppChangeBGColor *pppChangeBGColor,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  
  if (DAT_8032ed70 != 0) {
    return;
  }
  iVar1 = param_3->m_serializedDataOffsets[1];
  MapMng._141705_1_ = 1;
  MapMng._141712_1_ = (&pppChangeBGColor->field_0x88)[iVar1];
  MapMng._141713_1_ = (&pppChangeBGColor->field_0x89)[iVar1];
  MapMng._141714_1_ = (&pppChangeBGColor->field_0x8a)[iVar1];
  MapMng._141715_1_ = (&pppChangeBGColor->field_0x8b)[iVar1];
  return;
}

