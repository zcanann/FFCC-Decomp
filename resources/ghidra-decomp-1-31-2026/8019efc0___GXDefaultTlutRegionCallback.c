// Function: __GXDefaultTlutRegionCallback
// Entry: 8019efc0
// Size: 36 bytes

int __GXDefaultTlutRegionCallback(uint param_1)

{
  int iVar1;
  
  if (param_1 < 0x14) {
    iVar1 = DAT_80333828 + param_1 * 0x10 + 0x2d0;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

