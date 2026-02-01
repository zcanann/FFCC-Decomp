// Function: GXSetTlutRegionCallback
// Entry: 801a46bc
// Size: 20 bytes

undefined4 GXSetTlutRegionCallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(DAT_80333828 + 0x414);
  *(undefined4 *)(DAT_80333828 + 0x414) = param_1;
  return uVar1;
}

