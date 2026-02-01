// Function: GXSetTexRegionCallback
// Entry: 801a46a8
// Size: 20 bytes

undefined4 GXSetTexRegionCallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(DAT_80333828 + 0x410);
  *(undefined4 *)(DAT_80333828 + 0x410) = param_1;
  return uVar1;
}

