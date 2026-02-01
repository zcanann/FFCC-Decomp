// Function: TRKDoReadRegisters
// Entry: 801aa8a8
// Size: 736 bytes

undefined4 TRKDoReadRegisters(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined uVar3;
  undefined auStack_d8 [4];
  undefined4 local_d4;
  undefined local_d0;
  undefined local_cc;
  undefined4 local_94;
  undefined local_90;
  undefined local_8c;
  undefined4 local_54;
  undefined local_50;
  
  if (*(ushort *)(param_1 + 0x20) < *(ushort *)(param_1 + 0x1c)) {
    memset(&local_94,0,0x40);
    local_90 = 0x80;
    local_94 = 0x40;
    local_8c = 0x14;
    TRKWriteUARTN(&local_94,0x40);
    return 0;
  }
  local_50 = 0x80;
  local_54 = 0x468;
  TRKResetBuffer(param_1,0);
  MWTRACE(4,s_DoReadRegisters___Buffer_length_0_801e6900,*(undefined4 *)(param_1 + 8));
  TRKAppendBuffer_ui8(param_1,&local_54,0x40);
  MWTRACE(4,s_DoReadRegisters___Buffer_length_0_801e6900,*(undefined4 *)(param_1 + 8));
  iVar1 = TRKTargetAccessDefault(0,0x24,param_1,auStack_d8,1);
  MWTRACE(4,s_DoReadRegisters___Error_reading_d_801e6928,iVar1);
  MWTRACE(4,s_DoReadRegisters___Buffer_length_0_801e6900,*(undefined4 *)(param_1 + 8));
  if (iVar1 == 0) {
    iVar1 = TRKTargetAccessFP(0,0x21,param_1,auStack_d8,1);
  }
  MWTRACE(4,s_DoReadRegisters___Error_FP_regs_0_801e6960,iVar1);
  MWTRACE(4,s_DoReadRegisters___Buffer_length_0_801e6900,*(undefined4 *)(param_1 + 8));
  if (iVar1 == 0) {
    iVar1 = TRKTargetAccessExtended1(0,0x60,param_1,auStack_d8,1);
  }
  MWTRACE(4,s_DoReadRegisters___Error_extended_801e6988,iVar1);
  MWTRACE(4,s_DoReadRegisters___Buffer_length_0_801e6900,*(undefined4 *)(param_1 + 8));
  if (iVar1 == 0) {
    iVar1 = TRKTargetAccessExtended2(0,0x1f,param_1,auStack_d8,1);
  }
  MWTRACE(4,s_DoReadRegisters___Error_extended_801e69b8,iVar1);
  MWTRACE(4,s_DoReadRegisters___Buffer_length_0_801e6900,*(undefined4 *)(param_1 + 8));
  if (iVar1 == 0) {
    MWTRACE(1,s_SendACK___Calling_MessageSend_801e68c8);
    uVar2 = TRKMessageSend(param_1);
    MWTRACE(1,s_MessageSend_err____ld_801e68e8,uVar2);
    return uVar2;
  }
  if (iVar1 == 0x704) {
    uVar3 = 0x21;
    goto LAB_801aab00;
  }
  if (iVar1 < 0x704) {
    if (iVar1 == 0x702) {
      uVar3 = 0x15;
      goto LAB_801aab00;
    }
    if (0x701 < iVar1) {
      uVar3 = 0x12;
      goto LAB_801aab00;
    }
    if (0x700 < iVar1) {
      uVar3 = 0x14;
      goto LAB_801aab00;
    }
  }
  else {
    if (iVar1 == 0x706) {
      uVar3 = 0x20;
      goto LAB_801aab00;
    }
    if (iVar1 < 0x706) {
      uVar3 = 0x22;
      goto LAB_801aab00;
    }
  }
  uVar3 = 3;
LAB_801aab00:
  memset(&local_d4,0,0x40);
  local_d0 = 0x80;
  local_d4 = 0x40;
  local_cc = uVar3;
  TRKWriteUARTN(&local_d4,0x40);
  return 0;
}

