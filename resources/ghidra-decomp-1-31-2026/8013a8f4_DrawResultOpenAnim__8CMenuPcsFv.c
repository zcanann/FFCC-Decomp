// Function: DrawResultOpenAnim__8CMenuPcsFv
// Entry: 8013a8f4
// Size: 2136 bytes

/* WARNING: Removing unreachable block (ram,0x8013b130) */
/* WARNING: Removing unreachable block (ram,0x8013b128) */
/* WARNING: Removing unreachable block (ram,0x8013b120) */
/* WARNING: Removing unreachable block (ram,0x8013a914) */
/* WARNING: Removing unreachable block (ram,0x8013a90c) */
/* WARNING: Removing unreachable block (ram,0x8013a904) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawResultOpenAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  CFont *font;
  int iVar6;
  short *psVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  undefined auStack_120 [4];
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined local_10c;
  undefined local_10b;
  undefined local_10a;
  undefined local_109;
  undefined local_108;
  undefined local_107;
  undefined local_106;
  undefined local_105;
  undefined local_104;
  undefined local_103;
  undefined local_102;
  undefined local_101;
  undefined auStack_100 [128];
  undefined8 local_80;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  undefined8 local_68;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) != '\0') {
    iVar11 = *DAT_8032eea8;
    DrawInit__8CMenuPcsFv(menuPcs);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    iVar9 = 0;
    iVar8 = 0;
    iVar10 = 0;
    iVar5 = 0;
    for (iVar6 = 0; iVar6 < **(short **)&menuPcs->field_0x84c; iVar6 = iVar6 + 1) {
      psVar7 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar10 + 8);
      iVar2 = *(int *)(psVar7 + 0xe);
      if ((-1 < iVar2) || (iVar2 == -2)) {
        if (iVar2 == -2) {
          if (iVar9 < iVar11) {
            iVar2 = *(int *)((int)DAT_8032eea8 + iVar5 + 0x20);
          }
          else {
            iVar2 = *(int *)((int)menuPcs + (iVar9 - iVar11) * 4 + 0x774);
          }
          if (DOUBLE_80331e90 < (double)*(float *)(*(int *)(iVar2 + 0x168) + 0x9c)) {
            SetProjection__8CMenuPcsFi(menuPcs,iVar9);
            SetLight__8CMenuPcsFi(menuPcs,1);
            *(undefined4 *)(iVar2 + 8) = 0x300543;
            Draw__Q29CCharaPcs7CHandleFi(iVar2,5);
            RestoreProjection__8CMenuPcsFv(menuPcs);
            iVar8 = *(int *)(psVar7 + 0xe);
            iVar9 = iVar9 + 1;
            iVar5 = iVar5 + 0x2c;
          }
          else {
            iVar9 = iVar9 + 1;
            iVar5 = iVar5 + 0x2c;
          }
        }
        else {
          if (iVar8 < 0) {
            DrawInit__8CMenuPcsFv(menuPcs);
          }
          if ((iVar8 == 0x17) || (*(int *)(psVar7 + 0xe) != 0x17)) {
            if ((iVar8 == 0x17) && (*(int *)(psVar7 + 0xe) != 0x17)) {
              SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
            }
          }
          else {
            SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
          }
          if (*(int *)(psVar7 + 0xe) == 0x17) {
            local_110 = 0xffffffff;
            local_10c = 0xff;
            local_10b = 0xff;
            local_10a = 0xff;
            local_109 = 0xff;
            local_108 = 0xff;
            local_107 = 0xff;
            local_106 = 0xff;
            local_105 = 0xff;
            local_104 = 0xff;
            local_103 = 0xff;
            local_102 = 0xff;
            local_101 = 0xff;
            local_114 = 0xffffffff;
            GXSetChanMatColor(4,&local_114);
          }
          if (*(int *)(psVar7 + 0xe) != 0x17) {
            local_80 = (double)(longlong)(int)(FLOAT_80331e98 * *(float *)(psVar7 + 8));
            local_110 = CONCAT31(0xffffff,(char)(int)(FLOAT_80331e98 * *(float *)(psVar7 + 8)));
            local_118 = local_110;
            GXSetChanMatColor(4,&local_118);
          }
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar7 + 0xe));
          if (*(int *)(psVar7 + 0xe) == 0x17) {
            local_80 = (double)(CONCAT44(0x43300000,(int)*psVar7) ^ 0x80000000);
            dVar15 = (double)(float)(local_80 - DOUBLE_80331e88);
            dVar14 = (double)(float)((double)CONCAT44(0x43300000,(int)psVar7[1] ^ 0x80000000) -
                                    DOUBLE_80331e88);
            fVar1 = FLOAT_80331eb0;
            if (*(int *)(psVar7 + 0x10) < (int)*(uint *)(psVar7 + 0x14)) {
              local_80 = (double)CONCAT44(0x43300000,*(int *)(psVar7 + 0x10) - 1U ^ 0x80000000);
              fVar1 = (float)((DOUBLE_80331ed8 /
                              ((double)CONCAT44(0x43300000,*(uint *)(psVar7 + 0x14) ^ 0x80000000) -
                              DOUBLE_80331e88)) * (local_80 - DOUBLE_80331e88));
              if (fVar1 < FLOAT_80331eac) {
                fVar1 = FLOAT_80331eac;
              }
            }
            local_78 = 0x43300000;
            uStack_74 = (int)psVar7[2] ^ 0x80000000;
            dVar12 = (double)*(float *)(psVar7 + 4);
            dVar13 = (double)(fVar1 * (float)((double)CONCAT44(0x43300000,uStack_74) -
                                             DOUBLE_80331e88));
            if ((double)FLOAT_80331eac < dVar13) {
              local_78 = 0x43300000;
              uStack_74 = (int)psVar7[3] ^ 0x80000000;
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (dVar15,dVar14,dVar13,
                         (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331e88),
                         dVar12,(double)*(float *)(psVar7 + 6),(double)FLOAT_80331eb0,
                         (double)FLOAT_80331eb0,&MenuPcs,0,&local_110);
              dVar12 = dVar13;
              dVar15 = (double)(float)(dVar15 + dVar12);
              dVar13 = dVar12;
            }
            if ((double)FLOAT_80331eac < dVar13) {
              local_78 = 0x43300000;
              uVar4 = (int)psVar7[2] ^ 0x80000000;
              uStack_74 = uVar4;
              if (dVar13 < (double)(float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80331e88)) {
                local_10c = 0xff;
                local_10b = 0xff;
                local_10a = 0xff;
                local_109 = 0;
                local_104 = 0xff;
                local_103 = 0xff;
                local_102 = 0xff;
                local_101 = 0;
                local_78 = 0x43300000;
                uStack_74 = *(uint *)(psVar7 + 0x14) ^ 0x80000000;
                uStack_6c = (int)psVar7[3] ^ 0x80000000;
                local_80 = (double)CONCAT44(0x43300000,uVar4);
                local_70 = 0x43300000;
                DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                          (dVar15,dVar14,
                           (double)((float)(DOUBLE_80331ed8 /
                                           ((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331e88
                                           )) * (float)(local_80 - DOUBLE_80331e88)),
                           (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331e88)
                           ,dVar12,(double)*(float *)(psVar7 + 6),(double)FLOAT_80331eb0,
                           (double)FLOAT_80331eb0,&MenuPcs,0,&local_110);
              }
            }
          }
          else if ((iVar6 < DAT_8032eeac) || (DAT_8032eeac + iVar11 <= iVar6)) {
            uStack_6c = (int)psVar7[1] ^ 0x80000000;
            local_68 = (double)(CONCAT44(0x43300000,(int)*psVar7) ^ 0x80000000);
            uStack_74 = (int)psVar7[2] ^ 0x80000000;
            local_70 = 0x43300000;
            local_78 = 0x43300000;
            local_80 = (double)CONCAT44(0x43300000,(int)psVar7[3] ^ 0x80000000);
            DrawRect__8CMenuPcsFUlfffffffff
                      ((double)((float)(local_68 - DOUBLE_80331e88) + *(float *)(psVar7 + 0x18)),
                       (double)((float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331e88) +
                               *(float *)(psVar7 + 0x1a)),
                       (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331e88),
                       (double)(float)(local_80 - DOUBLE_80331e88),(double)*(float *)(psVar7 + 4),
                       (double)*(float *)(psVar7 + 6),(double)*(float *)(psVar7 + 10),
                       (double)*(float *)(psVar7 + 10),&MenuPcs,0);
          }
          else {
            uVar4 = (int)psVar7[2] ^ 0x80000000;
            uStack_6c = (int)psVar7[3] ^ 0x80000000;
            local_80 = (double)CONCAT44(0x43300000,(int)*psVar7 ^ 0x80000000);
            local_68 = (double)CONCAT44(0x43300000,uVar4);
            dVar14 = local_68 - DOUBLE_80331e88;
            local_70 = 0x43300000;
            local_68 = (double)CONCAT44(0x43300000,(int)psVar7[1] ^ 0x80000000);
            uStack_74 = 0x80000000;
            local_78 = 0x43300000;
            DrawRect__8CMenuPcsFUlfffffffff
                      ((double)(float)((DOUBLE_80331ec8 *
                                        ((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80331e88) -
                                       (double)(float)((double)CONCAT44(0x43300000,uVar4) -
                                                      DOUBLE_80331e88)) * DOUBLE_80331e78 +
                                      (local_80 - DOUBLE_80331e88)),
                       (double)(float)(local_68 - DOUBLE_80331e88),(double)(float)dVar14,
                       (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331e88),
                       (double)(float)(4503601774854144.0 - DOUBLE_80331e88),
                       (double)*(float *)(psVar7 + 6),(double)*(float *)(psVar7 + 10),
                       (double)*(float *)(psVar7 + 10),&MenuPcs,0);
          }
          iVar8 = *(int *)(psVar7 + 0xe);
        }
      }
      iVar10 = iVar10 + 0x40;
    }
    DrawInit__8CMenuPcsFv(menuPcs);
    font = *(CFont **)&menuPcs->field_0xf8;
    SetMargin__5CFontFf(FLOAT_80331eb0,font);
    SetShadow__5CFontFi(font,1);
    SetScale__5CFontFf(FLOAT_80331f38,font);
    SetTlut__5CFontFi(font,7);
    DrawInit__5CFontFv(font);
    iVar6 = 0;
    iVar10 = 0;
    for (iVar5 = 0; iVar5 < **(short **)&menuPcs->field_0x84c; iVar5 = iVar5 + 1) {
      psVar7 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar10 + 8);
      if (*(int *)(psVar7 + 0xe) == -1) {
        local_68 = (double)(longlong)(int)(FLOAT_80331e98 * *(float *)(psVar7 + 8));
        puVar3 = (undefined4 *)
                 __ct__6CColorFUcUcUcUc
                           (auStack_120,0xff,0xff,0xff,
                            (int)(FLOAT_80331e98 * *(float *)(psVar7 + 8)));
        local_11c = *puVar3;
        SetColor__5CFontF8_GXColor(font,&local_11c);
        if (iVar6 < iVar11) {
          strcpy(auStack_100,
                 Game.game.m_scriptFoodBase
                 [DAT_8032eea8[(iVar6 - (iVar6 / iVar11) * iVar11) * 0xb + 7]] + 0x3ca);
        }
        else {
          strcpy(auStack_100,
                 Game.game.m_cFlatDataArr[1].m_table[7].index
                 [(uint)*(byte *)(Game.game.m_scriptFoodBase
                                  [DAT_8032eea8[(iVar6 - (iVar6 / iVar11) * iVar11) * 0xb + 7]] +
                                 0xba4) * 2 + 1]);
        }
        uStack_6c = (int)psVar7[1] ^ 0x80000000;
        local_68 = (double)(CONCAT44(0x43300000,(int)*psVar7) ^ 0x80000000);
        local_70 = 0x43300000;
        dVar14 = (double)((float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331e88) +
                         *(float *)(psVar7 + 0x1a));
        if (iVar6 < iVar11) {
          dVar14 = (double)(float)(dVar14 - (double)FLOAT_80331f3c);
        }
        SetPosX__5CFontFf((float)(local_68 - DOUBLE_80331e88) + *(float *)(psVar7 + 0x18),font);
        SetPosY__5CFontFf((float)(dVar14 - (double)FLOAT_80331f3c),font);
        Draw__5CFontFPc(font,auStack_100);
        iVar6 = iVar6 + 1;
        if (iVar6 == iVar11) {
          font = *(CFont **)&menuPcs->field_0xfc;
          SetMargin__5CFontFf(FLOAT_80331eb0,font);
          SetShadow__5CFontFi(font,0);
          SetScaleX__5CFontFf(FLOAT_80331f90,font);
          SetScaleY__5CFontFf(FLOAT_80331eb0,font);
          DrawInit__5CFontFv(font);
        }
      }
      iVar10 = iVar10 + 0x40;
    }
    DrawInit__8CMenuPcsFv(menuPcs);
  }
  return;
}

