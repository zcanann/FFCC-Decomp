// Function: onDraw__8CMesMenuFv
// Entry: 8009bedc
// Size: 6080 bytes

/* WARNING: Removing unreachable block (ram,0x8009d680) */
/* WARNING: Removing unreachable block (ram,0x8009d678) */
/* WARNING: Removing unreachable block (ram,0x8009d670) */
/* WARNING: Removing unreachable block (ram,0x8009d668) */
/* WARNING: Removing unreachable block (ram,0x8009d660) */
/* WARNING: Removing unreachable block (ram,0x8009d658) */
/* WARNING: Removing unreachable block (ram,0x8009d650) */
/* WARNING: Removing unreachable block (ram,0x8009d648) */
/* WARNING: Removing unreachable block (ram,0x8009d640) */
/* WARNING: Removing unreachable block (ram,0x8009d638) */
/* WARNING: Removing unreachable block (ram,0x8009d630) */
/* WARNING: Removing unreachable block (ram,0x8009d628) */
/* WARNING: Removing unreachable block (ram,0x8009d620) */
/* WARNING: Removing unreachable block (ram,0x8009d618) */
/* WARNING: Removing unreachable block (ram,0x8009d610) */
/* WARNING: Removing unreachable block (ram,0x8009d608) */
/* WARNING: Removing unreachable block (ram,0x8009bf64) */
/* WARNING: Removing unreachable block (ram,0x8009bf5c) */
/* WARNING: Removing unreachable block (ram,0x8009bf54) */
/* WARNING: Removing unreachable block (ram,0x8009bf4c) */
/* WARNING: Removing unreachable block (ram,0x8009bf44) */
/* WARNING: Removing unreachable block (ram,0x8009bf3c) */
/* WARNING: Removing unreachable block (ram,0x8009bf34) */
/* WARNING: Removing unreachable block (ram,0x8009bf2c) */
/* WARNING: Removing unreachable block (ram,0x8009bf24) */
/* WARNING: Removing unreachable block (ram,0x8009bf1c) */
/* WARNING: Removing unreachable block (ram,0x8009bf14) */
/* WARNING: Removing unreachable block (ram,0x8009bf0c) */
/* WARNING: Removing unreachable block (ram,0x8009bf04) */
/* WARNING: Removing unreachable block (ram,0x8009befc) */
/* WARNING: Removing unreachable block (ram,0x8009bef4) */
/* WARNING: Removing unreachable block (ram,0x8009beec) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDraw__8CMesMenuFv(int param_1)

{
  float fVar1;
  bool bVar2;
  ushort uVar5;
  uint uVar3;
  int iVar4;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint32_t uVar14;
  int iVar15;
  int iVar16;
  uint32_t uVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  double dVar31;
  double dVar32;
  double dVar33;
  undefined auStack_1b0 [4];
  undefined auStack_1ac [4];
  undefined auStack_1a8 [4];
  undefined auStack_1a4 [4];
  undefined auStack_1a0 [4];
  undefined auStack_19c [4];
  undefined4 local_198;
  undefined auStack_194 [4];
  undefined auStack_190 [4];
  undefined auStack_18c [4];
  undefined auStack_188 [4];
  undefined4 local_184;
  undefined auStack_180 [4];
  undefined auStack_17c [4];
  undefined auStack_178 [4];
  undefined4 local_174;
  undefined auStack_170 [4];
  undefined auStack_16c [4];
  undefined auStack_168 [8];
  undefined4 local_160;
  uint uStack_15c;
  undefined8 local_158;
  undefined8 local_150;
  undefined8 local_148;
  undefined8 local_140;
  undefined8 local_138;
  longlong local_130;
  
  if ((*(int *)(param_1 + 0x18) == 0) &&
     ((int)((uint)(byte)CFlat._4836_1_ << 0x1e | (uint)((byte)CFlat._4836_1_ >> 2)) < 0)) {
    iVar12 = 0;
    if (Chara._8196_4_ == 2) {
      iVar12 = 5;
    }
    else if ((int)Chara._8196_4_ < 2) {
      if (Chara._8196_4_ == 0) {
        iVar12 = 3;
      }
      else if (-1 < (int)Chara._8196_4_) {
        iVar12 = 4;
      }
    }
    else if (Chara._8196_4_ == 4) {
      bVar2 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar5 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar5 = Pad._4_2_;
      }
      iVar12 = DAT_8020f9a8;
      if ((uVar5 & 0x100) != 0) {
        iVar12 = *(int *)((int)&DAT_8020f9a8 + (System.m_frameCounter & 6) * 2);
      }
    }
    else if ((int)Chara._8196_4_ < 4) {
      iVar12 = 2;
    }
    uVar6 = __ct__6CColorFUcUcUcUc(auStack_168,0xff,0xff,0xff,0xff);
    SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
    uStack_15c = Chara._8204_4_ - 0x20 ^ 0x80000000;
    local_160 = 0x43300000;
    local_158 = (double)CONCAT44(0x43300000,Chara._8208_4_ ^ 0x80000000);
    local_150 = (double)CONCAT44(0x43300000,iVar12 << 5 ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_15c) - DOUBLE_80330900),
               (double)(float)(local_158 - DOUBLE_80330900),(double)FLOAT_8033092c,
               (double)FLOAT_8033092c,(double)FLOAT_803308d8,
               (double)(float)(local_150 - DOUBLE_80330900),(double)FLOAT_80330914,
               (double)FLOAT_80330914,&MenuPcs,0);
  }
  uVar6 = MenuPcs._248_4_;
  iVar12 = *(int *)(param_1 + 0x18);
  if (((iVar12 < 4) || (*(int *)(param_1 + 8) != 0)) &&
     ((Game.game.m_gameWork.m_menuStageMode == '\0' || ((iVar12 < 1 || (3 < iVar12)))))) {
    SetMargin__5CFontFf(FLOAT_803308d8,(CFont *)MenuPcs._248_4_);
    SetShadow__5CFontFi((CFont *)uVar6,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_150 = (double)(CONCAT44(0x43300000,*(undefined4 *)(param_1 + 0x3df4)) ^ 0x80000000);
    dVar33 = (double)((float)(local_150 - DOUBLE_80330900) * FLOAT_80330918);
    if (*(int *)(param_1 + 0x3df8) != 0) {
      dVar33 = (double)(float)((double)FLOAT_80330914 - dVar33);
    }
    dVar18 = (double)FLOAT_803308d8;
    if (dVar18 != dVar33) {
      iVar12 = *(int *)(param_1 + 0xc);
      if (((iVar12 == 0) || (iVar12 - 1U < 2)) || (iVar12 == 3)) {
        if (iVar12 == 0) {
          local_150 = (double)(CONCAT44(0x43300000,*(undefined4 *)(param_1 + 0x10)) ^ 0x80000000);
          local_158 = (double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x14) ^ 0x80000000);
          dVar18 = (double)((float)(local_150 - DOUBLE_80330900) /
                           (float)(local_158 - DOUBLE_80330900));
        }
        else if (iVar12 == 3) {
          local_150 = (double)(CONCAT44(0x43300000,*(undefined4 *)(param_1 + 0x10)) ^ 0x80000000);
          local_158 = (double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x14) ^ 0x80000000);
          dVar18 = (double)(FLOAT_80330914 -
                           (float)(local_150 - DOUBLE_80330900) /
                           (float)(local_158 - DOUBLE_80330900));
        }
        else {
          dVar18 = (double)FLOAT_80330914;
        }
      }
      if (*(int *)(param_1 + 0x18) < 4) {
        uVar17 = Game.game.m_scriptFoodBase[*(int *)(param_1 + 0x18)];
        if (uVar17 == 0) {
          return;
        }
        dVar20 = (double)sin((double)(float)((double)FLOAT_80330930 * dVar33));
        dVar23 = (double)(FLOAT_8033092c * (FLOAT_80330914 - (float)dVar20));
        GetDispCounter__9CRingMenuFv
                  (*(CRingMenu **)(&MenuPcs.field_0x13c + *(int *)(param_1 + 0x18) * 4));
        uVar9 = *(uint *)(param_1 + 0x18) & 1;
        dVar20 = dVar23;
        if (uVar9 == 0) {
          dVar20 = -dVar23;
        }
        uVar3 = *(uint *)(param_1 + 0x18) & 2;
        dVar20 = (double)(float)((double)(*(float *)(param_1 + 0x3d6c) +
                                         *(float *)(param_1 + 0x3d74)) + dVar20);
        if (uVar3 == 0) {
          dVar23 = -dVar23;
        }
        dVar23 = (double)(float)((double)(*(float *)(param_1 + 0x3d70) +
                                         *(float *)(param_1 + 0x3d78)) + dVar23);
        if ((double)FLOAT_803308d8 < dVar18) {
          dVar19 = (double)*(float *)(param_1 + 0x3d7c);
          dVar22 = (double)*(float *)(param_1 + 0x3d80);
          dVar27 = (double)(float)(dVar19 * dVar18);
          dVar28 = (double)(float)(dVar22 * dVar18);
          if (uVar9 == 0) {
            dVar19 = (double)(float)(dVar19 - dVar27);
          }
          else {
            dVar19 = -dVar19;
          }
          dVar19 = (double)(float)(dVar20 + dVar19);
          fVar1 = FLOAT_803308f8;
          if (uVar3 != 0) {
            fVar1 = (float)((double)FLOAT_80330934 - dVar22) + (float)(dVar22 - dVar28);
          }
          dVar29 = (double)(float)(dVar23 + (double)fVar1);
          dVar22 = (double)(float)((double)FLOAT_80330908 * dVar18) * dVar33;
          dVar26 = (double)(float)dVar22;
          iVar12 = (int)dVar22;
          local_150 = (double)(longlong)iVar12;
          uVar7 = __ct__6CColorFUcUcUcUc(auStack_16c,0xff,0xff,0xff,iVar12);
          SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar7);
          DrawWindow__8CMenuPcsFffffQ28CMenuPcs3TEXf
                    (dVar19,dVar29,dVar27,dVar28,(double)FLOAT_8033092c,&MenuPcs,2);
          if ((*(int *)(param_1 + 0xc) == 1) && ((double)FLOAT_80330914 == dVar33)) {
            Draw__4CMesFv(param_1 + 0x1c);
            DrawInit__8CMenuPcsFv(&MenuPcs);
          }
          if ((-1 < *(int *)(param_1 + 0x3d94)) || (-1 < *(int *)(param_1 + 0x3d98))) {
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x14);
            local_150 = (double)(longlong)(int)dVar26;
            uVar7 = __ct__6CColorFUcUcUcUc(auStack_170,0xff,0xff,0xff,(int)dVar26);
            SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar7);
            dVar18 = (double)sin((double)(FLOAT_80330930 * (float)((double)FLOAT_80330914 - dVar18)
                                         + FLOAT_80330930));
            uVar3 = 0xffffffe0;
            uVar9 = *(uint *)(param_1 + 0x18) & 1;
            if (uVar9 != 0) {
              uVar3 = 0x20;
            }
            local_158 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
            fVar1 = FLOAT_80330938;
            if (uVar9 == 0) {
              fVar1 = (float)(dVar27 - (double)FLOAT_8033093c) - FLOAT_80330938;
            }
            uVar3 = *(uint *)(param_1 + 0x18) & 2;
            dVar18 = (double)((float)(dVar19 + (double)((float)(local_158 - DOUBLE_80330900) *
                                                       (FLOAT_80330914 - (float)dVar18))) + fVar1);
            fVar1 = FLOAT_80330944;
            if (uVar3 != 0) {
              fVar1 = (float)((double)FLOAT_80330940 + dVar28);
            }
            dVar19 = (double)(float)(dVar29 + (double)fVar1);
            local_160 = 0x43300000;
            uStack_15c = (int)(-uVar3 | uVar3) >> 0x1f & 0x90U ^ 0x80000000;
            DrawRect__8CMenuPcsFUlfffffffff
                      (dVar18,dVar19,(double)FLOAT_8033093c,(double)FLOAT_80330948,
                       (double)(float)((double)CONCAT44(0x43300000,uStack_15c) - DOUBLE_80330900),
                       (double)FLOAT_803308d8,(double)FLOAT_80330914,(double)FLOAT_80330914,&MenuPcs
                       ,(int)(-uVar9 | uVar9) >> 0x1f & 8);
            if (-1 < *(int *)(param_1 + 0x3d98)) {
              SetScale__5CFontFf(FLOAT_8033094c,(CFont *)uVar6);
              SetShadow__5CFontFi((CFont *)uVar6,1);
              SetMargin__5CFontFf(FLOAT_803308d8,(CFont *)uVar6);
              dVar22 = (double)GetWidth__5CFontFPc((CFont *)uVar6,
                                                   Game.game.m_cFlatDataArr[1].m_table[2].index
                                                   [*(int *)(param_1 + 0x3d98)]);
              DrawInit__5CFontFv((CFont *)uVar6);
              SetTlut__5CFontFi((CFont *)uVar6,0xf);
              local_150 = (double)(longlong)(int)dVar26;
              puVar8 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_178,0xff,0xff,0xff,(int)dVar26);
              local_174 = *puVar8;
              SetColor__5CFontF8_GXColor((CFont *)uVar6,&local_174);
              fVar1 = FLOAT_80330950;
              if ((*(uint *)(param_1 + 0x18) & 1) == 0) {
                fVar1 = (float)((double)FLOAT_80330954 - dVar22);
              }
              SetPosX__5CFontFf((float)(dVar18 + (double)fVar1),(CFont *)uVar6);
              uVar9 = 0x1f;
              if ((*(uint *)(param_1 + 0x18) & 2) != 0) {
                uVar9 = 8;
              }
              local_158 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
              SetPosY__5CFontFf((float)(dVar19 + (double)(float)(local_158 - DOUBLE_80330900)),
                                (CFont *)uVar6);
              Draw__5CFontFPc((CFont *)uVar6,
                              Game.game.m_cFlatDataArr[1].m_table[2].index
                              [*(int *)(param_1 + 0x3d98)]);
              DrawInit__8CMenuPcsFv(&MenuPcs);
            }
            uVar9 = *(uint *)(param_1 + 0x3d94);
            if (-1 < (int)uVar9) {
              local_150 = (double)(longlong)(int)dVar26;
              iVar12 = (int)uVar9 >> 0x1f;
              uVar7 = __ct__6CColorFUcUcUcUc(auStack_17c,0xff,0xff,0xff,(int)dVar26);
              SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar7);
              SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x18);
              SetExternalTlut__8CTextureFPvi((CTexture *)MenuPcs._492_4_,0,1);
              uVar10 = 0x53;
              uVar3 = *(uint *)(param_1 + 0x18) & 1;
              if (uVar3 != 0) {
                uVar10 = 0xd;
              }
              uVar11 = 0;
              if ((uVar3 != 0) && ((*(uint *)(param_1 + 0x3d8c) & 4) == 0)) {
                uVar11 = 1;
              }
              uStack_15c = ((iVar12 * 8 | uVar9 * 0x20000000 + iVar12 >> 0x1d) - iVar12) * 0x30 ^
                           0x80000000;
              local_158 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
              local_160 = 0x43300000;
              local_148 = (double)CONCAT44(0x43300000,
                                           (((int)uVar9 >> 3) +
                                           (uint)((int)uVar9 < 0 && (uVar9 & 7) != 0)) * 0x30 ^
                                           0x80000000);
              DrawRect__8CMenuPcsFUlfffffffff
                        ((double)(float)(dVar18 + (double)(float)(local_158 - DOUBLE_80330900)),
                         (double)(float)((double)FLOAT_80330958 + dVar19),(double)FLOAT_8033095c,
                         (double)FLOAT_80330960,
                         (double)(float)((double)CONCAT44(0x43300000,uStack_15c) - DOUBLE_80330900),
                         (double)(float)(local_148 - DOUBLE_80330900),(double)FLOAT_80330914,
                         (double)FLOAT_80330914,&MenuPcs,(int)(-uVar11 | uVar11) >> 0x1f & 8);
            }
          }
        }
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x16);
        dVar22 = (double)(float)((double)FLOAT_80330908 * dVar33);
        iVar12 = (int)((double)FLOAT_80330908 * dVar33);
        local_148 = (double)(longlong)iVar12;
        uVar7 = __ct__6CColorFUcUcUcUc(auStack_180,0xff,0xff,0xff,iVar12);
        SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar7);
        uVar3 = *(uint *)(param_1 + 0x18);
        uVar9 = -(uVar3 & 1);
        local_150 = (double)CONCAT44(0x43300000,uVar9 & 0x80 ^ 0x80000000);
        uStack_15c = (int)(-(uVar3 & 2) | uVar3 & 2) >> 0x1f & 0x80U ^ 0x80000000;
        local_158 = (double)CONCAT44(0x43300000,-(uVar3 >> 1 & 1) & 0x38 ^ 0x80000000);
        dVar19 = (double)(float)(dVar20 - (double)(float)(local_150 - DOUBLE_80330900));
        local_160 = 0x43300000;
        dVar23 = (double)(float)(dVar23 - (double)(float)(local_158 - DOUBLE_80330900));
        local_140 = (double)CONCAT44(0x43300000,
                                     (int)(uVar9 | uVar3 & 1) >> 0x1f & 0x38U ^ 0x80000000);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar19,dVar23,(double)FLOAT_80330964,(double)FLOAT_80330948,
                   (double)(float)((double)CONCAT44(0x43300000,uStack_15c) - DOUBLE_80330900),
                   (double)(float)(local_140 - DOUBLE_80330900),(double)FLOAT_80330914,
                   (double)FLOAT_80330914,&MenuPcs,0);
        SetScale__5CFontFf(FLOAT_8033094c,(CFont *)uVar6);
        dVar18 = (double)GetWidth__5CFontFPc((CFont *)uVar6,uVar17 + 0x3ca);
        DrawInit__5CFontFv((CFont *)uVar6);
        SetTlut__5CFontFi((CFont *)uVar6,0xf);
        local_138 = (double)(longlong)(int)dVar22;
        puVar8 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_188,0xff,0xff,0xff,(int)dVar22);
        local_184 = *puVar8;
        SetColor__5CFontF8_GXColor((CFont *)uVar6,&local_184);
        fVar1 = FLOAT_80330950;
        if ((*(uint *)(param_1 + 0x18) & 1) != 0) {
          fVar1 = (float)((double)FLOAT_80330968 - dVar18);
        }
        SetPosX__5CFontFf((float)(dVar20 + (double)fVar1),(CFont *)uVar6);
        SetPosY__5CFontFf((float)((double)FLOAT_8033096c + dVar23),(CFont *)uVar6);
        Draw__5CFontFPc((CFont *)uVar6,uVar17 + 0x3ca);
        DrawInit__8CMenuPcsFv(&MenuPcs);
        uVar14 = Game.game.m_scriptFoodBase[*(int *)(param_1 + 0x18)];
        if ((uVar14 != 0) && ((double)FLOAT_803308d8 < dVar33)) {
          local_138 = (double)(longlong)(int)dVar22;
          uVar6 = __ct__6CColorFUcUcUcUc(auStack_1b0,0xff,0xff,0xff,(int)dVar22);
          SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x17);
          uVar9 = 0x4c;
          if ((*(uint *)(param_1 + 0x18) & 1) != 0) {
            uVar9 = 0x30;
          }
          local_140 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
          iVar13 = 0;
          dVar27 = (double)(float)((double)FLOAT_8033090c + dVar23);
          dVar28 = (double)FLOAT_80330910;
          dVar26 = (double)FLOAT_80330918;
          dVar29 = (double)FLOAT_80330914;
          dVar18 = dVar19 + (double)(float)(local_140 - DOUBLE_80330900);
          dVar30 = (double)FLOAT_8033091c;
          dVar31 = (double)FLOAT_80330920;
          dVar32 = (double)FLOAT_803308d8;
          iVar12 = param_1;
          dVar20 = DOUBLE_80330900;
          for (iVar15 = 0; dVar18 = (double)(float)dVar18,
              iVar15 < (int)(uint)(*(ushort *)(uVar14 + 0x1a) >> 1); iVar15 = iVar15 + 1) {
            iVar16 = *(int *)(param_1 + 0x3da8) - iVar13;
            local_138 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 0x3db0)) ^ 0x80000000)
            ;
            dVar21 = (double)sin((double)(float)(dVar28 * -(double)(float)((double)(float)(local_138
                                                                                          - dVar20)
                                                                           * dVar26 - dVar29)));
            uVar9 = *(uint *)(iVar12 + 0x3dd0);
            dVar21 = (double)(float)((double)(float)(dVar30 * (double)(float)dVar21 + dVar29) *
                                    dVar31);
            if (uVar9 == 0) {
              iVar4 = 0;
            }
            else {
              iVar4 = ((int)uVar9 >> 2) * *(int *)(&DAT_8020f998 + ((uVar9 + 1) * 4 & 0xc));
            }
            local_140 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
            if (uVar9 == 0) {
              uVar9 = 0;
            }
            else {
              uVar9 = ((int)uVar9 >> 2) * *(int *)(&DAT_8020f998 + (uVar9 & 3) * 4);
            }
            dVar25 = (double)(float)(dVar18 + (double)(float)(local_140 - dVar20));
            local_148 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
            dVar24 = (double)(float)(dVar27 + (double)(float)(local_148 - dVar20));
            DrawRect__8CMenuPcsFUlfffffffff
                      (dVar25,dVar24,(double)FLOAT_803308dc,(double)FLOAT_803308dc,dVar32,dVar32,
                       dVar21,dVar21,&MenuPcs,3);
            if (0 < iVar16) {
              iVar4 = 0xb;
              if (iVar16 < 0xb) {
                iVar4 = iVar16;
              }
              local_138 = (double)(CONCAT44(0x43300000,
                                            ~((int)(-(uint)*(ushort *)(uVar14 + 0x42) |
                                                   (uint)*(ushort *)(uVar14 + 0x42)) >> 0x1f)) &
                                   0xffffffff00000018 ^ 0x80000000);
              local_140 = (double)(CONCAT44(0x43300000,(0xc - iVar4) * 0x18) ^ 0x80000000);
              DrawRect__8CMenuPcsFUlfffffffff
                        (dVar25,dVar24,(double)FLOAT_803308dc,(double)FLOAT_803308dc,
                         (double)(float)(local_138 - DOUBLE_80330900),
                         (double)(float)(local_140 - DOUBLE_80330900),dVar21,dVar21,&MenuPcs,3);
            }
            fVar1 = FLOAT_80330928;
            if ((*(uint *)(param_1 + 0x18) & 1) != 0) {
              fVar1 = FLOAT_80330924;
            }
            dVar18 = dVar18 + (double)fVar1;
            iVar13 = iVar13 + 0xc;
            iVar12 = iVar12 + 4;
          }
        }
        uVar9 = *(uint *)(param_1 + 0x3df0);
        iVar12 = *(ushort *)(uVar17 + 0x14) - 100;
        iVar12 = iVar12 / 100 + (iVar12 >> 0x1f);
        uVar3 = (uint)*(ushort *)(uVar17 + 0x14) % 100 + (iVar12 - (iVar12 >> 0x1f)) * 4;
        iVar12 = (int)uVar3 >> 0x1f;
        if (uVar9 == 0) {
          uVar10 = 0;
        }
        else {
          uVar10 = ((int)uVar9 >> 2) * *(int *)(&DAT_8020f998 + (3 - (uVar9 + 1 & 3)) * 4);
        }
        local_138 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
        dVar18 = (double)(float)(local_138 - DOUBLE_80330900);
        if (uVar9 == 0) {
          uVar9 = 0;
        }
        else {
          uVar9 = ((int)uVar9 >> 2) * *(int *)(&DAT_8020f998 + (3 - (uVar9 & 3)) * 4);
        }
        local_148 = (double)(longlong)(int)dVar22;
        local_140 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
        dVar20 = (double)(float)(local_140 - DOUBLE_80330900);
        uVar6 = __ct__6CColorFUcUcUcUc
                          (local_140,DOUBLE_80330900,auStack_18c,0xff,0xff,0xff,(int)dVar22);
        SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x18);
        uVar6 = 0x802ea500;
        if (*(short *)(uVar17 + 0x1c) != 0) {
          uVar6 = 0;
        }
        SetExternalTlut__8CTextureFPvi((CTexture *)MenuPcs._492_4_,uVar6,1);
        uVar10 = 5;
        uVar9 = *(uint *)(param_1 + 0x18) & 1;
        if (uVar9 != 0) {
          uVar10 = 0x4b;
        }
        uStack_15c = (((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0)) * 0x30 ^
                     0x80000000;
        local_150 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
        local_158 = (double)CONCAT44(0x43300000,
                                     ((iVar12 * 8 | uVar3 * 0x20000000 + iVar12 >> 0x1d) - iVar12) *
                                     0x30 ^ 0x80000000);
        local_160 = 0x43300000;
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)((float)(dVar19 + dVar18) + (float)(local_150 - DOUBLE_80330900)),
                   (double)(FLOAT_80330958 + (float)(dVar23 + dVar20)),(double)FLOAT_8033095c,
                   (double)FLOAT_80330960,(double)(float)(local_158 - DOUBLE_80330900),
                   (double)(float)((double)CONCAT44(0x43300000,uStack_15c) - DOUBLE_80330900),
                   (double)FLOAT_80330914,(double)FLOAT_80330914,&MenuPcs,
                   ~((int)(-uVar9 | uVar9) >> 0x1f) & 8);
      }
      else {
        dVar20 = (double)FLOAT_803308ec;
        dVar23 = (double)(float)((double)*(float *)(param_1 + 0x3d7c) * dVar18);
        dVar19 = (double)(float)((double)*(float *)(param_1 + 0x3d80) * dVar18);
        dVar22 = -(double)(float)(dVar20 * dVar23 -
                                 (double)(float)(dVar20 * (double)*(float *)(param_1 + 0x3d7c) +
                                                (double)(*(float *)(param_1 + 0x3d6c) +
                                                        *(float *)(param_1 + 0x3d74))));
        dVar20 = -(double)(float)(dVar20 * dVar19 -
                                 (double)(float)(dVar20 * (double)*(float *)(param_1 + 0x3d80) +
                                                (double)(*(float *)(param_1 + 0x3d70) +
                                                        *(float *)(param_1 + 0x3d78))));
        if ((*(uint *)(param_1 + 0x3d8c) & 1) == 0) {
          dVar27 = (double)(float)((double)FLOAT_80330908 * dVar18) * dVar33;
          dVar28 = (double)(float)dVar27;
          iVar12 = (int)dVar27;
          local_138 = (double)(longlong)iVar12;
          uVar7 = __ct__6CColorFUcUcUcUc(auStack_190,0xff,0xff,0xff,iVar12);
          SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar7);
          uVar7 = 0xb;
          if ((*(uint *)(param_1 + 0x3d8c) & 0x200) != 0) {
            uVar7 = 2;
          }
          DrawWindow__8CMenuPcsFffffQ28CMenuPcs3TEXf
                    (dVar22,dVar20,dVar23,dVar19,(double)FLOAT_8033092c,&MenuPcs,uVar7);
          if (((-1 < *(int *)(param_1 + 0x3d94)) || (-1 < *(int *)(param_1 + 0x3d98))) &&
             (uVar9 = *(uint *)(param_1 + 0x3d8c) >> 10 & 7, uVar9 != 0)) {
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x14);
            local_138 = (double)(longlong)(int)dVar28;
            uVar7 = __ct__6CColorFUcUcUcUc(auStack_194,0xff,0xff,0xff,(int)dVar28);
            SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar7);
            uVar3 = uVar9 - 1 & 1;
            fVar1 = FLOAT_80330938;
            if (uVar3 == 0) {
              fVar1 = (float)(dVar23 - (double)FLOAT_8033093c) - FLOAT_80330938;
            }
            uVar9 = uVar9 - 1 & 2;
            dVar23 = (double)((float)(dVar22 + (double)FLOAT_803308d8) + fVar1);
            fVar1 = FLOAT_80330944;
            if (uVar9 != 0) {
              fVar1 = (float)((double)FLOAT_80330940 + dVar19);
            }
            dVar19 = (double)(float)(dVar20 + (double)fVar1);
            local_140 = (double)(CONCAT44(0x43300000,(int)(-uVar9 | uVar9) >> 0x1f) &
                                 0xffffffff00000090 ^ 0x80000000);
            DrawRect__8CMenuPcsFUlfffffffff
                      (dVar23,dVar19,(double)FLOAT_8033093c,(double)FLOAT_80330948,
                       (double)(float)(local_140 - DOUBLE_80330900),(double)FLOAT_803308d8,
                       (double)FLOAT_80330914,(double)FLOAT_80330914,&MenuPcs,
                       (int)(-uVar3 | uVar3) >> 0x1f & 8);
            if (-1 < *(int *)(param_1 + 0x3d98)) {
              SetScale__5CFontFf(FLOAT_8033094c,(CFont *)uVar6);
              SetShadow__5CFontFi((CFont *)uVar6,1);
              SetMargin__5CFontFf(FLOAT_803308d8,(CFont *)uVar6);
              dVar27 = (double)GetWidth__5CFontFPc((CFont *)uVar6,
                                                   Game.game.m_cFlatDataArr[1].m_table[2].index
                                                   [*(int *)(param_1 + 0x3d98)]);
              DrawInit__5CFontFv((CFont *)uVar6);
              SetTlut__5CFontFi((CFont *)uVar6,0xf);
              local_138 = (double)(longlong)(int)dVar28;
              puVar8 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_19c,0xff,0xff,0xff,(int)dVar28);
              local_198 = *puVar8;
              SetColor__5CFontF8_GXColor((CFont *)uVar6,&local_198);
              fVar1 = FLOAT_80330950;
              if (uVar3 == 0) {
                fVar1 = (float)((double)FLOAT_80330954 - dVar27);
              }
              SetPosX__5CFontFf((float)(dVar23 + (double)fVar1),(CFont *)uVar6);
              uVar10 = 0x1f;
              if (uVar9 != 0) {
                uVar10 = 8;
              }
              local_140 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
              SetPosY__5CFontFf((float)(dVar19 + (double)(float)(local_140 - DOUBLE_80330900)),
                                (CFont *)uVar6);
              Draw__5CFontFPc((CFont *)uVar6,
                              Game.game.m_cFlatDataArr[1].m_table[2].index
                              [*(int *)(param_1 + 0x3d98)]);
              DrawInit__8CMenuPcsFv(&MenuPcs);
            }
            uVar9 = *(uint *)(param_1 + 0x3d94);
            if (-1 < (int)uVar9) {
              local_138 = (double)(longlong)(int)dVar28;
              iVar12 = (int)uVar9 >> 0x1f;
              uVar6 = __ct__6CColorFUcUcUcUc(auStack_1a0,0xff,0xff,0xff,(int)dVar28);
              SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
              SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x18);
              SetExternalTlut__8CTextureFPvi((CTexture *)MenuPcs._492_4_,0,1);
              uVar10 = 0x53;
              if (uVar3 != 0) {
                uVar10 = 0xd;
              }
              uVar11 = 0;
              if ((uVar3 != 0) && ((*(uint *)(param_1 + 0x3d8c) & 4) == 0)) {
                uVar11 = 1;
              }
              local_140 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
              local_148 = (double)CONCAT44(0x43300000,
                                           ((iVar12 * 8 | uVar9 * 0x20000000 + iVar12 >> 0x1d) -
                                           iVar12) * 0x30 ^ 0x80000000);
              local_150 = (double)CONCAT44(0x43300000,
                                           (((int)uVar9 >> 3) +
                                           (uint)((int)uVar9 < 0 && (uVar9 & 7) != 0)) * 0x30 ^
                                           0x80000000);
              DrawRect__8CMenuPcsFUlfffffffff
                        ((double)(float)(dVar23 + (double)(float)(local_140 - DOUBLE_80330900)),
                         (double)(float)((double)FLOAT_80330958 + dVar19),(double)FLOAT_8033095c,
                         (double)FLOAT_80330960,(double)(float)(local_148 - DOUBLE_80330900),
                         (double)(float)(local_150 - DOUBLE_80330900),(double)FLOAT_80330914,
                         (double)FLOAT_80330914,&MenuPcs,(int)(-uVar11 | uVar11) >> 0x1f & 8);
            }
          }
        }
        if ((*(int *)(param_1 + 0xc) == 1) && ((*(uint *)(param_1 + 0x3d8c) & 0x2000) != 0)) {
          dVar23 = (double)(float)(dVar18 * dVar33);
          dVar18 = (double)FLOAT_80330914;
          local_138 = (double)(CONCAT44(0x43300000,*(undefined4 *)(param_1 + 0x10)) ^ 0x80000000);
          dVar19 = (double)(float)((double)FLOAT_80330970 * (double)(float)(dVar18 - dVar23) +
                                  dVar18);
          dVar18 = (double)fmod((double)(FLOAT_80330974 * (float)(local_138 - DOUBLE_80330900)),
                                DOUBLE_80330978,dVar18,(double)FLOAT_80330970);
          fVar1 = (float)dVar18;
          if (FLOAT_80330914 < fVar1) {
            fVar1 = FLOAT_803308e8 - fVar1;
          }
          dVar27 = (double)(FLOAT_80330910 * fVar1);
          dVar18 = (double)sin(dVar27);
          dVar28 = (double)(float)dVar18;
          dVar18 = (double)sin((double)(float)((double)FLOAT_80330980 + dVar27));
          dVar27 = (double)(float)dVar18;
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
          dVar23 = (double)(float)((double)FLOAT_80330908 * dVar23);
          iVar12 = (int)((double)(float)((double)FLOAT_803308ec * dVar23) * dVar33);
          local_140 = (double)(longlong)iVar12;
          uVar6 = __ct__6CColorFUcUcUcUc(auStack_1a4,0,0,0,iVar12);
          SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
          local_148 = (double)(longlong)(int)((double)FLOAT_803308f8 + dVar22);
          local_158 = (double)(longlong)(int)((double)FLOAT_8033092c + dVar20);
          local_160 = 0x43300000;
          dVar18 = (double)(float)((double)FLOAT_80330914 - dVar19);
          uStack_15c = (int)((double)FLOAT_8033092c + dVar20) ^ 0x80000000;
          local_150 = (double)(CONCAT44(0x43300000,(int)((double)FLOAT_803308f8 + dVar22)) ^
                              0x80000000);
          dVar22 = (double)((float)(local_150 - DOUBLE_80330900) +
                           FLOAT_80330984 * (float)(dVar19 * dVar27));
          dVar20 = (double)((float)((double)CONCAT44(0x43300000,uStack_15c) - DOUBLE_80330900) -
                           FLOAT_80330988 * (float)(dVar19 * dVar28));
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)(float)((double)FLOAT_803308e4 + dVar22),
                     (double)(float)((double)FLOAT_803308e4 + dVar20),(double)FLOAT_8033098c,
                     (double)FLOAT_8033095c,(double)FLOAT_803308d8,(double)FLOAT_803308d8,
                     (double)(FLOAT_80330990 * (float)((double)FLOAT_80330914 + dVar18)),
                     (double)(FLOAT_80330990 * (float)(dVar19 + dVar18)),&MenuPcs,3);
          local_130 = (longlong)(int)(dVar23 * dVar33);
          uVar6 = __ct__6CColorFUcUcUcUc(auStack_1a8,0xff,0xff,0xff,(int)(dVar23 * dVar33));
          SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar22,dVar20,(double)FLOAT_8033098c,(double)FLOAT_8033095c,
                     (double)FLOAT_803308d8,(double)FLOAT_803308d8,
                     (double)(float)((double)FLOAT_80330990 * dVar19),
                     (double)(float)((double)FLOAT_80330990 * dVar19),&MenuPcs,3);
        }
        if (*(int *)(param_1 + 0xc) == 1) {
          Draw__4CMesFv(param_1 + 0x1c);
          DrawInit__8CMenuPcsFv(&MenuPcs);
        }
      }
      if ((*(int *)(param_1 + 0xc) == 1) && (iVar12 = GetWait__4CMesFv(param_1 + 0x1c), iVar12 == 3)
         ) {
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
        local_130 = (longlong)(int)((double)FLOAT_80330908 * dVar33);
        uVar6 = __ct__6CColorFUcUcUcUc
                          (auStack_1ac,0xff,0xff,0xff,(int)((double)FLOAT_80330908 * dVar33));
        SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
        local_138 = (double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x3d34) ^ 0x80000000);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(FLOAT_80330994 + *(float *)(param_1 + 0x3cb8)),
                   (double)((float)(local_138 - DOUBLE_80330900) * *(float *)(param_1 + 0x3d40) +
                           FLOAT_803308e8 + *(float *)(param_1 + 0x3cbc) +
                           *(float *)(param_1 + 0x3d3c)),(double)FLOAT_8033092c,
                   (double)FLOAT_8033092c,(double)FLOAT_803308d8,(double)FLOAT_803308d8,
                   (double)FLOAT_80330914,(double)FLOAT_80330914,&MenuPcs,0);
      }
    }
  }
  return;
}

