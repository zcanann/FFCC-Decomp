// Function: GetCmdItem__8CMenuPcsFv
// Entry: 8014cce0
// Size: 536 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GetCmdItem__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  ushort uVar1;
  bool bVar2;
  uint32_t uVar3;
  undefined2 *puVar4;
  uint uVar5;
  short *psVar6;
  uint32_t uVar7;
  int iVar8;
  int iVar9;
  undefined2 *puVar10;
  int iVar11;
  short sVar12;
  int iVar13;
  
  uVar3 = Game.game.m_scriptFoodBase[0];
  puVar4 = (undefined2 *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
  iVar11 = 0;
  puVar10 = puVar4;
  uVar7 = uVar3;
  for (iVar9 = 0; iVar9 < 0x40; iVar9 = iVar9 + 1) {
    iVar13 = GetItemType__8CMenuPcsFii(menuPcs,iVar9,0);
    if (((((iVar13 != 0) && (iVar13 != 5)) && (iVar13 != 6)) && ((iVar13 != 8 && (iVar13 != 9)))) &&
       ((iVar13 != 1 ||
        (uVar1 = *(ushort *)(uVar3 + 0x3e0),
        uVar5 = GetItemIcon__8CMenuPcsFi(menuPcs,(int)*(short *)(uVar7 + 0xb6)),
        uVar5 == (uVar1 & 3))))) {
      puVar10 = puVar10 + 1;
      *puVar10 = (short)iVar9;
      iVar11 = iVar11 + 1;
    }
    uVar7 = uVar7 + 2;
  }
  iVar9 = 0;
  psVar6 = puVar4 + iVar11;
  iVar13 = 0x49;
  uVar7 = uVar3;
  do {
    iVar8 = iVar9 + 0x9f;
    if (*(short *)(uVar7 + 0x136) == iVar8) {
      bVar2 = false;
      if ((0xde < iVar8) && (iVar8 < 0xe4)) {
        bVar2 = true;
      }
      if (bVar2) {
        iVar11 = iVar11 + 1;
        psVar6 = psVar6 + 1;
        *psVar6 = (short)iVar9 + 0x40;
      }
    }
    uVar7 = uVar7 + 2;
    iVar9 = iVar9 + 1;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  puVar4 = puVar4 + iVar11;
  bVar2 = false;
  if ((0xde < *(short *)(uVar3 + 0x1f6)) && (*(short *)(uVar3 + 0x1f6) < 0xe4)) {
    bVar2 = true;
  }
  if (bVar2) {
    iVar11 = iVar11 + 1;
    puVar4 = puVar4 + 1;
    *puVar4 = 0xa0;
  }
  sVar12 = (short)iVar11;
  bVar2 = false;
  if ((0xde < *(short *)(uVar3 + 0x1f8)) && (*(short *)(uVar3 + 0x1f8) < 0xe4)) {
    bVar2 = true;
  }
  if (bVar2) {
    sVar12 = sVar12 + 1;
    puVar4 = puVar4 + 1;
    *puVar4 = 0xa1;
  }
  bVar2 = false;
  if ((0xde < *(short *)(uVar3 + 0x1fa)) && (*(short *)(uVar3 + 0x1fa) < 0xe4)) {
    bVar2 = true;
  }
  if (bVar2) {
    sVar12 = sVar12 + 1;
    puVar4 = puVar4 + 1;
    *puVar4 = 0xa2;
  }
  bVar2 = false;
  if ((0xde < *(short *)(uVar3 + 0x1fc)) && (*(short *)(uVar3 + 0x1fc) < 0xe4)) {
    bVar2 = true;
  }
  if (bVar2) {
    sVar12 = sVar12 + 1;
    puVar4[1] = 0xa3;
  }
  psVar6 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
  *psVar6 = sVar12 + 2;
  return;
}

