// Function: SetVtxFmt_POS_CLR_TEX__5CUtilFv
// Entry: 80024d54
// Size: 140 bytes

void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void)

{
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  GXSetVtxAttrFmt(7,0xd,1,4,0);
  return;
}

