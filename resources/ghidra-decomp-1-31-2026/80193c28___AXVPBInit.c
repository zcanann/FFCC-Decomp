// Function: __AXVPBInit
// Entry: 80193c28
// Size: 508 bytes

void __AXVPBInit(void)

{
  undefined4 *puVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  
  puVar6 = (undefined4 *)&DAT_80314940;
  DAT_8032f290 = DAT_800000f8 / 400;
  DAT_8032f294 = 0;
  iVar7 = 0x1d8;
  puVar1 = puVar6;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1 = puVar1 + 8;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  iVar7 = 0x80;
  puVar1 = &DAT_80318440;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1 = puVar1 + 8;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  iVar7 = 0x448;
  puVar1 = &DAT_8031d440;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1 = puVar1 + 8;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar5 = &DAT_80318440;
  puVar4 = &DAT_80319440;
  uVar3 = 0;
  puVar1 = &DAT_8031d440;
  do {
    puVar1[6] = uVar3;
    puVar1[0xc] = puVar1 + 0xd;
    puVar1[0x4d] = puVar5;
    *(undefined2 *)((int)puVar1 + 0x146) = 0;
    *(undefined2 *)((int)puVar1 + 0x16e) = 0;
    puVar1[7] = 0xa4;
    puVar1[10] = 0;
    puVar1[9] = 0;
    puVar1[0xc] = puVar1 + 0xd;
    *(undefined2 *)(puVar1 + 0x61) = 0;
    *(undefined2 *)((int)puVar1 + 0x182) = 0;
    *(undefined2 *)(puVar1 + 0x60) = 0;
    *(undefined2 *)((int)puVar1 + 0x17e) = 0;
    *(undefined2 *)(puVar1 + 0x5f) = 0;
    if (uVar3 == 0x3f) {
      *(undefined2 *)((int)puVar6 + 2) = 0;
      *(undefined2 *)puVar6 = 0;
      *(undefined2 *)((int)puVar1 + 0x13a) = 0;
      *(undefined2 *)(puVar1 + 0x4e) = 0;
    }
    else {
      puVar1[0x4e] = puVar6 + 0x3b;
      *puVar6 = puVar6 + 0x3b;
    }
    uVar2 = (undefined2)((uint)puVar6 >> 0x10);
    *(undefined2 *)(puVar1 + 0x4f) = uVar2;
    *(short *)((int)puVar1 + 0x13e) = (short)puVar6;
    *(undefined2 *)(puVar6 + 1) = uVar2;
    *(short *)((int)puVar6 + 6) = (short)puVar6;
    uVar2 = (undefined2)((uint)puVar5 >> 0x10);
    *(undefined2 *)(puVar1 + 0x5c) = uVar2;
    *(short *)((int)puVar1 + 0x172) = (short)puVar5;
    *(undefined2 *)(puVar6 + 0xe) = uVar2;
    *(short *)((int)puVar6 + 0x3a) = (short)puVar5;
    uVar2 = (undefined2)((uint)puVar4 >> 0x10);
    *(undefined2 *)((int)puVar1 + 0x186) = uVar2;
    *(short *)(puVar1 + 0x62) = (short)puVar4;
    *(undefined2 *)((int)puVar6 + 0x4e) = uVar2;
    *(short *)(puVar6 + 0x14) = (short)puVar4;
    puVar1[3] = 1;
    __AXPushFreeStack(puVar1);
    uVar3 = uVar3 + 1;
    puVar6 = puVar6 + 0x3b;
    puVar5 = puVar5 + 0x10;
    puVar4 = puVar4 + 0x100;
    puVar1 = puVar1 + 0x89;
  } while (uVar3 < 0x40);
  DCFlushRange(&DAT_80314940,0x3b00);
  return;
}

