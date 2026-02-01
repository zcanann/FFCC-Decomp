// Function: CARDFormatAsync
// Entry: 8019d5c8
// Size: 72 bytes

void CARDFormatAsync(undefined4 param_1,undefined4 param_2)

{
  short encode;
  
  encode = __CARDGetFontEncode();
  __CARDFormatRegionAsync(param_1,encode,param_2);
  return;
}

