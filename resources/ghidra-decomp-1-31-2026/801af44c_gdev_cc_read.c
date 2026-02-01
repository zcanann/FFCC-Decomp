// Function: gdev_cc_read
// Entry: 801af44c
// Size: 244 bytes

int gdev_cc_read(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined auStack_518 [1280];
  
  iVar3 = 0;
  if (DAT_8032f368 == 0) {
    iVar3 = -0x2711;
  }
  else {
    MWTRACE(1,s_Expected_packet_size___0x_08x____801e6de4,param_2,param_2);
    while (uVar2 = CBGetBytesAvailableForRead(&DAT_8032b3e0), uVar2 < param_2) {
      iVar3 = 0;
      iVar1 = DBQueryData();
      if ((iVar1 != 0) && (iVar3 = DBRead(auStack_518,param_2), iVar3 == 0)) {
        CircleBufferWriteBytes(&DAT_8032b3e0,auStack_518,iVar1);
      }
    }
    if (iVar3 == 0) {
      CircleBufferReadBytes(&DAT_8032b3e0,param_1,param_2);
    }
    else {
      MWTRACE(8,s_cc_read___error_reading_bytes_fr_801e6e0c,iVar3);
    }
  }
  return iVar3;
}

