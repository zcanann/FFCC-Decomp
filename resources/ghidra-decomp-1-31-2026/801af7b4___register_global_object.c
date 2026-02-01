// Function: __register_global_object
// Entry: 801af7b4
// Size: 24 bytes

void __register_global_object(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  *param_3 = DAT_8032f370;
  param_3[1] = param_2;
  param_3[2] = param_1;
  DAT_8032f370 = param_3;
  return;
}

