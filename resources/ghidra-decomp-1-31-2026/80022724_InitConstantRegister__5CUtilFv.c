// Function: InitConstantRegister__5CUtilFv
// Entry: 80022724
// Size: 92 bytes

void InitConstantRegister__5CUtilFv(void)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    GXSetTevKColorSel(iVar1,6);
    GXSetTevKAlphaSel(iVar1,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(iVar1,0,0);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x10);
  return;
}

