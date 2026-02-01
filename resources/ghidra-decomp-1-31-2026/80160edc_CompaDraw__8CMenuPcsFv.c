// Function: CompaDraw__8CMenuPcsFv
// Entry: 80160edc
// Size: 3024 bytes

/* WARNING: Removing unreachable block (ram,0x80161a90) */
/* WARNING: Removing unreachable block (ram,0x80161a88) */
/* WARNING: Removing unreachable block (ram,0x80161a80) */
/* WARNING: Removing unreachable block (ram,0x80161a78) */
/* WARNING: Removing unreachable block (ram,0x80161a70) */
/* WARNING: Removing unreachable block (ram,0x80161a68) */
/* WARNING: Removing unreachable block (ram,0x80161a60) */
/* WARNING: Removing unreachable block (ram,0x80161a58) */
/* WARNING: Removing unreachable block (ram,0x80161a50) */
/* WARNING: Removing unreachable block (ram,0x80161a48) */
/* WARNING: Removing unreachable block (ram,0x80160f34) */
/* WARNING: Removing unreachable block (ram,0x80160f2c) */
/* WARNING: Removing unreachable block (ram,0x80160f24) */
/* WARNING: Removing unreachable block (ram,0x80160f1c) */
/* WARNING: Removing unreachable block (ram,0x80160f14) */
/* WARNING: Removing unreachable block (ram,0x80160f0c) */
/* WARNING: Removing unreachable block (ram,0x80160f04) */
/* WARNING: Removing unreachable block (ram,0x80160efc) */
/* WARNING: Removing unreachable block (ram,0x80160ef4) */
/* WARNING: Removing unreachable block (ram,0x80160eec) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CompaDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  double dVar1;
  byte bVar2;
  uint32_t uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  short *psVar10;
  int iVar11;
  int32_t iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  CFont *pCVar17;
  int iVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  undefined auStack_130 [4];
  undefined4 local_12c;
  undefined auStack_128 [4];
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined local_110;
  undefined local_10f;
  undefined local_10e;
  undefined local_10d;
  undefined local_10c;
  undefined local_10b;
  undefined local_10a;
  undefined local_109;
  undefined local_108;
  undefined local_107;
  undefined local_106;
  undefined local_105;
  undefined4 local_100;
  uint uStack_fc;
  undefined4 local_f8;
  uint uStack_f4;
  undefined8 local_f0;
  undefined8 local_e8;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  uVar3 = Game.game.m_scriptFoodBase[0];
  psVar10 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  for (iVar13 = 0; iVar13 < **(short **)&menuPcs->field_0x850; iVar13 = iVar13 + 1) {
    if (-1 < *(int *)(psVar10 + 0xe)) {
      uStack_fc = (int)*psVar10 ^ 0x80000000;
      uStack_f4 = (int)psVar10[1] ^ 0x80000000;
      local_100 = 0x43300000;
      dVar20 = (double)*(float *)(psVar10 + 4);
      dVar26 = (double)(float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80333030);
      dVar22 = (double)*(float *)(psVar10 + 6);
      local_f8 = 0x43300000;
      dVar25 = (double)(float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80333030);
      local_f0 = (double)CONCAT44(0x43300000,(int)psVar10[2] ^ 0x80000000);
      dVar21 = (double)(float)(local_f0 - DOUBLE_80333030);
      local_e8 = (double)CONCAT44(0x43300000,(int)psVar10[3] ^ 0x80000000);
      dVar23 = (double)(float)(local_e8 - DOUBLE_80333030);
      if (iVar13 < 3) {
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar10 + 0xe));
        local_114 = 0xffffffff;
        local_110 = 0xff;
        local_10f = 0xff;
        local_10e = 0xff;
        local_10d = 0xff;
        local_10c = 0xff;
        local_10b = 0xff;
        local_10a = 0xff;
        local_109 = 0xff;
        local_108 = 0xff;
        local_107 = 0xff;
        local_106 = 0xff;
        local_105 = 0xff;
        local_118 = 0xffffffff;
        GXSetChanMatColor(4,&local_118);
        dVar21 = (double)(float)((double)*(float *)(psVar10 + 8) * dVar21);
        if ((double)FLOAT_80332ff8 < dVar21) {
          if (*(int *)(psVar10 + 0xe) == 0x51) {
            uVar14 = (uint)dVar25;
            dVar19 = (double)(float)(dVar25 + dVar23);
            dVar27 = (double)FLOAT_80332ffc;
            dVar24 = DOUBLE_80333030;
            while (local_e8 = (double)(CONCAT44(0x43300000,uVar14) ^ 0x80000000),
                  (double)(float)(local_e8 - dVar24) < dVar19) {
              local_e8 = (double)(CONCAT44(0x43300000,uVar14) ^ 0x80000000);
              dVar1 = dVar19 - (double)(float)(local_e8 - dVar24);
              if ((double)(float)dVar1 < dVar27) {
                uStack_fc = (uint)dVar1;
                local_f0 = (double)(longlong)(int)uStack_fc;
              }
              else {
                uStack_fc = 0x18;
              }
              uStack_f4 = uVar14 ^ 0x80000000;
              uStack_fc = uStack_fc ^ 0x80000000;
              local_f8 = 0x43300000;
              local_100 = 0x43300000;
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (dVar26,(double)(float)((double)CONCAT44(0x43300000,uStack_f4) - dVar24),
                         dVar21,(double)(float)((double)CONCAT44(0x43300000,uStack_fc) - dVar24),
                         dVar20,dVar22,(double)FLOAT_80333000,(double)FLOAT_80333000,&MenuPcs,
                         *(undefined4 *)(psVar10 + 0xc),&local_114);
              uVar14 = uVar14 + 0x18;
            }
          }
          else {
            DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                      (dVar26,dVar25,dVar21,dVar23,dVar20,dVar22,(double)FLOAT_80333000,
                       (double)FLOAT_80333000,&MenuPcs,*(undefined4 *)(psVar10 + 0xc),&local_114);
          }
          dVar20 = (double)(float)(dVar20 + dVar21);
          dVar26 = (double)(float)(dVar21 * (double)*(float *)(psVar10 + 10) + dVar26);
        }
        if ((double)FLOAT_80332ff8 < dVar21) {
          local_e8 = (double)(CONCAT44(0x43300000,(int)psVar10[2]) ^ 0x80000000);
          if (dVar21 < (double)(float)(local_e8 - DOUBLE_80333030)) {
            local_110 = 0xff;
            local_10f = 0xff;
            local_10e = 0xff;
            local_10d = 0;
            local_108 = 0xff;
            local_107 = 0xff;
            local_106 = 0xff;
            local_105 = 0;
            local_e8 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar10 + 0x14)) ^ 0x80000000);
            local_f0 = (double)CONCAT44(0x43300000,(int)psVar10[2] ^ 0x80000000);
            dVar21 = (double)((float)(DOUBLE_80333008 / (local_e8 - DOUBLE_80333030)) *
                             (float)(local_f0 - DOUBLE_80333030));
            if (*(int *)(psVar10 + 0xe) == 0x51) {
              uVar14 = (uint)dVar25;
              dVar25 = (double)(float)(dVar25 + dVar23);
              dVar24 = (double)FLOAT_80332ffc;
              dVar23 = DOUBLE_80333030;
              while (local_e8 = (double)(CONCAT44(0x43300000,uVar14) ^ 0x80000000),
                    (double)(float)(local_e8 - dVar23) < dVar25) {
                local_e8 = (double)(CONCAT44(0x43300000,uVar14) ^ 0x80000000);
                dVar19 = dVar25 - (double)(float)(local_e8 - dVar23);
                if ((double)(float)dVar19 < dVar24) {
                  uStack_fc = (uint)dVar19;
                  local_f0 = (double)(longlong)(int)uStack_fc;
                }
                else {
                  uStack_fc = 0x18;
                }
                uStack_f4 = uVar14 ^ 0x80000000;
                uStack_fc = uStack_fc ^ 0x80000000;
                local_f8 = 0x43300000;
                local_100 = 0x43300000;
                DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                          (dVar26,(double)(float)((double)CONCAT44(0x43300000,uStack_f4) - dVar23),
                           dVar21,(double)(float)((double)CONCAT44(0x43300000,uStack_fc) - dVar23),
                           dVar20,dVar22,(double)FLOAT_80333000,(double)FLOAT_80333000,&MenuPcs,
                           *(undefined4 *)(psVar10 + 0xc),&local_114);
                uVar14 = uVar14 + 0x18;
              }
            }
            else {
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (dVar26,dVar25,dVar21,dVar23,dVar20,dVar22,(double)FLOAT_80333000,
                         (double)FLOAT_80333000,&MenuPcs,*(undefined4 *)(psVar10 + 0xc),&local_114);
            }
          }
        }
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      }
      else {
        dVar24 = (double)*(float *)(psVar10 + 8);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(int *)(psVar10 + 0xe));
        local_e8 = (double)(longlong)(int)((double)FLOAT_80333010 * dVar24);
        local_114 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80333010 * dVar24));
        local_11c = local_114;
        GXSetChanMatColor(4,&local_11c);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar26,dVar25,dVar21,dVar23,dVar20,dVar22,(double)*(float *)(psVar10 + 10),
                   (double)*(float *)(psVar10 + 10),&MenuPcs,0);
      }
    }
    psVar10 = psVar10 + 0x20;
  }
  iVar13 = (int)(FLOAT_80333010 * *(float *)(*(short **)&menuPcs->field_0x850 + 0xc));
  local_e8 = (double)(longlong)iVar13;
  local_114 = CONCAT31(0xffffff,(char)iVar13);
  local_120 = local_114;
  GXSetChanMatColor(4,&local_120);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3a);
  iVar18 = 2;
  iVar16 = *(int *)&menuPcs->field_0x850;
  iVar13 = 5;
  iVar5 = uVar3 + 4;
  do {
    if (0 < *(short *)(iVar5 + 0x9ca)) {
      iVar18 = iVar18 + 1;
    }
    iVar5 = iVar5 + 2;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  if ((4 < iVar18) && (System.m_execParam != 0)) {
    Printf__7CSystemFPce
              (&System,s__s__d__family_cnt_error____d__801dedc8,s_menu_compa_cpp_801dede8,0x1bf,
               iVar18);
  }
  if (4 < iVar18) {
    iVar18 = 4;
  }
  uVar14 = 0;
  dVar22 = (double)FLOAT_80332ff8;
  dVar21 = DOUBLE_80333030;
  for (iVar13 = 0; iVar13 < iVar18; iVar13 = iVar13 + 1) {
    local_e8 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar16 + 10) + 0x40U ^ 0x80000000);
    uStack_f4 = (int)*(short *)(iVar16 + 8) + 0x10U ^ 0x80000000;
    local_f0 = (double)CONCAT44(0x43300000,uVar14 ^ 0x80000000);
    local_f8 = 0x43300000;
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_f4) - dVar21),
               (double)((float)(local_e8 - dVar21) + (float)(local_f0 - dVar21)),
               (double)FLOAT_80333014,(double)FLOAT_80333018,dVar22,dVar22,(double)FLOAT_80333000,
               (double)FLOAT_80333000,&MenuPcs,0);
    uVar14 = uVar14 + 0x28;
  }
  iVar13 = 0;
  uVar14 = 0;
  iVar5 = 0;
  dVar21 = DOUBLE_80333030;
  for (iVar15 = 0; (iVar5 < 8 && (iVar15 < iVar18)); iVar15 = iVar15 + 1) {
    uStack_f4 = uVar14 ^ 0x80000000;
    local_f0 = (double)(CONCAT44(0x43300000,*(short *)(iVar16 + 10) + 0x40) ^ 0x80000000);
    local_f8 = 0x43300000;
    local_e8 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar16 + 8) + 0x128U ^ 0x80000000);
    dVar20 = (double)((float)(local_f0 - dVar21) +
                     (float)((double)CONCAT44(0x43300000,uStack_f4) - dVar21));
    dVar22 = (double)(float)(local_e8 - dVar21);
    iVar11 = iVar5;
    if (1 < iVar5) {
      iVar4 = 7 - iVar13;
      iVar7 = uVar3 + iVar13 * 2;
      iVar9 = iVar13;
      iVar11 = iVar13;
      if (iVar13 < 7) {
        do {
          iVar11 = iVar9;
          if (*(short *)(iVar7 + 0x9ca) != 0) break;
          iVar7 = iVar7 + 2;
          iVar9 = iVar9 + 1;
          iVar4 = iVar4 + -1;
          iVar11 = iVar13;
        } while (iVar4 != 0);
      }
      if (7 < iVar9) break;
    }
    iVar13 = *(int *)(uVar3 + 8) * 0x208 + -0x7fde1140 + iVar11;
    if ((*(char *)(iVar13 + 0xa9) == '\0') && (System.m_execParam != 0)) {
      Printf__7CSystemFPce
                (&System,s__s__d__family_cnt_error____d__801dedc8,s_menu_compa_cpp_801dede8,0x1e0,
                 iVar15);
    }
    bVar2 = *(byte *)(iVar13 + 0xa9);
    if (bVar2 < 0x15) {
      uVar8 = 0x21;
    }
    else if (bVar2 < 0x29) {
      uVar8 = 0x20;
    }
    else if (bVar2 < 0x3d) {
      uVar8 = 0x1f;
    }
    else if (bVar2 < 0x51) {
      uVar8 = 0x1e;
    }
    else {
      uVar8 = 0x1d;
    }
    local_e8 = (double)(longlong)(int)dVar22;
    local_f0 = (double)(longlong)(int)dVar20;
    DrawSingleIcon__8CMenuPcsFiiifif
              ((double)*(float *)(iVar16 + 0x18),(double)FLOAT_80333000,menuPcs,uVar8,(int)dVar22,
               (int)dVar20,1);
    uVar14 = uVar14 + 0x28;
    iVar5 = iVar5 + 1;
    iVar13 = iVar11 + 1;
  }
  pCVar17 = *(CFont **)&menuPcs->field_0x108;
  iVar15 = *(int *)&menuPcs->field_0x850;
  SetMargin__5CFontFf(FLOAT_80333000,pCVar17);
  SetShadow__5CFontFi(pCVar17,0);
  SetScaleX__5CFontFf(FLOAT_8033301c,pCVar17);
  SetScaleY__5CFontFf(FLOAT_80333000,pCVar17);
  DrawInit__5CFontFv(pCVar17);
  iVar13 = (int)(FLOAT_80333010 * *(float *)(iVar15 + 0x18));
  local_e8 = (double)(longlong)iVar13;
  puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_128,0xff,0xff,0xff,iVar13);
  local_124 = *puVar6;
  SetColor__5CFontF8_GXColor(pCVar17,&local_124);
  uVar3 = Game.game.m_scriptFoodBase[0];
  iVar13 = 0;
  uVar14 = 0;
  iVar5 = 0;
  dVar22 = (double)FLOAT_80333020;
  dVar21 = DOUBLE_80333030;
  for (iVar16 = 0; (iVar5 < 8 && (iVar16 < iVar18)); iVar16 = iVar16 + 1) {
    iVar11 = iVar5;
    if (1 < iVar5) {
      iVar4 = 7 - iVar13;
      iVar7 = uVar3 + iVar13 * 2;
      iVar9 = iVar13;
      iVar11 = iVar13;
      if (iVar13 < 7) {
        do {
          iVar11 = iVar9;
          if (0 < *(short *)(iVar7 + 0x9ca)) break;
          iVar7 = iVar7 + 2;
          iVar9 = iVar9 + 1;
          iVar4 = iVar4 + -1;
          iVar11 = iVar13;
        } while (iVar4 != 0);
      }
      if (7 < iVar9) break;
    }
    uVar8 = GetMenuStr__8CMenuPcsFi(menuPcs,iVar11 + 0x16);
    uStack_f4 = uVar14 ^ 0x80000000;
    local_f0 = (double)(CONCAT44(0x43300000,*(short *)(iVar15 + 10) + 0x45) ^ 0x80000000);
    local_f8 = 0x43300000;
    local_e8 = (double)(CONCAT44(0x43300000,*(short *)(iVar15 + 8) + 0x18) ^ 0x80000000);
    dVar20 = (double)((float)(local_f0 - dVar21) +
                     (float)((double)CONCAT44(0x43300000,uStack_f4) - dVar21));
    SetPosX__5CFontFf((float)(local_e8 - dVar21),pCVar17);
    SetPosY__5CFontFf((float)(dVar20 - dVar22),pCVar17);
    Draw__5CFontFPc(pCVar17,uVar8);
    local_100 = 0x43300000;
    uStack_fc = (int)*(short *)(iVar15 + 8) + 0x90U ^ 0x80000000;
    iVar12 = Game.game.m_cFlatDataArr[1].m_table[2].index[*(short *)(uVar3 + iVar11 * 2 + 0x9ca)];
    SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_fc) - dVar21),pCVar17);
    SetPosY__5CFontFf((float)(dVar20 - dVar22),pCVar17);
    Draw__5CFontFPc(pCVar17,iVar12);
    uVar14 = uVar14 + 0x28;
    iVar5 = iVar5 + 1;
    iVar13 = iVar11 + 1;
  }
  pCVar17 = *(CFont **)&menuPcs->field_0x108;
  SetMargin__5CFontFf(FLOAT_80333000,pCVar17);
  SetShadow__5CFontFi(pCVar17,0);
  SetScale__5CFontFf(FLOAT_80333024,pCVar17);
  DrawInit__5CFontFv(pCVar17);
  iVar5 = *(int *)&menuPcs->field_0x850;
  iVar13 = (int)(FLOAT_80333010 * *(float *)(iVar5 + 0x18));
  local_e8 = (double)(longlong)iVar13;
  puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_130,0xff,0xff,0xff,iVar13);
  local_12c = *puVar6;
  SetColor__5CFontF8_GXColor(pCVar17,&local_12c);
  uVar8 = GetJobStr__8CMenuPcsFi(menuPcs,*(undefined4 *)(uVar3 + 0x3ac));
  GetWidth__5CFontFPc(pCVar17,uVar8);
  local_f8 = 0x43300000;
  uStack_f4 = (int)*(short *)(iVar5 + 8) + 0x18U ^ 0x80000000;
  local_f0 = (double)(CONCAT44(0x43300000,*(short *)(iVar5 + 10) + 0x20) ^ 0x80000000);
  dVar21 = (double)(float)(local_f0 - DOUBLE_80333030);
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80333030),pCVar17);
  SetPosY__5CFontFf((float)(dVar21 - (double)FLOAT_80333020) - FLOAT_80333028,pCVar17);
  Draw__5CFontFPc(pCVar17,uVar8);
  DrawInit__8CMenuPcsFv(menuPcs);
  return;
}

