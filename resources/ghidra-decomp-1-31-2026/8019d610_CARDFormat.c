// Function: CARDFormat
// Entry: 8019d610
// Size: 84 bytes

void CARDFormat(undefined4 param_1)

{
  short encode;
  int iVar1;
  
  encode = __CARDGetFontEncode();
  iVar1 = __CARDFormatRegionAsync(param_1,encode,__CARDSyncCallback);
  if (-1 < iVar1) {
    __CARDSync(param_1);
  }
  return;
}

