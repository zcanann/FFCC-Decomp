// Function: Odekake__14CMemoryCardManFiRQ22Mc7SaveDatiRQ22Mc7SaveDati
// Entry: 800c18fc
// Size: 1572 bytes

void Odekake__14CMemoryCardManFiRQ22Mc7SaveDatiRQ22Mc7SaveDati
               (CMemoryCardMan *memoryCardMan,int param_2,byte *param_3,int param_4,byte *param_5,
               int param_6)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  byte *pbVar7;
  undefined *puVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  byte *pbVar12;
  int iVar13;
  
  if (2 < (uint)System.m_execParam) {
    puVar8 = &DAT_80330cd0;
    if (param_2 != 0) {
      puVar8 = &DAT_801dae6c;
    }
    Printf__7CSystemFPce(&System,&DAT_801dae28,param_4,param_6,puVar8);
  }
  pbVar12 = param_3 + param_4 * 0x9c0 + 0x14d0;
  pbVar11 = param_5 + param_6 * 0x9c0 + 0x14d0;
  if (param_2 == 0) {
    memcpy(pbVar11 + 0xbc,pbVar12 + 0xbc,0xc);
    pbVar7 = param_3 + param_4 * 0x208;
    iVar9 = 2;
    do {
      pbVar7[0xc0] = 0;
      pbVar7[0xc1] = 0;
      pbVar7[0xc2] = 0;
      pbVar7[0xc3] = 0;
      pbVar7[0xc4] = 0;
      pbVar7[0xc5] = 0;
      pbVar7[0xc6] = 0;
      pbVar7[199] = 0;
      pbVar7[0x100] = 0;
      pbVar7[0x101] = 0;
      pbVar7[0x102] = 0;
      pbVar7[0x103] = 0;
      pbVar7[0x104] = 0;
      pbVar7[0x105] = 0;
      pbVar7[0x106] = 0;
      pbVar7[0x107] = 0;
      pbVar7[0x140] = 0;
      pbVar7[0x141] = 0;
      pbVar7[0x142] = 0;
      pbVar7[0x143] = 0;
      pbVar7[0x144] = 0;
      pbVar7[0x145] = 0;
      pbVar7[0x146] = 0;
      pbVar7[0x147] = 0;
      pbVar7[0x180] = 0;
      pbVar7[0x181] = 0;
      pbVar7[0x182] = 0;
      pbVar7[0x183] = 0;
      pbVar7[0x184] = 0;
      pbVar7[0x185] = 0;
      pbVar7[0x186] = 0;
      pbVar7[0x187] = 0;
      pbVar7 = pbVar7 + 0x100;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    pbVar11[0x8c0] = 0;
    pbVar12[0x8c2] = 0;
    memset(pbVar12,0,0x9c0);
    pbVar11[0x6c2] = 0;
    pbVar11[0x6c3] = 0xc;
  }
  else {
    memset(pbVar11,0,0x9c0);
    *(undefined2 *)pbVar11 = *(undefined2 *)pbVar12;
    *(undefined2 *)(pbVar11 + 2) = *(undefined2 *)(pbVar12 + 2);
    *(undefined2 *)(pbVar11 + 4) = *(undefined2 *)(pbVar12 + 4);
    *(undefined2 *)(pbVar11 + 6) = *(undefined2 *)(pbVar12 + 6);
    *(undefined2 *)(pbVar11 + 8) = *(undefined2 *)(pbVar12 + 8);
    *(undefined2 *)(pbVar11 + 10) = *(undefined2 *)(pbVar12 + 10);
    *(undefined2 *)(pbVar11 + 0xc) = *(undefined2 *)(pbVar12 + 0xc);
    *(undefined2 *)(pbVar11 + 0xe) = *(undefined2 *)(pbVar12 + 0xe);
    *(undefined2 *)(pbVar11 + 0x10) = *(undefined2 *)(pbVar12 + 0x10);
    memcpy(pbVar11 + 0x12,pbVar12 + 0x12,0x12);
    *(undefined2 *)(pbVar11 + 0x24) = *(undefined2 *)(pbVar12 + 0x24);
    *(undefined2 *)(pbVar11 + 0x26) = *(undefined2 *)(pbVar12 + 0x26);
    *(undefined2 *)(pbVar11 + 0x2a) = *(undefined2 *)(pbVar12 + 0x2a);
    *(undefined2 *)(pbVar11 + 0x2c) = *(undefined2 *)(pbVar12 + 0x2c);
    *(undefined2 *)(pbVar11 + 0x2e) = *(undefined2 *)(pbVar12 + 0x2e);
    *(undefined2 *)(pbVar11 + 0x30) = *(undefined2 *)(pbVar12 + 0x30);
    *(undefined2 *)(pbVar11 + 0x32) = *(undefined2 *)(pbVar12 + 0x32);
    memcpy(pbVar11 + 0x34,pbVar12 + 0x34,8);
    memcpy(pbVar11 + 0xbc,pbVar12 + 0xbc,0xc);
    *(undefined4 *)(pbVar11 + 0xe8) = *(undefined4 *)(pbVar12 + 0xe8);
    memcpy(pbVar11 + 0xf0,pbVar12 + 0xf0,0x10);
    *(undefined4 *)(pbVar11 + 0x5b4) = *(undefined4 *)(pbVar12 + 0x5b4);
    memcpy(pbVar11 + 0x5b8,pbVar12 + 0x5b8,0x100);
    memcpy(pbVar11 + 0x6b8,pbVar12 + 0x6b8,0x200);
    pbVar7 = param_5 + param_6 * 0x200;
    *(undefined4 *)(pbVar11 + 0x8b8) = *(undefined4 *)(pbVar12 + 0x8b8);
    iVar9 = 0;
    *(undefined4 *)(pbVar11 + 0x8bc) = *(undefined4 *)(pbVar12 + 0x8bc);
    pbVar11[0x8c2] = pbVar12[0x8c2];
    *(undefined4 *)(pbVar11 + 0x8c4) = *(undefined4 *)(pbVar12 + 0x8c4);
    uVar2 = *(undefined4 *)(param_3 + 0x13d0);
    *(undefined4 *)(pbVar11 + 0x8cc) = *(undefined4 *)(param_3 + 0x13d4);
    *(undefined4 *)(pbVar11 + 0x8c8) = uVar2;
    *(undefined4 *)(pbVar11 + 0x8d0) = *(undefined4 *)(param_3 + 0x13d8);
    do {
      pbVar5 = pbVar7 + param_6 * 8;
      iVar10 = 0;
      iVar13 = 2;
      do {
        iVar3 = 0;
        if ((iVar9 == 0) && (iVar10 == 0)) {
          iVar3 = 1;
        }
        iVar4 = 0;
        pbVar5[0xc0] = (byte)(-iVar3 >> 0x1f) & 0x32;
        if ((iVar9 == 0) && (iVar10 == -1)) {
          iVar4 = 1;
        }
        iVar3 = 0;
        pbVar5[0xc1] = (byte)(-iVar4 >> 0x1f) & 0x32;
        if ((iVar9 == 0) && (iVar10 == -2)) {
          iVar3 = 1;
        }
        iVar4 = 0;
        pbVar5[0xc2] = (byte)(-iVar3 >> 0x1f) & 0x32;
        if ((iVar9 == 0) && (iVar10 == -3)) {
          iVar4 = 1;
        }
        iVar10 = iVar10 + 4;
        pbVar5[0xc3] = (byte)(-iVar4 >> 0x1f) & 0x32;
        pbVar5 = pbVar5 + 4;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
      iVar9 = iVar9 + 1;
      pbVar7 = pbVar7 + 0x40;
    } while (iVar9 < 8);
    memset(pbVar11 + 200,0xff,0x10);
    memset(pbVar11 + 0xd8,0,0x10);
    pbVar11[0x28] = 0;
    pbVar11[0x29] = 0;
    memset(pbVar11 + 0x3c,0xff,0x80);
    iVar9 = (int)*(short *)(pbVar11 + 0x34);
    if ((-1 < iVar9) && (iVar9 < 0x40)) {
      iVar9 = iVar9 * 2 + 0x3c;
      *(undefined2 *)(pbVar11 + iVar9) = *(undefined2 *)(pbVar12 + iVar9);
      *(short *)(pbVar11 + 0x28) = *(short *)(pbVar11 + 0x28) + 1;
    }
    iVar9 = (int)*(short *)(pbVar11 + 0x36);
    if ((-1 < iVar9) && (iVar9 < 0x40)) {
      iVar9 = iVar9 * 2 + 0x3c;
      *(undefined2 *)(pbVar11 + iVar9) = *(undefined2 *)(pbVar12 + iVar9);
      *(short *)(pbVar11 + 0x28) = *(short *)(pbVar11 + 0x28) + 1;
    }
    iVar9 = (int)*(short *)(pbVar11 + 0x38);
    if ((-1 < iVar9) && (iVar9 < 0x40)) {
      iVar9 = iVar9 * 2 + 0x3c;
      *(undefined2 *)(pbVar11 + iVar9) = *(undefined2 *)(pbVar12 + iVar9);
      *(short *)(pbVar11 + 0x28) = *(short *)(pbVar11 + 0x28) + 1;
    }
    iVar9 = (int)*(short *)(pbVar11 + 0x3a);
    if ((-1 < iVar9) && (iVar9 < 0x40)) {
      iVar9 = iVar9 * 2 + 0x3c;
      *(undefined2 *)(pbVar11 + iVar9) = *(undefined2 *)(pbVar12 + iVar9);
      *(short *)(pbVar11 + 0x28) = *(short *)(pbVar11 + 0x28) + 1;
    }
    pbVar12[0x8c0] = 1;
    pbVar11[0x8c1] = 1;
    pbVar11[0x6c2] = 0;
    pbVar11[0x6c3] = 3;
  }
  uVar2 = Rand__5CMathFUl(&Math,0x7fffffff);
  *(undefined4 *)(param_3 + 0x18) = uVar2;
  pbVar11 = param_3;
  if (param_3 == (byte *)0x0) {
    pbVar11 = memoryCardMan->m_saveBuffer;
  }
  uVar6 = 0xffffffff;
  iVar9 = 0x1c;
  pbVar12 = pbVar11;
  while (iVar9 = iVar9 + -1, -1 < iVar9) {
    bVar1 = *pbVar12;
    pbVar12 = pbVar12 + 1;
    uVar6 = uVar6 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar6 >> 0x18 ^ (uint)bVar1) * 4);
  }
  pbVar11 = pbVar11 + 0x20;
  iVar9 = 0x8bb0;
  while (iVar9 = iVar9 + -1, -1 < iVar9) {
    bVar1 = *pbVar11;
    pbVar11 = pbVar11 + 1;
    uVar6 = uVar6 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar6 >> 0x18 ^ (uint)bVar1) * 4);
  }
  *(uint *)(param_3 + 0x1c) = ~uVar6;
  uVar2 = Rand__5CMathFUl(&Math,0x7fffffff);
  *(undefined4 *)(param_5 + 0x18) = uVar2;
  pbVar11 = param_5;
  if (param_5 == (byte *)0x0) {
    pbVar11 = memoryCardMan->m_saveBuffer;
  }
  uVar6 = 0xffffffff;
  iVar9 = 0x1c;
  pbVar12 = pbVar11;
  while (iVar9 = iVar9 + -1, -1 < iVar9) {
    bVar1 = *pbVar12;
    pbVar12 = pbVar12 + 1;
    uVar6 = uVar6 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar6 >> 0x18 ^ (uint)bVar1) * 4);
  }
  pbVar11 = pbVar11 + 0x20;
  iVar9 = 0x8bb0;
  while (iVar9 = iVar9 + -1, -1 < iVar9) {
    bVar1 = *pbVar11;
    pbVar11 = pbVar11 + 1;
    uVar6 = uVar6 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar6 >> 0x18 ^ (uint)bVar1) * 4);
  }
  *(uint *)(param_5 + 0x1c) = ~uVar6;
  return;
}

