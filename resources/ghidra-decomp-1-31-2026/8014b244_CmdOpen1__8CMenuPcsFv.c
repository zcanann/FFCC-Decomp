// Function: CmdOpen1__8CMenuPcsFv
// Entry: 8014b244
// Size: 900 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CmdOpen1__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  uint32_t uVar1;
  double dVar2;
  double dVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short *psVar9;
  undefined2 *puVar10;
  double dVar11;
  undefined auStack_68 [40];
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  double local_18;
  
  dVar3 = DOUBLE_80332a90;
  dVar2 = DOUBLE_80332a80;
  dVar11 = DOUBLE_80332a58;
  uVar1 = Game.game.m_scriptFoodBase[0];
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar8 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
  iVar5 = 1;
  *(float *)(*(int *)&menuPcs->field_0x850 + iVar8 * 0x40 + 0x18) =
       (float)-(dVar3 * ((double)CONCAT44(0x43300000,
                                          (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^
                                          0x80000000) - dVar2) - dVar11);
  if (*(short *)(uVar1 + (iVar8 + 1) * 2 + 0x214) == -1) {
    iVar5 = 2;
    *(float *)(*(int *)&menuPcs->field_0x850 + (iVar8 + 1) * 0x40 + 0x18) =
         (float)-(dVar3 * ((double)CONCAT44(0x43300000,
                                            (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^
                                            0x80000000) - dVar2) - dVar11);
    if (*(short *)(uVar1 + (iVar8 + 2) * 2 + 0x214) == -1) {
      iVar5 = 3;
      *(float *)(*(int *)&menuPcs->field_0x850 + (iVar8 + 2) * 0x40 + 0x18) =
           (float)-(dVar3 * ((double)CONCAT44(0x43300000,
                                              (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22)
                                              ^ 0x80000000) - dVar2) - dVar11);
    }
  }
  iVar6 = *(int *)&menuPcs->field_0x850;
  iVar7 = 0;
  puVar10 = (undefined2 *)(iVar6 + (*(short *)(iVar6 + 2) + 3) * 0x40 + 8);
  if (((iVar8 != s_UniteTop[0]) && (iVar7 = 1, iVar8 != s_UniteTop[1])) &&
     (iVar7 = 2, iVar8 != s_UniteTop[2])) {
    iVar7 = 3;
  }
  psVar9 = (short *)(iVar6 + (*(short *)(iVar6 + 2) + iVar7) * 0x40 + 8);
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xc) == '\0') {
    local_40 = 0x43300000;
    uStack_3c = (int)*psVar9 + (int)psVar9[2] ^ 0x80000000;
    iVar8 = (int)(((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332a80) - DOUBLE_80332a98);
    local_38 = (longlong)iVar8;
    *puVar10 = (short)iVar8;
    if (iVar5 == 2) {
      iVar5 = ChkUnite__8CMenuPcsFiPA2_i
                        (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26),auStack_68);
    }
    else {
      iVar5 = 0;
    }
    dVar11 = DOUBLE_80332a58;
    if (iVar5 != 0) {
      dVar11 = DOUBLE_80332aa0;
    }
    *(float *)(puVar10 + 10) = (float)dVar11;
    dVar2 = DOUBLE_80332a80;
    puVar10[2] = 0xc0;
    dVar11 = DOUBLE_80332a60;
    puVar10[3] = 0x40;
    fVar4 = FLOAT_80332ab0;
    puVar10[1] = (short)(int)((-(double)((float)((double)CONCAT44(0x43300000,
                                                                  (int)(short)puVar10[3] ^
                                                                  0x80000000) - dVar2) *
                                         *(float *)(puVar10 + 10) -
                                        (float)((double)CONCAT44(0x43300000,
                                                                 (int)psVar9[3] ^ 0x80000000) -
                                               dVar2)) * dVar11 +
                              ((double)CONCAT44(0x43300000,(int)psVar9[1] ^ 0x80000000) - dVar2)) -
                             DOUBLE_80332aa8);
    *(float *)(puVar10 + 4) = fVar4;
    *(float *)(puVar10 + 6) = fVar4;
    *(undefined4 *)(puVar10 + 0xe) = 0x39;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
  }
  dVar2 = DOUBLE_80332a80;
  dVar11 = DOUBLE_80332a78;
  local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22)) ^
                     0x80000000);
  *(float *)(puVar10 + 8) = (float)(DOUBLE_80332a90 * (local_18 - DOUBLE_80332a80));
  if (dVar11 <= (double)CONCAT44(0x43300000,
                                 (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^ 0x80000000)
                - dVar2) {
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2a) = 0;
  }
  return;
}

