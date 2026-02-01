// Function: LetterListDraw__8CMenuPcsFv
// Entry: 80165554
// Size: 1528 bytes

/* WARNING: Removing unreachable block (ram,0x80165b30) */
/* WARNING: Removing unreachable block (ram,0x80165b28) */
/* WARNING: Removing unreachable block (ram,0x80165b20) */
/* WARNING: Removing unreachable block (ram,0x80165574) */
/* WARNING: Removing unreachable block (ram,0x8016556c) */
/* WARNING: Removing unreachable block (ram,0x80165564) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LetterListDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint32_t uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  byte bVar9;
  int iVar10;
  CFont *font;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  undefined4 local_90;
  undefined4 local_8c;
  undefined auStack_88 [4];
  undefined4 local_84;
  undefined auStack_80 [4];
  undefined4 local_7c;
  undefined8 local_78;
  double local_70;
  undefined8 local_68;
  longlong local_60;
  
  iVar8 = *(int *)&menuPcs->field_0x850;
  if ((DAT_8032eeea != '\0') && (menuPcs->field_0x872 == '\0')) {
    DrawSingleCrescent__8CMenuPcsFff
              ((double)FLOAT_803330f8,
               (double)(float)(DOUBLE_803330e8 - (double)*(float *)(iVar8 + 0x18)));
    DrawSingleStat__8CMenuPcsFf
              ((double)(float)(DOUBLE_803330e8 - (double)*(float *)(iVar8 + 0x18)),menuPcs);
    DrawSingleHelpWim__8CMenuPcsFf
              ((double)(float)(DOUBLE_803330e8 - (double)*(float *)(iVar8 + 0x18)),menuPcs);
  }
  if (**(short **)&menuPcs->field_0x850 != 1) {
    LetterLstBaseDraw__8CMenuPcsFf((double)*(float *)(iVar8 + 0x58),menuPcs);
    font = *(CFont **)&menuPcs->field_0xf8;
    SetMargin__5CFontFf(FLOAT_803330f8,font);
    SetShadow__5CFontFi(font,1);
    SetScale__5CFontFf(FLOAT_803330f8,font);
    DrawInit__5CFontFv(font);
    iVar10 = (int)(FLOAT_803330a0 * *(float *)(iVar8 + 0x58));
    local_78 = (double)(longlong)iVar10;
    puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_80,0xff,0xff,0xff,iVar10);
    local_7c = *puVar4;
    SetColor__5CFontF8_GXColor(font,&local_7c);
    uVar5 = GetMenuStr__8CMenuPcsFi(menuPcs,0x1d);
    dVar11 = (double)GetWidth__5CFontFPc(font,uVar5);
    DrawShadowFont__8CMenuPcsFP5CFontPcffii
              ((double)(float)((double)(float)((double)FLOAT_80333158 - dVar11) * DOUBLE_803330a8),
               (double)FLOAT_8033315c,menuPcs,font,uVar5,0x18,0x12);
    if (DOUBLE_803330e8 <= (double)*(float *)(iVar8 + 0x58)) {
      puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_88,0xff,0xff,0xff,0xff);
      local_84 = *puVar4;
      SetColor__5CFontF8_GXColor(font,&local_84);
      uVar2 = Game.game.m_scriptFoodBase[0];
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
      dVar12 = (double)FLOAT_80333148;
      iVar10 = 0x60;
      dVar11 = DOUBLE_803330c8;
      for (iVar8 = 0; (iVar8 < 9 && (iVar6 = sVar1 + iVar8, iVar6 < *(int *)(uVar2 + 1000)));
          iVar8 = iVar8 + 1) {
        iVar6 = iVar6 * 0xc + 0x3ec;
        if ((char)*(byte *)(uVar2 + iVar6) < '\0') {
          if ((*(byte *)(uVar2 + iVar6) >> 5 & 1) == 0) {
            uVar5 = 0;
          }
          else {
            uVar5 = 8;
          }
        }
        else {
          uVar5 = 9;
        }
        SetTlut__5CFontFi(font,uVar5);
        local_78 = (double)(CONCAT44(0x43300000,iVar10) ^ 0x80000000);
        uVar5 = *(undefined4 *)
                 ((int)Game.game.m_cFlatDataArr[1].m_table[5].index +
                 (*(ushort *)(uVar2 + iVar6) & 0x7fc));
        dVar13 = (double)(float)(local_78 - dVar11);
        SetPosX__5CFontFf(FLOAT_80333160,font);
        SetPosY__5CFontFf((float)(dVar13 - dVar12),font);
        Draw__5CFontFPc(font,uVar5);
        uVar5 = *(undefined4 *)
                 ((int)Game.game.m_cFlatDataArr[1].m_table[2].index +
                 (*(uint *)(uVar2 + iVar6) >> 7 & 0x7fc));
        SetPosX__5CFontFf(FLOAT_80333164,font);
        local_70 = (double)(CONCAT44(0x43300000,iVar10) ^ 0x80000000);
        SetPosY__5CFontFf((float)((double)(float)(local_70 - dVar11) - dVar12),font);
        Draw__5CFontFPc(font,uVar5);
        iVar10 = iVar10 + 0x20;
      }
      DrawInit__8CMenuPcsFv(menuPcs);
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
      bVar9 = sVar1 != 0;
      if (sVar1 + 9 < *(int *)(uVar2 + 1000)) {
        bVar9 = bVar9 | 2;
      }
      if (bVar9 != 0) {
        iVar8 = (int)System.m_frameCounter / 0x14 + ((int)System.m_frameCounter >> 0x1f);
        dVar13 = (double)FLOAT_80333088;
        dVar14 = (double)FLOAT_8033308c;
        uVar7 = (System.m_frameCounter + (iVar8 - (iVar8 >> 0x1f)) * -0x14) - 10;
        uVar3 = (int)uVar7 >> 0x1f;
        uVar3 = (uVar3 ^ uVar7) - uVar3;
        local_70 = (double)(CONCAT44(0x43300000,uVar3) ^ 0x80000000);
        dVar15 = (double)(float)(DOUBLE_80333098 * (local_70 - DOUBLE_803330c8) + DOUBLE_80333090);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
        local_78 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
        iVar8 = (int)(FLOAT_803330a0 *
                     (float)(DOUBLE_803330b0 * (local_78 - DOUBLE_803330c8) + DOUBLE_803330a8));
        local_68 = (double)(longlong)iVar8;
        local_90 = CONCAT31(0xffffff,(char)iVar8);
        local_8c = local_90;
        GXSetChanMatColor(4,&local_8c);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x43);
        dVar12 = (double)FLOAT_803330b8;
        dVar11 = -(double)(float)(dVar12 * dVar15 - dVar12) * DOUBLE_803330a8;
        dVar13 = (double)(float)(dVar13 + dVar11);
        dVar11 = (double)(float)(dVar14 + dVar11);
        if ((bVar9 & 1) != 0) {
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar13,dVar11,dVar12,dVar12,(double)FLOAT_803330bc,(double)FLOAT_803330bc,
                     dVar15,dVar15,&MenuPcs,4);
        }
        if ((bVar9 & 2) != 0) {
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar13,(double)(float)(dVar11 + (double)FLOAT_803330c0),(double)FLOAT_803330b8,
                     (double)FLOAT_803330b8,(double)FLOAT_803330bc,(double)FLOAT_803330bc,dVar15,
                     dVar15,&MenuPcs,0);
        }
      }
      uVar3 = 0x5b;
      iVar8 = (int)FLOAT_80333168;
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
      for (iVar10 = 0; (iVar10 < 9 && (iVar6 = sVar1 + iVar10, iVar6 < *(int *)(uVar2 + 1000)));
          iVar10 = iVar10 + 1) {
        iVar6 = uVar2 + iVar6 * 0xc;
        if ((*(ushort *)(iVar6 + 0x3ee) & 0x1ff) != 0) {
          local_68 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
          local_70 = (double)(longlong)(int)(local_68 - DOUBLE_803330c8);
          DrawSingleIcon__8CMenuPcsFiiifif
                    ((double)FLOAT_803330f8,(double)FLOAT_803330f8,menuPcs,
                     0x26 - ((int)-(*(byte *)(iVar6 + 0x3ec) >> 6 & 1) >> 0x1f),iVar8,
                     (int)(local_68 - DOUBLE_803330c8),1);
        }
        uVar3 = uVar3 + 0x20;
      }
      iVar8 = (int)System.m_frameCounter >> 0x1f;
      local_68 = (double)(CONCAT44(0x43300000,
                                   (iVar8 * 8 | System.m_frameCounter * 0x20000000 + iVar8 >> 0x1d)
                                   - iVar8) ^ 0x80000000);
      local_78 = (double)CONCAT44(0x43300000,
                                  *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x20 + 0x60U ^
                                  0x80000000);
      iVar8 = (int)(FLOAT_803330f4 + (float)(local_68 - DOUBLE_803330c8));
      local_70 = (double)(longlong)iVar8;
      local_60 = (longlong)(int)(local_78 - DOUBLE_803330c8);
      DrawCursor__8CMenuPcsFiif
                ((double)FLOAT_803330f8,menuPcs,iVar8,(int)(local_78 - DOUBLE_803330c8));
    }
  }
  return;
}

