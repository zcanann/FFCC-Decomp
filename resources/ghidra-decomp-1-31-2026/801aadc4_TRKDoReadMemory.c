// Function: TRKDoReadMemory
// Entry: 801aadc4
// Size: 580 bytes

/* WARNING: Type propagation algorithm not settling */

undefined4 TRKDoReadMemory(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined uVar6;
  uint auStack_920 [2];
  undefined uStack_918;
  undefined uStack_914;
  undefined4 uStack_8dc;
  undefined uStack_8d8;
  undefined uStack_8d4;
  int iStack_89c;
  undefined uStack_898;
  undefined uStack_894;
  undefined auStack_840 [2088];
  
  uVar4 = *(uint *)(param_1 + 0x20);
  uVar5 = (uint)*(ushort *)(param_1 + 0x1c);
  bVar1 = *(byte *)(param_1 + 0x18);
  MWTRACE(1,s_ReadMemory__0x_02x____0x_08x_0x__801e6a18,*(undefined *)(param_1 + 0x14),uVar4,uVar5,
          bVar1);
  if ((bVar1 & 2) == 0) {
    auStack_920[0] = uVar5;
    if ((bVar1 & 0x40) == 0) {
      iVar3 = TRKTargetAccessMemory(auStack_840,uVar4,auStack_920,bVar1 >> 3 & 1 ^ 1,1);
    }
    else {
      iVar3 = TRKTargetAccessARAM(auStack_840,uVar4,auStack_920,1);
    }
    TRKResetBuffer(param_1,0);
    if (iVar3 == 0) {
      memset(&iStack_89c,0,0x40);
      uStack_894 = 0;
      iStack_89c = auStack_920[0] + 0x40;
      uStack_898 = 0x80;
      TRKAppendBuffer(param_1,&iStack_89c,0x40);
      if ((bVar1 & 0x40) == 0) {
        iVar3 = TRKAppendBuffer(param_1,auStack_840,auStack_920[0]);
      }
      else {
        iVar3 = TRKAppendBuffer(param_1,auStack_840 + (uVar4 & 0x1f),auStack_920[0]);
      }
    }
    if (iVar3 == 0) {
      MWTRACE(1,s_SendACK___Calling_MessageSend_801e68c8);
      uVar2 = TRKMessageSend(param_1);
      MWTRACE(1,s_MessageSend_err____ld_801e68e8,uVar2);
    }
    else {
      switch(iVar3) {
      case 0x700:
        uVar6 = 0x13;
        break;
      default:
        uVar6 = 3;
        break;
      case 0x702:
        uVar6 = 0x15;
        break;
      case 0x704:
        uVar6 = 0x21;
        break;
      case 0x705:
        uVar6 = 0x22;
        break;
      case 0x706:
        uVar6 = 0x20;
      }
      memset(auStack_920 + 1,0,0x40);
      uStack_918 = 0x80;
      auStack_920[1] = 0x40;
      uStack_914 = uVar6;
      TRKWriteUARTN(auStack_920 + 1,0x40);
      uVar2 = 0;
    }
  }
  else {
    memset(&uStack_8dc,0,0x40);
    uStack_8d8 = 0x80;
    uStack_8dc = 0x40;
    uStack_8d4 = 0x12;
    TRKWriteUARTN(&uStack_8dc,0x40);
    uVar2 = 0;
  }
  return uVar2;
}

