// Function: Next__4CMesFv
// Entry: 8009af54
// Size: 528 bytes

void Next__4CMesFv(int param_1)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  float *pfVar8;
  int iVar9;
  float *pfVar10;
  undefined auStack_58 [84];
  
  if (*(int *)(param_1 + 4) != 0) {
    iVar9 = *(int *)(param_1 + 0x3c0c);
    pbVar7 = (byte *)(param_1 + *(int *)(param_1 + 0x3c10) * 6 + 0x3c14);
    while (fVar3 = FLOAT_8033089c, *(int *)(param_1 + 0x3c10) < iVar9) {
      bVar1 = *pbVar7;
      if ((bVar1 != 3) && (bVar1 < 3)) {
        if (bVar1 == 1) {
          iVar6 = (uint)pbVar7[2] * 4 + 0x3cc0;
          *(int *)(param_1 + iVar6) = *(int *)(param_1 + iVar6) + 1;
        }
        else if (bVar1 != 0) {
          *(int *)(param_1 + (uint)pbVar7[2] * 4 + 0x3cc0) = (int)*(short *)(pbVar7 + 4);
        }
      }
      pbVar7 = pbVar7 + 6;
      *(int *)(param_1 + 0x3c10) = *(int *)(param_1 + 0x3c10) + 1;
    }
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 0x3c10) = 0;
    *(undefined4 *)(param_1 + 0x3c0c) = 0;
    *(float *)(param_1 + 0x3c88) = fVar3;
    *(float *)(param_1 + 0x3c84) = fVar3;
    *(float *)(param_1 + 0x3c90) = fVar3;
    *(float *)(param_1 + 0x3c8c) = fVar3;
    *(undefined4 *)(param_1 + 0x3c80) = 0;
    *(undefined4 *)(param_1 + 0x3c7c) = 0;
    *(undefined4 *)(param_1 + 0x3cac) = 0;
    memcpy(auStack_58,param_1 + 0x3cc0,0x50);
    addString__4CMesFPPci(param_1,param_1 + 4,0);
    memcpy((void *)(param_1 + 0x3cc0),auStack_58,0x50);
    fVar3 = FLOAT_803308b0;
    iVar9 = 0;
    pfVar10 = (float *)(param_1 + 0xc);
    while (pfVar8 = pfVar10, iVar6 = *(int *)(param_1 + 8), iVar9 < iVar6) {
      iVar9 = iVar9 + 1;
      pfVar10 = pfVar8 + 5;
      iVar4 = iVar6 - iVar9;
      if (iVar9 < iVar6) {
        do {
          if ((*(byte *)((int)pfVar8 + 0xe) >> 4 != *(byte *)((int)pfVar10 + 0xe) >> 4) ||
             (*(short *)(pfVar8 + 2) != *(short *)(pfVar10 + 2))) break;
          iVar9 = iVar9 + 1;
          pfVar10 = pfVar10 + 5;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      uVar5 = (uint)((int)pfVar10 - (int)pfVar8) / 0x14;
      fVar2 = (pfVar10[-5] - *pfVar8) + pfVar8[1] + *(float *)(param_1 + 0x3d3c);
      if (pfVar8 <= pfVar10 + -5) {
        do {
          bVar1 = *(byte *)((int)pfVar8 + 0xe) >> 4;
          if (bVar1 == 1) {
            *pfVar8 = fVar3 * (*(float *)(param_1 + 0x3ca4) - fVar2) + *pfVar8;
          }
          else if (bVar1 == 2) {
            *pfVar8 = *pfVar8 + (*(float *)(param_1 + 0x3ca4) - fVar2);
          }
          pfVar8 = pfVar8 + 5;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
    }
  }
  return;
}

