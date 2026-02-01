// Function: TRKSuppAccessFile
// Entry: 801ab75c
// Size: 544 bytes

int TRKSuppAccessFile(int param_1,int param_2,uint *param_3,uint *param_4,int param_5,int param_6)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int unaff_r22;
  uint uVar7;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  int local_7c;
  undefined local_78;
  int local_74;
  undefined2 local_70;
  
  if ((param_2 == 0) || (*param_3 == 0)) {
    iVar4 = 2;
  }
  else {
    bVar1 = false;
    *param_4 = 0;
    uVar7 = 0;
    iVar4 = 0;
    while ((((!bVar1 && (uVar7 < *param_3)) && (iVar4 == 0)) && (*param_4 == 0))) {
      memset(&local_7c,0,0x40);
      uVar5 = 0x800;
      if (*param_3 - uVar7 < 0x801) {
        uVar5 = *param_3 - uVar7;
      }
      local_78 = 0xd0;
      if (param_6 != 0) {
        local_78 = 0xd1;
      }
      local_7c = 0x40;
      if (param_6 == 0) {
        local_7c = uVar5 + 0x40;
      }
      local_70 = (undefined2)uVar5;
      local_74 = param_1;
      TRKGetFreeBuffer(&local_84,&local_88);
      iVar4 = TRKAppendBuffer_ui8(local_88,&local_7c,0x40);
      if ((param_6 == 0) && (iVar4 == 0)) {
        iVar4 = TRKAppendBuffer_ui8(local_88,param_2 + uVar7,uVar5);
      }
      if (iVar4 == 0) {
        if (param_5 == 0) {
          iVar4 = TRKMessageSend(local_88);
        }
        else {
          uVar2 = 0;
          if ((param_6 != 0) && (param_1 == 0)) {
            uVar2 = 1;
          }
          uVar3 = countLeadingZeros(uVar2);
          iVar4 = TRKRequestSend(local_88,&local_80,5,3,uVar3 >> 5);
          if (iVar4 == 0) {
            unaff_r22 = TRKGetBuffer(local_80);
          }
          uVar3 = *(uint *)(unaff_r22 + 0x20);
          uVar6 = (uint)*(ushort *)(unaff_r22 + 0x24);
          if (((param_6 != 0) && (iVar4 == 0)) && (uVar6 <= uVar5)) {
            TRKSetBufferPosition(unaff_r22,0x40);
            iVar4 = TRKReadBuffer_ui8(unaff_r22,param_2 + uVar7,uVar6);
            if (iVar4 == 0x302) {
              iVar4 = 0;
            }
          }
          if (uVar6 != uVar5) {
            bVar1 = true;
            uVar5 = uVar6;
          }
          *param_4 = uVar3 & 0xff;
          TRKReleaseBuffer(local_80);
        }
      }
      TRKReleaseBuffer(local_84);
      uVar7 = uVar7 + uVar5;
    }
    *param_3 = uVar7;
  }
  return iVar4;
}

