// Function: DrawResultCountAnim__8CMenuPcsFv
// Entry: 80139b14
// Size: 1816 bytes

/* WARNING: Removing unreachable block (ram,0x8013a210) */
/* WARNING: Removing unreachable block (ram,0x8013a208) */
/* WARNING: Removing unreachable block (ram,0x8013a200) */
/* WARNING: Removing unreachable block (ram,0x8013a1f8) */
/* WARNING: Removing unreachable block (ram,0x80139b3c) */
/* WARNING: Removing unreachable block (ram,0x80139b34) */
/* WARNING: Removing unreachable block (ram,0x80139b2c) */
/* WARNING: Removing unreachable block (ram,0x80139b24) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawResultCountAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  CFont *font;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 uVar10;
  short *psVar11;
  int iVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  undefined auStack_140 [4];
  undefined4 local_13c;
  undefined4 local_138;
  int local_134 [3];
  undefined4 local_128;
  undefined uStack_125;
  undefined auStack_118 [128];
  undefined8 local_98;
  undefined4 local_90;
  uint uStack_8c;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) != '\0') {
    iVar12 = *DAT_8032eea8;
    DrawInit__8CMenuPcsFv(menuPcs);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    iVar5 = 0;
    iVar7 = 0;
    iVar3 = 0;
    iVar8 = 0;
    for (iVar6 = 0; iVar6 < **(short **)&menuPcs->field_0x84c; iVar6 = iVar6 + 1) {
      psVar11 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar7 + 8);
      iVar1 = *(int *)(psVar11 + 0xe);
      if ((-1 < iVar1) || (iVar1 == -2)) {
        if (iVar1 == -2) {
          if (iVar5 < iVar12) {
            iVar3 = *(int *)((int)DAT_8032eea8 + iVar8 + 0x20);
          }
          else {
            if (iVar12 << 1 <= iVar5) goto LAB_80139fd8;
            iVar3 = *(int *)((int)menuPcs + (iVar5 - iVar12) * 4 + 0x774);
          }
          SetProjection__8CMenuPcsFi(menuPcs,iVar5);
          SetLight__8CMenuPcsFi(menuPcs,1);
          uVar10 = *(undefined4 *)(iVar3 + 8);
          *(undefined4 *)(iVar3 + 8) = 0x300543;
          Draw__Q29CCharaPcs7CHandleFi(iVar3,5);
          *(undefined4 *)(iVar3 + 8) = uVar10;
          RestoreProjection__8CMenuPcsFv(menuPcs);
          iVar3 = *(int *)(psVar11 + 0xe);
          iVar8 = iVar8 + 0x2c;
          iVar5 = iVar5 + 1;
        }
        else {
          if (iVar3 < 0) {
            DrawInit__8CMenuPcsFv(menuPcs);
            SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
          }
          local_98 = (double)(longlong)(int)(FLOAT_80331e98 * *(float *)(psVar11 + 8));
          local_128 = CONCAT31(0xffffff,(char)(int)(FLOAT_80331e98 * *(float *)(psVar11 + 8)));
          local_138 = local_128;
          GXSetChanMatColor(4,&local_138);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar11 + 0xe));
          iVar3 = (int)DAT_8032eeac;
          if ((iVar6 < iVar3) || (iVar3 + iVar12 <= iVar6)) {
            local_80 = 0x43300000;
            uStack_7c = (int)*psVar11 ^ 0x80000000;
            uStack_84 = (int)psVar11[1] ^ 0x80000000;
            uStack_8c = (int)psVar11[2] ^ 0x80000000;
            local_88 = 0x43300000;
            local_90 = 0x43300000;
            local_98 = (double)CONCAT44(0x43300000,(int)psVar11[3] ^ 0x80000000);
            DrawRect__8CMenuPcsFUlfffffffff
                      ((double)((float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331e88) +
                               *(float *)(psVar11 + 0x18)),
                       (double)((float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331e88) +
                               *(float *)(psVar11 + 0x1a)),
                       (double)(float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88),
                       (double)(float)(local_98 - DOUBLE_80331e88),(double)*(float *)(psVar11 + 4),
                       (double)*(float *)(psVar11 + 6),(double)*(float *)(psVar11 + 10),
                       (double)*(float *)(psVar11 + 10),&MenuPcs,0);
          }
          else {
            iVar3 = DAT_8032eea8[(iVar6 - iVar3) * 0xb + 10];
            if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 0) {
              local_98 = (double)(CONCAT44(0x43300000,
                                           (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22)) ^
                                 0x80000000);
              dVar14 = (local_98 - DOUBLE_80331e88) - DOUBLE_80331f98;
              if (DOUBLE_80331e90 < dVar14) {
                local_98 = (double)(CONCAT44(0x43300000,iVar3) ^ 0x80000000);
                if (dVar14 < local_98 - DOUBLE_80331e88) {
                  iVar3 = (int)dVar14;
                }
              }
              else {
                iVar3 = 0;
              }
            }
            if (iVar3 < 100) {
              if (iVar3 < 10) {
                iVar1 = 1;
                local_134[0] = iVar3;
              }
              else {
                iVar1 = 2;
                iVar4 = iVar3 / 10 + (iVar3 >> 0x1f);
                local_134[0] = iVar4 - (iVar4 >> 0x1f);
                local_134[1] = iVar3 + (iVar4 - (iVar4 >> 0x1f)) * -10;
              }
            }
            else {
              iVar1 = 3;
              iVar4 = iVar3 / 100 + (iVar3 >> 0x1f);
              local_134[0] = iVar4 - (iVar4 >> 0x1f);
              iVar3 = iVar3 + (iVar4 - (iVar4 >> 0x1f)) * -100;
              iVar4 = iVar3 / 10 + (iVar3 >> 0x1f);
              local_134[1] = iVar4 - (iVar4 >> 0x1f);
              local_134[2] = iVar3 + (iVar4 - (iVar4 >> 0x1f)) * -10;
            }
            uStack_8c = (int)psVar11[2] ^ 0x80000000;
            piVar9 = local_134;
            local_98 = (double)(CONCAT44(0x43300000,iVar1 * psVar11[2]) ^ 0x80000000);
            local_90 = 0x43300000;
            uStack_84 = (int)*psVar11 ^ 0x80000000U;
            local_88 = 0x43300000;
            uStack_7c = uStack_8c;
            local_80 = 0x43300000;
            dVar14 = (DOUBLE_80331ec8 * ((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88) -
                     (double)(float)(local_98 - DOUBLE_80331e88)) * DOUBLE_80331e78 +
                     ((double)CONCAT44(0x43300000,(int)*psVar11 ^ 0x80000000U) - DOUBLE_80331e88);
            dVar13 = (double)(float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88);
            dVar15 = DOUBLE_80331e88;
            for (iVar3 = 0; dVar14 = (double)(float)dVar14, iVar3 < iVar1; iVar3 = iVar3 + 1) {
              uStack_7c = (int)psVar11[1] ^ 0x80000000;
              local_80 = 0x43300000;
              uStack_84 = (int)psVar11[3] ^ 0x80000000;
              uStack_8c = (int)psVar11[2] * *piVar9 ^ 0x80000000;
              local_88 = 0x43300000;
              local_90 = 0x43300000;
              DrawRect__8CMenuPcsFUlfffffffff
                        (dVar14,(double)(float)((double)CONCAT44(0x43300000,uStack_7c) - dVar15),
                         dVar13,(double)(float)((double)CONCAT44(0x43300000,uStack_84) - dVar15),
                         (double)(float)((double)CONCAT44(0x43300000,uStack_8c) - dVar15),
                         (double)*(float *)(psVar11 + 6),(double)*(float *)(psVar11 + 10),
                         (double)*(float *)(psVar11 + 10),&MenuPcs,0);
              dVar14 = dVar14 + dVar13;
              piVar9 = piVar9 + 1;
            }
          }
          iVar3 = *(int *)(psVar11 + 0xe);
        }
      }
LAB_80139fd8:
      iVar7 = iVar7 + 0x40;
    }
    DrawInit__8CMenuPcsFv(menuPcs);
    font = *(CFont **)&menuPcs->field_0xf8;
    SetMargin__5CFontFf(FLOAT_80331eb0,font);
    SetShadow__5CFontFi(font,1);
    SetScale__5CFontFf(FLOAT_80331f38,font);
    SetTlut__5CFontFi(font,7);
    DrawInit__5CFontFv(font);
    iVar3 = 0;
    iVar7 = 0;
    for (iVar5 = 0; iVar5 < **(short **)&menuPcs->field_0x84c; iVar5 = iVar5 + 1) {
      psVar11 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar7 + 8);
      if (*(int *)(psVar11 + 0xe) == -1) {
        puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_140,0xff,0xff,0xff,0xff);
        local_13c = *puVar2;
        SetColor__5CFontF8_GXColor(font,&local_13c);
        if (iVar3 < iVar12) {
          strcpy(auStack_118,
                 Game.game.m_scriptFoodBase
                 [DAT_8032eea8[(iVar3 - (iVar3 / iVar12) * iVar12) * 0xb + 7]] + 0x3ca);
        }
        else {
          strcpy(auStack_118,
                 Game.game.m_cFlatDataArr[1].m_table[7].index
                 [(uint)*(byte *)(Game.game.m_scriptFoodBase
                                  [DAT_8032eea8[(iVar3 - (iVar3 / iVar12) * iVar12) * 0xb + 7]] +
                                 0xba4) * 2 + 1]);
        }
        uStack_7c = (int)*psVar11 ^ 0x80000000;
        local_80 = 0x43300000;
        uStack_84 = (int)psVar11[1] ^ 0x80000000;
        local_88 = 0x43300000;
        dVar14 = (double)((float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331e88) +
                         *(float *)(psVar11 + 0x1a));
        if (iVar3 < iVar12) {
          dVar14 = (double)(float)(dVar14 - (double)FLOAT_80331f3c);
        }
        SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331e88) +
                          *(float *)(psVar11 + 0x18),font);
        SetPosY__5CFontFf((float)(dVar14 - (double)FLOAT_80331f3c),font);
        Draw__5CFontFPc(font,auStack_118);
        iVar3 = iVar3 + 1;
        if (iVar3 == iVar12) {
          font = *(CFont **)&menuPcs->field_0xfc;
          SetMargin__5CFontFf(FLOAT_80331eb0,font);
          SetScaleX__5CFontFf(FLOAT_80331f90,font);
          SetScaleY__5CFontFf(FLOAT_80331eb0,font);
          SetShadow__5CFontFi(font,0);
          DrawInit__5CFontFv(font);
        }
      }
      iVar7 = iVar7 + 0x40;
    }
    DrawInit__8CMenuPcsFv(menuPcs);
  }
  return;
}

