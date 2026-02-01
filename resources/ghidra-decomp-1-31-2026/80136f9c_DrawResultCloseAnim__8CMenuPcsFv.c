// Function: DrawResultCloseAnim__8CMenuPcsFv
// Entry: 80136f9c
// Size: 2452 bytes

/* WARNING: Removing unreachable block (ram,0x80137914) */
/* WARNING: Removing unreachable block (ram,0x8013790c) */
/* WARNING: Removing unreachable block (ram,0x80137904) */
/* WARNING: Removing unreachable block (ram,0x801378fc) */
/* WARNING: Removing unreachable block (ram,0x80136fc4) */
/* WARNING: Removing unreachable block (ram,0x80136fbc) */
/* WARNING: Removing unreachable block (ram,0x80136fb4) */
/* WARNING: Removing unreachable block (ram,0x80136fac) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawResultCloseAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int *piVar8;
  CFont *font;
  int iVar9;
  short *psVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  undefined auStack_140 [4];
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  int local_130 [3];
  undefined4 local_124;
  undefined local_120;
  undefined local_11f;
  undefined local_11e;
  undefined local_11d;
  undefined local_11c;
  undefined local_11b;
  undefined local_11a;
  undefined local_119;
  undefined local_118;
  undefined local_117;
  undefined local_116;
  undefined local_115;
  undefined auStack_114 [132];
  undefined8 local_90;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  undefined8 local_78;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) != '\0') {
    iVar12 = *DAT_8032eea8;
    DrawInit__8CMenuPcsFv(menuPcs);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    iVar13 = 0;
    iVar6 = 0;
    iVar9 = 0;
    iVar11 = 0;
    for (iVar14 = 0; iVar14 < **(short **)&menuPcs->field_0x84c; iVar14 = iVar14 + 1) {
      psVar10 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar9 + 8);
      iVar2 = *(int *)(psVar10 + 0xe);
      if ((-1 < iVar2) || (iVar2 == -2)) {
        if (iVar2 == -2) {
          if (iVar13 < iVar12) {
            iVar2 = *(int *)((int)DAT_8032eea8 + iVar11 + 0x20);
          }
          else {
            if (1 < iVar13 / iVar12) {
              iVar13 = iVar13 + 1;
              iVar11 = iVar11 + 0x2c;
              goto LAB_801376c0;
            }
            iVar2 = *(int *)((int)menuPcs + (iVar13 - iVar12) * 4 + 0x774);
          }
          if (DOUBLE_80331e90 < (double)*(float *)(*(int *)(iVar2 + 0x168) + 0x9c)) {
            SetProjection__8CMenuPcsFi(menuPcs,iVar13);
            SetLight__8CMenuPcsFi(menuPcs,1);
            uVar7 = *(undefined4 *)(iVar2 + 8);
            *(undefined4 *)(iVar2 + 8) = 0x300543;
            Draw__Q29CCharaPcs7CHandleFi(iVar2,5);
            *(undefined4 *)(iVar2 + 8) = uVar7;
            RestoreProjection__8CMenuPcsFv(menuPcs);
            iVar6 = *(int *)(psVar10 + 0xe);
            iVar13 = iVar13 + 1;
            iVar11 = iVar11 + 0x2c;
          }
          else {
            iVar13 = iVar13 + 1;
            iVar11 = iVar11 + 0x2c;
          }
        }
        else {
          if (iVar6 < 0) {
            DrawInit__8CMenuPcsFv(menuPcs);
          }
          if ((iVar6 == 0x17) || (*(int *)(psVar10 + 0xe) != 0x17)) {
            if ((iVar6 == 0x17) && (*(int *)(psVar10 + 0xe) != 0x17)) {
              SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
            }
          }
          else {
            SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
          }
          if (*(int *)(psVar10 + 0xe) == 0x17) {
            local_124 = 0xffffffff;
            local_120 = 0xff;
            local_11f = 0xff;
            local_11e = 0xff;
            local_11d = 0xff;
            local_11c = 0xff;
            local_11b = 0xff;
            local_11a = 0xff;
            local_119 = 0xff;
            local_118 = 0xff;
            local_117 = 0xff;
            local_116 = 0xff;
            local_115 = 0xff;
            local_134 = 0xffffffff;
            GXSetChanMatColor(4,&local_134);
          }
          if (*(int *)(psVar10 + 0xe) != 0x17) {
            local_90 = (double)(longlong)(int)(FLOAT_80331e98 * *(float *)(psVar10 + 8));
            local_124 = CONCAT31(0xffffff,(char)(int)(FLOAT_80331e98 * *(float *)(psVar10 + 8)));
            local_138 = local_124;
            GXSetChanMatColor(4,&local_138);
          }
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar10 + 0xe));
          if (*(int *)(psVar10 + 0xe) == 0x17) {
            uVar4 = *(uint *)(psVar10 + 0x14);
            iVar6 = *(int *)(psVar10 + 0x10);
            if ((int)uVar4 <= iVar6) {
              iVar6 = 0x17;
              goto LAB_801376c0;
            }
            local_90 = (double)(CONCAT44(0x43300000,(int)*psVar10) ^ 0x80000000);
            dVar18 = (double)(float)(local_90 - DOUBLE_80331e88);
            dVar17 = (double)(float)((double)CONCAT44(0x43300000,(int)psVar10[1] ^ 0x80000000) -
                                    DOUBLE_80331e88);
            fVar1 = FLOAT_80331eac;
            if ((int)uVar4 > iVar6) {
              local_90 = (double)CONCAT44(0x43300000,iVar6 - 1U ^ 0x80000000);
              fVar1 = (float)-((DOUBLE_80331ed8 /
                               ((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DOUBLE_80331e88))
                               * (local_90 - DOUBLE_80331e88) - DOUBLE_80331ed8);
              if (fVar1 < FLOAT_80331eac) {
                fVar1 = FLOAT_80331eac;
              }
            }
            dVar15 = (double)*(float *)(psVar10 + 4);
            dVar16 = (double)(fVar1 * (float)((double)CONCAT44(0x43300000,
                                                               (int)psVar10[2] ^ 0x80000000) -
                                             DOUBLE_80331e88));
            if ((double)FLOAT_80331eac < dVar16) {
              local_88 = 0x43300000;
              uStack_84 = (int)psVar10[3] ^ 0x80000000;
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (dVar18,dVar17,dVar16,
                         (double)(float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331e88),
                         dVar15,(double)*(float *)(psVar10 + 6),(double)FLOAT_80331eb0,
                         (double)FLOAT_80331eb0,&MenuPcs,0,&local_124);
              dVar15 = dVar16;
              dVar18 = (double)(float)(dVar18 + dVar15);
              dVar16 = dVar15;
            }
            local_88 = 0x43300000;
            uVar4 = (int)psVar10[2] ^ 0x80000000;
            uStack_84 = uVar4;
            if (dVar16 < (double)(float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80331e88)) {
              local_120 = 0xff;
              local_11f = 0xff;
              local_11e = 0xff;
              local_11d = 0;
              local_118 = 0xff;
              local_117 = 0xff;
              local_116 = 0xff;
              local_115 = 0;
              local_88 = 0x43300000;
              uStack_84 = *(uint *)(psVar10 + 0x14) ^ 0x80000000;
              uStack_7c = (int)psVar10[3] ^ 0x80000000;
              local_90 = (double)CONCAT44(0x43300000,uVar4);
              local_80 = 0x43300000;
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (dVar18,dVar17,
                         (double)((float)(DOUBLE_80331ed8 /
                                         ((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331e88))
                                 * (float)(local_90 - DOUBLE_80331e88)),
                         (double)(float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331e88),
                         dVar15,(double)*(float *)(psVar10 + 6),(double)FLOAT_80331eb0,
                         (double)FLOAT_80331eb0,&MenuPcs,0,&local_124);
            }
          }
          else {
            iVar6 = (int)DAT_8032eeac;
            if ((iVar14 < iVar6) || (iVar6 + iVar12 <= iVar14)) {
              uStack_7c = (int)psVar10[1] ^ 0x80000000;
              local_78 = (double)(CONCAT44(0x43300000,(int)*psVar10) ^ 0x80000000);
              uStack_84 = (int)psVar10[2] ^ 0x80000000;
              local_80 = 0x43300000;
              local_88 = 0x43300000;
              local_90 = (double)CONCAT44(0x43300000,(int)psVar10[3] ^ 0x80000000);
              DrawRect__8CMenuPcsFUlfffffffff
                        ((double)((float)(local_78 - DOUBLE_80331e88) + *(float *)(psVar10 + 0x18)),
                         (double)((float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331e88)
                                 + *(float *)(psVar10 + 0x1a)),
                         (double)(float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331e88),
                         (double)(float)(local_90 - DOUBLE_80331e88),(double)*(float *)(psVar10 + 4)
                         ,(double)*(float *)(psVar10 + 6),(double)*(float *)(psVar10 + 10),
                         (double)*(float *)(psVar10 + 10),&MenuPcs,0);
            }
            else {
              iVar6 = DAT_8032eea8[(iVar14 - iVar6) * 0xb + 10];
              if (iVar6 < 100) {
                if (iVar6 < 10) {
                  iVar2 = 1;
                  local_130[0] = iVar6;
                }
                else {
                  iVar2 = 2;
                  iVar5 = iVar6 / 10 + (iVar6 >> 0x1f);
                  local_130[0] = iVar5 - (iVar5 >> 0x1f);
                  local_130[1] = iVar6 + (iVar5 - (iVar5 >> 0x1f)) * -10;
                }
              }
              else {
                iVar2 = 3;
                iVar5 = iVar6 / 100 + (iVar6 >> 0x1f);
                local_130[0] = iVar5 - (iVar5 >> 0x1f);
                iVar6 = iVar6 + (iVar5 - (iVar5 >> 0x1f)) * -100;
                iVar5 = iVar6 / 10 + (iVar6 >> 0x1f);
                local_130[1] = iVar5 - (iVar5 >> 0x1f);
                local_130[2] = iVar6 + (iVar5 - (iVar5 >> 0x1f)) * -10;
              }
              uStack_84 = (int)psVar10[2] ^ 0x80000000;
              local_80 = 0x43300000;
              piVar8 = local_130;
              uStack_7c = iVar2 * psVar10[2] ^ 0x80000000;
              local_88 = 0x43300000;
              local_90 = (double)CONCAT44(0x43300000,(int)*psVar10 ^ 0x80000000);
              local_78 = (double)CONCAT44(0x43300000,uStack_84);
              dVar17 = (DOUBLE_80331ec8 * ((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331e88)
                       - (double)(float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331e88))
                       * DOUBLE_80331e78 + (local_90 - DOUBLE_80331e88);
              dVar16 = (double)(float)(local_78 - DOUBLE_80331e88);
              dVar18 = DOUBLE_80331e88;
              for (iVar6 = 0; dVar17 = (double)(float)dVar17, iVar6 < iVar2; iVar6 = iVar6 + 1) {
                uStack_7c = (int)psVar10[3] ^ 0x80000000;
                local_78 = (double)(CONCAT44(0x43300000,(int)psVar10[1]) ^ 0x80000000);
                uStack_84 = (int)psVar10[2] * *piVar8 ^ 0x80000000;
                local_80 = 0x43300000;
                local_88 = 0x43300000;
                DrawRect__8CMenuPcsFUlfffffffff
                          (dVar17,(double)(float)(local_78 - dVar18),dVar16,
                           (double)(float)((double)CONCAT44(0x43300000,uStack_7c) - dVar18),
                           (double)(float)((double)CONCAT44(0x43300000,uStack_84) - dVar18),
                           (double)*(float *)(psVar10 + 6),(double)*(float *)(psVar10 + 10),
                           (double)*(float *)(psVar10 + 10),&MenuPcs,0);
                dVar17 = dVar17 + dVar16;
                piVar8 = piVar8 + 1;
              }
            }
          }
          iVar6 = *(int *)(psVar10 + 0xe);
        }
      }
LAB_801376c0:
      iVar9 = iVar9 + 0x40;
    }
    DrawInit__8CMenuPcsFv(menuPcs);
    font = *(CFont **)&menuPcs->field_0xf8;
    SetMargin__5CFontFf(FLOAT_80331eb0,font);
    SetShadow__5CFontFi(font,1);
    SetScale__5CFontFf(FLOAT_80331f38,font);
    SetTlut__5CFontFi(font,7);
    DrawInit__5CFontFv(font);
    iVar6 = 0;
    iVar9 = 0;
    for (iVar11 = 0; iVar11 < **(short **)&menuPcs->field_0x84c; iVar11 = iVar11 + 1) {
      psVar10 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar9 + 8);
      if (*(int *)(psVar10 + 0xe) == -1) {
        local_78 = (double)(longlong)(int)(FLOAT_80331e98 * *(float *)(psVar10 + 8));
        puVar3 = (undefined4 *)
                 __ct__6CColorFUcUcUcUc
                           (auStack_140,0xff,0xff,0xff,
                            (int)(FLOAT_80331e98 * *(float *)(psVar10 + 8)));
        local_13c = *puVar3;
        SetColor__5CFontF8_GXColor(font,&local_13c);
        if (iVar6 < iVar12) {
          strcpy(auStack_114,
                 Game.game.m_scriptFoodBase
                 [DAT_8032eea8[(iVar6 - (iVar6 / iVar12) * iVar12) * 0xb + 7]] + 0x3ca);
        }
        else {
          strcpy(auStack_114,
                 Game.game.m_cFlatDataArr[1].m_table[7].index
                 [(uint)*(byte *)(Game.game.m_scriptFoodBase
                                  [DAT_8032eea8[(iVar6 - (iVar6 / iVar12) * iVar12) * 0xb + 7]] +
                                 0xba4) * 2 + 1]);
        }
        uStack_7c = (int)psVar10[1] ^ 0x80000000;
        local_78 = (double)(CONCAT44(0x43300000,(int)*psVar10) ^ 0x80000000);
        local_80 = 0x43300000;
        dVar17 = (double)((float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331e88) +
                         *(float *)(psVar10 + 0x1a));
        if (iVar6 < iVar12) {
          dVar17 = (double)(float)(dVar17 - (double)FLOAT_80331f3c);
        }
        SetPosX__5CFontFf((float)(local_78 - DOUBLE_80331e88) + *(float *)(psVar10 + 0x18),font);
        SetPosY__5CFontFf((float)(dVar17 - (double)FLOAT_80331f3c),font);
        Draw__5CFontFPc(font,auStack_114);
        iVar6 = iVar6 + 1;
        if (iVar6 == iVar12) {
          font = *(CFont **)&menuPcs->field_0xfc;
          SetMargin__5CFontFf(FLOAT_80331eb0,font);
          SetShadow__5CFontFi(font,0);
          SetScaleX__5CFontFf(FLOAT_80331f90,font);
          SetScaleY__5CFontFf(FLOAT_80331eb0,font);
          DrawInit__5CFontFv(font);
        }
      }
      iVar9 = iVar9 + 0x40;
    }
    DrawInit__8CMenuPcsFv(menuPcs);
  }
  return;
}

