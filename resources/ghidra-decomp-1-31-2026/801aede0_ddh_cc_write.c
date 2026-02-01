// Function: ddh_cc_write
// Entry: 801aede0
// Size: 192 bytes

undefined4 ddh_cc_write(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_8032f360 == 0) {
    MWTRACE(8,s_cc_not_initialized_801e6ca8);
    uVar1 = 0xffffd8ef;
  }
  else {
    MWTRACE(8,s_cc_write___Output_data_0x_08x__l_801e6cbc,param_1,param_2);
    for (; 0 < param_2; param_2 = param_2 - iVar2) {
      MWTRACE(1,s_cc_write_sending__ld_bytes_801e6ce8,param_2);
      iVar2 = EXI2_WriteN(param_1,param_2);
      if (iVar2 == 0) break;
      param_1 = param_1 + iVar2;
    }
    uVar1 = 0;
  }
  return uVar1;
}

