// Function: EquipDraw__8CMenuPcsFv
// Entry: 8015bc50
// Size: 4280 bytes

/* WARNING: Removing unreachable block (ram,0x8015ccec) */
/* WARNING: Removing unreachable block (ram,0x8015cce4) */
/* WARNING: Removing unreachable block (ram,0x8015ccdc) */
/* WARNING: Removing unreachable block (ram,0x8015ccd4) */
/* WARNING: Removing unreachable block (ram,0x8015cccc) */
/* WARNING: Removing unreachable block (ram,0x8015ccc4) */
/* WARNING: Removing unreachable block (ram,0x8015ccbc) */
/* WARNING: Removing unreachable block (ram,0x8015bc90) */
/* WARNING: Removing unreachable block (ram,0x8015bc88) */
/* WARNING: Removing unreachable block (ram,0x8015bc80) */
/* WARNING: Removing unreachable block (ram,0x8015bc78) */
/* WARNING: Removing unreachable block (ram,0x8015bc70) */
/* WARNING: Removing unreachable block (ram,0x8015bc68) */
/* WARNING: Removing unreachable block (ram,0x8015bc60) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void EquipDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  uint32_t uVar3;
  undefined4 *puVar4;
  short *psVar5;
  char cVar6;
  short *psVar7;
  int iVar8;
  int iVar9;
  uint32_t uVar10;
  CFont *pCVar11;
  int unaff_r17;
  short *psVar12;
  int32_t iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  double dVar19;
  double dVar20;
  double in_f26;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  undefined auStack_120 [4];
  undefined4 local_11c;
  undefined auStack_118 [4];
  undefined4 local_114;
  undefined auStack_110 [4];
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined auStack_100 [4];
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined local_f0;
  undefined local_ef;
  undefined local_ee;
  undefined local_ed;
  undefined local_ec;
  undefined local_eb;
  undefined local_ea;
  undefined local_e9;
  undefined local_e8;
  undefined local_e7;
  undefined local_e6;
  undefined local_e5;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  int local_c0;
  
  bVar2 = false;
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  uVar3 = Game.game.m_scriptFoodBase[0];
  local_c0 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x30);
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  psVar12 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  for (iVar9 = 0; iVar9 < **(short **)&menuPcs->field_0x850; iVar9 = iVar9 + 1) {
    if (-1 < *(int *)(psVar12 + 0xe)) {
      local_e0 = (double)CONCAT44(0x43300000,(int)*psVar12 ^ 0x80000000);
      dVar19 = (double)(float)(local_e0 - DOUBLE_80332ed8);
      dVar23 = (double)*(float *)(psVar12 + 4);
      local_d8 = (double)CONCAT44(0x43300000,(int)psVar12[1] ^ 0x80000000);
      dVar24 = (double)*(float *)(psVar12 + 6);
      dVar21 = (double)(float)(local_d8 - DOUBLE_80332ed8);
      local_d0 = (double)CONCAT44(0x43300000,(int)psVar12[2] ^ 0x80000000);
      in_f26 = (double)(float)(local_d0 - DOUBLE_80332ed8);
      local_c8 = (double)CONCAT44(0x43300000,(int)psVar12[3] ^ 0x80000000);
      dVar22 = (double)(float)(local_c8 - DOUBLE_80332ed8);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(int *)(psVar12 + 0xe));
      if ((sVar1 == 1) && (iVar9 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
        dVar24 = (double)(float)(dVar24 + dVar22);
      }
      local_c8 = (double)(longlong)(int)(FLOAT_80332ee4 * *(float *)(psVar12 + 8));
      local_f4 = CONCAT31(0xffffff,(char)(int)(FLOAT_80332ee4 * *(float *)(psVar12 + 8)));
      local_f8 = local_f4;
      GXSetChanMatColor(4,&local_f8);
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar19,dVar21,in_f26,dVar22,dVar23,dVar24,(double)*(float *)(psVar12 + 10),
                 (double)*(float *)(psVar12 + 10),&MenuPcs,0);
    }
    psVar12 = psVar12 + 0x20;
  }
  psVar12 = *(short **)&menuPcs->field_0x850 + 4;
  iVar9 = 0;
  uVar10 = uVar3;
  do {
    if (-1 < *(short *)(uVar10 + 0xac)) {
      local_d8 = (double)CONCAT44(0x43300000,(int)psVar12[1] + 6U ^ 0x80000000);
      local_c8 = (double)(CONCAT44(0x43300000,(int)*psVar12 + psVar12[2] + -0x10) ^ 0x80000000);
      iVar8 = (int)((float)(local_d8 - DOUBLE_80332ed8) - FLOAT_80332ee0);
      local_e0 = (double)(longlong)iVar8;
      local_d0 = (double)(longlong)(int)(local_c8 - DOUBLE_80332ed8);
      DrawSingleIcon__8CMenuPcsFiiifif
                ((double)*(float *)(psVar12 + 8),menuPcs,
                 (int)*(short *)(uVar3 + *(short *)(uVar10 + 0xac) * 2 + 0xb6),
                 (int)(local_c8 - DOUBLE_80332ed8),iVar8,0);
    }
    iVar9 = iVar9 + 1;
    psVar12 = psVar12 + 0x20;
    uVar10 = uVar10 + 2;
  } while (iVar9 < 4);
  pCVar11 = *(CFont **)&menuPcs->field_0x108;
  SetMargin__5CFontFf(FLOAT_80332ee0,pCVar11);
  SetShadow__5CFontFi(pCVar11,0);
  SetScale__5CFontFf(FLOAT_80332ee8,pCVar11);
  DrawInit__5CFontFv(pCVar11);
  psVar12 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  iVar9 = 0;
  uVar10 = uVar3;
  do {
    if (-1 < *(short *)(uVar10 + 0xac)) {
      local_c8 = (double)(longlong)(int)(FLOAT_80332ee4 * *(float *)(psVar12 + 8));
      puVar4 = (undefined4 *)
               __ct__6CColorFUcUcUcUc
                         (auStack_100,0xff,0xff,0xff,(int)(FLOAT_80332ee4 * *(float *)(psVar12 + 8))
                         );
      local_fc = *puVar4;
      SetColor__5CFontF8_GXColor(pCVar11,&local_fc);
      iVar8 = (int)*(short *)(uVar3 + *(short *)(uVar10 + 0xac) * 2 + 0xb6);
      iVar13 = Game.game.m_cFlatDataArr[1].m_table[0].index[iVar8 * 5 + 4];
      if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) == 0) &&
         (iVar9 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
        bVar2 = true;
        unaff_r17 = iVar8;
      }
      dVar19 = (double)GetWidth__5CFontFPc(pCVar11,iVar13);
      local_d0 = (double)CONCAT44(0x43300000,(int)psVar12[2] ^ 0x80000000);
      local_d8 = (double)CONCAT44(0x43300000,(int)*psVar12 ^ 0x80000000);
      local_c8 = (double)CONCAT44(0x43300000,(int)psVar12[1] + 0xbU ^ 0x80000000);
      dVar21 = (double)(float)(local_c8 - DOUBLE_80332ed8);
      SetPosX__5CFontFf((float)((double)(float)((double)(float)(local_d0 - DOUBLE_80332ed8) - dVar19
                                               ) * DOUBLE_80332ed0 + (local_d8 - DOUBLE_80332ed8)),
                        pCVar11);
      SetPosY__5CFontFf((float)(dVar21 - (double)FLOAT_80332eec),pCVar11);
      Draw__5CFontFPc(pCVar11,iVar13);
    }
    iVar9 = iVar9 + 1;
    psVar12 = psVar12 + 0x20;
    uVar10 = uVar10 + 2;
  } while (iVar9 < 4);
  DrawInit__8CMenuPcsFv(menuPcs);
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x32) != 0) {
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    iVar8 = 0;
    psVar12 = *(short **)&menuPcs->field_0x850 + **(short **)&menuPcs->field_0x850 * 0x20 + 4;
    psVar5 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    iVar9 = (int)*psVar5;
    for (iVar15 = (int)**(short **)&menuPcs->field_0x850; uVar10 = Game.game.m_scriptFoodBase[0],
        iVar15 < (*(short **)&menuPcs->field_0x850)[1]; iVar15 = iVar15 + 1) {
      iVar16 = *(int *)(psVar12 + 0xe);
      if (-1 < iVar16) {
        local_c8 = (double)CONCAT44(0x43300000,(int)*psVar12 ^ 0x80000000);
        dVar24 = (double)(float)(local_c8 - DOUBLE_80332ed8);
        dVar21 = (double)*(float *)(psVar12 + 4);
        local_d0 = (double)CONCAT44(0x43300000,(int)psVar12[1] ^ 0x80000000);
        dVar19 = (double)*(float *)(psVar12 + 6);
        dVar23 = (double)(float)(local_d0 - DOUBLE_80332ed8);
        local_d8 = (double)CONCAT44(0x43300000,(int)psVar12[2] ^ 0x80000000);
        in_f26 = (double)(float)(local_d8 - DOUBLE_80332ed8);
        local_e0 = (double)CONCAT44(0x43300000,(int)psVar12[3] ^ 0x80000000);
        dVar22 = (double)(float)(local_e0 - DOUBLE_80332ed8);
        if (iVar15 == **(short **)&menuPcs->field_0x850) {
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar12 + 0xe));
          local_f4 = 0xffffffff;
          local_f0 = 0xff;
          local_ef = 0xff;
          local_ee = 0xff;
          local_ed = 0xff;
          local_ec = 0xff;
          local_eb = 0xff;
          local_ea = 0xff;
          local_e9 = 0xff;
          local_e8 = 0xff;
          local_e7 = 0xff;
          local_e6 = 0xff;
          local_e5 = 0xff;
          local_104 = 0xffffffff;
          GXSetChanMatColor(4,&local_104);
          in_f26 = (double)(float)((double)*(float *)(psVar12 + 8) * in_f26);
          if ((double)FLOAT_80332eb8 < in_f26) {
            DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                      (dVar24,dVar23,in_f26,dVar22,dVar21,dVar19,(double)FLOAT_80332ee0,
                       (double)FLOAT_80332ee0,&MenuPcs,0,&local_f4);
            dVar24 = (double)(float)(dVar24 + in_f26);
            dVar21 = (double)(float)(dVar21 + in_f26);
          }
          if ((double)FLOAT_80332eb8 < in_f26) {
            local_c8 = (double)(CONCAT44(0x43300000,(int)psVar12[2]) ^ 0x80000000);
            if (in_f26 < (double)(float)(local_c8 - DOUBLE_80332ed8)) {
              local_f0 = 0xff;
              local_ef = 0xff;
              local_ee = 0xff;
              local_ed = 0;
              local_e8 = 0xff;
              local_e7 = 0xff;
              local_e6 = 0xff;
              local_e5 = 0;
              local_c8 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar12 + 0x14)) ^ 0x80000000)
              ;
              local_d0 = (double)CONCAT44(0x43300000,(int)psVar12[2] ^ 0x80000000);
              in_f26 = (double)((float)(DOUBLE_80332ec0 / (local_c8 - DOUBLE_80332ed8)) *
                               (float)(local_d0 - DOUBLE_80332ed8));
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (dVar24,dVar23,in_f26,dVar22,dVar21,dVar19,(double)FLOAT_80332ee0,
                         (double)FLOAT_80332ee0,&MenuPcs,0,&local_f4);
            }
          }
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
        }
        else {
          dVar20 = (double)*(float *)(psVar12 + 8);
          if (iVar16 == 0x37) {
            iVar18 = iVar8 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
            if ((iVar18 < 1) || (iVar9 <= iVar18)) {
              if (iVar18 < iVar9) {
                psVar7 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
                iVar17 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
                if ((iVar18 < 0) || (*psVar7 <= iVar18)) {
                  uVar14 = 0;
                }
                else if (iVar18 == 0) {
                  if (iVar17 < 3) {
                    uVar14 = 0;
                  }
                  else {
                    uVar14 = (uint)(int)*(short *)(uVar10 + iVar17 * 2 + 0xac) >> 0x1f ^ 1;
                  }
                }
                else {
                  iVar18 = (int)*(short *)(uVar10 + psVar7[iVar18] * 2 + 0xb6);
                  uVar14 = ChkEquipPossible__8CMenuPcsFi(menuPcs,iVar18);
                  if (((uVar14 & 0xff) != 0) &&
                     (iVar18 = GetEquipType__8CMenuPcsFi(menuPcs,iVar18), iVar18 != iVar17)) {
                    uVar14 = 0;
                  }
                }
                if ((uVar14 & 0xff) != 0) goto LAB_8015c53c;
              }
              iVar16 = 0x34;
              dVar20 = (double)(float)(DOUBLE_80332ed0 * (double)*(float *)(psVar12 + 8));
            }
            else {
              cVar6 = EquipChk__8CMenuPcsFi(menuPcs,(int)psVar5[iVar18]);
              uVar10 = Game.game.m_scriptFoodBase[0];
              if ((iVar18 < iVar9) && (cVar6 == '\0')) {
                psVar7 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
                iVar17 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
                if ((iVar18 < 0) || (*psVar7 <= iVar18)) {
                  uVar14 = 0;
                }
                else if (iVar18 == 0) {
                  if (iVar17 < 3) {
                    uVar14 = 0;
                  }
                  else {
                    uVar14 = (uint)(int)*(short *)(uVar10 + iVar17 * 2 + 0xac) >> 0x1f ^ 1;
                  }
                }
                else {
                  iVar18 = (int)*(short *)(uVar10 + psVar7[iVar18] * 2 + 0xb6);
                  uVar14 = ChkEquipPossible__8CMenuPcsFi(menuPcs,iVar18);
                  if (((uVar14 & 0xff) != 0) &&
                     (iVar18 = GetEquipType__8CMenuPcsFi(menuPcs,iVar18), iVar18 != iVar17)) {
                    uVar14 = 0;
                  }
                }
                if ((uVar14 & 0xff) != 0) goto LAB_8015c53c;
              }
              if (cVar6 != '\0') {
                local_c8 = (double)(longlong)(int)(dVar24 - (double)FLOAT_80332ef0);
                iVar16 = (int)((double)(float)(dVar22 - (double)FLOAT_80332ef4) * DOUBLE_80332ed0 +
                              dVar23);
                local_d0 = (double)(longlong)iVar16;
                DrawEquipMark__8CMenuPcsFiif
                          ((double)*(float *)(psVar12 + 8),menuPcs,
                           (int)(dVar24 - (double)FLOAT_80332ef0),iVar16);
              }
              iVar16 = 0x34;
              dVar20 = (double)(float)(DOUBLE_80332ed0 * (double)*(float *)(psVar12 + 8));
            }
LAB_8015c53c:
            if ((iVar16 == 0x37) && (iVar8 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x28))) {
              dVar19 = (double)(float)(dVar19 + dVar22);
            }
            iVar8 = iVar8 + 1;
          }
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar16);
          local_c8 = (double)(longlong)(int)((double)FLOAT_80332ee4 * dVar20);
          local_f4 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332ee4 * dVar20));
          local_108 = local_f4;
          GXSetChanMatColor(4,&local_108);
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar24,dVar23,in_f26,dVar22,dVar21,dVar19,(double)*(float *)(psVar12 + 10),
                     (double)*(float *)(psVar12 + 10),&MenuPcs,0);
        }
      }
      psVar12 = psVar12 + 0x20;
    }
  }
  if (local_c0 == 1) {
    pCVar11 = *(CFont **)&menuPcs->field_0x108;
    SetMargin__5CFontFf(FLOAT_80332ee0,pCVar11);
    SetShadow__5CFontFi(pCVar11,0);
    SetScale__5CFontFf(FLOAT_80332ee8,pCVar11);
    DrawInit__5CFontFv(pCVar11);
    psVar5 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    psVar7 = *(short **)&menuPcs->field_0x850;
    iVar16 = (int)*psVar5;
    iVar15 = (int)*psVar7;
    iVar9 = iVar15 << 6;
    iVar8 = psVar7[1] - iVar15;
    if (iVar15 < psVar7[1]) {
      do {
        psVar12 = (short *)((int)psVar7 + iVar9 + 8);
        if (*(int *)(psVar12 + 0xe) == 0x37) break;
        iVar9 = iVar9 + 0x40;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    dVar19 = (double)FLOAT_80332ee4;
    psVar7 = psVar12;
    for (iVar9 = 0;
        (iVar9 < 8 &&
        (iVar8 = iVar9 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34), iVar8 < iVar16));
        iVar9 = iVar9 + 1) {
      local_c8 = (double)(longlong)(int)(dVar19 * (double)*(float *)(psVar12 + 8));
      puVar4 = (undefined4 *)
               __ct__6CColorFUcUcUcUc
                         (auStack_110,0xff,0xff,0xff,(int)(dVar19 * (double)*(float *)(psVar12 + 8))
                         );
      local_10c = *puVar4;
      SetColor__5CFontF8_GXColor(pCVar11,&local_10c);
      if (iVar8 == 0) {
        iVar13 = GetMenuStr__8CMenuPcsFi(menuPcs,0xb);
LAB_8015c744:
        GetWidth__5CFontFPc(pCVar11,iVar13);
        local_c8 = (double)(CONCAT44(0x43300000,psVar7[1] + 0xb) ^ 0x80000000);
        local_d0 = (double)(CONCAT44(0x43300000,*psVar7 + 0x1c) ^ 0x80000000);
        dVar21 = (double)(float)(local_c8 - DOUBLE_80332ed8);
        SetPosX__5CFontFf((float)(local_d0 - DOUBLE_80332ed8),pCVar11);
        SetPosY__5CFontFf((float)(dVar21 - (double)FLOAT_80332eec),pCVar11);
        Draw__5CFontFPc(pCVar11,iVar13);
      }
      else if ((iVar8 < iVar16) && (-1 < psVar5[iVar8])) {
        iVar15 = (int)*(short *)(uVar3 + psVar5[iVar8] * 2 + 0xb6);
        iVar13 = Game.game.m_cFlatDataArr[1].m_table[0].index[iVar15 * 5 + 4];
        if (iVar8 == (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28) +
                     (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34)) {
          bVar2 = true;
          unaff_r17 = iVar15;
        }
        goto LAB_8015c744;
      }
      psVar7 = psVar7 + 0x20;
    }
    DrawInit__8CMenuPcsFv(menuPcs);
    psVar7 = psVar12;
    for (iVar9 = 0;
        (iVar9 < 8 &&
        (iVar8 = iVar9 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34), iVar8 < iVar16));
        iVar9 = iVar9 + 1) {
      if ((0 < iVar8) && (-1 < psVar5[iVar8])) {
        local_d8 = (double)CONCAT44(0x43300000,(int)psVar7[1] + 6U ^ 0x80000000);
        local_c8 = (double)(CONCAT44(0x43300000,(int)*psVar7 + psVar7[2] + -0x10) ^ 0x80000000);
        iVar15 = (int)((float)(local_d8 - DOUBLE_80332ed8) - FLOAT_80332ee0);
        local_e0 = (double)(longlong)iVar15;
        local_d0 = (double)(longlong)(int)(local_c8 - DOUBLE_80332ed8);
        DrawSingleIcon__8CMenuPcsFiiifif
                  ((double)*(float *)(psVar12 + 8),menuPcs,
                   (int)*(short *)(uVar3 + psVar5[iVar8] * 2 + 0xb6),
                   (int)(local_c8 - DOUBLE_80332ed8),iVar15,0);
      }
      psVar7 = psVar7 + 0x20;
    }
  }
  if ((local_c0 == 1) && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1)) {
    psVar12 = *(short **)&menuPcs->field_0x850 + **(short **)&menuPcs->field_0x850 * 0x20 + 4;
    psVar5 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    dVar19 = (double)CalcListPos__8CMenuPcsFiii
                               (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34),
                                (int)*psVar5,0);
    if ((double)FLOAT_80332eb8 < dVar19) {
      local_c8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
      local_d0 = (double)CONCAT44(0x43300000,(int)psVar12[1] ^ 0x80000000);
      DrawListPosMark__8CMenuPcsFfff
                ((double)(float)(local_c8 - DOUBLE_80332ed8),
                 (double)(float)(local_d0 - DOUBLE_80332ed8),dVar19,menuPcs);
    }
  }
  if (((local_c0 == 0) && (sVar1 == 1)) ||
     ((local_c0 != 0 && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1)))) {
    if (local_c0 == 0) {
      psVar12 = (short *)(*(int *)&menuPcs->field_0x850 +
                         *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x40 + 8);
      sVar1 = *psVar12;
      local_d0 = (double)(CONCAT44(0x43300000,psVar12[3] + -0x20) ^ 0x80000000);
      local_d8 = (double)(CONCAT44(0x43300000,(int)psVar12[1]) ^ 0x80000000);
      dVar19 = (local_d0 - DOUBLE_80332ed8) * DOUBLE_80332ed0 + (local_d8 - DOUBLE_80332ed8);
    }
    else {
      psVar5 = *(short **)&menuPcs->field_0x850;
      iVar15 = (int)*psVar5;
      iVar9 = iVar15 << 6;
      iVar8 = psVar5[1] - iVar15;
      if (iVar15 < psVar5[1]) {
        do {
          psVar12 = (short *)((int)psVar5 + iVar9 + 8);
          if (*(int *)((int)psVar5 + iVar9 + 0x24) == 0x37) break;
          iVar9 = iVar9 + 0x40;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      psVar12 = psVar12 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) * 0x20;
      sVar1 = *psVar12;
      local_d0 = (double)(CONCAT44(0x43300000,psVar12[3] + -0x20) ^ 0x80000000);
      local_d8 = (double)(CONCAT44(0x43300000,(int)psVar12[1]) ^ 0x80000000);
      dVar19 = (local_d0 - DOUBLE_80332ed8) * DOUBLE_80332ed0 + (local_d8 - DOUBLE_80332ed8);
    }
    local_d8 = (double)(longlong)(int)dVar19;
    iVar9 = (int)System.m_frameCounter >> 0x1f;
    local_c8 = (double)(CONCAT44(0x43300000,
                                 (iVar9 * 8 | System.m_frameCounter * 0x20000000 + iVar9 >> 0x1d) -
                                 iVar9) ^ 0x80000000);
    iVar9 = (int)((float)((double)CONCAT44(0x43300000,(int)sVar1 - 0x14U ^ 0x80000000) -
                         DOUBLE_80332ed8) + (float)(local_c8 - DOUBLE_80332ed8));
    local_d0 = (double)(longlong)iVar9;
    DrawCursor__8CMenuPcsFiif((double)FLOAT_80332ee0,menuPcs,iVar9,(int)dVar19);
  }
  iVar9 = *(int *)&menuPcs->field_0x82c;
  iVar8 = (int)*(short *)(iVar9 + 0x30);
  iVar15 = (int)*(short *)(iVar9 + iVar8 * 2 + 0x26) + (int)*(short *)(iVar9 + 0x34);
  if (iVar8 == 1) {
    iVar16 = (int)**(short **)&menuPcs->field_0x850;
  }
  else {
    iVar16 = 0;
  }
  uVar14 = (uint)(FLOAT_80332ee4 * *(float *)(*(int *)&menuPcs->field_0x850 + iVar16 * 0x40 + 0x18))
  ;
  local_c8 = (double)(longlong)(int)uVar14;
  if (!bVar2) {
    unaff_r17 = -1;
  }
  if ((iVar15 < 1) && (iVar8 == 1)) {
    unaff_r17 = -1;
  }
  if (((*(short *)(iVar9 + 0x30) == 0) && (*(short *)(iVar9 + 0x2c) == 0)) && (unaff_r17 == -1)) {
    unaff_r17 = 0x267;
  }
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_118,0xff,0xff,0xff,uVar14 & 0xff);
  local_114 = *puVar4;
  local_d0 = (double)(longlong)(int)FLOAT_80332f00;
  local_c8 = (double)(longlong)
                     (int)-(float)(in_f26 * (double)FLOAT_80332efc - (double)FLOAT_80332ef8);
  DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(menuPcs,unaff_r17);
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) == 1) {
    uVar14 = (uint)(FLOAT_80332ee4 *
                   *(float *)(*(short **)&menuPcs->field_0x850 +
                             **(short **)&menuPcs->field_0x850 * 0x20 + 0xc));
    local_c8 = (double)(longlong)(int)uVar14;
    if (iVar15 < 1) {
      puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_120,0xff,0xff,0xff,uVar14 & 0xff);
      local_11c = *puVar4;
      DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(menuPcs,0x265);
    }
  }
  return;
}

