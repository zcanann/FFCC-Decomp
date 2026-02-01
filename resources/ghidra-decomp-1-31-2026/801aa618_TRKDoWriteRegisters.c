// Function: TRKDoWriteRegisters
// Entry: 801aa618
// Size: 656 bytes

/* WARNING: Removing unreachable block (ram,0x801aa6b4) */

undefined4 TRKDoWriteRegisters(int param_1)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined uVar6;
  undefined auStack_d8 [4];
  undefined4 local_d4;
  undefined local_d0;
  undefined local_cc;
  undefined4 local_94;
  undefined local_90;
  undefined local_8c;
  undefined4 local_54;
  undefined local_50;
  undefined local_4c;
  
  bVar1 = *(byte *)(param_1 + 0x18);
  uVar2 = *(ushort *)(param_1 + 0x1c);
  uVar3 = *(ushort *)(param_1 + 0x20);
  TRKSetBufferPosition(param_1,0);
  if (uVar3 < uVar2) {
    memset(&local_94,0,0x40);
    local_90 = 0x80;
    local_94 = 0x40;
    local_8c = 0x14;
    TRKWriteUARTN(&local_94,0x40);
    return 0;
  }
  TRKSetBufferPosition(param_1,0x40);
  if (bVar1 == 2) {
    iVar5 = TRKTargetAccessExtended1(uVar2,uVar3,param_1,auStack_d8,0);
  }
  else if (bVar1 < 2) {
    if (bVar1 == 0) {
      iVar5 = TRKTargetAccessDefault(uVar2,uVar3,param_1,auStack_d8,0);
    }
    else {
      iVar5 = TRKTargetAccessFP(uVar2,uVar3,param_1,auStack_d8,0);
    }
  }
  else if (bVar1 < 4) {
    iVar5 = TRKTargetAccessExtended2(uVar2,uVar3,param_1,auStack_d8,0);
  }
  else {
    iVar5 = 0x703;
  }
  TRKResetBuffer(param_1,0);
  if (iVar5 == 0) {
    memset(&local_54,0,0x40);
    local_54 = 0x40;
    local_50 = 0x80;
    local_4c = 0;
    iVar5 = TRKAppendBuffer(param_1,&local_54,0x40);
  }
  if (iVar5 == 0) {
    MWTRACE(1,s_SendACK___Calling_MessageSend_801e68c8);
    uVar4 = TRKMessageSend(param_1);
    MWTRACE(1,s_MessageSend_err____ld_801e68e8,uVar4);
    return uVar4;
  }
  if (iVar5 == 0x703) {
    uVar6 = 0x12;
    goto LAB_801aa814;
  }
  if (iVar5 < 0x703) {
    if (iVar5 == 0x701) {
      uVar6 = 0x14;
      goto LAB_801aa814;
    }
    if (0x700 < iVar5) {
      uVar6 = 0x15;
      goto LAB_801aa814;
    }
    if (iVar5 == 0x302) {
      uVar6 = 2;
      goto LAB_801aa814;
    }
  }
  else {
    if (iVar5 == 0x706) {
      uVar6 = 0x20;
      goto LAB_801aa814;
    }
    if (iVar5 < 0x706) {
      if (iVar5 < 0x705) {
        uVar6 = 0x21;
      }
      else {
        uVar6 = 0x22;
      }
      goto LAB_801aa814;
    }
  }
  uVar6 = 3;
LAB_801aa814:
  memset(&local_d4,0,0x40);
  local_d0 = 0x80;
  local_d4 = 0x40;
  local_cc = uVar6;
  TRKWriteUARTN(&local_d4,0x40);
  return 0;
}

