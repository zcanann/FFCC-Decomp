// Function: DrawMCList__8CMenuPcsFv
// Entry: 800eb6f8
// Size: 6328 bytes

/* WARNING: Removing unreachable block (ram,0x800ecf94) */
/* WARNING: Removing unreachable block (ram,0x800ecf8c) */
/* WARNING: Removing unreachable block (ram,0x800ecf84) */
/* WARNING: Removing unreachable block (ram,0x800ecf7c) */
/* WARNING: Removing unreachable block (ram,0x800ecf74) */
/* WARNING: Removing unreachable block (ram,0x800ecf6c) */
/* WARNING: Removing unreachable block (ram,0x800ecf64) */
/* WARNING: Removing unreachable block (ram,0x800ecf5c) */
/* WARNING: Removing unreachable block (ram,0x800ecf54) */
/* WARNING: Removing unreachable block (ram,0x800ecf4c) */
/* WARNING: Removing unreachable block (ram,0x800ecf44) */
/* WARNING: Removing unreachable block (ram,0x800ecf3c) */
/* WARNING: Removing unreachable block (ram,0x800ecf34) */
/* WARNING: Removing unreachable block (ram,0x800ecf2c) */
/* WARNING: Removing unreachable block (ram,0x800eb770) */
/* WARNING: Removing unreachable block (ram,0x800eb768) */
/* WARNING: Removing unreachable block (ram,0x800eb760) */
/* WARNING: Removing unreachable block (ram,0x800eb758) */
/* WARNING: Removing unreachable block (ram,0x800eb750) */
/* WARNING: Removing unreachable block (ram,0x800eb748) */
/* WARNING: Removing unreachable block (ram,0x800eb740) */
/* WARNING: Removing unreachable block (ram,0x800eb738) */
/* WARNING: Removing unreachable block (ram,0x800eb730) */
/* WARNING: Removing unreachable block (ram,0x800eb728) */
/* WARNING: Removing unreachable block (ram,0x800eb720) */
/* WARNING: Removing unreachable block (ram,0x800eb718) */
/* WARNING: Removing unreachable block (ram,0x800eb710) */
/* WARNING: Removing unreachable block (ram,0x800eb708) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawMCList__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  bool bVar3;
  uint8_t uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint32_t *puVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  char *pcVar12;
  undefined4 uVar13;
  int iVar14;
  short *psVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  uint *puVar19;
  int iVar20;
  CTexture *texture;
  CFont *font;
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
  undefined4 local_320;
  undefined4 local_31c;
  undefined auStack_318 [4];
  undefined4 local_314;
  undefined auStack_310 [4];
  undefined4 local_30c;
  undefined auStack_308 [4];
  undefined4 local_304;
  undefined auStack_300 [4];
  undefined4 local_2fc;
  undefined auStack_2f8 [4];
  undefined4 local_2f4;
  undefined4 local_2f0;
  undefined4 local_2ec;
  int local_2e8;
  int local_2e4;
  undefined4 local_2e0;
  undefined local_2dc;
  undefined local_2db;
  undefined local_2da;
  undefined local_2d9;
  undefined local_2d8;
  undefined local_2d7;
  undefined local_2d6;
  undefined local_2d5;
  undefined local_2d4;
  undefined local_2d3;
  undefined local_2d2;
  undefined local_2d1;
  uint local_2d0 [4];
  int local_2c0;
  Mtx MStack_2bc;
  undefined local_28c [64];
  undefined auStack_24c [64];
  char local_20c [64];
  undefined auStack_1cc [132];
  undefined8 local_148;
  undefined4 local_140;
  uint uStack_13c;
  undefined8 local_138;
  undefined8 local_130;
  
  font = *(CFont **)&menuPcs->field_0xf8;
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (((sVar2 == 2) || (sVar2 == 3)) && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x16) != 0)) {
    uVar17 = 0;
    iVar16 = 0;
    do {
      iVar14 = *(int *)&menuPcs->field_0x82c;
      if ((*(short *)(iVar14 + 0x16) == 1) || (*(short *)(iVar14 + 0x10) == 3)) {
        if (*(short *)(iVar14 + 0x10) == 2) {
          uVar5 = *(short *)(iVar14 + 0x22) - iVar16;
        }
        else {
          uVar5 = 10 - ((int)*(short *)(iVar14 + 0x22) + (3 - uVar17) * -3);
        }
        if (-1 < (int)uVar5) {
          if ((int)uVar5 < 0xb) {
            uStack_13c = uVar5 ^ 0x80000000;
            local_140 = 0x43300000;
            local_148 = (double)CONCAT44(0x43300000,uStack_13c);
            dVar24 = (double)(float)(DOUBLE_803314e8 *
                                    ((double)CONCAT44(0x43300000,uStack_13c) - DOUBLE_80331408));
            dVar31 = (double)((float)(local_148 - DOUBLE_80331408) * FLOAT_803314e0 + FLOAT_803314dc
                             );
          }
          else {
            dVar31 = (double)FLOAT_803314d8;
            dVar24 = (double)FLOAT_803313e8;
          }
          goto LAB_800eb868;
        }
      }
      else {
        dVar31 = (double)FLOAT_803314d8;
        dVar24 = (double)FLOAT_803313e8;
LAB_800eb868:
        if (DOUBLE_803314f0 < dVar24) {
          uStack_13c = uVar17 ^ 0x80000000;
          local_140 = 0x43300000;
          dVar27 = (double)(float)(DOUBLE_80331498 *
                                   ((double)CONCAT44(0x43300000,uStack_13c) - DOUBLE_80331408) +
                                  DOUBLE_80331490);
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
          dVar25 = (double)(float)((double)FLOAT_80331458 * dVar24);
          iVar14 = (int)((double)FLOAT_80331458 * dVar24);
          local_148 = (double)(longlong)iVar14;
          local_2e0 = CONCAT31(0xffffff,(char)iVar14);
          local_2ec = local_2e0;
          GXSetChanMatColor(4,&local_2ec);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x24);
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar31,dVar27,(double)FLOAT_80331468,(double)FLOAT_803314f8,
                     (double)FLOAT_803313dc,(double)FLOAT_803313dc,(double)FLOAT_803313e8,
                     (double)FLOAT_803313e8,&MenuPcs,0);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x25);
          dVar24 = (double)(float)(dVar31 + (double)FLOAT_80331468);
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar24,dVar27,(double)FLOAT_803314fc,(double)FLOAT_803314f8,
                     (double)FLOAT_803313dc,(double)FLOAT_803313dc,(double)FLOAT_803313e8,
                     (double)FLOAT_803313e8,&MenuPcs,0);
          dVar24 = (double)(float)(dVar24 + (double)FLOAT_803314fc);
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
          local_138 = (double)(longlong)(int)dVar25;
          local_2d5 = (undefined)(int)dVar25;
          local_2e0 = CONCAT31(0xffffff,local_2d5);
          local_2dc = 0xff;
          local_2db = 0xff;
          local_2da = 0xff;
          local_2d9 = 0;
          local_2d8 = 0xff;
          local_2d7 = 0xff;
          local_2d6 = 0xff;
          local_2d4 = 0xff;
          local_2d3 = 0xff;
          local_2d2 = 0xff;
          local_2d1 = 0;
          local_130 = local_138;
          DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                    (dVar24,dVar27,(double)FLOAT_80331500,(double)FLOAT_803314f8,
                     (double)FLOAT_803313dc,(double)FLOAT_803313dc,(double)FLOAT_803313e8,
                     (double)FLOAT_803313e8,&MenuPcs,0,&local_2e0);
        }
      }
      uVar17 = uVar17 + 1;
      iVar16 = iVar16 + 3;
    } while ((int)uVar17 < 4);
  }
  iVar16 = *(int *)&menuPcs->field_0x82c;
  sVar2 = *(short *)(iVar16 + 0x10);
  if (sVar2 == 0) {
    local_130 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar16 + 0x22)) ^ 0x80000000);
    dVar24 = (double)(float)(DOUBLE_803314e8 * (local_130 - DOUBLE_80331408));
  }
  else if ((sVar2 < 1) || (3 < sVar2)) {
    local_130 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar16 + 0x22)) ^ 0x80000000);
    dVar24 = (double)(float)-(DOUBLE_803314e8 * (local_130 - DOUBLE_80331408) - DOUBLE_80331420);
  }
  else {
    dVar24 = (double)FLOAT_803313e8;
  }
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_130 = (double)(longlong)(int)(DOUBLE_80331508 * dVar24);
  local_320 = CONCAT31(0xffffff,(char)(int)(DOUBLE_80331508 * dVar24));
  local_31c = local_320;
  GXSetChanMatColor(4,&local_31c);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
  iVar16 = 0;
  iVar14 = 0;
  do {
    if ((1 << iVar16 & 2U) != 0) {
      psVar15 = (short *)(*(int *)&menuPcs->field_0x820 + iVar14 + 4);
      local_130 = (double)(CONCAT44(0x43300000,(int)*psVar15) ^ 0x80000000);
      uStack_13c = (int)psVar15[2] ^ 0x80000000;
      local_138 = (double)CONCAT44(0x43300000,(int)psVar15[1] ^ 0x80000000);
      local_140 = 0x43300000;
      local_148 = (double)CONCAT44(0x43300000,(int)psVar15[3] ^ 0x80000000);
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)(local_130 - DOUBLE_80331408),
                 (double)(float)(local_138 - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_13c) - DOUBLE_80331408),
                 (double)(float)(local_148 - DOUBLE_80331408),(double)*(float *)(psVar15 + 4),
                 (double)*(float *)(psVar15 + 6),(double)FLOAT_803313e8,(double)FLOAT_803313e8,
                 &MenuPcs,*(undefined4 *)(psVar15 + 0xc));
    }
    iVar16 = iVar16 + 1;
    iVar14 = iVar14 + 0x1c;
  } while (iVar16 < 2);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_2e0 = 0xffffffff;
  local_2f0 = 0xffffffff;
  GXSetChanMatColor(4,&local_2f0);
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
  if (((sVar2 != 0) && (1 < sVar2)) && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2)) {
    uVar17 = 0;
    dVar24 = DOUBLE_80331510;
    dVar31 = DOUBLE_80331490;
    dVar25 = DOUBLE_80331408;
    dVar27 = DOUBLE_80331498;
    do {
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
      dVar21 = (double)FLOAT_803314d8;
      local_130 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
      local_138 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar21,(double)(float)((double)(float)(dVar27 * (local_130 - dVar25) + dVar31) -
                                       dVar24),dVar21,dVar21,
                 (double)(float)(dVar31 * (local_138 - dVar25)),(double)FLOAT_803313e0,
                 (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
      uVar17 = uVar17 + 1;
    } while ((int)uVar17 < 4);
  }
  uVar4 = Game.game.m_gameWork.m_languageId;
  if ((0x10 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x16)) &&
     (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) < 3)) {
    uVar17 = 0;
    dVar27 = DOUBLE_80331510 + (double)FLOAT_80331518;
    iVar16 = 0;
    dVar24 = DOUBLE_80331490;
    dVar31 = DOUBLE_80331498;
    dVar25 = DOUBLE_80331408;
    do {
      iVar14 = (int)menuPcs->m_unk0x838 + iVar16;
      local_130 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
      dVar21 = (double)(float)(dVar31 * (local_130 - dVar25) + dVar24);
      if ((*(char *)(iVar14 + 0x42) == '\0') && (*(char *)(iVar14 + 0x41) != '\0')) {
        dVar26 = (double)FLOAT_80331468;
        dVar32 = (double)(float)((double)FLOAT_80331440 + dVar21);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x26);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)FLOAT_80331468,dVar32,(double)FLOAT_803314d8,(double)FLOAT_80331440,
                   (double)FLOAT_803313dc,(double)FLOAT_803313dc,(double)FLOAT_803313e8,
                   (double)FLOAT_803313e8,&MenuPcs,0);
        uVar5 = (uint)(-1 < *(int *)(iVar14 + 0x18));
        if (-1 < *(int *)(iVar14 + 0x1c)) {
          uVar5 = uVar5 + 1;
        }
        if (-1 < *(int *)(iVar14 + 0x20)) {
          uVar5 = uVar5 + 1;
        }
        if (-1 < *(int *)(iVar14 + 0x24)) {
          uVar5 = uVar5 + 1;
        }
        uVar18 = uVar5 * 0x30 + 0x40;
        local_130 = (double)(CONCAT44(0x43300000,uVar18) ^ 0x80000000);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)(dVar26 + (double)(float)((double)FLOAT_803314d8 +
                                                           (double)(float)(local_130 -
                                                                          DOUBLE_80331408))),dVar32,
                   (double)FLOAT_803314d8,(double)FLOAT_80331440,(double)FLOAT_803313dc,
                   (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,8);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x2a);
        local_138 = (double)CONCAT44(0x43300000,uVar18 ^ 0x80000000);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)FLOAT_8033151c,dVar32,(double)(float)(local_138 - DOUBLE_80331408),
                   (double)FLOAT_80331440,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
                   (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
        dVar26 = (double)FLOAT_80331520;
        if (uVar4 != '\x05') {
          dVar32 = (double)(float)((double)FLOAT_803314d8 + dVar21);
        }
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x17);
        uVar18 = *(uint *)(iVar14 + 8);
        iVar7 = 1 - ((int)(((int)(uVar18 ^ 9) >> 1) - ((uVar18 ^ 9) & uVar18)) >> 0x1f);
        if (99 < (int)uVar18) {
          iVar7 = 3;
        }
        if (iVar7 == 3) {
          local_130 = (double)CONCAT44(0x43300000,DAT_801dc140 ^ 0x80000000);
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)FLOAT_80331520,dVar32,(double)(float)(local_130 - DOUBLE_80331408),
                     (double)FLOAT_80331410,(double)FLOAT_80331524,(double)FLOAT_80331528,
                     (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
        }
        else {
          iVar20 = 0;
          for (iVar6 = iVar7; iVar6 != 0; iVar6 = iVar6 + -1) {
            iVar8 = (int)uVar18 >> 0x1f;
            if (iVar7 == 1) {
              iVar8 = (int)uVar18 / 10 + iVar8;
              uVar5 = *(uint *)(&DAT_801dc118 + (uVar18 + (iVar8 - (iVar8 >> 0x1f)) * -10) * 4);
            }
            else if (iVar20 == 0) {
              iVar8 = (int)uVar18 / 10 + iVar8;
              uVar5 = *(uint *)(&DAT_801dc118 + (iVar8 - (iVar8 >> 0x1f)) * 4);
            }
            else {
              iVar8 = (int)uVar18 / 10 + iVar8;
              uVar5 = uVar5 + *(int *)(&DAT_801dc118 +
                                      (uVar18 + (iVar8 - (iVar8 >> 0x1f)) * -10) * 4);
            }
            iVar20 = iVar20 + 1;
          }
          dVar29 = DOUBLE_80331420;
          if (uVar4 != '\x05') {
            dVar29 = DOUBLE_80331530;
          }
          dVar29 = (double)(float)dVar29;
          if (uVar4 == '\x02') {
            uVar5 = uVar5 + 8;
          }
          else if (uVar4 == '\x03') {
            uVar5 = uVar5 + 0xb;
          }
          else if (uVar4 != '\x05') {
            uVar5 = uVar5 + 0x20;
          }
          local_130 = (double)CONCAT44(0x43300000,uVar5 ^ 0x80000000);
          local_140 = 0x43300000;
          iVar20 = (int)((double)(float)(local_130 - DOUBLE_80331408) * dVar29);
          local_138 = (double)(longlong)iVar20;
          uStack_13c = (0x20 - iVar20) / 2 ^ 0x80000000;
          dVar26 = dVar26 + (double)(float)((double)CONCAT44(0x43300000,uStack_13c) -
                                           DOUBLE_80331408);
          dVar22 = DOUBLE_80331490;
          dVar28 = DOUBLE_80331540;
          dVar30 = DOUBLE_80331538;
          dVar33 = DOUBLE_80331408;
          for (iVar20 = 0; dVar26 = (double)(float)dVar26, iVar20 < iVar7; iVar20 = iVar20 + 1) {
            if (iVar7 == 1) {
              iVar8 = *(int *)(iVar14 + 8);
              iVar6 = iVar8 / 10 + (iVar8 >> 0x1f);
              iVar8 = iVar8 + (iVar6 - (iVar6 >> 0x1f)) * -10;
            }
            else if (iVar20 == 0) {
              iVar8 = *(int *)(iVar14 + 8) / 10 + (*(int *)(iVar14 + 8) >> 0x1f);
              iVar8 = iVar8 - (iVar8 >> 0x1f);
            }
            else {
              iVar8 = *(int *)(iVar14 + 8);
              iVar6 = iVar8 / 10 + (iVar8 >> 0x1f);
              iVar8 = iVar8 + (iVar6 - (iVar6 >> 0x1f)) * -10;
            }
            iVar6 = iVar8 / 5 + (iVar8 >> 0x1f);
            local_140 = 0x43300000;
            uStack_13c = iVar6 - (iVar6 >> 0x1f) ^ 0x80000000;
            local_138 = (double)(CONCAT44(0x43300000,iVar8 + (iVar6 - (iVar6 >> 0x1f)) * -5) ^
                                0x80000000);
            local_130 = (double)CONCAT44(0x43300000,
                                         *(uint *)(&DAT_801dc118 + iVar8 * 4) ^ 0x80000000);
            dVar23 = (double)(float)(local_130 - dVar33);
            DrawRect__8CMenuPcsFUlfffffffff
                      (dVar26,dVar32,dVar23,(double)FLOAT_80331410,
                       (double)(float)(dVar22 * (double)(float)(local_138 - dVar33)),
                       (double)(float)(dVar28 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_13c) -
                                                               dVar33) + dVar30),dVar29,
                       (double)FLOAT_803313e8,&MenuPcs,0);
            dVar26 = dVar23 * dVar29 + dVar26;
          }
          if (uVar4 == '\x02') {
            dVar29 = (double)FLOAT_80331548;
          }
          else if (uVar4 == '\x03') {
            dVar29 = (double)FLOAT_8033154c;
          }
          else {
            dVar29 = (double)FLOAT_80331410;
          }
          dVar22 = (double)FLOAT_803313dc;
          bVar3 = false;
          if ((uVar4 == '\x01') || (uVar4 == '\x04')) {
            bVar3 = true;
          }
          dVar28 = DOUBLE_80331420;
          if (bVar3) {
            dVar28 = DOUBLE_80331530;
          }
          dVar28 = (double)(float)dVar28;
          if (uVar4 == '\x01') {
            iVar20 = *(int *)(iVar14 + 8);
            iVar7 = iVar20 / 10 + (iVar20 >> 0x1f);
            if (iVar7 - (iVar7 >> 0x1f) == 1) {
              dVar22 = (double)FLOAT_8033151c;
            }
            else {
              iVar20 = iVar20 + (iVar7 - (iVar7 >> 0x1f)) * -10;
              if ((iVar20 < 1) || (3 < iVar20)) {
                dVar22 = (double)FLOAT_8033151c;
              }
              else {
                local_130 = (double)(CONCAT44(0x43300000,iVar20 + -1) ^ 0x80000000);
                dVar22 = (double)(FLOAT_803314d8 * (float)(local_130 - DOUBLE_80331408));
              }
            }
          }
          else if (uVar4 == '\x04') {
            if (*(int *)(iVar14 + 8) != 1) {
              dVar22 = (double)FLOAT_803314d8;
            }
          }
          else if (uVar4 == '\x02') {
            dVar32 = (double)(float)(dVar32 + (double)FLOAT_80331550);
          }
          if (uVar4 != '\x05') {
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x34);
            DrawRect__8CMenuPcsFUlfffffffff
                      (dVar26,dVar32,dVar29,(double)FLOAT_803314d8,(double)FLOAT_803313dc,dVar22,
                       dVar28,(double)FLOAT_803313e8,&MenuPcs,0);
          }
        }
        if (uVar4 == '\x05') {
          fVar1 = FLOAT_803314c8 + (float)((double)FLOAT_803314d8 + dVar21);
        }
        else {
          fVar1 = (float)((double)FLOAT_80331554 + dVar21);
        }
        dVar32 = (double)fVar1;
        dVar26 = (double)(FLOAT_80331520 - FLOAT_80331550);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x21);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar26,dVar32,(double)FLOAT_80331440,(double)FLOAT_80331558,
                   (double)FLOAT_803313dc,(double)FLOAT_803313dc,(double)FLOAT_803313e8,
                   (double)FLOAT_803313e8,&MenuPcs,0);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x37);
        dVar26 = (double)FLOAT_8033155c;
        iVar20 = 0;
        dVar32 = (double)(float)((double)FLOAT_803314d8 + dVar21);
        iVar7 = iVar14;
        do {
          if (-1 < *(int *)(iVar7 + 0x18)) {
            iVar6 = *(int *)(iVar7 + 0x18) + -100;
            iVar8 = iVar6 / 100 + (iVar6 >> 0x1f);
            uVar5 = iVar8 - (iVar8 >> 0x1f);
            dVar29 = DOUBLE_803314f0;
            if ((uVar5 & 1) != 0) {
              dVar29 = (double)FLOAT_80331560;
            }
            dVar22 = (double)FLOAT_80331468;
            iVar8 = iVar6 / 100 + (iVar6 >> 0x1f);
            local_138 = (double)(CONCAT44(0x43300000,(int)uVar5 / 2) ^ 0x80000000);
            local_130 = (double)(CONCAT44(0x43300000,iVar6 + (iVar8 - (iVar8 >> 0x1f)) * -100) ^
                                0x80000000);
            DrawRect__8CMenuPcsFUlfffffffff
                      (dVar26,dVar32,dVar22,dVar22,
                       (double)((float)dVar29 +
                               (float)((double)(float)(local_130 - DOUBLE_80331408) * dVar22)),
                       (double)(float)((double)(float)(local_138 - DOUBLE_80331408) * dVar22),
                       (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
            dVar26 = (double)(float)(dVar26 + (double)FLOAT_80331468);
          }
          iVar20 = iVar20 + 1;
          iVar7 = iVar7 + 4;
        } while (iVar20 < 4);
        dVar26 = (double)(float)((double)FLOAT_80331468 + dVar21);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x20);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)FLOAT_80331564,dVar26,(double)FLOAT_80331554,(double)FLOAT_803314d8,
                   (double)FLOAT_803313dc,(double)FLOAT_803313dc,(double)FLOAT_803313e8,
                   (double)FLOAT_803313e8,&MenuPcs,0);
        CnvPlayTime__14CMemoryCardManFUiPiPi
                  (&MemoryCardMan,*(undefined4 *)(iVar14 + 0x14),&local_2e4,&local_2e8);
        iVar7 = local_2e4 / 100 + (local_2e4 >> 0x1f);
        local_2d0[0] = iVar7 - (iVar7 >> 0x1f);
        if (local_2d0[0] == 0) {
          local_2d0[0] = 0xffffffff;
          fVar1 = FLOAT_803313dc;
        }
        else {
          local_130 = (double)(CONCAT44(0x43300000,*(undefined4 *)(&DAT_801dc2a8 + local_2d0[0] * 4)
                                       ) ^ 0x80000000);
          fVar1 = FLOAT_803313dc + (float)(local_130 - DOUBLE_80331408);
        }
        iVar7 = local_2e4 / 100 + (local_2e4 >> 0x1f);
        iVar7 = local_2e4 + (iVar7 - (iVar7 >> 0x1f)) * -100;
        iVar20 = iVar7 / 10 + (iVar7 >> 0x1f);
        local_2d0[1] = iVar20 - (iVar20 >> 0x1f);
        if ((local_2d0[1] == 0) && ((int)local_2d0[0] < 1)) {
          local_2d0[1] = -1;
        }
        else {
          local_130 = (double)(CONCAT44(0x43300000,*(undefined4 *)(&DAT_801dc2a8 + local_2d0[1] * 4)
                                       ) ^ 0x80000000);
          fVar1 = fVar1 + (float)(local_130 - DOUBLE_80331408);
        }
        iVar20 = iVar7 / 10 + (iVar7 >> 0x1f);
        local_138 = (double)CONCAT44(0x43300000,DAT_801dc2d0 ^ 0x80000000);
        puVar19 = local_2d0;
        iVar6 = 0;
        local_140 = 0x43300000;
        local_2d0[2] = iVar7 + (iVar20 - (iVar20 >> 0x1f)) * -10;
        iVar7 = local_2e8 / 10 + (local_2e8 >> 0x1f);
        local_130 = (double)(CONCAT44(0x43300000,*(undefined4 *)(&DAT_801dc2a8 + local_2d0[2] * 4))
                            ^ 0x80000000);
        local_2d0[3] = iVar7 - (iVar7 >> 0x1f);
        local_2c0 = local_2e8 + (iVar7 - (iVar7 >> 0x1f)) * -10;
        uStack_13c = *(uint *)(&DAT_801dc2a8 + local_2d0[3] * 4) ^ 0x80000000;
        local_148 = (double)(CONCAT44(0x43300000,*(undefined4 *)(&DAT_801dc2a8 + local_2c0 * 4)) ^
                            0x80000000);
        dVar32 = (double)(FLOAT_80331518 -
                         (fVar1 + (float)(local_130 - DOUBLE_80331408) +
                          (float)(local_138 - DOUBLE_80331408) +
                          (float)((double)CONCAT44(0x43300000,
                                                   *(uint *)(&DAT_801dc2a8 + local_2d0[3] * 4) ^
                                                   0x80000000) - DOUBLE_80331408) +
                         (float)(local_148 - DOUBLE_80331408)));
        do {
          if (-1 < (int)*puVar19) {
            if (iVar6 == 3) {
              local_130 = (double)CONCAT44(0x43300000,DAT_801dc2d0 ^ 0x80000000);
              dVar29 = (double)(float)(local_130 - DOUBLE_80331408);
              DrawRect__8CMenuPcsFUlfffffffff
                        (dVar32,dVar26,dVar29,(double)FLOAT_803314d8,(double)FLOAT_80331568,
                         (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,
                         &MenuPcs,0);
              dVar32 = (double)(float)(dVar32 + dVar29);
            }
            local_138 = (double)CONCAT44(0x43300000,*puVar19 ^ 0x80000000);
            local_130 = (double)(CONCAT44(0x43300000,*(undefined4 *)(&DAT_801dc2a8 + *puVar19 * 4))
                                ^ 0x80000000);
            dVar29 = (double)(float)(local_130 - DOUBLE_80331408);
            DrawRect__8CMenuPcsFUlfffffffff
                      (dVar32,dVar26,dVar29,(double)FLOAT_803314d8,
                       (double)(float)(DOUBLE_80331490 * (local_138 - DOUBLE_80331408) +
                                      DOUBLE_80331570),(double)FLOAT_803313dc,(double)FLOAT_803313e8
                       ,(double)FLOAT_803313e8,&MenuPcs,0);
            dVar32 = (double)(float)(dVar32 + dVar29);
          }
          iVar6 = iVar6 + 1;
          puVar19 = puVar19 + 1;
        } while (iVar6 < 5);
        iVar14 = *(int *)(iVar14 + 0x10) * 4;
        iVar7 = GetMaterialID__7CMapMngFUc(&MapMng,(&DAT_801dc2d4)[iVar14]);
        texture = *(CTexture **)(iVar7 + 0x3c);
        SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,texture);
        local_130 = (double)CONCAT44(0x43300000,texture->field94_0x64);
        local_138 = (double)CONCAT44(0x43300000,texture->field95_0x68);
        PSMTXScale(FLOAT_803313e8 / (float)(local_130 - DOUBLE_803313f0),
                   FLOAT_803313e8 / (float)(local_138 - DOUBLE_803313f0),FLOAT_803313e8,&MStack_2bc)
        ;
        GXLoadTexMtxImm(&MStack_2bc,0x1e,1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
        SetTextureTev__11CTextureManFP8CTexture(&TextureMan,texture);
        local_140 = 0x43300000;
        uStack_13c = (int)(char)(&DAT_801dc2d5)[iVar14] << 7 ^ 0x80000000;
        local_148 = (double)(CONCAT44(0x43300000,(int)(char)(&DAT_801dc2d6)[iVar14] << 7) ^
                            0x80000000);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)dVar27,(double)(float)(DOUBLE_80331510 + dVar21),
                   (double)FLOAT_80331578,(double)FLOAT_80331578,
                   (double)(float)((double)CONCAT44(0x43300000,uStack_13c) - DOUBLE_80331408),
                   (double)(float)(local_148 - DOUBLE_80331408),(double)FLOAT_80331434,
                   (double)FLOAT_80331434,&MenuPcs,0);
      }
      uVar17 = uVar17 + 1;
      iVar16 = iVar16 + 0x48;
    } while ((int)uVar17 < 4);
    uVar17 = 0;
    iVar16 = 0;
    dVar24 = DOUBLE_80331490;
    dVar31 = DOUBLE_80331408;
    dVar25 = DOUBLE_80331498;
    do {
      puVar9 = menuPcs->m_unk0x838;
      local_130 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
      dVar27 = (double)(float)(dVar25 * (local_130 - dVar31) + dVar24);
      if ((*(char *)((int)puVar9 + iVar16 + 0x42) == '\0') &&
         (0 < *(int *)((int)puVar9 + iVar16 + 8))) {
        SetMargin__5CFontFf(FLOAT_803313e8,font);
        SetShadow__5CFontFi(font,0);
        SetScale__5CFontFf(FLOAT_80331588,font);
        DrawInit__5CFontFv(font);
        puVar10 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_300,0xff,0xff,0xff,0xff);
        local_2fc = *puVar10;
        SetColor__5CFontF8_GXColor(font,&local_2fc);
        SetTlut__5CFontFi(font,0x2c);
        SetPosX__5CFontFf(FLOAT_80331520,font);
        SetPosY__5CFontFf((float)(dVar27 - DOUBLE_80331510),font);
        strcpy(local_20c,(int)puVar9 + iVar16 + 0x2c);
        if (local_20c[0] != '\0') {
          local_20c[0] = _toupperLatin1();
        }
        Draw__5CFontFPc(font,local_20c);
        SetMargin__5CFontFf(FLOAT_803313e8,font);
        SetShadow__5CFontFi(font,1);
        SetScale__5CFontFf(FLOAT_8033158c,font);
        DrawInit__5CFontFv(font);
        puVar10 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_308,0xff,0xff,0xff,0xff);
        local_304 = *puVar10;
        SetColor__5CFontF8_GXColor(font,&local_304);
        SetTlut__5CFontFi(font,7);
        iVar14 = *(int *)((int)puVar9 + iVar16 + 0x10);
        if (iVar14 == 0xf) {
          strcpy(local_20c,(int)puVar9 + iVar16 + 0x2c);
        }
        else if (iVar14 == 0x16) {
          if (Game.game.m_gameWork.m_languageId == 2) {
            strcpy(local_20c,(int)puVar9 + iVar16 + 0x2c);
            strcat(local_20c,PTR_s__Hafen_80210d14);
          }
          else {
            strcpy(local_20c,(&PTR_s_cc_logo03_80210d0c)[Game.game.m_gameWork.m_languageId]);
            strcat(local_20c,(char *)((int)puVar9 + iVar16 + 0x2c));
          }
        }
        else {
          strcpy(local_20c,Game.game.m_cFlatDataArr[1].m_table[3].index[iVar14]);
        }
        if (local_20c[0] != '\0') {
          local_20c[0] = _toupperLatin1();
        }
        dVar21 = (double)GetWidth__5CFontFPc(font,local_20c);
        dVar27 = (double)(float)((double)FLOAT_80331558 + dVar27);
        if ((double)FLOAT_8033155c < dVar21) {
          dVar27 = (double)(float)(dVar27 + (double)FLOAT_80331550);
          strcpy(auStack_24c,local_20c);
          pcVar12 = local_20c;
          local_28c[0] = 0;
          while (iVar14 = strchr(pcVar12,0x20), iVar14 != 0) {
            memcpy(auStack_1cc,local_20c,iVar14 - (int)local_20c);
            auStack_1cc[iVar14 - (int)local_20c] = 0;
            dVar21 = (double)GetWidth__5CFontFPc(font,auStack_1cc);
            local_130 = (double)(longlong)(int)dVar21;
            if (0x90 < (int)dVar21) break;
            strcpy(auStack_24c,auStack_1cc);
            strcpy(local_28c,iVar14 + 1);
            pcVar12 = (char *)(iVar14 + 1);
          }
          dVar21 = (double)GetWidth__5CFontFPc(font,auStack_24c);
          SetPosX__5CFontFf((float)((double)FLOAT_80331518 - dVar21),font);
          SetPosY__5CFontFf((float)(dVar27 - (double)FLOAT_80331590),font);
          Draw__5CFontFPc(font,auStack_24c);
          dVar21 = (double)GetWidth__5CFontFPc(font,local_28c);
          SetPosX__5CFontFf((float)((double)FLOAT_80331518 - dVar21),font);
          SetPosY__5CFontFf((float)dVar27,font);
          Draw__5CFontFPc(font,local_28c);
        }
        else {
          SetPosX__5CFontFf((float)((double)FLOAT_80331518 - dVar21),font);
          SetPosY__5CFontFf((float)dVar27,font);
          Draw__5CFontFPc(font,local_20c);
        }
      }
      else {
        SetMargin__5CFontFf(FLOAT_803313e8,font);
        SetShadow__5CFontFi(font,1);
        SetScale__5CFontFf(FLOAT_803313e8,font);
        DrawInit__5CFontFv(font);
        puVar10 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2f8,0xff,0xff,0xff,0xff);
        local_2f4 = *puVar10;
        SetColor__5CFontF8_GXColor(font,&local_2f4);
        SetTlut__5CFontFi(font,0x19);
        uVar5 = countLeadingZeros((int)*(char *)((int)puVar9 + iVar16 + 0x42));
        uVar11 = GetMcStr__8CMenuPcsFi(menuPcs,uVar5 >> 5);
        dVar21 = (double)GetWidth__5CFontFPc(font,uVar11);
        local_130 = (double)(longlong)(int)dVar21;
        local_138 = (double)(CONCAT44(0x43300000,0x238 - (int)dVar21) ^ 0x80000000);
        SetPosX__5CFontFf((float)((double)(float)(local_138 - DOUBLE_80331408) * DOUBLE_803313f8 +
                                 (double)FLOAT_803314d8),font);
        SetPosY__5CFontFf((float)(DOUBLE_80331580 + dVar27),font);
        uVar11 = GetMcStr__8CMenuPcsFi(menuPcs,uVar5 >> 5);
        Draw__5CFontFPc(font,uVar11);
      }
      uVar17 = uVar17 + 1;
      iVar16 = iVar16 + 0x48;
    } while ((int)uVar17 < 4);
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x16) == 0x11) {
      sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1c);
      if (sVar2 == 5) {
        puVar10 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_310,0xff,0xff,0xff,0xff);
        local_30c = *puVar10;
        uVar11 = GetMcStr__8CMenuPcsFi(menuPcs,2);
        uVar13 = GetMcStr__8CMenuPcsFi(menuPcs,2);
        dVar24 = (double)CalcCenteringPos2__8CMenuPcsFPcff
                                   ((double)FLOAT_80331594,(double)FLOAT_803313e8,menuPcs,uVar13);
        local_130 = (double)(longlong)(int)dVar24;
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  ((double)FLOAT_80331594,(double)FLOAT_803313e8,(double)FLOAT_803313e8,menuPcs,
                   (int)dVar24,0x187,&local_30c,7,uVar11);
      }
      else if (sVar2 == 2) {
        puVar10 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_318,0xff,0xff,0xff,0xff);
        local_314 = *puVar10;
        uVar11 = GetMcStr__8CMenuPcsFi(menuPcs,3);
        uVar13 = GetMcStr__8CMenuPcsFi(menuPcs,3);
        dVar24 = (double)CalcCenteringPos2__8CMenuPcsFPcff
                                   ((double)FLOAT_80331594,(double)FLOAT_803313e8,menuPcs,uVar13);
        local_130 = (double)(longlong)(int)dVar24;
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  ((double)FLOAT_80331594,(double)FLOAT_803313e8,(double)FLOAT_803313e8,menuPcs,
                   (int)dVar24,0x187,&local_314,7,uVar11);
      }
      DrawInit__8CMenuPcsFv(menuPcs);
    }
  }
  return;
}

