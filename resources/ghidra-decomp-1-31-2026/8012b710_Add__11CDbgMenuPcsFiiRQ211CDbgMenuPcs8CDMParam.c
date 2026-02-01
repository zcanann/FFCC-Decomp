// Function: Add__11CDbgMenuPcsFiiRQ211CDbgMenuPcs8CDMParam
// Entry: 8012b710
// Size: 432 bytes

void Add__11CDbgMenuPcsFiiRQ211CDbgMenuPcs8CDMParam
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  iVar3 = searchID__11CDbgMenuPcsFiRQ211CDbgMenuPcs3CDM(param_1,param_2,param_1 + 8);
  iVar4 = 0;
  iVar6 = 0x80;
  iVar2 = param_1;
  do {
    if (-1 < (int)((uint)*(byte *)(iVar2 + 0x90) << 0x18)) {
      puVar5 = (undefined4 *)(param_1 + iVar4 * 0x54 + 0x5c);
      goto LAB_8012b77c;
    }
    iVar2 = iVar2 + 0x54;
    iVar4 = iVar4 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  puVar5 = (undefined4 *)0x0;
LAB_8012b77c:
  memset(puVar5 + 0xd,0,0x20);
  *(byte *)(puVar5 + 0xd) = *(byte *)(puVar5 + 0xd) & 0x7f | 0x80;
  *puVar5 = *param_4;
  puVar5[1] = param_4[1];
  puVar5[2] = param_4[2];
  puVar5[3] = param_4[3];
  puVar5[4] = param_4[4];
  puVar5[5] = param_4[5];
  puVar5[6] = param_4[6];
  puVar5[7] = param_4[7];
  puVar5[8] = param_4[8];
  puVar5[9] = param_4[9];
  puVar5[10] = param_4[10];
  puVar5[0xb] = param_4[0xb];
  puVar5[0xc] = param_4[0xc];
  puVar5[0x13] = iVar3;
  puVar5[0x11] = puVar5;
  puVar5[0x12] = puVar5;
  puVar5[0xe] = param_3;
  iVar2 = *(int *)(iVar3 + 0x50);
  if (iVar2 == 0) {
    *(undefined4 **)(iVar3 + 0x50) = puVar5;
    if ((puVar5[1] & 1) != 0) {
      *(byte *)(puVar5 + 0xd) = *(byte *)(puVar5 + 0xd) & 0xbf | 0x40;
      *(undefined4 **)(param_1 + 0x2a64) = puVar5;
    }
    if ((puVar5[1] & 2) != 0) {
      *(undefined4 **)(param_1 + 0x2a60) = puVar5;
    }
  }
  else {
    bVar1 = false;
    do {
      if ((!bVar1) && ((*(uint *)(iVar2 + 4) & 1) != 0)) {
        bVar1 = true;
        *(byte *)(iVar2 + 0x34) = *(byte *)(iVar2 + 0x34) & 0xbf | 0x40;
        *(int *)(param_1 + 0x2a64) = iVar2;
      }
      iVar2 = *(int *)(iVar2 + 0x48);
    } while (iVar2 != *(int *)(iVar3 + 0x50));
    *(undefined4 **)(*(int *)(iVar2 + 0x44) + 0x48) = puVar5;
    puVar5[0x11] = *(undefined4 *)(iVar2 + 0x44);
    *(undefined4 **)(iVar2 + 0x44) = puVar5;
    puVar5[0x12] = iVar2;
  }
  return;
}

