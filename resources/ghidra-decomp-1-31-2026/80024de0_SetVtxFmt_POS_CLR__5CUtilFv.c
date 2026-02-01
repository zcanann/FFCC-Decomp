// Function: SetVtxFmt_POS_CLR__5CUtilFv
// Entry: 80024de0
// Size: 104 bytes

void SetVtxFmt_POS_CLR__5CUtilFv(void)

{
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  return;
}

