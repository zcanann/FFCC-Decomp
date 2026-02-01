// Function: SetVtxFmt_POS_CLR_TEX0_TEX1__5CUtilFv
// Entry: 80024c18
// Size: 176 bytes

void SetVtxFmt_POS_CLR_TEX0_TEX1__5CUtilFv(void)

{
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxDesc(0xe,1);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  GXSetVtxAttrFmt(7,0xd,1,4,0);
  GXSetVtxAttrFmt(7,0xe,1,4,0);
  return;
}

