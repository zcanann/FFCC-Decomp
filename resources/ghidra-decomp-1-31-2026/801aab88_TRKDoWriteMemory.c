// Function: TRKDoWriteMemory
// Entry: 801aab88
// Size: 572 bytes

/* WARNING: Type propagation algorithm not settling */

undefined4 TRKDoWriteMemory(int param_1)

{
  byte bVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined uVar6;
  uint auStack_920 [2];
  undefined uStack_918;
  undefined uStack_914;
  undefined4 uStack_8dc;
  undefined uStack_8d8;
  undefined uStack_8d4;
  undefined4 uStack_89c;
  undefined uStack_898;
  undefined uStack_894;
  undefined auStack_840 [2092];
  
  uVar5 = *(uint *)(param_1 + 0x20);
  uVar2 = *(ushort *)(param_1 + 0x1c);
  bVar1 = *(byte *)(param_1 + 0x18);
  MWTRACE(1,s_WriteMemory__0x_02x____0x_08x_0x_801e69e8,*(undefined *)(param_1 + 0x14),uVar5,
          (uint)uVar2,bVar1);
  if ((bVar1 & 2) == 0) {
    auStack_920[0] = (uint)uVar2;
    TRKSetBufferPosition(param_1,0x40);
    if ((bVar1 & 0x40) == 0) {
      TRKReadBuffer(param_1,auStack_840,auStack_920[0]);
      iVar4 = TRKTargetAccessMemory(auStack_840,uVar5,auStack_920,bVar1 >> 3 & 1 ^ 1,0);
    }
    else {
      TRKReadBuffer(param_1,auStack_840 + (uVar5 & 0x1f),auStack_920[0]);
      iVar4 = TRKTargetAccessARAM(auStack_840,uVar5,auStack_920,0);
    }
    TRKResetBuffer(param_1,0);
    if (iVar4 == 0) {
      memset(&uStack_89c,0,0x40);
      uStack_89c = 0x40;
      uStack_898 = 0x80;
      uStack_894 = 0;
      iVar4 = TRKAppendBuffer(param_1,&uStack_89c,0x40);
    }
    if (iVar4 == 0) {
      MWTRACE(1,s_SendACK___Calling_MessageSend_801e68c8);
      uVar3 = TRKMessageSend(param_1);
      MWTRACE(1,s_MessageSend_err____ld_801e68e8,uVar3);
    }
    else {
      switch(iVar4) {
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
      uVar3 = 0;
    }
  }
  else {
    memset(&uStack_8dc,0,0x40);
    uStack_8d8 = 0x80;
    uStack_8dc = 0x40;
    uStack_8d4 = 0x12;
    TRKWriteUARTN(&uStack_8dc,0x40);
    uVar3 = 0;
  }
  return uVar3;
}

