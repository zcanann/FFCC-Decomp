// Function: SetVtxFmt_POS_TEX0_TEX1__5CUtilFv
// Entry: 80024cc8
// Size: 140 bytes

void SetVtxFmt_POS_TEX0_TEX1__5CUtilFv(void)

{
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxDesc(0xe,1);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xd,1,4,0);
  GXSetVtxAttrFmt(7,0xe,1,4,0);
  return;
}

