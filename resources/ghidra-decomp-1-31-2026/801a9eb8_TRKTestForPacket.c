// Function: TRKTestForPacket
// Entry: 801a9eb8
// Size: 316 bytes

undefined4 TRKTestForPacket(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_8d8;
  undefined4 local_8d4;
  int local_8d0 [16];
  undefined auStack_890 [2184];
  
  iVar1 = TRKPollUART();
  if (iVar1 < 1) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = TRKGetFreeBuffer(&local_8d4,&local_8d8);
    MWTRACE(4,s_TestForPacket___FreeBuffer_is__l_801e6768,uVar2);
    TRKSetBufferPosition(local_8d8,0);
    iVar1 = TRKReadUARTN(local_8d0,0x40);
    if (iVar1 == 0) {
      TRKAppendBuffer_ui8(local_8d8,local_8d0,0x40);
      uVar2 = local_8d4;
      if (0 < local_8d0[0] + -0x40) {
        MWTRACE(1,s_Reading_payload__ld_bytes_801e678c);
        iVar1 = TRKReadUARTN(auStack_890,local_8d0[0] + -0x40);
        if (iVar1 == 0) {
          TRKAppendBuffer_ui8(local_8d8,auStack_890,local_8d0[0]);
        }
        else {
          MWTRACE(8,s_TestForPacket___Invalid_size_of_p_801e67a8);
          TRKReleaseBuffer(local_8d4);
          uVar2 = 0xffffffff;
        }
      }
    }
    else {
      MWTRACE(8,s_TestForPacket___Invalid_size_of_p_801e67dc);
      TRKReleaseBuffer(uVar2);
      uVar2 = 0xffffffff;
    }
    MWTRACE(1,s_TestForPacket_returning__ld_801e6804,uVar2);
  }
  return uVar2;
}

