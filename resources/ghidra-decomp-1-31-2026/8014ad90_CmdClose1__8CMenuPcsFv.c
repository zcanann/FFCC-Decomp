// Function: CmdClose1__8CMenuPcsFv
// Entry: 8014ad90
// Size: 1192 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint CmdClose1__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint32_t uVar2;
  double dVar3;
  double dVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  uint unaff_r30;
  int local_48;
  undefined4 local_44;
  
  uVar2 = Game.game.m_scriptFoodBase[0];
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  dVar4 = DOUBLE_80332a90;
  dVar3 = DOUBLE_80332a80;
  iVar6 = *(int *)&menuPcs->field_0x82c;
  sVar1 = *(short *)(iVar6 + 0x14);
  if (sVar1 == 0) {
    iVar6 = (int)*(short *)(iVar6 + 0x26);
    *(float *)(*(int *)&menuPcs->field_0x850 + iVar6 * 0x40 + 0x18) =
         (float)(DOUBLE_80332a90 *
                ((double)CONCAT44(0x43300000,
                                  (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^ 0x80000000
                                 ) - DOUBLE_80332a80));
    if ((*(short *)(uVar2 + (iVar6 + 1) * 2 + 0x214) == -1) &&
       (*(float *)(*(int *)&menuPcs->field_0x850 + (iVar6 + 1) * 0x40 + 0x18) =
             (float)(dVar4 * ((double)CONCAT44(0x43300000,
                                               (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22)
                                               ^ 0x80000000) - dVar3)),
       *(short *)(uVar2 + (iVar6 + 2) * 2 + 0x214) == -1)) {
      *(float *)(*(int *)&menuPcs->field_0x850 + (iVar6 + 2) * 0x40 + 0x18) =
           (float)(dVar4 * ((double)CONCAT44(0x43300000,
                                             (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^
                                             0x80000000) - dVar3));
    }
    dVar3 = DOUBLE_80332a58;
    iVar6 = *(int *)&menuPcs->field_0x850 +
            (*(short *)(*(int *)&menuPcs->field_0x850 + 2) + 3) * 0x40 + 8;
    *(float *)(iVar6 + 0x10) =
         (float)-(DOUBLE_80332a90 *
                  ((double)CONCAT44(0x43300000,
                                    (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^
                                    0x80000000) - DOUBLE_80332a80) - DOUBLE_80332a58);
    if (dVar3 == (double)*(float *)(iVar6 + 0x14)) {
      iVar6 = 2;
    }
    else {
      iVar6 = 3;
    }
    iVar7 = *(int *)&menuPcs->field_0x82c;
    unaff_r30 = (uint)(DOUBLE_80332a78 <=
                      (double)CONCAT44(0x43300000,(int)*(short *)(iVar7 + 0x22) ^ 0x80000000) -
                      DOUBLE_80332a80);
    if ((unaff_r30 != 0) && ('\0' < *(char *)(iVar7 + 8))) {
      *(undefined *)(iVar7 + 8) = 0;
      iVar7 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar7 + 0x2a) == 0) {
        unaff_r30 = 0;
        *(undefined2 *)(iVar7 + 0x14) = 1;
      }
      else if ((iVar6 == 3) && (*(short *)(iVar7 + 0x2a) == 1)) {
        unaff_r30 = 0;
        *(undefined2 *)(iVar7 + 0x14) = 2;
      }
    }
    if (unaff_r30 != 0) {
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
    }
  }
  else if (sVar1 == 1) {
    iVar9 = (int)*(short *)(iVar6 + 0x26);
    puVar5 = s_UniteTop;
    iVar7 = 0;
    iVar6 = DAT_8032eec8;
    if (0 < DAT_8032eec8) {
      do {
        if (iVar9 == *puVar5) break;
        puVar5 = puVar5 + 1;
        iVar7 = iVar7 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    unaff_r30 = UniteCloseAnim__8CMenuPcsFi(menuPcs,iVar7);
    if (unaff_r30 != 0) {
      uVar8 = 1;
      if ((*(short *)(Game.game.m_scriptFoodBase[0] + (iVar9 + 1) * 2 + 0x214) == -1) &&
         (uVar8 = 2, *(short *)(Game.game.m_scriptFoodBase[0] + (iVar9 + 2) * 2 + 0x214) == -1)) {
        uVar8 = 3;
      }
      UnuniteComList__12CCaravanWorkFii((CCaravanWork *)Game.game.m_scriptFoodBase[0],iVar9,uVar8);
    }
  }
  else if (sVar1 == 2) {
    iVar6 = ChkUnite__8CMenuPcsFiPA2_i(menuPcs,(int)*(short *)(iVar6 + 0x26),&local_48);
    if (iVar6 == 1) {
      unaff_r30 = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x14) = 3;
    }
    else {
      unaff_r30 = 1;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
    }
  }
  else if (sVar1 == 3) {
    sVar1 = *(short *)(iVar6 + 0x26);
    puVar5 = s_UniteTop;
    iVar7 = 0;
    iVar6 = DAT_8032eec8;
    if (0 < DAT_8032eec8) {
      do {
        if ((int)sVar1 == *puVar5) break;
        puVar5 = puVar5 + 1;
        iVar7 = iVar7 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    unaff_r30 = UniteCloseAnim__8CMenuPcsFi(menuPcs,iVar7);
    if (unaff_r30 != 0) {
      ChkUnite__8CMenuPcsFiPA2_i(menuPcs,(int)sVar1,&local_48);
      iVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
      uVar8 = 1;
      if ((*(short *)(Game.game.m_scriptFoodBase[0] + (iVar6 + 1) * 2 + 0x214) == -1) &&
         (uVar8 = 2, *(short *)(Game.game.m_scriptFoodBase[0] + (iVar6 + 2) * 2 + 0x214) == -1)) {
        uVar8 = 3;
      }
      UnuniteComList__12CCaravanWorkFii((CCaravanWork *)Game.game.m_scriptFoodBase[0],iVar6,uVar8);
      UniteComList__12CCaravanWorkFiii
                ((CCaravanWork *)Game.game.m_scriptFoodBase[0],local_44,
                 (int)(short)(&DAT_801de914)[local_48 * 6],(&DAT_801de912)[local_48 * 6]);
      unaff_r30 = 0;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)local_44;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x14) = 4;
    }
  }
  else if (sVar1 == 4) {
    unaff_r30 = UniteOpenAnim__8CMenuPcsFi(menuPcs,0xffffffff);
  }
  return unaff_r30;
}

