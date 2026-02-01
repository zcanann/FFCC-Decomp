// Function: UniteOpenAnim__8CMenuPcsFi
// Entry: 8014b7ec
// Size: 564 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 UniteOpenAnim__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  float fVar1;
  float fVar2;
  uint32_t uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  double local_8;
  
  dVar6 = DOUBLE_80332ac0;
  dVar5 = DOUBLE_80332ab8;
  dVar4 = DOUBLE_80332a80;
  uVar3 = Game.game.m_scriptFoodBase[0];
  if (DAT_8032eec8 == 0) {
    uVar7 = 1;
  }
  else {
    fVar1 = (float)((double)CONCAT44(0x43300000,
                                     (int)*(short *)(*(int *)&menuPcs->field_0x850 + 8) ^ 0x80000000
                                    ) - DOUBLE_80332a80);
    if (param_2 < 1) {
      iVar14 = 0;
      fVar2 = FLOAT_80332ac8 + fVar1;
      puVar10 = s_UniteTop;
      for (iVar12 = 0; iVar12 < DAT_8032eec8; iVar12 = iVar12 + 1) {
        iVar8 = 0;
        iVar11 = 3;
        do {
          iVar9 = *(int *)&menuPcs->field_0x850;
          iVar13 = (iVar8 + *puVar10) * 0x40 + 8;
          if ((iVar8 != 0) && (*(short *)(uVar3 + (iVar8 + *puVar10) * 2 + 0x214) != -1)) break;
          local_8 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar9 + iVar13)) ^ 0x80000000);
          *(short *)(iVar9 + iVar13) = (short)(int)((local_8 - dVar4) + dVar5);
          if ((dVar6 < ABS((double)((float)((double)CONCAT44(0x43300000,
                                                             (int)*(short *)(iVar9 + iVar13) ^
                                                             0x80000000) - dVar4) - fVar1))) &&
             (*(short *)(iVar9 + iVar13) = (short)(int)fVar2, iVar8 == 0)) {
            iVar14 = iVar14 + 1;
          }
          iVar8 = iVar8 + 1;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
        puVar10 = puVar10 + 1;
      }
      if (iVar14 == DAT_8032eec8) {
        return 1;
      }
    }
    else {
      iVar12 = 0;
      iVar14 = 3;
      do {
        iVar8 = *(int *)&menuPcs->field_0x850;
        iVar11 = (iVar12 + s_UniteTop[param_2]) * 0x40 + 8;
        if ((iVar12 != 0) && (*(short *)(uVar3 + (iVar12 + s_UniteTop[param_2]) * 2 + 0x214) != -1))
        break;
        *(short *)(iVar8 + iVar11) =
             (short)(int)(((double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + iVar11) ^ 0x80000000)
                          - dVar4) + dVar5);
        local_8 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + iVar11)) ^ 0x80000000);
        if (dVar6 < ABS((double)((float)(local_8 - dVar4) - fVar1))) {
          *(short *)(iVar8 + iVar11) = (short)(int)(FLOAT_80332ac8 + fVar1);
          return 1;
        }
        iVar12 = iVar12 + 1;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
    }
    uVar7 = 0;
  }
  return uVar7;
}

