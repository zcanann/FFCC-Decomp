// Function: Calc__4CMesFv
// Entry: 800992d0
// Size: 368 bytes

void Calc__4CMesFv(int param_1)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 8) == 0) {
    return;
  }
  iVar4 = param_1 + 0xc;
  uVar6 = 0;
  for (iVar7 = 0; iVar7 < *(int *)(param_1 + 8); iVar7 = iVar7 + 1) {
    if ((int)(uint)*(ushort *)(iVar4 + 0xc) <= *(int *)(param_1 + 0x3c80)) {
      bVar3 = *(byte *)(iVar4 + 0xf) >> 4;
      bVar2 = (*(byte *)(iVar4 + 0xf) & 0xf) + 1;
      if (bVar2 < bVar3) {
        bVar3 = bVar2;
      }
      *(byte *)(iVar4 + 0xf) = bVar3 & 0xf | *(byte *)(iVar4 + 0xf) & 0xf0;
      uVar6 = (uint)*(byte *)(iVar4 + 0x13);
    }
    iVar4 = iVar4 + 0x14;
  }
  pbVar5 = (byte *)(param_1 + *(int *)(param_1 + 0x3c10) * 6 + 0x3c14);
  do {
    if ((int)uVar6 <= *(int *)(param_1 + 0x3c10)) {
      bVar1 = true;
LAB_800993f0:
      if (bVar1) {
        iVar7 = *(int *)(param_1 + 0x3c80) + 1;
        iVar4 = 0x7fff;
        if (iVar7 < 0x7fff) {
          iVar4 = iVar7;
        }
        *(int *)(param_1 + 0x3c80) = iVar4;
      }
      if (*(int *)(param_1 + 0x3cac) != 0) {
        iVar7 = *(int *)(param_1 + 0x3cbc) + 1;
        iVar4 = *(int *)(param_1 + 0x3cb8);
        if (iVar7 < *(int *)(param_1 + 0x3cb8)) {
          iVar4 = iVar7;
        }
        *(int *)(param_1 + 0x3cbc) = iVar4;
        return;
      }
      return;
    }
    bVar3 = *pbVar5;
    if (bVar3 != 3) {
      if (bVar3 < 3) {
        if (bVar3 == 1) {
          iVar4 = (uint)pbVar5[2] * 4 + 0x3cc0;
          *(int *)(param_1 + iVar4) = *(int *)(param_1 + iVar4) + 1;
        }
        else if (bVar3 != 0) {
          *(int *)(param_1 + (uint)pbVar5[2] * 4 + 0x3cc0) = (int)*(short *)(pbVar5 + 4);
        }
      }
      else if ((bVar3 < 5) && (*(int *)(param_1 + (uint)pbVar5[2] * 4 + 0x3cc0) == 0)) {
        bVar1 = false;
        goto LAB_800993f0;
      }
    }
    pbVar5 = pbVar5 + 6;
    *(int *)(param_1 + 0x3c10) = *(int *)(param_1 + 0x3c10) + 1;
  } while( true );
}

