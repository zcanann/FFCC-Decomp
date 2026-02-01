// Function: ddh_cc_read
// Entry: 801aeea0
// Size: 236 bytes

int ddh_cc_read(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined auStack_818 [2052];
  
  iVar3 = 0;
  if (DAT_8032f360 == 0) {
    iVar3 = -0x2711;
  }
  else {
    MWTRACE(1,s_Expected_packet_size___0x_08x____801e6d04,param_2,param_2);
    while (uVar2 = CBGetBytesAvailableForRead(&DAT_8032aec0), uVar2 < param_2) {
      iVar3 = 0;
      iVar1 = EXI2_Poll();
      if ((iVar1 != 0) && (iVar3 = EXI2_ReadN(auStack_818,iVar1), iVar3 == 0)) {
        CircleBufferWriteBytes(&DAT_8032aec0,auStack_818,iVar1);
      }
    }
    if (iVar3 == 0) {
      CircleBufferReadBytes(&DAT_8032aec0,param_1,param_2);
    }
    else {
      MWTRACE(8,s_cc_read___error_reading_bytes_fr_801e6d2c,iVar3);
    }
  }
  return iVar3;
}

