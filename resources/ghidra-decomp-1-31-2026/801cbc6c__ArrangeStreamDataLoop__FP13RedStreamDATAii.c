// Function: _ArrangeStreamDataLoop__FP13RedStreamDATAii
// Entry: 801cbc6c
// Size: 856 bytes

undefined4 _ArrangeStreamDataLoop__FP13RedStreamDATAii(int param_1,uint param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined4 *puVar7;
  int iVar8;
  
  param_2 = param_2 & 1;
  if (*(short *)(param_1 + 0x2a) == 2) {
    do {
      pbVar6 = (byte *)(*(int *)(param_1 + 0xc) + param_2 * 0x1000);
      iVar8 = *(int *)(param_1 + 4);
      puVar7 = (undefined4 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x120));
      pbVar4 = pbVar6 + 0x2000;
      puVar3 = puVar7 + 0x400;
      pbVar5 = pbVar6;
      do {
        *(undefined4 *)pbVar5 = *puVar7;
        *(undefined4 *)(pbVar5 + 4) = puVar7[1];
        pbVar5 = pbVar5 + 8;
        *(undefined4 *)pbVar4 = puVar7[2];
        puVar1 = puVar7 + 3;
        puVar7 = puVar7 + 4;
        *(undefined4 *)(pbVar4 + 4) = *puVar1;
        pbVar4 = pbVar4 + 8;
      } while (puVar7 < puVar3);
      *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + 0x1000;
      if (*(int *)(param_1 + 0x118) <= *(int *)(param_1 + 0x120)) {
        *(undefined4 *)(param_1 + 0x120) = 0;
      }
      puVar7 = (undefined4 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x120));
      puVar3 = puVar7 + 0x400;
      do {
        *(undefined4 *)pbVar5 = *puVar7;
        *(undefined4 *)(pbVar5 + 4) = puVar7[1];
        pbVar5 = pbVar5 + 8;
        *(undefined4 *)pbVar4 = puVar7[2];
        puVar1 = puVar7 + 3;
        puVar7 = puVar7 + 4;
        *(undefined4 *)(pbVar4 + 4) = *puVar1;
        pbVar4 = pbVar4 + 8;
      } while (puVar7 < puVar3);
      *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + 0x1000;
      if (*(int *)(param_1 + 0x118) <= *(int *)(param_1 + 0x120)) {
        *(undefined4 *)(param_1 + 0x120) = 0;
      }
      RedDmaEntry__FiiiiiPFPv_vPv
                (0x8001,0,pbVar6,*(int *)(param_1 + 300) + param_2 * 0x1000,0x1000,(void *)0x0,
                 (void *)0x0);
      uVar2 = RedDmaEntry__FiiiiiPFPv_vPv
                        (0x8001,0,pbVar6 + 0x2000,*(int *)(param_1 + 300) + (param_2 + 2) * 0x1000,
                         0x1000,(void *)0x0,(void *)0x0);
      if ((param_2 == 0) && (*(int *)(iVar8 + 0x14) != 0)) {
        *(ushort *)(*(int *)(iVar8 + 0x14) + 0x1ec) = (ushort)*pbVar6;
        *(undefined2 *)(*(int *)(iVar8 + 0x14) + 0x1f0) = 0;
        *(undefined2 *)(*(int *)(iVar8 + 0x14) + 0x1ee) = 0;
        *(uint *)(*(int *)(iVar8 + 0x14) + 0x1c) =
             *(uint *)(*(int *)(iVar8 + 0x14) + 0x1c) | 0x100000;
        *(ushort *)(*(int *)(iVar8 + 0xd4) + 0x1ec) = (ushort)pbVar6[0x2000];
        *(undefined2 *)(*(int *)(iVar8 + 0xd4) + 0x1f0) = 0;
        *(undefined2 *)(*(int *)(iVar8 + 0xd4) + 0x1ee) = 0;
        *(uint *)(*(int *)(iVar8 + 0xd4) + 0x1c) =
             *(uint *)(*(int *)(iVar8 + 0xd4) + 0x1c) | 0x100000;
      }
      param_2 = param_2 ^ 1;
      param_3 = param_3 + -0x1000;
      *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) + 0x200;
      if (*(int *)(param_1 + 0x1c) <= *(int *)(param_1 + 0x124)) {
        *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) - *(int *)(param_1 + 0x1c);
        *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) + *(int *)(param_1 + 0x20);
      }
    } while (0 < param_3);
  }
  else {
    do {
      pbVar5 = (byte *)(*(int *)(param_1 + 0xc) + param_2 * 0x1000);
      iVar8 = *(int *)(param_1 + 4);
      memcpy(pbVar5,*(int *)(param_1 + 8) + *(int *)(param_1 + 0x120),0x1000);
      *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + 0x1000;
      if (*(int *)(param_1 + 0x118) <= *(int *)(param_1 + 0x120)) {
        *(undefined4 *)(param_1 + 0x120) = 0;
      }
      uVar2 = RedDmaEntry__FiiiiiPFPv_vPv
                        (0x8001,0,pbVar5,*(int *)(param_1 + 300) + param_2 * 0x1000,0x1000,
                         (void *)0x0,(void *)0x0);
      if ((param_2 == 0) && (*(int *)(iVar8 + 0x14) != 0)) {
        *(ushort *)(*(int *)(iVar8 + 0x14) + 0x1ec) = (ushort)*pbVar5;
        *(undefined2 *)(*(int *)(iVar8 + 0x14) + 0x1f0) = 0;
        *(undefined2 *)(*(int *)(iVar8 + 0x14) + 0x1ee) = 0;
        *(uint *)(*(int *)(iVar8 + 0x14) + 0x1c) =
             *(uint *)(*(int *)(iVar8 + 0x14) + 0x1c) | 0x100000;
      }
      param_2 = param_2 ^ 1;
      param_3 = param_3 + -0x1000;
      *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) + 0x200;
      if (*(int *)(param_1 + 0x1c) <= *(int *)(param_1 + 0x124)) {
        *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) - *(int *)(param_1 + 0x1c);
        *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) + *(int *)(param_1 + 0x20);
      }
    } while (0 < param_3);
  }
  return uVar2;
}

