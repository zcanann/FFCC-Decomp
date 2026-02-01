// Function: ItemDraw__8CMenuPcsFv
// Entry: 80159df4
// Size: 2596 bytes

/* WARNING: Removing unreachable block (ram,0x8015a7fc) */
/* WARNING: Removing unreachable block (ram,0x8015a7f4) */
/* WARNING: Removing unreachable block (ram,0x8015a7ec) */
/* WARNING: Removing unreachable block (ram,0x8015a7e4) */
/* WARNING: Removing unreachable block (ram,0x8015a7dc) */
/* WARNING: Removing unreachable block (ram,0x8015a7d4) */
/* WARNING: Removing unreachable block (ram,0x8015a7cc) */
/* WARNING: Removing unreachable block (ram,0x80159e34) */
/* WARNING: Removing unreachable block (ram,0x80159e2c) */
/* WARNING: Removing unreachable block (ram,0x80159e24) */
/* WARNING: Removing unreachable block (ram,0x80159e1c) */
/* WARNING: Removing unreachable block (ram,0x80159e14) */
/* WARNING: Removing unreachable block (ram,0x80159e0c) */
/* WARNING: Removing unreachable block (ram,0x80159e04) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ItemDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  short sVar2;
  short sVar3;
  bool bVar4;
  uint32_t uVar5;
  int iVar6;
  char cVar8;
  undefined4 *puVar7;
  short *psVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  CFont *font;
  int unaff_r26;
  short *psVar14;
  int iVar15;
  int32_t iVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double in_f29;
  double dVar21;
  double dVar22;
  undefined auStack_f0 [4];
  undefined4 local_ec;
  undefined auStack_e8 [4];
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined local_d4;
  undefined local_d3;
  undefined local_d2;
  undefined local_d1;
  undefined local_d0;
  undefined local_cf;
  undefined local_ce;
  undefined local_cd;
  undefined local_cc;
  undefined local_cb;
  undefined local_ca;
  undefined local_c9;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  
  bVar4 = false;
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  uVar5 = Game.game.m_scriptFoodBase[0];
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x30);
  psVar14 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  iVar15 = 0;
  iVar6 = SingGetLetterAttachflg__8CMenuPcsFv(menuPcs);
  for (iVar11 = 0; iVar11 < **(short **)&menuPcs->field_0x850; iVar11 = iVar11 + 1) {
    iVar10 = *(int *)(psVar14 + 0xe);
    if (-1 < iVar10) {
      local_c8 = (double)CONCAT44(0x43300000,(int)*psVar14 ^ 0x80000000);
      dVar19 = (double)*(float *)(psVar14 + 4);
      dVar22 = (double)(float)(local_c8 - DOUBLE_80332ea0);
      dVar18 = (double)*(float *)(psVar14 + 6);
      local_c0 = (double)CONCAT44(0x43300000,(int)psVar14[1] ^ 0x80000000);
      dVar21 = (double)(float)(local_c0 - DOUBLE_80332ea0);
      local_b8 = (double)CONCAT44(0x43300000,(int)psVar14[2] ^ 0x80000000);
      in_f29 = (double)(float)(local_b8 - DOUBLE_80332ea0);
      local_b0 = (double)CONCAT44(0x43300000,(int)psVar14[3] ^ 0x80000000);
      dVar20 = (double)(float)(local_b0 - DOUBLE_80332ea0);
      if (iVar11 == 0) {
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar14 + 0xe));
        local_d8 = 0xffffffff;
        local_d4 = 0xff;
        local_d3 = 0xff;
        local_d2 = 0xff;
        local_d1 = 0xff;
        local_d0 = 0xff;
        local_cf = 0xff;
        local_ce = 0xff;
        local_cd = 0xff;
        local_cc = 0xff;
        local_cb = 0xff;
        local_ca = 0xff;
        local_c9 = 0xff;
        local_dc = 0xffffffff;
        GXSetChanMatColor(4,&local_dc);
        in_f29 = (double)(float)((double)*(float *)(psVar14 + 8) * in_f29);
        if ((double)FLOAT_80332e60 < in_f29) {
          DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                    (dVar22,dVar21,in_f29,dVar20,dVar19,dVar18,(double)FLOAT_80332e64,
                     (double)FLOAT_80332e64,&MenuPcs,0,&local_d8);
          dVar22 = (double)(float)(dVar22 + in_f29);
          dVar19 = (double)(float)(dVar19 + in_f29);
        }
        if ((double)FLOAT_80332e60 < in_f29) {
          local_b0 = (double)(CONCAT44(0x43300000,(int)psVar14[2]) ^ 0x80000000);
          if (in_f29 < (double)(float)(local_b0 - DOUBLE_80332ea0)) {
            local_d4 = 0xff;
            local_d3 = 0xff;
            local_d2 = 0xff;
            local_d1 = 0;
            local_cc = 0xff;
            local_cb = 0xff;
            local_ca = 0xff;
            local_c9 = 0;
            local_b0 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar14 + 0x14)) ^ 0x80000000);
            local_b8 = (double)CONCAT44(0x43300000,(int)psVar14[2] ^ 0x80000000);
            in_f29 = (double)((float)(DOUBLE_80332e68 / (local_b0 - DOUBLE_80332ea0)) *
                             (float)(local_b8 - DOUBLE_80332ea0));
            DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                      (dVar22,dVar21,in_f29,dVar20,dVar19,dVar18,(double)FLOAT_80332e64,
                       (double)FLOAT_80332e64,&MenuPcs,0,&local_d8);
          }
        }
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      }
      else {
        dVar17 = (double)*(float *)(psVar14 + 8);
        if (iVar10 == 0x37) {
          iVar13 = iVar15 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
          if (0x3f < iVar13) {
            iVar13 = iVar13 + -0x40;
          }
          iVar12 = iVar13 * 2 + 0xb6;
          if (((*(short *)(uVar5 + iVar12) < 1) ||
              (cVar8 = EquipChk__8CMenuPcsFi(menuPcs,iVar13), cVar8 != '\0')) ||
             ((-1 < iVar6 && (*(short *)(uVar5 + iVar12) < 0x125)))) {
            cVar8 = EquipChk__8CMenuPcsFi(menuPcs,iVar13);
            if (cVar8 != '\0') {
              local_b0 = (double)(longlong)(int)(dVar22 - (double)FLOAT_80332e70);
              iVar10 = (int)((double)(float)(dVar20 - (double)FLOAT_80332e74) * DOUBLE_80332e78 +
                            dVar21);
              local_b8 = (double)(longlong)iVar10;
              DrawEquipMark__8CMenuPcsFiif
                        ((double)*(float *)(psVar14 + 8),menuPcs,
                         (int)(dVar22 - (double)FLOAT_80332e70),iVar10);
            }
            iVar10 = 0x34;
            dVar17 = (double)(float)(DOUBLE_80332e78 * (double)*(float *)(psVar14 + 8));
          }
          if ((iVar10 == 0x37) && (iVar15 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
            dVar18 = (double)(float)(dVar18 + dVar20);
          }
          iVar15 = iVar15 + 1;
        }
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar10);
        local_b0 = (double)(longlong)(int)((double)FLOAT_80332e80 * dVar17);
        local_d8 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332e80 * dVar17));
        local_e0 = local_d8;
        GXSetChanMatColor(4,&local_e0);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar22,dVar21,in_f29,dVar20,dVar19,dVar18,(double)*(float *)(psVar14 + 10),
                   (double)*(float *)(psVar14 + 10),&MenuPcs,0);
      }
    }
    psVar14 = psVar14 + 0x20;
  }
  font = *(CFont **)&menuPcs->field_0x108;
  SetMargin__5CFontFf(FLOAT_80332e64,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_80332e84,font);
  DrawInit__5CFontFv(font);
  iVar11 = 0;
  iVar6 = (int)**(short **)&menuPcs->field_0x850;
  if (0 < iVar6) {
    do {
      psVar14 = (short *)((int)*(short **)&menuPcs->field_0x850 + iVar11 + 8);
      if (*(int *)(psVar14 + 0xe) == 0x37) break;
      iVar11 = iVar11 + 0x40;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  dVar18 = (double)FLOAT_80332e80;
  iVar6 = 0;
  psVar9 = psVar14;
  do {
    iVar11 = iVar6 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
    if (0x3f < iVar11) {
      iVar11 = iVar11 + -0x40;
    }
    local_b0 = (double)(longlong)(int)(dVar18 * (double)*(float *)(psVar14 + 8));
    puVar7 = (undefined4 *)
             __ct__6CColorFUcUcUcUc
                       (auStack_e8,0xff,0xff,0xff,(int)(dVar18 * (double)*(float *)(psVar14 + 8)));
    local_e4 = *puVar7;
    SetColor__5CFontF8_GXColor(font,&local_e4);
    sVar3 = *(short *)(uVar5 + iVar11 * 2 + 0xb6);
    if (0 < sVar3) {
      iVar16 = Game.game.m_cFlatDataArr[1].m_table[0].index[sVar3 * 5 + 4];
      iVar15 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) +
               (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
      if (0x3f < iVar15) {
        iVar15 = iVar15 + -0x40;
      }
      if (iVar11 == iVar15) {
        bVar4 = true;
        unaff_r26 = (int)sVar3;
      }
      GetWidth__5CFontFPc(font,iVar16);
      local_b0 = (double)(CONCAT44(0x43300000,psVar9[1] + 0xb) ^ 0x80000000);
      local_b8 = (double)(CONCAT44(0x43300000,*psVar9 + 0x1c) ^ 0x80000000);
      dVar19 = (double)(float)(local_b0 - DOUBLE_80332ea0);
      SetPosX__5CFontFf((float)(local_b8 - DOUBLE_80332ea0),font);
      SetPosY__5CFontFf((float)(dVar19 - (double)FLOAT_80332e88),font);
      Draw__5CFontFPc(font,iVar16);
    }
    iVar6 = iVar6 + 1;
    psVar9 = psVar9 + 0x20;
  } while (iVar6 < 8);
  DrawInit__8CMenuPcsFv(menuPcs);
  iVar6 = 0;
  psVar9 = psVar14;
  do {
    iVar11 = iVar6 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
    if (0x3f < iVar11) {
      iVar11 = iVar11 + -0x40;
    }
    sVar3 = *(short *)(uVar5 + iVar11 * 2 + 0xb6);
    if (0 < sVar3) {
      local_c0 = (double)CONCAT44(0x43300000,(int)psVar9[1] + 6U ^ 0x80000000);
      local_b0 = (double)CONCAT44(0x43300000,(int)*psVar9 + psVar9[2] + -0x10 ^ 0x80000000);
      iVar11 = (int)((float)(local_c0 - DOUBLE_80332ea0) - FLOAT_80332e64);
      local_c8 = (double)(longlong)iVar11;
      local_b8 = (double)(longlong)(int)(local_b0 - DOUBLE_80332ea0);
      DrawSingleIcon__8CMenuPcsFiiifif
                ((double)*(float *)(psVar14 + 8),menuPcs,(int)sVar3,
                 (int)(local_b0 - DOUBLE_80332ea0),iVar11,0);
    }
    iVar6 = iVar6 + 1;
    psVar9 = psVar9 + 0x20;
  } while (iVar6 < 8);
  if (sVar1 == 1) {
    iVar6 = *(int *)&menuPcs->field_0x850;
    psVar14 = (short *)(iVar6 + 8);
    dVar18 = (double)CalcListPos__8CMenuPcsFiii
                               (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34),0x40,1
                               );
    if ((double)FLOAT_80332e60 < dVar18) {
      local_b0 = (double)(CONCAT44(0x43300000,(int)*psVar14) ^ 0x80000000);
      local_b8 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar6 + 10) ^ 0x80000000);
      DrawListPosMark__8CMenuPcsFfff
                ((double)(float)(local_b0 - DOUBLE_80332ea0),
                 (double)(float)(local_b8 - DOUBLE_80332ea0),dVar18,menuPcs);
    }
  }
  if (sVar2 == 1) {
    DrawSingWin__8CMenuPcsFs(menuPcs,0xffff);
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1) {
      DrawSingWinMess__8CMenuPcsFiii(menuPcs,0,(int)*(char *)(*(int *)&menuPcs->field_0x82c + 9),0);
    }
  }
  if (((sVar2 == 0) && (sVar1 == 1)) ||
     ((sVar2 != 0 && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1)))) {
    if (sVar2 == 0) {
      psVar9 = *(short **)&menuPcs->field_0x850;
      iVar11 = 0;
      iVar6 = (int)*psVar9;
      if (0 < iVar6) {
        do {
          psVar14 = (short *)((int)psVar9 + iVar11 + 8);
          if (*(int *)((int)psVar9 + iVar11 + 0x24) == 0x37) break;
          iVar11 = iVar11 + 0x40;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      psVar14 = psVar14 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x20;
      local_b8 = (double)(CONCAT44(0x43300000,psVar14[3] + -0x20) ^ 0x80000000);
      local_c0 = (double)(CONCAT44(0x43300000,(int)psVar14[1]) ^ 0x80000000);
      local_b0 = (double)CONCAT44(0x43300000,(int)*psVar14 - 0x14U ^ 0x80000000);
      dVar18 = (local_b8 - DOUBLE_80332ea0) * DOUBLE_80332e78 + (local_c0 - DOUBLE_80332ea0);
      dVar19 = (double)(float)(local_b0 - DOUBLE_80332ea0);
    }
    else {
      local_b0 = (double)(CONCAT44(0x43300000,(int)**(short **)&menuPcs->field_0x848) ^ 0x80000000);
      local_b8 = (double)(CONCAT44(0x43300000,(*(short **)&menuPcs->field_0x848)[1] + 0x20) ^
                         0x80000000);
      dVar19 = (double)(float)(local_b0 - DOUBLE_80332ea0);
      dVar18 = (double)(float)(local_b8 - DOUBLE_80332ea0);
      iVar6 = SingWinMessHeight__8CMenuPcsFv(menuPcs);
      local_c0 = (double)(CONCAT44(0x43300000,
                                   *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) * iVar6) ^
                         0x80000000);
      dVar18 = dVar18 + (double)(float)(local_c0 - DOUBLE_80332ea0);
    }
    local_c0 = (double)(longlong)(int)dVar18;
    iVar6 = (int)System.m_frameCounter >> 0x1f;
    local_b0 = (double)(CONCAT44(0x43300000,
                                 (iVar6 * 8 | System.m_frameCounter * 0x20000000 + iVar6 >> 0x1d) -
                                 iVar6) ^ 0x80000000);
    iVar6 = (int)(dVar19 + (double)(float)(local_b0 - DOUBLE_80332ea0));
    local_b8 = (double)(longlong)iVar6;
    DrawCursor__8CMenuPcsFiif((double)FLOAT_80332e64,menuPcs,iVar6,(int)dVar18);
  }
  DrawInit__8CMenuPcsFv(menuPcs);
  DrawSingLife__8CMenuPcsFv(menuPcs);
  local_b0 = (double)(longlong)(int)(FLOAT_80332e80 * *(float *)(psVar14 + 8));
  if (!bVar4) {
    unaff_r26 = -1;
  }
  puVar7 = (undefined4 *)
           __ct__6CColorFUcUcUcUc
                     (auStack_f0,0xff,0xff,0xff,
                      (int)(FLOAT_80332e80 * *(float *)(psVar14 + 8)) & 0xff);
  local_ec = *puVar7;
  local_c0 = (double)(longlong)(int)FLOAT_80332e94;
  local_b8 = (double)(longlong)
                     (int)-(float)(in_f29 * (double)FLOAT_80332e90 - (double)FLOAT_80332e8c);
  DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(menuPcs,unaff_r26);
  return;
}

