// Function: gdev_cc_initialize
// Entry: 801af574
// Size: 136 bytes

undefined4 gdev_cc_initialize(undefined4 param_1,undefined4 param_2)

{
  MWTRACE(1,s_CALLING_EXI2_Init_801e6e3c);
  DBInitComm(param_1,param_2);
  MWTRACE(1,s_DONE_CALLING_EXI2_Init_801e6e50);
  CircleBufferInitialize(&DAT_8032b3e0,&DAT_8032aee0,0x500);
  return 0;
}

