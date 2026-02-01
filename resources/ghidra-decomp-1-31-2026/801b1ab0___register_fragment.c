// Function: __register_fragment
// Entry: 801b1ab0
// Size: 52 bytes

undefined4 __register_fragment(undefined4 param_1,undefined4 param_2)

{
  if (DAT_8032b408 == 0) {
    DAT_8032b400 = param_1;
    DAT_8032b404 = param_2;
    DAT_8032b408 = 1;
    return 0;
  }
  return 0xffffffff;
}

