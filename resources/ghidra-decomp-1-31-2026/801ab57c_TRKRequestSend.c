// Function: TRKRequestSend
// Entry: 801ab57c
// Size: 480 bytes

int TRKRequestSend(undefined4 param_1,int *param_2,undefined4 param_3,int param_4,int param_5)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  uint unaff_r26;
  uint unaff_r28;
  int unaff_r29;
  int iVar4;
  
  param_4 = param_4 + 1;
  iVar4 = 0;
  bVar2 = true;
  *param_2 = -1;
LAB_801ab718:
  if (((param_4 == 0) || (*param_2 != -1)) || (iVar4 != 0)) {
    if (*param_2 == -1) {
      iVar4 = 0x800;
    }
    return iVar4;
  }
  MWTRACE(1,s_Calling_MessageSend_801e6a50);
  iVar4 = TRKMessageSend(param_1);
  if (iVar4 == 0) {
    if (param_5 != 0) {
      unaff_r28 = 0;
    }
LAB_801ab5e4:
    iVar3 = TRKTestForPacket();
    *param_2 = iVar3;
    if (*param_2 == -1) goto code_r0x801ab5f8;
    goto LAB_801ab614;
  }
  goto LAB_801ab714;
code_r0x801ab5f8:
  if ((param_5 == 0) || (unaff_r28 = unaff_r28 + 1, unaff_r28 < 0x4c4b3ec)) goto LAB_801ab5e4;
LAB_801ab614:
  if (*param_2 != -1) {
    bVar2 = false;
    unaff_r29 = TRKGetBuffer();
    TRKSetBufferPosition(unaff_r29,0);
    OutputData(unaff_r29 + 0x10,*(undefined4 *)(unaff_r29 + 8));
    unaff_r26 = (uint)*(byte *)(unaff_r29 + 0x14);
    MWTRACE(1,s_msg_command___0x_02x_hdr_>cmdID_0_801e6a68,unaff_r26,unaff_r26);
    if (0x7f < unaff_r26) goto LAB_801ab674;
    TRKProcessInput(*param_2);
    *param_2 = -1;
    goto LAB_801ab5e4;
  }
LAB_801ab674:
  if (*param_2 != -1) {
    if (*(uint *)(unaff_r29 + 8) < 0x40) {
      bVar2 = true;
    }
    if (!bVar2) {
      cVar1 = *(char *)(unaff_r29 + 0x18);
      MWTRACE(1,s_msg_error___0x_02x_801e6a90,cVar1);
      if ((unaff_r26 != 0x80) || (cVar1 != '\0')) {
        MWTRACE(8,s_RequestSend___Bad_ack_or_non_ack_801e6aa4,unaff_r26,cVar1);
        bVar2 = true;
      }
    }
    if (bVar2) {
      TRKReleaseBuffer(*param_2);
      *param_2 = -1;
    }
  }
LAB_801ab714:
  param_4 = param_4 + -1;
  goto LAB_801ab718;
}

