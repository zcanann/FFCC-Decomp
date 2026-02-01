// Function: DrawFukidashi__8CMenuPcsFv
// Entry: 800f4b24
// Size: 2600 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawFukidashi__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  undefined *puVar1;
  undefined4 *puVar2;
  Vec *targetPosition;
  uint uVar3;
  short *psVar4;
  int iVar5;
  undefined4 uVar6;
  CFont *font;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  int *piVar10;
  CFont *font_00;
  int iVar11;
  bool bVar12;
  double dVar13;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined auStack_200 [4];
  undefined auStack_1fc [4];
  undefined4 local_1f8;
  undefined4 local_1f4;
  undefined4 local_1f0;
  CVector CStack_1ec;
  CVector CStack_1e0;
  Mat4x4 MStack_1d4;
  Mat4x4 MStack_194;
  Mtx MStack_154;
  undefined local_124 [64];
  undefined auStack_e4 [64];
  char local_a4 [68];
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  font_00 = *(CFont **)&menuPcs->field_0xfc;
  if (menuPcs->field_0x9 == '\x01') {
    if ((menuPcs->field_0x8 == '\0') || (menuPcs->field_0x8 == '\x02')) {
      uVar6 = 0;
    }
    else {
      uVar6 = 8;
    }
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_1f0 = 0xffffffff;
    local_1f4 = 0xffffffff;
    GXSetChanMatColor(4,&local_1f4);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x18);
    psVar4 = *(short **)&menuPcs->field_0x818;
    uStack_5c = (int)*psVar4 ^ 0x80000000;
    local_60 = 0x43300000;
    uStack_54 = (int)psVar4[1] ^ 0x80000000;
    uStack_4c = (int)psVar4[2] ^ 0x80000000;
    uStack_44 = (int)psVar4[3] ^ 0x80000000;
    local_58 = 0x43300000;
    local_50 = 0x43300000;
    local_48 = 0x43300000;
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408),
               (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331408),
               (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408),
               (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),
               (double)*(float *)(psVar4 + 4),(double)*(float *)(psVar4 + 6),(double)FLOAT_803313e8,
               (double)FLOAT_803313e8,&MenuPcs,uVar6);
    if ((*(ushort *)&menuPcs->field_0x1a & 0x3f0) != 0) {
      iVar5 = *(int *)&menuPcs->field_0x818;
      uStack_44 = (int)*(short *)(iVar5 + 0x1c) ^ 0x80000000;
      local_48 = 0x43300000;
      uStack_4c = (int)*(short *)(iVar5 + 0x1e) ^ 0x80000000;
      uStack_54 = (int)*(short *)(iVar5 + 0x20) ^ 0x80000000;
      uStack_5c = (int)*(short *)(iVar5 + 0x22) ^ 0x80000000;
      local_50 = 0x43300000;
      local_58 = 0x43300000;
      local_60 = 0x43300000;
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408),
                 (double)*(float *)(iVar5 + 0x24),(double)*(float *)(iVar5 + 0x28),
                 (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
    }
    uVar3 = (uint)*(short *)&menuPcs->field_0x1a;
    if (((uVar3 & 0x3f0) != 0) && ((uVar3 & 0x1ff) != 0)) {
      if ((uVar3 & 0xf) == 0) {
        iVar5 = 0;
        iVar9 = 5;
        do {
          if ((uVar3 & 0x10 << iVar5) != 0) {
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar5 + 0x19);
            iVar5 = *(int *)&menuPcs->field_0x818;
            uStack_44 = (int)*(short *)(iVar5 + 0x38) ^ 0x80000000;
            local_48 = 0x43300000;
            uStack_4c = (int)*(short *)(iVar5 + 0x3a) ^ 0x80000000;
            uStack_54 = (int)*(short *)(iVar5 + 0x3c) ^ 0x80000000;
            uStack_5c = (int)*(short *)(iVar5 + 0x3e) ^ 0x80000000;
            local_50 = 0x43300000;
            local_58 = 0x43300000;
            local_60 = 0x43300000;
            DrawRect__8CMenuPcsFUlfffffffff
                      ((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),
                       (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408),
                       (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331408),
                       (double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408),
                       (double)*(float *)(iVar5 + 0x40),(double)*(float *)(iVar5 + 0x44),
                       (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
            break;
          }
          iVar5 = iVar5 + 1;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
      else {
        iVar9 = 0;
        iVar5 = 0;
        while ((iVar5 < 4 && (iVar9 < 2))) {
          if (((int)*(short *)&menuPcs->field_0x1a & 1 << iVar5) != 0) {
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar5 + 0x19);
            if (iVar9 == 0) {
              psVar4 = (short *)(*(int *)&menuPcs->field_0x818 + 0x38);
            }
            else {
              psVar4 = (short *)(*(int *)&menuPcs->field_0x818 + 0x54);
            }
            uStack_44 = (int)*psVar4 ^ 0x80000000;
            uStack_4c = (int)psVar4[1] ^ 0x80000000;
            uStack_54 = (int)psVar4[2] ^ 0x80000000;
            local_48 = 0x43300000;
            uStack_5c = (int)psVar4[3] ^ 0x80000000;
            local_50 = 0x43300000;
            local_58 = 0x43300000;
            local_60 = 0x43300000;
            DrawRect__8CMenuPcsFUlfffffffff
                      ((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),
                       (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408),
                       (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331408),
                       (double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408),
                       (double)*(float *)(psVar4 + 4),(double)*(float *)(psVar4 + 6),
                       (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
            iVar9 = iVar9 + 1;
          }
          iVar5 = iVar5 + 1;
        }
      }
    }
    iVar5 = (int)(char)menuPcs->field_0x7;
    if (iVar5 == 0xf) {
      strcpy(local_a4,0x8021ff68);
    }
    else if (iVar5 == 0x16) {
      strcpy(local_a4,0x8021ff68);
      if (Game.game.m_gameWork.m_languageId == 2) {
        strcpy(local_a4,0x8021ff68);
        strcat(local_a4,PTR_s__Hafen_80210d14);
      }
      else {
        strcpy(local_a4,(&PTR_s_cc_logo03_80210d0c)[Game.game.m_gameWork.m_languageId]);
        strcat(local_a4,Game.game.m_gameWork.m_townName);
      }
    }
    else {
      strcpy(local_a4,Game.game.m_cFlatDataArr[1].m_table[3].index[iVar5]);
    }
    if (local_a4[0] != '\0') {
      local_a4[0] = _toupperLatin1();
    }
    uVar3 = 0xd8;
    local_124[0] = 0;
    font = *(CFont **)&menuPcs->field_0xfc;
    if (*(short *)&menuPcs->field_0x1a != 0) {
      uVar3 = 0xa2;
    }
    SetMargin__5CFontFf(FLOAT_803313e8,font);
    SetShadow__5CFontFi(font,0);
    SetScale__5CFontFf(FLOAT_803313e8,font);
    dVar13 = (double)GetWidth__5CFontFPc(font,local_a4);
    uStack_44 = uVar3 ^ 0x80000000;
    local_48 = 0x43300000;
    bVar12 = (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408) < dVar13;
    if (bVar12) {
      strcpy(auStack_e4,local_a4);
      puVar1 = (undefined *)strrchr(auStack_e4,0x20);
      if (puVar1 == (undefined *)0x0) {
        local_124[0] = 0;
      }
      else {
        *puVar1 = 0;
        strcpy(local_124,puVar1 + 1);
      }
      strcpy(local_a4,auStack_e4);
    }
    SetMargin__5CFontFf(FLOAT_803313e8,font_00);
    SetShadow__5CFontFi(font_00,0);
    SetScale__5CFontFf(FLOAT_803313e8,font_00);
    DrawInit__5CFontFv(font_00);
    puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_1fc,0xff,0xff,0xff,0xff);
    local_1f8 = *puVar2;
    SetColor__5CFontF8_GXColor(font_00,&local_1f8);
    local_48 = 0x43300000;
    uStack_44 = (int)*(short *)(*(int *)&menuPcs->field_0x818 + 0x70) ^ 0x80000000;
    SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),font_00);
    local_50 = 0x43300000;
    uStack_4c = (int)*(short *)(*(int *)&menuPcs->field_0x818 + 0x72) ^ 0x80000000;
    SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408),font_00);
    Draw__5CFontFPc(font_00,local_a4);
    if (bVar12) {
      strcpy(local_a4,&DAT_803316fc);
      dVar13 = (double)GetWidth__5CFontFPc(font_00,local_124);
      local_48 = 0x43300000;
      uStack_44 = (int)**(short **)&menuPcs->field_0x818 ^ 0x80000000;
      SetPosX__5CFontFf((float)((double)FLOAT_80331704 - dVar13) * FLOAT_80331434 +
                        (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),font_00);
      local_50 = 0x43300000;
      uStack_4c = (int)*(short *)(*(int *)&menuPcs->field_0x818 + 0x72) + 0x16U ^ 0x80000000;
      SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408),font_00);
      Draw__5CFontFPc(font_00,local_124);
    }
    DrawInit__8CMenuPcsFv(menuPcs);
    bVar12 = false;
    if ((*(ushort *)&menuPcs->field_0x1a & 0x3f0) != 0) {
      puVar1 = &menuPcs->field_0x18;
      iVar5 = 6;
      iVar11 = 0x1e0;
      iVar9 = 0x1ed8;
      do {
        piVar10 = (int *)(*(int *)&menuPcs->field_0x814 + iVar11);
        if (*piVar10 != 0) {
          if (!bVar12) {
            C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,
                             (Mtx *)&MStack_194);
            GXSetProjection(&MStack_194,0);
            PSMTX44Copy(&MStack_194,&CameraPcs.m_screenMatrix);
            targetPosition =
                 (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_1e0)
            ;
            uVar6 = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_1ec);
            C_MTXLookAt(&MStack_154,(Vec *)(piVar10 + 4),uVar6,targetPosition);
            PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
            PSMTXCopy(&MStack_154,&CameraPcs.m_cameraMatrix);
            InitEnv__9CCharaPcsFi(&CharaPcs,5);
            GXSetColorUpdate(0);
            GXSetAlphaUpdate(0);
            puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_200,0,0,0,0);
            local_204 = *puVar2;
            GXSetCopyClear(&local_204,0xffffff);
            GXSetColorUpdate(1);
            GXSetAlphaUpdate(1);
            uStack_44 = (int)*(short *)(piVar10 + 2) ^ 0x80000000;
            uStack_4c = (int)*(short *)((int)piVar10 + 10) ^ 0x80000000;
            uStack_54 = (int)*(short *)(piVar10 + 3) ^ 0x80000000;
            uStack_5c = (int)*(short *)((int)piVar10 + 0xe) ^ 0x80000000;
            local_48 = 0x43300000;
            local_50 = 0x43300000;
            local_58 = 0x43300000;
            local_60 = 0x43300000;
            GXSetViewport((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),
                          (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408),
                          (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331408),
                          (double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408),
                          (double)FLOAT_803313dc,(double)FLOAT_803313e8);
            GXSetScissor(piVar10[0x10],piVar10[0x11],piVar10[0x12],piVar10[0x13]);
            bVar12 = true;
          }
          SetFog__8CGraphicFii(&Graphic,1,0);
          local_20c = DAT_80210830;
          SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_20c);
          SetNumDiffuse__9CLightPcsFUl(&LightPcs,DAT_8021082c);
          puVar8 = &DAT_8021082c;
          puVar2 = puVar8;
          for (iVar7 = 0; iVar7 < DAT_8021082c; iVar7 = iVar7 + 1) {
            local_208 = puVar2[2];
            SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs,iVar7,&local_208,puVar8 + 5,0);
            puVar2 = puVar2 + 1;
            puVar8 = puVar8 + 3;
          }
          SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
          Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)(puVar1 + 0x774),5);
          if (iVar5 != 6) {
            piVar10 = (int *)(*(int *)&menuPcs->field_0x840 + iVar9);
            iVar7 = *piVar10;
            if ((-1 < iVar7) && (-1 < piVar10[2])) {
              DrawMenu__8CPartPcsFi(&PartPcs,(short)iVar7);
            }
          }
        }
        iVar5 = iVar5 + 1;
        puVar1 = puVar1 + 4;
        iVar9 = iVar9 + 0x524;
        iVar11 = iVar11 + 0x50;
      } while (iVar5 < 0x11);
    }
    if (bVar12) {
      PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
      local_210 = DAT_802381a7;
      GXSetCopyClear(&local_210,0xffffff);
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_1d4);
      GXSetProjection(&MStack_1d4,0);
      SetViewport__8CGraphicFv(&Graphic);
      GXSetScissor(0,0,0x280,0x1c0);
      DrawInit__8CMenuPcsFv(menuPcs);
    }
  }
  return;
}

