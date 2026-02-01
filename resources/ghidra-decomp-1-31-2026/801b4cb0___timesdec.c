// Function: __timesdec
// Entry: 801b4cb0
// Size: 632 bytes

void __timesdec(undefined *param_1,int param_2,int param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  byte *pbVar13;
  byte *pbVar14;
  byte bVar15;
  byte bVar16;
  byte bVar17;
  byte bVar18;
  char cVar19;
  int iVar20;
  byte *pbVar21;
  byte *pbVar22;
  byte *pbVar23;
  int iVar24;
  uint uVar25;
  uint uVar26;
  byte *pbVar27;
  int iVar28;
  uint uVar29;
  byte abStack_68 [84];
  
  bVar15 = *(byte *)(param_3 + 4);
  bVar16 = *(byte *)(param_2 + 4);
  uVar29 = 0;
  iVar28 = (uint)bVar16 + (bVar15 - 1);
  pbVar23 = abStack_68 + iVar28 + 1;
  *param_1 = 0;
  pbVar22 = pbVar23;
  for (; 0 < iVar28; iVar28 = iVar28 + -1) {
    iVar24 = bVar15 - 1;
    iVar20 = (iVar28 - iVar24) + -1;
    if (iVar20 < 0) {
      iVar20 = 0;
      iVar24 = iVar28 + -1;
    }
    uVar26 = (uint)bVar16 - iVar20;
    pbVar27 = (byte *)(param_2 + iVar20 + 5);
    pbVar21 = (byte *)(param_3 + iVar24 + 5);
    uVar25 = iVar24 + 1U;
    if ((int)uVar26 < (int)(iVar24 + 1U)) {
      uVar25 = uVar26;
    }
    if (0 < (int)uVar25) {
      uVar26 = uVar25 >> 3;
      if (uVar26 != 0) {
        do {
          bVar17 = *pbVar27;
          bVar18 = *pbVar21;
          pbVar1 = pbVar27 + 1;
          pbVar2 = pbVar21 + -1;
          pbVar3 = pbVar27 + 2;
          pbVar4 = pbVar21 + -2;
          pbVar5 = pbVar27 + 3;
          pbVar6 = pbVar21 + -3;
          pbVar7 = pbVar27 + 4;
          pbVar8 = pbVar21 + -4;
          pbVar9 = pbVar27 + 5;
          pbVar10 = pbVar21 + -5;
          pbVar11 = pbVar27 + 6;
          pbVar12 = pbVar21 + -6;
          pbVar13 = pbVar27 + 7;
          pbVar14 = pbVar21 + -7;
          pbVar27 = pbVar27 + 8;
          pbVar21 = pbVar21 + -8;
          uVar29 = uVar29 + (uint)bVar17 * (uint)bVar18 + (uint)*pbVar1 * (uint)*pbVar2 +
                   (uint)*pbVar3 * (uint)*pbVar4 + (uint)*pbVar5 * (uint)*pbVar6 +
                   (uint)*pbVar7 * (uint)*pbVar8 + (uint)*pbVar9 * (uint)*pbVar10 +
                   (uint)*pbVar11 * (uint)*pbVar12 + (uint)*pbVar13 * (uint)*pbVar14;
          uVar26 = uVar26 - 1;
        } while (uVar26 != 0);
        uVar25 = uVar25 & 7;
        if (uVar25 == 0) goto LAB_801b4df8;
      }
      do {
        bVar17 = *pbVar27;
        pbVar27 = pbVar27 + 1;
        bVar18 = *pbVar21;
        pbVar21 = pbVar21 + -1;
        uVar29 = uVar29 + (uint)bVar17 * (uint)bVar18;
        uVar25 = uVar25 - 1;
      } while (uVar25 != 0);
    }
LAB_801b4df8:
    uVar25 = uVar29 / 10;
    cVar19 = (char)uVar29;
    uVar29 = uVar29 / 10;
    pbVar22 = pbVar22 + -1;
    *pbVar22 = cVar19 + (char)uVar25 * -10;
  }
  *(short *)(param_1 + 2) = *(short *)(param_2 + 2) + *(short *)(param_3 + 2);
  if (uVar29 != 0) {
    pbVar22 = pbVar22 + -1;
    *pbVar22 = (byte)uVar29;
    *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
  }
  iVar28 = 0;
  for (; (iVar28 < 0x24 && (pbVar22 < pbVar23)); pbVar22 = pbVar22 + 1) {
    iVar20 = iVar28 + 5;
    iVar28 = iVar28 + 1;
    param_1[iVar20] = *pbVar22;
  }
  param_1[4] = (char)iVar28;
  if ((pbVar22 < pbVar23) && (4 < *pbVar22)) {
    if (*pbVar22 == 5) {
      pbVar21 = pbVar22 + 1;
      iVar28 = (int)pbVar23 - (int)pbVar21;
      if (pbVar21 < pbVar23) {
        do {
          if (*pbVar21 != 0) goto LAB_801b4ec4;
          pbVar21 = pbVar21 + 1;
          iVar28 = iVar28 + -1;
        } while (iVar28 != 0);
      }
      if ((pbVar22[-1] & 1) == 0) {
        return;
      }
    }
LAB_801b4ec4:
    for (pbVar22 = param_1 + 5 + ((byte)param_1[4] - 1); 8 < *pbVar22; pbVar22 = pbVar22 + -1) {
      if (pbVar22 == param_1 + 5) {
        *pbVar22 = 1;
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
        return;
      }
      *pbVar22 = 0;
    }
    *pbVar22 = *pbVar22 + 1;
  }
  return;
}

