// Function: MakeJoyData__6JoyBusFPciPUi
// Entry: 800ab24c
// Size: 420 bytes

int MakeJoyData__6JoyBusFPciPUi(JoyBus *joyBus,byte *source,int length,undefined *outBuffer)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  undefined *puVar6;
  int iVar7;
  uint uVar8;
  undefined local_8;
  undefined uStack_7;
  
  uVar5 = 0xffff;
  iVar7 = length;
  pbVar4 = source;
  while (iVar7 = iVar7 + -1, -1 < iVar7) {
    bVar2 = *pbVar4;
    pbVar4 = pbVar4 + 1;
    uVar5 = (uVar5 << 8 ^ (uint)JoyBusCrcTable[uVar5 >> 8 ^ (uint)bVar2]) & 0xffff;
  }
  iVar7 = (length + -1) / 3;
  *outBuffer = 5;
  if (length + -1 != iVar7 * 3) {
    iVar7 = iVar7 + 1;
  }
  iVar3 = iVar7 + 2;
  if (iVar3 < 0x100) {
    outBuffer[1] = (char)iVar3;
    uStack_7 = (undefined)~(ushort)uVar5;
    local_8 = (undefined)((ushort)~(ushort)uVar5 >> 8);
    *(ushort *)(outBuffer + 2) = CONCAT11(uStack_7,local_8);
    puVar6 = outBuffer + 8;
    outBuffer[4] = 0x45;
    pbVar4 = source + 1;
    outBuffer[5] = (char)length;
    outBuffer[6] = (char)((uint)length >> 8);
    outBuffer[7] = *source;
    uVar5 = iVar7 + 1;
    if (1 < iVar3) {
      uVar8 = uVar5 >> 2;
      if (uVar8 != 0) {
        do {
          *puVar6 = 0x85;
          puVar6[1] = *pbVar4;
          puVar6[2] = pbVar4[1];
          puVar6[3] = pbVar4[2];
          puVar6[4] = 0x85;
          puVar6[5] = pbVar4[3];
          puVar6[6] = pbVar4[4];
          puVar6[7] = pbVar4[5];
          puVar6[8] = 0x85;
          puVar6[9] = pbVar4[6];
          puVar6[10] = pbVar4[7];
          puVar6[0xb] = pbVar4[8];
          puVar6[0xc] = 0x85;
          puVar6[0xd] = pbVar4[9];
          puVar6[0xe] = pbVar4[10];
          pbVar1 = pbVar4 + 0xb;
          pbVar4 = pbVar4 + 0xc;
          puVar6[0xf] = *pbVar1;
          puVar6 = puVar6 + 0x10;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar5 = uVar5 & 3;
        if (uVar5 == 0) {
          return iVar3;
        }
      }
      do {
        *puVar6 = 0x85;
        puVar6[1] = *pbVar4;
        puVar6[2] = pbVar4[1];
        pbVar1 = pbVar4 + 2;
        pbVar4 = pbVar4 + 3;
        puVar6[3] = *pbVar1;
        puVar6 = puVar6 + 4;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
  }
  else {
    iVar3 = -1;
  }
  return iVar3;
}

