// Function: _ArrangeStreamDataNoLoop__FP13RedStreamDATAii
// Entry: 801cba90
// Size: 476 bytes

undefined4 _ArrangeStreamDataNoLoop__FP13RedStreamDATAii(int param_1,uint param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  byte *dstBuffer;
  int iVar3;
  
  param_2 = param_2 & 1;
  do {
    dstBuffer = (byte *)(*(int *)(param_1 + 0xc) + param_2 * 0x1000);
    iVar3 = *(int *)(param_1 + 4);
    memcpy(dstBuffer,*(int *)(param_1 + 8) + *(int *)(param_1 + 0x120),0x1000);
    *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + 0x1000;
    if (*(int *)(param_1 + 0x118) <= *(int *)(param_1 + 0x120)) {
      *(undefined4 *)(param_1 + 0x120) = 0;
    }
    if (*(short *)(param_1 + 0x2a) == 2) {
      memcpy(dstBuffer + 0x2000,*(int *)(param_1 + 8) + *(int *)(param_1 + 0x120),0x1000);
      *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + 0x1000;
      if (*(int *)(param_1 + 0x118) <= *(int *)(param_1 + 0x120)) {
        *(undefined4 *)(param_1 + 0x120) = 0;
      }
    }
    iVar2 = *(int *)(param_1 + 300) + param_2 * 0x1000;
    uVar1 = RedDmaEntry__FiiiiiPFPv_vPv(0x8001,0,dstBuffer,iVar2,0x1000,(void *)0x0,(void *)0x0);
    if ((param_2 == 0) && (*(int *)(iVar3 + 0x14) != 0)) {
      *(ushort *)(*(int *)(iVar3 + 0x14) + 0x1ec) = (ushort)*dstBuffer;
      *(undefined2 *)(*(int *)(iVar3 + 0x14) + 0x1f0) = 0;
      *(undefined2 *)(*(int *)(iVar3 + 0x14) + 0x1ee) = 0;
      *(uint *)(*(int *)(iVar3 + 0x14) + 0x1c) = *(uint *)(*(int *)(iVar3 + 0x14) + 0x1c) | 0x100000
      ;
    }
    if (*(short *)(param_1 + 0x2a) == 2) {
      uVar1 = RedDmaEntry__FiiiiiPFPv_vPv
                        (0x8001,0,dstBuffer + 0x2000,iVar2 + 0x2000,0x1000,(void *)0x0,(void *)0x0);
      if ((param_2 == 0) && (*(int *)(iVar3 + 0xd4) != 0)) {
        *(ushort *)(*(int *)(iVar3 + 0xd4) + 0x1ec) = (ushort)dstBuffer[0x2000];
        *(undefined2 *)(*(int *)(iVar3 + 0xd4) + 0x1f0) = 0;
        *(undefined2 *)(*(int *)(iVar3 + 0xd4) + 0x1ee) = 0;
        *(uint *)(*(int *)(iVar3 + 0xd4) + 0x1c) =
             *(uint *)(*(int *)(iVar3 + 0xd4) + 0x1c) | 0x100000;
      }
    }
    param_3 = param_3 + -0x1000;
    param_2 = param_2 ^ 1;
    *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) + 0x200;
  } while (0 < param_3);
  return uVar1;
}

