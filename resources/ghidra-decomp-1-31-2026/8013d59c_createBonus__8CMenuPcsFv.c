// Function: createBonus__8CMenuPcsFv
// Entry: 8013d59c
// Size: 3300 bytes

/* WARNING: Removing unreachable block (ram,0x8013dab8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void createBonus__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  undefined *puVar1;
  short sVar2;
  ushort uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  undefined4 uVar10;
  undefined2 *puVar11;
  CCharaPcsCHandle *pCVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  float *pfVar22;
  int *piVar23;
  int *piVar24;
  ushort uVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int *piVar35;
  CMenuPcs *pCVar36;
  int iVar37;
  uint32_t *puVar38;
  CProcess *pCVar39;
  int iVar40;
  int iVar41;
  int iVar42;
  int local_c8 [4];
  undefined auStack_b8 [128];
  
  iVar26 = 0;
  Pad._456_4_ = 0x28;
  do {
    OpenMenu__8GbaQueueFiii(&GbaQue,iVar26,0,0);
    SetRadarMode__8GbaQueueFii(&GbaQue,iVar26,0);
    iVar26 = iVar26 + 1;
  } while (iVar26 < 4);
  loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii
            (menuPcs,&PTR_s_bonus_802128c0,2,1,&DAT_802128e4,0x16,0x12,0);
  pcVar9 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_b8,s_dvd__smenu_subfont_fnt_801dd5d4,pcVar9);
  loadFont__8CMenuPcsFiPcii(menuPcs,0,auStack_b8,1,0xffffffff);
  DAT_8032eea8 = (int *)__nw__FUlPQ27CMemory6CStagePci
                                  (0xcc,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xdd);
  memset(DAT_8032eea8,0,0xcc);
  *(undefined2 *)((int)DAT_8032eea8 + 10) = 0xffff;
  *(undefined2 *)(DAT_8032eea8 + 3) = 0xffff;
  *(undefined2 *)((int)DAT_8032eea8 + 0xe) = 0xffff;
  *(undefined2 *)(DAT_8032eea8 + 4) = 0xffff;
  *(undefined2 *)((int)DAT_8032eea8 + 0x12) = 0xffff;
  *(undefined2 *)(DAT_8032eea8 + 5) = 0xffff;
  *(undefined2 *)((int)DAT_8032eea8 + 0x16) = 0xffff;
  *(undefined2 *)(DAT_8032eea8 + 6) = 0xffff;
  uVar10 = __nw__FUlPQ27CMemory6CStagePci(0x48,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xe5)
  ;
  *(undefined4 *)&menuPcs->field_0x82c = uVar10;
  uVar10 = __nwa__FUlPQ27CMemory6CStagePci
                     (0xcdb0,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xe6);
  uVar10 = __construct_new_array(uVar10,__ct__Q28CMenuPcs10EffectInfoFv,0,0x524,0x28);
  *(undefined4 *)&menuPcs->field_0x840 = uVar10;
  iVar26 = 0;
  iVar42 = 5;
  do {
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar26) = 0xffffffff;
    iVar27 = iVar26 + 0x528;
    iVar28 = iVar26 + 0x52c;
    iVar29 = iVar26 + 0xa48;
    iVar30 = iVar26 + 0xa4c;
    iVar31 = iVar26 + 0xa50;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar26 + 4) = 0xffffffff;
    iVar41 = iVar26 + 0xf6c;
    iVar40 = iVar26 + 0xf70;
    iVar37 = iVar26 + 0xf74;
    iVar34 = iVar26 + 0x1490;
    iVar33 = iVar26 + 0x1494;
    iVar32 = iVar26 + 0x1498;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar26 + 8) = 0xffffffff;
    iVar21 = iVar26 + 0x19b4;
    iVar20 = iVar26 + 0x19b8;
    iVar19 = iVar26 + 0x19bc;
    iVar18 = iVar26 + 0x1ed8;
    iVar17 = iVar26 + 0x1edc;
    iVar16 = iVar26 + 0x1ee0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar26 + 0x524) = 0xffffffff;
    iVar15 = iVar26 + 0x23fc;
    iVar14 = iVar26 + 0x2400;
    iVar13 = iVar26 + 0x2404;
    iVar26 = iVar26 + 0x2920;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar27) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar28) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar29) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar30) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar31) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar41) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar40) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar37) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar34) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar33) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar32) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar21) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar20) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar19) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar18) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar17) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar16) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar15) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar14) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar13) = 0xffffffff;
    iVar42 = iVar42 + -1;
  } while (iVar42 != 0);
  memset(*(undefined4 *)&menuPcs->field_0x82c,0,0x48);
  DAT_8032eeb0 = __nw__FUlPQ27CMemory6CStagePci
                           (0x48,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xf1);
  memset(DAT_8032eeb0,0,0x48);
  uVar10 = __nw__FUlPQ27CMemory6CStagePci
                     (0x1008,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xf5);
  *(undefined4 *)&menuPcs->field_0x84c = uVar10;
  memset(*(undefined4 *)&menuPcs->field_0x84c,0,0x1008);
  uVar10 = __nwa__FUlPQ27CMemory6CStagePci
                     (0x780,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xf8);
  *(undefined4 *)&menuPcs->field_0x814 = uVar10;
  uVar10 = __nw__FUlPQ27CMemory6CStagePci(0xc,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xfa);
  *(undefined4 *)&menuPcs->field_0x848 = uVar10;
  memset(*(undefined4 *)&menuPcs->field_0x848,0,0xc);
  fVar6 = FLOAT_80331f6c;
  fVar5 = FLOAT_80331eb0;
  fVar4 = FLOAT_80331eac;
  iVar26 = 0;
  iVar42 = 0x18;
  do {
    iVar14 = 0;
    iVar30 = iVar26 + 4;
    pfVar22 = (float *)(*(int *)&menuPcs->field_0x814 + iVar26 + 0x1c);
    iVar29 = iVar26 + 8;
    pfVar22[2] = fVar4;
    iVar28 = iVar26 + 10;
    iVar27 = iVar26 + 0xc;
    pfVar22[1] = fVar4;
    iVar21 = iVar26 + 0xe;
    iVar20 = iVar26 + 0x10;
    *pfVar22 = fVar4;
    iVar19 = iVar26 + 0x14;
    iVar18 = iVar26 + 0x18;
    iVar17 = iVar26 + 0x40;
    pfVar22[5] = fVar4;
    iVar16 = iVar26 + 0x44;
    iVar15 = iVar26 + 0x48;
    iVar13 = iVar26 + 0x4c;
    pfVar22[4] = fVar4;
    pfVar22[3] = fVar4;
    pfVar22[8] = fVar5;
    pfVar22[7] = fVar5;
    pfVar22[6] = fVar5;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar26) = 0;
    iVar26 = iVar26 + 0x50;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar30) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar29) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar28) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar27) = 0x280;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar21) = 0x1c0;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar20) = fVar4;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar19) = fVar4;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar18) = fVar6;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar17) = 0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar16) = 0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar15) = 0x280;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar13) = 0x1c0;
    iVar42 = iVar42 + -1;
  } while (iVar42 != 0);
  iVar17 = 0;
  iVar16 = 0;
  iVar42 = 4;
  iVar15 = -0x7fde1140;
  iVar13 = 0;
  iVar26 = 0;
  do {
    iVar18 = iVar26;
    if (*(int *)(iVar15 + 0xc5c0) != 0) {
      if ((Game.game.m_gameWork.m_menuStageMode != '\0') && (iVar16 != 0)) break;
      *(int *)((int)DAT_8032eea8 + iVar26 + 0x1c) = iVar16;
      fVar4 = FLOAT_80331eac;
      *(undefined4 *)((int)DAT_8032eea8 + iVar26 + 0x20) =
           *(undefined4 *)(*(int *)(iVar15 + 0xc5b0) + 0xf8);
      *(float *)(*(int *)(*(int *)((int)DAT_8032eea8 + iVar26 + 0x20) + 0x168) + 0x9c) = fVar4;
      *(uint *)((int)DAT_8032eea8 + iVar26 + 0x24) =
           (uint)*(byte *)(*(int *)(iVar15 + 0xc5c0) + 0xba4);
      uVar7 = (uint)*(ushort *)(*(int *)(iVar15 + 0xc5c0) + 0xbca) +
              (uint)*(ushort *)(*(int *)(iVar15 + 0xc5c0) + 0xbcc);
      uVar8 = 100;
      if (uVar7 < 0x65) {
        uVar8 = uVar7;
      }
      *(uint *)((int)DAT_8032eea8 + iVar26 + 0x2c) = uVar8;
      iVar18 = *(int *)(iVar15 + 0xc5c0);
      *(uint *)((int)DAT_8032eea8 + iVar26 + 0x30) =
           ((uint)*(ushort *)(iVar18 + 0xbc4) + (uint)*(ushort *)(iVar18 + 0xbc6)) -
           (uint)*(ushort *)(iVar18 + 0xbc8);
      *(int *)((int)DAT_8032eea8 + iVar26 + 0x28) =
           *(int *)((int)DAT_8032eea8 + iVar26 + 0x2c) + *(int *)((int)DAT_8032eea8 + iVar26 + 0x30)
      ;
      *(undefined4 *)((int)DAT_8032eea8 + iVar26 + 0x3c) = 0xffffffff;
      *(undefined4 *)((int)DAT_8032eea8 + iVar26 + 0x40) = 0xffffffff;
      iVar18 = *(int *)((int)DAT_8032eea8 + iVar26 + 0x28);
      if (iVar18 < 0) {
        iVar19 = 0;
      }
      else {
        iVar19 = 999;
        if (iVar18 < 1000) {
          iVar19 = iVar18;
        }
      }
      *(int *)((int)DAT_8032eea8 + iVar26 + 0x28) = iVar19;
      piVar23 = (int *)(iVar15 + 0xc5c0);
      iVar17 = iVar17 + 1;
      iVar18 = iVar26 + 0x2c;
      iVar13 = iVar13 + *(int *)((int)DAT_8032eea8 + iVar26 + 0x28);
      *(uint *)((int)DAT_8032eea8 + iVar26 + 0x44) =
           (uint)*(ushort *)(*(int *)(iVar15 + 0xc5c0) + 0x3e0);
      if (0 < *(short *)(*piVar23 + 0x1f6)) {
        iVar26 = iVar14 + 10;
        iVar14 = iVar14 + 2;
        *(short *)((int)DAT_8032eea8 + iVar26) = *(short *)(*piVar23 + 0x1f6);
      }
      if (0 < *(short *)(*piVar23 + 0x1f8)) {
        iVar26 = iVar14 + 10;
        iVar14 = iVar14 + 2;
        *(short *)((int)DAT_8032eea8 + iVar26) = *(short *)(*piVar23 + 0x1f8);
      }
      if (0 < *(short *)(*piVar23 + 0x1fa)) {
        iVar26 = iVar14 + 10;
        iVar14 = iVar14 + 2;
        *(short *)((int)DAT_8032eea8 + iVar26) = *(short *)(*piVar23 + 0x1fa);
      }
      if (0 < *(short *)(*piVar23 + 0x1fc)) {
        iVar26 = iVar14 + 10;
        iVar14 = iVar14 + 2;
        *(short *)((int)DAT_8032eea8 + iVar26) = *(short *)(*piVar23 + 0x1fc);
      }
    }
    iVar15 = iVar15 + 4;
    iVar16 = iVar16 + 1;
    iVar42 = iVar42 + -1;
    iVar26 = iVar18;
  } while (iVar42 != 0);
  *DAT_8032eea8 = iVar17;
  puVar11 = (undefined2 *)GetBossArtifact__5CGameFii(&Game.game,*DAT_8032eea8,iVar13);
  iVar42 = 0;
  iVar26 = 0;
  *(undefined2 *)((int)DAT_8032eea8 + 0x12) = *puVar11;
  *(undefined2 *)(DAT_8032eea8 + 5) = puVar11[1];
  *(undefined2 *)((int)DAT_8032eea8 + 0x16) = puVar11[2];
  *(undefined2 *)(DAT_8032eea8 + 6) = puVar11[3];
  *(undefined *)((int)DAT_8032eea8 + 9) = 0;
  iVar13 = 2;
  do {
    if (*(short *)((int)DAT_8032eea8 + iVar26 + 10) < 0) {
      *(byte *)((int)DAT_8032eea8 + 9) = *(byte *)((int)DAT_8032eea8 + 9) | (byte)(1 << iVar42);
    }
    if (*(short *)((int)DAT_8032eea8 + iVar26 + 0xc) < 0) {
      *(byte *)((int)DAT_8032eea8 + 9) = *(byte *)((int)DAT_8032eea8 + 9) | (byte)(1 << iVar42 + 1);
    }
    if (*(short *)((int)DAT_8032eea8 + iVar26 + 0xe) < 0) {
      *(byte *)((int)DAT_8032eea8 + 9) = *(byte *)((int)DAT_8032eea8 + 9) | (byte)(1 << iVar42 + 2);
    }
    if (*(short *)((int)DAT_8032eea8 + iVar26 + 0x10) < 0) {
      *(byte *)((int)DAT_8032eea8 + 9) = *(byte *)((int)DAT_8032eea8 + 9) | (byte)(1 << iVar42 + 3);
    }
    iVar26 = iVar26 + 8;
    iVar42 = iVar42 + 4;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  iVar42 = 0;
  for (iVar26 = 0; iVar26 < *DAT_8032eea8; iVar26 = iVar26 + 1) {
    iVar13 = 0;
    iVar14 = 0;
    puVar38 = Game.game.m_scriptFoodBase + *(int *)((int)DAT_8032eea8 + iVar42 + 0x1c);
    do {
      sVar2 = *(short *)((int)DAT_8032eea8 + iVar14 + 10);
      if (0 < sVar2) {
        iVar15 = GetItemType__8CMenuPcsFii(menuPcs,(int)sVar2,1);
        if (iVar15 == 2) {
          iVar15 = (int)*(short *)((int)DAT_8032eea8 + iVar14 + 10);
          if (*(short *)(*puVar38 + (iVar15 + -0x9f) * 2 + 0x136) == iVar15) {
            *(uint *)((int)DAT_8032eea8 + iVar42 + 0x38) =
                 *(uint *)((int)DAT_8032eea8 + iVar42 + 0x38) | 1 << iVar13;
          }
        }
        else if (0x40 < *(ushort *)(*puVar38 + 0xb4) + 1) {
          *(uint *)((int)DAT_8032eea8 + iVar42 + 0x38) =
               *(uint *)((int)DAT_8032eea8 + iVar42 + 0x38) | 1 << iVar13;
        }
      }
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 2;
    } while (iVar13 < 8);
    iVar42 = iVar42 + 0x2c;
  }
  piVar35 = local_c8;
  local_c8[0] = 0;
  local_c8[1] = 1;
  local_c8[2] = 2;
  local_c8[3] = 3;
  piVar23 = piVar35;
  for (iVar26 = 0; iVar26 < *DAT_8032eea8; iVar26 = iVar26 + 1) {
    iVar42 = iVar26 + 1;
    iVar13 = *piVar23;
    piVar24 = local_c8 + iVar42;
    for (; iVar42 < *DAT_8032eea8; iVar42 = iVar42 + 1) {
      iVar14 = *piVar24;
      iVar18 = DAT_8032eea8[iVar13 * 0xb + 10];
      iVar15 = DAT_8032eea8[iVar13 * 0xb + 0xb];
      iVar19 = DAT_8032eea8[iVar14 * 0xb + 10];
      iVar16 = DAT_8032eea8[iVar14 * 0xb + 0xb];
      iVar17 = DAT_8032eea8[iVar13 * 0xb + 0xc];
      iVar14 = DAT_8032eea8[iVar14 * 0xb + 0xc];
      uVar8 = rand();
      if ((((iVar18 < iVar19) || ((iVar18 == iVar19 && (iVar17 < iVar14)))) ||
          ((iVar18 == iVar19 && ((iVar17 == iVar14 && (iVar15 < iVar16)))))) ||
         ((iVar18 == iVar19 && (((iVar17 == iVar14 && (iVar15 == iVar16)) && ((uVar8 & 1) != 0))))))
      {
        iVar13 = *piVar23;
        *piVar23 = *piVar24;
        *piVar24 = iVar13;
        iVar13 = *piVar23;
      }
      piVar24 = piVar24 + 1;
    }
    piVar23 = piVar23 + 1;
  }
  for (iVar26 = 0; iVar26 < *DAT_8032eea8; iVar26 = iVar26 + 1) {
    iVar42 = *piVar35;
    DAT_8032eea8[iVar42 * 0xb + 0xd] = iVar26;
    if (iVar26 == 0) {
      DAT_8032eea8[1] = DAT_8032eea8[iVar42 * 0xb + 10];
    }
    piVar35 = piVar35 + 1;
  }
  iVar26 = 0;
  *(undefined4 *)&menuPcs->field_0x774 = 0;
  *(undefined4 *)&menuPcs->field_0x778 = 0;
  *(undefined4 *)&menuPcs->field_0x77c = 0;
  *(undefined4 *)&menuPcs->field_0x780 = 0;
  *(undefined4 *)&menuPcs->field_0x784 = 0;
  *(undefined4 *)&menuPcs->field_0x788 = 0;
  *(undefined4 *)&menuPcs->field_0x78c = 0;
  *(undefined4 *)&menuPcs->field_0x790 = 0;
  *(undefined4 *)&menuPcs->field_0x794 = 0;
  *(undefined4 *)&menuPcs->field_0x798 = 0;
  *(undefined4 *)&menuPcs->field_0x79c = 0;
  *(undefined4 *)&menuPcs->field_0x7a0 = 0;
  *(undefined4 *)&menuPcs->field_0x7a4 = 0;
  *(undefined4 *)&menuPcs->field_0x7a8 = 0;
  *(undefined4 *)&menuPcs->field_0x7ac = 0;
  *(undefined4 *)&menuPcs->field_0x7b0 = 0;
  *(undefined4 *)&menuPcs->field_0x7b4 = 0;
  *(undefined4 *)&menuPcs->field_0x7b8 = 0;
  *(undefined4 *)&menuPcs->field_0x7bc = 0;
  *(undefined4 *)&menuPcs->field_0x7c0 = 0;
  *(undefined4 *)&menuPcs->field_0x7c4 = 0;
  *(undefined4 *)&menuPcs->field_0x7c8 = 0;
  *(undefined4 *)&menuPcs->field_0x7cc = 0;
  *(undefined4 *)&menuPcs->field_0x7d0 = 0;
  iVar42 = *DAT_8032eea8;
  pCVar36 = menuPcs;
  do {
    if (iVar42 << 1 <= iVar26) break;
    pCVar12 = (CCharaPcsCHandle *)
              __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                        (0x194,(CCharaPcsCHandle *)MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,
                         0x183);
    if (pCVar12 != (CCharaPcsCHandle *)0x0) {
      pCVar12 = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(pCVar12);
    }
    *(CCharaPcsCHandle **)&pCVar36->field_0x774 = pCVar12;
    Add__Q29CCharaPcs7CHandleFv(*(CCharaPcsCHandle **)&pCVar36->field_0x774);
    uVar8 = DAT_8032eea8[(iVar26 - (iVar26 / iVar42) * iVar42) * 0xb + 7] + 0x83;
    if (iVar26 < iVar42) {
      uVar8 = DAT_8032eea8[(iVar26 - (iVar26 / iVar42) * iVar42) * 0xb + 7] + 0x87;
    }
    LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
              (*(undefined4 *)&pCVar36->field_0x774,3,uVar8 & 0xfff,uVar8 >> 0xc & 0xf,0,0xffffffff,
               0,0);
    puVar1 = &pCVar36->field_0x774;
    iVar26 = iVar26 + 1;
    pCVar36 = (CMenuPcs *)&pCVar36->field_0x4;
    *(undefined4 *)(*(int *)puVar1 + 8) = 0x300543;
  } while (iVar26 < 0x18);
  iVar13 = 0;
  iVar42 = 0;
  pCVar39 = &menuPcs->process + iVar26;
  do {
    iVar14 = (int)*(short *)((int)DAT_8032eea8 + iVar42 + 10);
    if (iVar14 < 1) {
      pCVar39[0x1dd] = (CManager)0x0;
    }
    else {
      pCVar12 = (CCharaPcsCHandle *)
                __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                          (0x194,(CCharaPcsCHandle *)MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2
                           ,0x19c);
      if (pCVar12 != (CCharaPcsCHandle *)0x0) {
        pCVar12 = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(pCVar12);
      }
      pCVar39[0x1dd] = (CProcess)pCVar12;
      Add__Q29CCharaPcs7CHandleFv(*(CCharaPcsCHandle **)(pCVar39 + 0x1dd));
      uVar3 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar14 * 0x48 + 2);
      uVar25 = uVar3 & 0xfff;
      LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
                ((CManager)pCVar39[0x1dd],3,uVar25,uVar3 >> 0xc,0,0xffffffff,0,0);
      *(undefined4 *)(*(int *)(pCVar39 + 0x1dd) + 8) = 0x300543;
      if (uVar25 == 0x79) {
        sVar2 = *(short *)((int)DAT_8032eea8 + iVar42 + 10);
        if (sVar2 == 0xdf) {
          uVar10 = 0x75;
        }
        else if (sVar2 == 0xe0) {
          uVar10 = 0x76;
        }
        else if (sVar2 == 0xe1) {
          uVar10 = 0x77;
        }
        else if (sVar2 == 0xe2) {
          uVar10 = 0x78;
        }
        else {
          if (sVar2 != 0xe3) goto LAB_8013e1d0;
          uVar10 = 0x79;
        }
        BindEffect__8CMenuPcsFiii(menuPcs,iVar26,uVar10,0xffffffff);
      }
    }
LAB_8013e1d0:
    iVar13 = iVar13 + 1;
    iVar26 = iVar26 + 1;
    iVar42 = iVar42 + 2;
    pCVar39 = pCVar39 + 1;
    if (7 < iVar13) {
      SetStartBonusFlg__8GbaQueueFv(&GbaQue);
      iVar26 = 0;
      iVar42 = -0x7fde1140;
      do {
        if (*(CCaravanWork **)(iVar42 + 0xc5c0) != (CCaravanWork *)0x0) {
          SafeDeleteTempItem__12CCaravanWorkFv(*(CCaravanWork **)(iVar42 + 0xc5c0));
          SortBeforeReturnWorldMap__12CCaravanWorkFv(*(CCaravanWork **)(iVar42 + 0xc5c0));
        }
        iVar26 = iVar26 + 1;
        iVar42 = iVar42 + 4;
      } while (iVar26 < 4);
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      DAT_8032eeac = 0;
      DAT_8032eead = 0;
      DAT_8032eeae = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c) = 0;
      ClearAll__5CWindFv(&Wind);
      menuPcs->field_0x8c = 0;
      menuPcs->field_0x8d = 0;
      return;
    }
  } while( true );
}

