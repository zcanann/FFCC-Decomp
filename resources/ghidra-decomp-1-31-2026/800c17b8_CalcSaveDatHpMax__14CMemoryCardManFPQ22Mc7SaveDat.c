// Function: CalcSaveDatHpMax__14CMemoryCardManFPQ22Mc7SaveDat
// Entry: 800c17b8
// Size: 324 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcSaveDatHpMax__14CMemoryCardManFPQ22Mc7SaveDat(CMemoryCardMan *memoryCardMan,void *saveDat)

{
  int iVar1;
  int iVar2;
  undefined2 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  short local_8 [4];
  
  iVar2 = 0;
  do {
    if (*(int *)((int)saveDat + 0x1a84) != 0) {
      iVar5 = 0;
      iVar6 = 0x49;
      do {
        if (0x44 < iVar5) {
          iVar1 = iVar5 >> 0x1f;
          if ((*(uint *)((int)saveDat + (iVar5 >> 5) * 4 + 0x158c) &
              1 << (iVar1 * 0x20 | (uint)(iVar5 * 0x8000000 + iVar1) >> 0x1b) - iVar1) == 0) {
            local_8[iVar5 + -0x45] = -1;
          }
          else {
            local_8[iVar5 + -0x45] = (short)iVar5 + 0x9f;
          }
        }
        iVar5 = iVar5 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      uVar4 = 0;
      if (-1 < local_8[0]) {
        uVar4 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + local_8[0] * 0x48 + 6);
      }
      if (-1 < local_8[1]) {
        uVar4 = uVar4 + *(ushort *)(Game.game.unkCFlatData0[2] + local_8[1] * 0x48 + 6);
      }
      if (-1 < local_8[2]) {
        uVar4 = uVar4 + *(ushort *)(Game.game.unkCFlatData0[2] + local_8[2] * 0x48 + 6);
      }
      if (-1 < local_8[3]) {
        uVar4 = uVar4 + *(ushort *)(Game.game.unkCFlatData0[2] + local_8[3] * 0x48 + 6);
      }
      uVar3 = 0x10;
      if (uVar4 + 8 < 0x10) {
        uVar3 = (undefined2)(uVar4 + 8);
      }
      *(undefined2 *)((int)saveDat + 0x14d6) = uVar3;
    }
    iVar2 = iVar2 + 1;
    saveDat = (void *)((int)saveDat + 0x9c0);
  } while (iVar2 < 8);
  return;
}

