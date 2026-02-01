// Function: __shl2i
// Entry: 801b044c
// Size: 36 bytes

undefined8 __shl2i(int param_1,uint param_2,int param_3)

{
  return CONCAT44(param_1 << param_3 | param_2 >> 0x20 - param_3 | param_2 << param_3 + -0x20,
                  param_2 << param_3);
}

