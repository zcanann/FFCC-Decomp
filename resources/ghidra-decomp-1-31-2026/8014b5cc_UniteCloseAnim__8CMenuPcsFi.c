// Function: UniteCloseAnim__8CMenuPcsFi
// Entry: 8014b5cc
// Size: 544 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 UniteCloseAnim__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  double dVar1;
  bool bVar2;
  uint32_t uVar3;
  double dVar4;
  double dVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  double local_8;
  
  dVar5 = DOUBLE_80332ab8;
  dVar4 = DOUBLE_80332a80;
  uVar3 = Game.game.m_scriptFoodBase[0];
  if (DAT_8032eec8 == 0) {
    uVar6 = 1;
  }
  else {
    dVar1 = (double)CONCAT44(0x43300000,
                             (int)*(short *)(*(int *)&menuPcs->field_0x850 + 8) ^ 0x80000000) -
            DOUBLE_80332a80;
    if (param_2 < 0) {
      iVar13 = 0;
      puVar9 = s_UniteTop;
      for (iVar11 = 0; iVar11 < DAT_8032eec8; iVar11 = iVar11 + 1) {
        iVar7 = 0;
        iVar10 = 3;
        do {
          iVar8 = *(int *)&menuPcs->field_0x850;
          iVar12 = (iVar7 + *puVar9) * 0x40 + 8;
          if ((iVar7 != 0) && (*(short *)(uVar3 + (iVar7 + *puVar9) * 2 + 0x214) != -1)) break;
          local_8 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + iVar12)) ^ 0x80000000);
          *(short *)(iVar8 + iVar12) = (short)(int)((local_8 - dVar4) - dVar5);
          if (((float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + iVar12) ^ 0x80000000) -
                      dVar4) <= (float)dVar1) &&
             (*(short *)(iVar8 + iVar12) = (short)(int)dVar1, iVar7 == 0)) {
            iVar13 = iVar13 + 1;
          }
          iVar7 = iVar7 + 1;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
        puVar9 = puVar9 + 1;
      }
      if (iVar13 == DAT_8032eec8) {
        return 1;
      }
    }
    else {
      bVar2 = false;
      iVar11 = 0;
      iVar13 = 3;
      do {
        iVar7 = *(int *)&menuPcs->field_0x850;
        iVar10 = (iVar11 + s_UniteTop[param_2]) * 0x40 + 8;
        if ((iVar11 != 0) && (*(short *)(uVar3 + (iVar11 + s_UniteTop[param_2]) * 2 + 0x214) != -1))
        break;
        *(short *)(iVar7 + iVar10) =
             (short)(int)(((double)CONCAT44(0x43300000,(int)*(short *)(iVar7 + iVar10) ^ 0x80000000)
                          - dVar4) - dVar5);
        local_8 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar7 + iVar10)) ^ 0x80000000);
        if ((float)(local_8 - dVar4) <= (float)dVar1) {
          bVar2 = true;
          *(short *)(iVar7 + iVar10) = (short)(int)dVar1;
        }
        iVar11 = iVar11 + 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
      if (bVar2) {
        return 1;
      }
    }
    uVar6 = 0;
  }
  return uVar6;
}

