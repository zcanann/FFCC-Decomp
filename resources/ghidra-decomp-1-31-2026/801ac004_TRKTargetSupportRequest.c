// Function: TRKTargetSupportRequest
// Entry: 801ac004
// Size: 512 bytes

int TRKTargetSupportRequest(void)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_38;
  int local_34;
  undefined auStack_30 [28];
  
  puVar2 = DAT_8032a1dc;
  iVar1 = DAT_8032a1d4;
  if ((((DAT_8032a1d4 == 0xd1) || (DAT_8032a1d4 == 0xd0)) || (DAT_8032a1d4 == 0xd2)) ||
     ((DAT_8032a1d4 == 0xd3 || (DAT_8032a1d4 == 0xd4)))) {
    if (DAT_8032a1d4 == 0xd2) {
      iVar4 = HandleOpenFileSupportRequest
                        (DAT_8032a1d8,(uint)DAT_8032a1dc & 0xff,DAT_8032a1e0,&local_34);
      if ((local_34 == 0) && (iVar4 != 0)) {
        local_34 = 1;
      }
      DAT_8032a1d4 = local_34;
    }
    else if (DAT_8032a1d4 == 0xd3) {
      iVar4 = HandleCloseFileSupportRequest(DAT_8032a1d8,&local_34);
      if ((local_34 == 0) && (iVar4 != 0)) {
        local_34 = 1;
      }
      DAT_8032a1d4 = local_34;
    }
    else if (DAT_8032a1d4 == 0xd4) {
      local_38 = *DAT_8032a1dc;
      iVar4 = HandlePositionFileSupportRequest(DAT_8032a1d8,&local_38,DAT_8032a1e0 & 0xff,&local_34)
      ;
      if ((local_34 == 0) && (iVar4 != 0)) {
        local_34 = 1;
      }
      DAT_8032a1d4 = local_34;
      *DAT_8032a1dc = local_38;
    }
    else {
      uVar3 = countLeadingZeros(0xd1 - DAT_8032a1d4);
      iVar4 = TRKSuppAccessFile(DAT_8032a1d8,DAT_8032a1e0,DAT_8032a1dc,&local_34,1,uVar3 >> 5);
      if ((local_34 == 0) && (iVar4 != 0)) {
        local_34 = 1;
      }
      DAT_8032a1d4 = local_34;
      if (iVar1 == 0xd1) {
        TRK_flush_cache(DAT_8032a1e0,*puVar2);
      }
    }
    DAT_8032a248 = DAT_8032a248 + 4;
  }
  else {
    TRKConstructEvent(auStack_30,4);
    TRKPostEvent(auStack_30);
    iVar4 = 0;
  }
  return iVar4;
}

