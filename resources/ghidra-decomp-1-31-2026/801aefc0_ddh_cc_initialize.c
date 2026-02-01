// Function: ddh_cc_initialize
// Entry: 801aefc0
// Size: 136 bytes

undefined4 ddh_cc_initialize(undefined4 param_1,undefined4 param_2)

{
  MWTRACE(1,s_CALLING_EXI2_Init_801e6d5c);
  EXI2_Init(param_1,param_2);
  MWTRACE(1,s_DONE_CALLING_EXI2_Init_801e6d70);
  CircleBufferInitialize(&DAT_8032aec0,&DAT_8032a6c0,0x800);
  return 0;
}

