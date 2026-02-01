// Function: pppInitPdt__FPlP7pppProg
// Entry: 800550ac
// Size: 604 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppInitPdt__FPlP7pppProg(long *progOffsetReconstructionTable,pppProg *pppProg)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  uint uVar9;
  
  iVar6 = *(int *)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[2]);
  iVar7 = *(int *)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[3]);
  piVar3 = (int *)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[2]) + 1;
  piVar2 = (int *)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[3]) + 1;
  piVar4 = progOffsetReconstructionTable + 6;
  if (progOffsetReconstructionTable[6] == 0) {
    return;
  }
  do {
    piVar8 = piVar4;
    *piVar8 = (int)progOffsetReconstructionTable + *piVar8;
    piVar4 = piVar8;
    for (iVar5 = 0; iVar5 < *(short *)((int)piVar8 + 0x26); iVar5 = iVar5 + 1) {
      piVar4[10] = (int)(pppProg + piVar4[10]);
      piVar4[0xc] = (int)progOffsetReconstructionTable + piVar4[0xc];
      piVar4[0xd] = (int)progOffsetReconstructionTable + piVar4[0xd];
      piVar4 = piVar4 + 4;
    }
    piVar4 = (int *)*piVar8;
  } while (*(int *)*piVar8 != 0);
  iVar5 = 0;
  *piVar8 = 0;
  if (0 < iVar6) {
    if ((8 < iVar6) && (uVar9 = iVar6 - 1U >> 3, piVar4 = piVar3, 0 < iVar6 + -8)) {
      do {
        iVar5 = iVar5 + 8;
        *piVar4 = (int)(pppProg + *piVar4);
        piVar4[1] = (int)(pppProg + piVar4[1]);
        piVar4[2] = (int)(pppProg + piVar4[2]);
        piVar4[3] = (int)(pppProg + piVar4[3]);
        piVar4[4] = (int)(pppProg + piVar4[4]);
        piVar4[5] = (int)(pppProg + piVar4[5]);
        piVar4[6] = (int)(pppProg + piVar4[6]);
        piVar4[7] = (int)(pppProg + piVar4[7]);
        piVar4 = piVar4 + 8;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
    }
    iVar1 = iVar6 - iVar5;
    piVar3 = piVar3 + iVar5;
    if (iVar5 < iVar6) {
      do {
        *piVar3 = (int)(pppProg + *piVar3);
        piVar3 = piVar3 + 1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  iVar6 = 0;
  if (0 < iVar7) {
    if ((8 < iVar7) && (uVar9 = iVar7 - 1U >> 3, piVar4 = piVar2, 0 < iVar7 + -8)) {
      do {
        iVar6 = iVar6 + 8;
        *piVar4 = *piVar4 + (int)progOffsetReconstructionTable;
        piVar4[1] = piVar4[1] + (int)progOffsetReconstructionTable;
        piVar4[2] = piVar4[2] + (int)progOffsetReconstructionTable;
        piVar4[3] = piVar4[3] + (int)progOffsetReconstructionTable;
        piVar4[4] = piVar4[4] + (int)progOffsetReconstructionTable;
        piVar4[5] = piVar4[5] + (int)progOffsetReconstructionTable;
        piVar4[6] = piVar4[6] + (int)progOffsetReconstructionTable;
        piVar4[7] = piVar4[7] + (int)progOffsetReconstructionTable;
        piVar4 = piVar4 + 8;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
    }
    iVar5 = iVar7 - iVar6;
    piVar2 = piVar2 + iVar6;
    if (iVar6 < iVar7) {
      do {
        *piVar2 = *piVar2 + (int)progOffsetReconstructionTable;
        piVar2 = piVar2 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      return;
    }
    return;
  }
  return;
}

