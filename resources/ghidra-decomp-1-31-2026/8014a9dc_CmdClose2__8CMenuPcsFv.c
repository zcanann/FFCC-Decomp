// Function: CmdClose2__8CMenuPcsFv
// Entry: 8014a9dc
// Size: 944 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CMenuPcs * CmdClose2__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint32_t uVar2;
  double dVar3;
  uint uVar4;
  undefined4 *puVar5;
  short *psVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int aiStack_48 [14];
  
  uVar2 = Game.game.m_scriptFoodBase[0];
  iVar9 = *(int *)&menuPcs->field_0x82c;
  iVar11 = (int)*(short *)(iVar9 + 0x26);
  iVar10 = (int)*(short *)(iVar9 + *(short *)(iVar9 + 0x30) * 2 + 0x26);
  *(short *)(iVar9 + 0x22) = *(short *)(iVar9 + 0x22) + 1;
  dVar3 = DOUBLE_80332a58;
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x14);
  if (sVar1 == 0) {
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    iVar9 = *(int *)&menuPcs->field_0x82c;
    if (*(char *)(iVar9 + 8) < '\0') {
      *(undefined2 *)(iVar9 + 0x14) = 3;
    }
    else if (*(short *)(uVar2 + iVar11 * 2 + 0x214) == 0) {
      *(undefined2 *)(iVar9 + 0x14) = 2;
    }
    else {
      *(undefined2 *)(iVar9 + 0x14) = 1;
    }
    menuPcs = (CMenuPcs *)0x0;
  }
  else if (sVar1 == 1) {
    puVar5 = s_UniteTop;
    iVar7 = 0;
    iVar9 = DAT_8032eec8;
    if (0 < DAT_8032eec8) {
      do {
        if (iVar11 == *puVar5) break;
        puVar5 = puVar5 + 1;
        iVar7 = iVar7 + 1;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
    iVar9 = UniteCloseAnim__8CMenuPcsFi(menuPcs,iVar7);
    if (iVar9 != 0) {
      ChkUnite__8CMenuPcsFiPA2_i(menuPcs,iVar11,aiStack_48);
      if (aiStack_48[1] < aiStack_48[3]) {
        uVar4 = (uint)(aiStack_48[1] - iVar10 | iVar10 - aiStack_48[1]) >> 0x1f;
      }
      else {
        uVar4 = countLeadingZeros(aiStack_48[3] - iVar10);
        uVar4 = uVar4 >> 5;
      }
      iVar9 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
      uVar8 = 1;
      if ((*(short *)(Game.game.m_scriptFoodBase[0] + (iVar9 + 1) * 2 + 0x214) == -1) &&
         (uVar8 = 2, *(short *)(Game.game.m_scriptFoodBase[0] + (iVar9 + 2) * 2 + 0x214) == -1)) {
        uVar8 = 3;
      }
      UnuniteComList__12CCaravanWorkFii((CCaravanWork *)Game.game.m_scriptFoodBase[0],iVar9,uVar8);
      UniteComList__12CCaravanWorkFiii
                ((CCaravanWork *)Game.game.m_scriptFoodBase[0],aiStack_48[uVar4 * 2 + 1],
                 (int)(short)(&DAT_801de914)[aiStack_48[uVar4 * 2] * 6],
                 (&DAT_801de912)[aiStack_48[uVar4 * 2] * 6]);
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)aiStack_48[uVar4 * 2 + 1];
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x14) = 2;
    }
    menuPcs = (CMenuPcs *)0x0;
  }
  else if (sVar1 == 2) {
    if (*(short *)(uVar2 + iVar11 * 2 + 0x214) == 0) {
      ChkUnite__8CMenuPcsFiPA2_i(menuPcs,iVar11,aiStack_48);
      if (aiStack_48[1] < aiStack_48[3]) {
        uVar4 = (uint)(aiStack_48[1] - iVar10 | iVar10 - aiStack_48[1]) >> 0x1f;
      }
      else {
        uVar4 = countLeadingZeros(aiStack_48[3] - iVar10);
        uVar4 = uVar4 >> 5;
      }
      UniteComList__12CCaravanWorkFiii
                ((CCaravanWork *)Game.game.m_scriptFoodBase[0],aiStack_48[uVar4 * 2 + 1],
                 (int)(short)(&DAT_801de914)[aiStack_48[uVar4 * 2] * 6],
                 (&DAT_801de912)[aiStack_48[uVar4 * 2] * 6]);
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)aiStack_48[uVar4 * 2 + 1];
    }
    else {
      iVar9 = UniteOpenAnim__8CMenuPcsFi(menuPcs,0xffffffff);
      if (iVar9 != 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x14) = 3;
      }
    }
    menuPcs = (CMenuPcs *)0x0;
  }
  else if (sVar1 == 3) {
    iVar9 = 0;
    for (iVar10 = 0; psVar6 = *(short **)&menuPcs->field_0x850, iVar10 < *psVar6;
        iVar10 = iVar10 + 1) {
      if (((double)*(float *)((int)psVar6 + iVar9 + 0x18) < dVar3) &&
         (*(float *)((int)psVar6 + iVar9 + 0x18) =
               (float)(DOUBLE_80332a68 *
                       ((double)CONCAT44(0x43300000,
                                         (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^
                                         0x80000000) - DOUBLE_80332a80) + DOUBLE_80332a60),
         dVar3 < (double)*(float *)((int)psVar6 + iVar9 + 0x18))) {
        *(float *)((int)psVar6 + iVar9 + 0x18) = FLOAT_80332a70;
      }
      iVar9 = iVar9 + 0x40;
    }
    if ((double)CONCAT44(0x43300000,
                         (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^ 0x80000000) -
        DOUBLE_80332a80 < DOUBLE_80332a78) {
      menuPcs = (CMenuPcs *)0x0;
    }
    else {
      menuPcs = (CMenuPcs *)0x1;
    }
  }
  return menuPcs;
}

