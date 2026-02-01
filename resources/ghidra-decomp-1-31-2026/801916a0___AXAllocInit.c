// Function: __AXAllocInit
// Entry: 801916a0
// Size: 180 bytes

void __AXAllocInit(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  DAT_8032f1e8 = 0;
  iVar3 = 2;
  puVar2 = &DAT_8030cd60;
  puVar1 = &DAT_8030cce0;
  do {
    *puVar2 = 0;
    *puVar1 = 0;
    puVar2[1] = 0;
    puVar1[1] = 0;
    puVar2[2] = 0;
    puVar1[2] = 0;
    puVar2[3] = 0;
    puVar1[3] = 0;
    puVar2[4] = 0;
    puVar1[4] = 0;
    puVar2[5] = 0;
    puVar1[5] = 0;
    puVar2[6] = 0;
    puVar1[6] = 0;
    puVar2[7] = 0;
    puVar1[7] = 0;
    puVar2[8] = 0;
    puVar1[8] = 0;
    puVar2[9] = 0;
    puVar1[9] = 0;
    puVar2[10] = 0;
    puVar1[10] = 0;
    puVar2[0xb] = 0;
    puVar1[0xb] = 0;
    puVar2[0xc] = 0;
    puVar1[0xc] = 0;
    puVar2[0xd] = 0;
    puVar1[0xd] = 0;
    puVar2[0xe] = 0;
    puVar1[0xe] = 0;
    puVar2[0xf] = 0;
    puVar2 = puVar2 + 0x10;
    puVar1[0xf] = 0;
    puVar1 = puVar1 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}

