// Function: __shr2u
// Entry: 801b0470
// Size: 36 bytes

undefined8 __shr2u(uint param_1,uint param_2,int param_3)

{
  return CONCAT44(param_1 >> param_3,
                  param_2 >> param_3 | param_1 << 0x20 - param_3 | param_1 >> param_3 + -0x20);
}

