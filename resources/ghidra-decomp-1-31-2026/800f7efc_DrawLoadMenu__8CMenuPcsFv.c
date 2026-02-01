// Function: DrawLoadMenu__8CMenuPcsFv
// Entry: 800f7efc
// Size: 4940 bytes

/* WARNING: Removing unreachable block (ram,0x800f922c) */
/* WARNING: Removing unreachable block (ram,0x800f9224) */
/* WARNING: Removing unreachable block (ram,0x800f7f14) */
/* WARNING: Removing unreachable block (ram,0x800f7f0c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawLoadMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  short sVar2;
  int iVar3;
  Vec *targetPosition;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint32_t *puVar6;
  short sVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined *puVar10;
  int iVar11;
  undefined4 *puVar12;
  int *piVar13;
  int iVar14;
  int iVar15;
  double dVar16;
  double in_f30;
  double dVar17;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined auStack_184 [4];
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined auStack_15c [4];
  undefined4 local_158;
  CVector CStack_154;
  CVector CStack_148;
  Mat4x4 MStack_13c;
  Mtx MStack_fc;
  Mat4x4 MStack_cc;
  double local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined4 local_68;
  uint uStack_64;
  undefined8 local_60;
  
  iVar3 = *(int *)&menuPcs->field_0x82c;
  if (*(char *)(iVar3 + 8) != '\0') {
    sVar7 = *(short *)(iVar3 + 0x10);
    if ((0 < sVar7) && (sVar7 < 4)) {
      if (sVar7 == 1) {
        local_88 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x22)) ^ 0x80000000);
        in_f30 = (double)(float)(DOUBLE_803314e8 * (local_88 - DOUBLE_80331408));
      }
      else if (sVar7 == 2) {
        in_f30 = (double)FLOAT_803313e8;
      }
      else {
        local_88 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x22)) ^ 0x80000000);
        in_f30 = (double)(float)-(DOUBLE_803314e8 * (local_88 - DOUBLE_80331408) - DOUBLE_80331420);
      }
      if (DOUBLE_803314f0 < in_f30) {
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
        local_88 = (double)(longlong)(int)((double)FLOAT_80331458 * in_f30);
        local_164 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331458 * in_f30));
        local_160 = local_164;
        GXSetChanMatColor(4,&local_160);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1f);
        dVar16 = (double)FLOAT_803313dc;
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar16,(double)(float)(DOUBLE_803314d0 - (double)FLOAT_80331440),
                   (double)FLOAT_803313e0,(double)FLOAT_80331440,dVar16,dVar16,
                   (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
      }
    }
    if (in_f30 < (double)FLOAT_803313dc) {
      in_f30 = (double)FLOAT_803313dc;
    }
    if (in_f30 <= (double)FLOAT_803313e8) {
      uVar9 = (uint)((double)FLOAT_80331458 * in_f30);
      local_88 = (double)(longlong)(int)uVar9;
    }
    else {
      uVar9 = 0xff;
    }
    if (*(char *)(DAT_8032ef08 + 0x18) == '\x0e') {
      puVar10 = (&PTR_s_Select_game_data_to_load__80210770)
                [(Game.game.m_gameWork.m_languageId - 1) * 0xb];
      puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_15c,0xff,0xff,0xff,uVar9 & 0xff);
      local_158 = *puVar5;
      dVar16 = (double)CalcCenteringPos2__8CMenuPcsFPcff
                                 ((double)FLOAT_80331594,(double)FLOAT_803313e8,&MenuPcs,puVar10);
      local_88 = (double)(longlong)(int)dVar16;
      local_80 = (double)(longlong)(int)FLOAT_803317d0;
      DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                ((double)FLOAT_80331594,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,
                 (int)dVar16,(int)FLOAT_803317d0,&local_158,7,puVar10);
    }
    DrawMCList__8CMenuPcsFv(menuPcs);
    iVar3 = *(int *)&menuPcs->field_0x82c;
    if ((*(short *)(iVar3 + 0x10) == 2) && (0x10 < *(short *)(iVar3 + 0x16))) {
      dVar16 = (double)(float)((double)FLOAT_803314d8 - DOUBLE_803317d8);
      if (*(short *)(iVar3 + 0x16) == 0x11) {
        uVar9 = (uint)*(short *)(iVar3 + 0x26);
      }
      else {
        uVar9 = (menuPcs->m_mcCtrl).m_saveIndex;
      }
      local_80 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      dVar17 = (double)(float)(DOUBLE_80331498 * (local_80 - DOUBLE_80331408) +
                              (double)(float)((double)FLOAT_803314d8 + (double)FLOAT_80331410));
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      local_16c = 0xffffffff;
      local_168 = 0xffffffff;
      GXSetChanMatColor(4,&local_168);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
      local_88 = (double)(longlong)(int)dVar16;
      local_70 = (double)(longlong)(int)dVar17;
      uStack_64 = (int)dVar17 ^ 0x80000000;
      local_78 = (double)(CONCAT44(0x43300000,(int)dVar16) ^ 0x80000000);
      local_68 = 0x43300000;
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)(local_78 - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408),
                 (double)FLOAT_80331410,(double)FLOAT_80331410,(double)FLOAT_803313dc,
                 (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
      iVar15 = 0;
      piVar13 = (int *)(*(int *)&menuPcs->field_0x814 + 0x550);
      iVar14 = 0;
      puVar6 = &(menuPcs->m_mcCtrl).m_serialHi;
      iVar3 = 0x550;
      do {
        if (*piVar13 != 0) {
          iVar11 = *(int *)&menuPcs->field_0x814 + iVar3;
          C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,
                           (Mtx *)&MStack_13c);
          GXSetProjection(&MStack_13c,0);
          PSMTX44Copy(&MStack_13c,&CameraPcs.m_screenMatrix);
          targetPosition =
               (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_148);
          uVar4 = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_154);
          C_MTXLookAt(&MStack_fc,(Vec *)(iVar11 + 0x10),uVar4,targetPosition);
          PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
          PSMTXCopy(&MStack_fc,&CameraPcs.m_cameraMatrix);
          InitEnv__9CCharaPcsFi(&CharaPcs,5);
          GXSetColorUpdate(0);
          GXSetAlphaUpdate(0);
          puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_184,0,0,0,0);
          local_188 = *puVar5;
          GXSetCopyClear(&local_188,0xffffff);
          GXSetColorUpdate(1);
          GXSetAlphaUpdate(1);
          uStack_64 = (int)*(short *)(iVar11 + 8) ^ 0x80000000;
          local_68 = 0x43300000;
          local_70 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar11 + 10) ^ 0x80000000);
          local_78 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar11 + 0xc) ^ 0x80000000);
          local_80 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar11 + 0xe) ^ 0x80000000);
          GXSetViewport((double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408),
                        (double)(float)(local_70 - DOUBLE_80331408),
                        (double)(float)(local_78 - DOUBLE_80331408),
                        (double)(float)(local_80 - DOUBLE_80331408),(double)FLOAT_803313dc,
                        (double)FLOAT_803313e8);
          GXSetScissor(*(undefined4 *)(iVar11 + 0x40),*(undefined4 *)(iVar11 + 0x44),
                       *(undefined4 *)(iVar11 + 0x48),*(undefined4 *)(iVar11 + 0x4c));
          SetFog__8CGraphicFii(&Graphic,1,0);
          local_190 = DAT_80210830;
          SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_190);
          SetNumDiffuse__9CLightPcsFUl(&LightPcs,DAT_8021082c);
          puVar12 = &DAT_8021082c;
          puVar5 = puVar12;
          for (iVar11 = 0; iVar11 < DAT_8021082c; iVar11 = iVar11 + 1) {
            local_18c = puVar5[2];
            SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs,iVar11,&local_18c,puVar12 + 5,0);
            puVar5 = puVar5 + 1;
            puVar12 = puVar12 + 3;
          }
          SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
          Draw__Q29CCharaPcs7CHandleFi(puVar6[0x1dd],5);
          if (-1 < *(int *)(*(int *)&menuPcs->field_0x840 + iVar14 + 0x5768)) {
            DrawMenuIdx__8CPartPcsFi(&PartPcs);
          }
          if (-1 < *(int *)(*(int *)&menuPcs->field_0x840 + iVar14 + 0x6bf8)) {
            DrawMenuIdx__8CPartPcsFi(&PartPcs);
          }
        }
        iVar15 = iVar15 + 1;
        iVar3 = iVar3 + 0x50;
        puVar6 = puVar6 + 1;
        piVar13 = piVar13 + 0x14;
        iVar14 = iVar14 + 0x524;
      } while (iVar15 < 4);
      DrawInit__8CMenuPcsFv(menuPcs);
      PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
      local_170 = DAT_802381a7;
      GXSetCopyClear(&local_170,0xffffff);
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_cc);
      GXSetProjection(&MStack_cc,0);
      SetViewport__8CGraphicFv(&Graphic);
      GXSetScissor(0,0,0x280,0x1c0);
      DrawInit__8CMenuPcsFv(menuPcs);
    }
    iVar3 = *(int *)&menuPcs->field_0x82c;
    sVar7 = *(short *)(iVar3 + 0x10);
    if ((sVar7 == 2) && (*(short *)(iVar3 + 0x18) == 0)) {
      sVar7 = *(short *)(iVar3 + 0x16);
      switch((int)sVar7) {
      case 0:
      case 2:
        sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
        DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
        if (sVar1 == 1) {
          DrawMcWinMess__8CMenuPcsFii(menuPcs,0,0);
          local_68 = 0x43300000;
          uStack_64 = (int)*(short *)(*(int *)&menuPcs->field_0x848 + 2) +
                      *(short *)(*(int *)&menuPcs->field_0x848 + 6) + -0x3e ^ 0x80000000;
          dVar16 = (double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408);
          uVar9 = GetSlotABXPos__8CMenuPcsFi
                            (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26));
          local_70 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
          dVar17 = (double)(float)(local_70 - DOUBLE_80331408);
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
          local_178 = 0xffffffff;
          local_174 = 0xffffffff;
          GXSetChanMatColor(4,&local_174);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
          local_78 = (double)(longlong)(int)dVar17;
          local_88 = (double)(longlong)(int)dVar16;
          local_80 = (double)(CONCAT44(0x43300000,(int)dVar17) ^ 0x80000000);
          local_60 = (double)CONCAT44(0x43300000,(int)dVar16 ^ 0x80000000);
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)(float)(local_80 - DOUBLE_80331408),
                     (double)(float)(local_60 - DOUBLE_80331408),(double)FLOAT_80331410,
                     (double)FLOAT_80331410,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
                     (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
        }
        if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
          iVar3 = *(int *)&menuPcs->field_0x82c;
          if (*(short *)(iVar3 + 0xe) < 0) {
            *(undefined2 *)(iVar3 + 0x1e) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
            *(undefined2 *)&menuPcs->field_0x870 = 1;
          }
          else if (*(short *)(iVar3 + 0x16) == 2) {
            *(undefined2 *)(iVar3 + 0x16) = 3;
          }
          else {
            *(undefined2 *)(iVar3 + 0x16) = 1;
          }
        }
        break;
      case 1:
        if (0x12 < *(short *)(iVar3 + 0x22)) {
          *(undefined2 *)(iVar3 + 0x16) = 3;
        }
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
        break;
      case 3:
        if (*(short *)(iVar3 + 0x2e) != 1) {
          memset(menuPcs->m_unk0x838,0,0x120);
          iVar3 = *(int *)&menuPcs->field_0x82c;
          sVar1 = *(short *)(iVar3 + 0x2e);
          if (sVar1 == -1) {
            *(undefined2 *)(iVar3 + 0x16) = 5;
          }
          else if (sVar1 == -2) {
            *(undefined2 *)(iVar3 + 0x16) = 8;
          }
          else if (sVar1 == -3) {
            *(undefined2 *)(iVar3 + 0x16) = 6;
          }
          else if (sVar1 == -4) {
            *(undefined2 *)(iVar3 + 0x16) = 7;
          }
          else if (sVar1 == 0) {
            *(undefined2 *)(iVar3 + 0x16) = 4;
          }
        }
        break;
      case 4:
        sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
        DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
        if (sVar1 == 1) {
          DrawMcWinMess__8CMenuPcsFii(menuPcs,6,0);
          sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x2e);
          if ((sVar1 != 0) && (sVar1 == 1)) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 0xc;
          }
        }
        else if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
          iVar3 = *(int *)&menuPcs->field_0x82c;
          sVar1 = *(short *)(iVar3 + 0x2e);
          if (sVar1 == -3) {
            *(undefined2 *)(iVar3 + 0x16) = 8;
          }
          else if (sVar1 == -4) {
            *(undefined2 *)(iVar3 + 0x16) = 8;
          }
          else if (sVar1 == -5) {
            *(undefined2 *)(iVar3 + 0x16) = 7;
          }
          else if (sVar1 == -6) {
            *(undefined2 *)(iVar3 + 0x16) = 0x10;
          }
          else {
            *(undefined2 *)(iVar3 + 0x16) = 10;
          }
        }
        break;
      case 5:
      case 6:
      case 7:
      case 10:
      case 0xe:
      case 0xf:
      case 0x10:
      case 0x17:
      case 0x18:
      case 0x1b:
      case 0x1c:
        sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
        DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
        if (sVar1 == 1) {
          uVar4 = 0;
          sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
          if (sVar2 == 5) {
            uVar8 = 1;
          }
          else if (sVar2 == 6) {
            uVar8 = 2;
          }
          else if (sVar2 == 7) {
            uVar8 = 3;
          }
          else if (sVar2 == 10) {
            uVar8 = 0xb;
          }
          else if (sVar2 == 0xe) {
            uVar8 = 0xc;
          }
          else if (sVar2 == 0xf) {
            uVar8 = 0xd;
          }
          else if (sVar2 == 0x1c) {
            uVar8 = 0x1b;
            uVar4 = 1;
          }
          else if (sVar2 == 0x1b) {
            uVar8 = 0x1c;
            uVar4 = 1;
          }
          else if (sVar2 == 0x18) {
            uVar8 = 0x10;
          }
          else if (sVar2 == 0x17) {
            uVar8 = 0x11;
          }
          else {
            uVar8 = 0x13;
          }
          DrawMcWinMess__8CMenuPcsFii(menuPcs,uVar8,uVar4);
        }
        if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
          iVar3 = *(int *)&menuPcs->field_0x82c;
          if ((*(short *)(iVar3 + 0xe) < 0) ||
             (((sVar1 = *(short *)(iVar3 + 0x16), sVar1 == 0x1c || (sVar1 == 0x1b)) ||
              (sVar1 == 0x17)))) {
            *(undefined2 *)(iVar3 + 0x16) = 3;
          }
          else if (sVar1 == 0x18) {
            *(undefined2 *)(iVar3 + 0x1e) = 1;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
            *(undefined2 *)&menuPcs->field_0x870 = 4;
          }
          else if ((*(short *)(iVar3 + 0x1c) == 8) && (menuPcs->field_0x889 != '\0')) {
            *(undefined2 *)(iVar3 + 0x1e) = 1;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
            *(undefined2 *)&menuPcs->field_0x870 = 2;
          }
          else {
            *(undefined2 *)(iVar3 + 0x16) = 2;
          }
        }
        break;
      case 8:
      case 0xb:
      case 0x19:
        sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
        DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
        if (sVar1 == 1) {
          uVar4 = 0;
          sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
          if (sVar2 == 8) {
            uVar8 = 4;
          }
          else if (sVar2 == 0x19) {
            uVar8 = 0x19;
            uVar4 = 1;
          }
          else {
            uVar8 = 5;
          }
          DrawMcWinMess__8CMenuPcsFii(menuPcs,uVar8,uVar4);
          local_60 = (double)(CONCAT44(0x43300000,
                                       (int)*(short *)(*(int *)&menuPcs->field_0x848 + 2) +
                                       *(short *)(*(int *)&menuPcs->field_0x848 + 6) + -0x3e) ^
                             0x80000000);
          dVar16 = (double)(float)(local_60 - DOUBLE_80331408);
          uStack_64 = GetYesNoXPos__8CMenuPcsFi
                                (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26));
          uStack_64 = uStack_64 ^ 0x80000000;
          iVar3 = *(int *)&menuPcs->field_0x82c;
          local_68 = 0x43300000;
          dVar17 = (double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408);
          if (*(short *)(iVar3 + 0x16) == 0x19) {
            sVar2 = *(short *)(iVar3 + 0x2e);
            if (sVar2 < 0) {
              if (sVar2 == -1) {
                *(undefined2 *)(iVar3 + 0x16) = 5;
              }
              else if (sVar2 == -2) {
                *(undefined2 *)(iVar3 + 0x16) = 8;
              }
              else if (sVar2 == -3) {
                *(undefined2 *)(iVar3 + 0x16) = 6;
              }
              else {
                *(undefined2 *)(iVar3 + 0x16) = 7;
              }
            }
          }
          else {
            SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
            local_180 = 0xffffffff;
            local_17c = 0xffffffff;
            GXSetChanMatColor(4,&local_17c);
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
            local_60 = (double)(longlong)(int)dVar17;
            local_70 = (double)(longlong)(int)dVar16;
            uStack_64 = (int)dVar17 ^ 0x80000000;
            local_68 = 0x43300000;
            local_78 = (double)CONCAT44(0x43300000,(int)dVar16 ^ 0x80000000);
            DrawRect__8CMenuPcsFUlfffffffff
                      ((double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408),
                       (double)(float)(local_78 - DOUBLE_80331408),(double)FLOAT_80331410,
                       (double)FLOAT_80331410,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
                       (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
          }
        }
        if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
          iVar3 = *(int *)&menuPcs->field_0x82c;
          sVar1 = *(short *)(iVar3 + 0x2e);
          if (sVar1 < 0) {
            if (sVar1 == -1) {
              *(undefined2 *)(iVar3 + 0x16) = 5;
            }
            else if (sVar1 == -2) {
              *(undefined2 *)(iVar3 + 0x16) = 8;
            }
            else if (sVar1 == -3) {
              *(undefined2 *)(iVar3 + 0x16) = 6;
            }
            else {
              *(undefined2 *)(iVar3 + 0x16) = 7;
            }
          }
          else if (*(short *)(iVar3 + 0xe) < 0) {
            if (*(short *)(iVar3 + 0x16) == 0x19) {
              *(undefined2 *)(iVar3 + 0x16) = 0x11;
              *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) =
                   (short)(menuPcs->m_mcCtrl).m_saveIndex;
            }
            else if ((*(short *)(iVar3 + 0x1c) == 8) && (menuPcs->field_0x889 != '\0')) {
              *(undefined2 *)(iVar3 + 0x1e) = 1;
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
              memset(menuPcs->m_unk0x838,0,0x120);
              *(undefined2 *)&menuPcs->field_0x870 = 1;
            }
            else {
              *(undefined2 *)(iVar3 + 0x16) = 2;
            }
          }
          else if (*(short *)(iVar3 + 0x16) == 8) {
            *(undefined2 *)(iVar3 + 0x16) = 0xb;
          }
          else if (*(short *)(iVar3 + 0x16) == 0x19) {
            *(undefined2 *)(iVar3 + 0x16) = 0x1a;
          }
          else {
            *(undefined2 *)(iVar3 + 0x16) = 0xd;
          }
        }
        break;
      case 0xc:
        sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
        DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
        if ((((sVar1 != 1) ||
             (DrawMcWinMess__8CMenuPcsFii(menuPcs,6,0),
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x2e) != 0)) && (sVar1 == 2)) &&
           (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
          iVar3 = *(int *)&menuPcs->field_0x82c;
          sVar1 = *(short *)(iVar3 + 0x2e);
          if (sVar1 == -1) {
            *(undefined2 *)(iVar3 + 0x16) = 10;
          }
          else if (sVar1 == -2) {
            *(undefined2 *)(iVar3 + 0x16) = 8;
          }
          else if (sVar1 == -3) {
            *(undefined2 *)(iVar3 + 0x16) = 8;
          }
          else if (sVar1 == -4) {
            *(undefined2 *)(iVar3 + 0x16) = 7;
          }
          else if (sVar1 == -999) {
            *(undefined2 *)(iVar3 + 0x1e) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
            *(undefined2 *)&menuPcs->field_0x870 = 2;
          }
          else {
            BindMcObj__8CMenuPcsFv(menuPcs);
            puVar6 = menuPcs->m_unk0x838;
            uVar9 = 0;
            if (((*(char *)((int)puVar6 + 0x42) == '\0') &&
                (uVar9 = 1, *(char *)((int)puVar6 + 0x8a) == '\0')) &&
               ((uVar9 = 2, *(char *)((int)puVar6 + 0xd2) == '\0' &&
                (uVar9 = 3, *(char *)((int)puVar6 + 0x11a) == '\0')))) {
              uVar9 = 4;
            }
            if (uVar9 < 4) {
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 0x19;
            }
            else {
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 0x11;
            }
          }
        }
        break;
      case 0xd:
      case 0x16:
      case 0x1a:
        sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
        DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
        if (sVar1 == 1) {
          uVar4 = 0;
          sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
          if (sVar1 == 0xd) {
            uVar8 = 7;
          }
          else if (sVar1 == 0x1a) {
            uVar8 = 0x1a;
            uVar4 = 1;
          }
          else {
            uVar8 = 9;
          }
          DrawMcWinMess__8CMenuPcsFii(menuPcs,uVar8,uVar4);
        }
        else if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
          iVar3 = *(int *)&menuPcs->field_0x82c;
          if (*(short *)(iVar3 + 0x16) == 0xd) {
            if (*(short *)(iVar3 + 0x2e) == 1) {
              *(undefined2 *)(iVar3 + 0x16) = 0xe;
            }
            else if (*(short *)(iVar3 + 0x2e) == -2) {
              *(undefined2 *)(iVar3 + 0x16) = 7;
            }
            else {
              *(undefined2 *)(iVar3 + 0x16) = 0xf;
            }
          }
          else if (*(short *)(iVar3 + 0x16) == 0x1a) {
            if (*(short *)(iVar3 + 0x2e) == 1) {
              *(undefined2 *)(iVar3 + 0x16) = 0x1c;
            }
            else if (*(short *)(iVar3 + 0x2e) == -2) {
              *(undefined2 *)(iVar3 + 0x16) = 7;
            }
            else {
              *(undefined2 *)(iVar3 + 0x16) = 0x1b;
            }
          }
          else if (*(short *)(iVar3 + 0x2e) == 1) {
            *(undefined2 *)(iVar3 + 0x16) = 0x18;
            PlaySe__6CSoundFiiii(&Sound,0x42,0x40,0x7f,0);
          }
          else if (*(short *)(iVar3 + 0x2e) == -4) {
            *(undefined2 *)(iVar3 + 0x16) = 7;
          }
          else {
            *(undefined2 *)(iVar3 + 0x16) = 0x17;
          }
        }
        break;
      case 0x11:
        if (*(short *)(iVar3 + 0x2e) < 0) {
          *(undefined2 *)(iVar3 + 0x16) = 3;
        }
        else if (*(short *)(iVar3 + 0xe) != 0) {
          if (*(short *)(iVar3 + 0xe) < 0) {
            if ((*(short *)(iVar3 + 0x1c) == 8) && (menuPcs->field_0x889 != '\0')) {
              *(undefined2 *)(iVar3 + 0x1e) = 1;
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
              memset(menuPcs->m_unk0x838,0,0x120);
              *(undefined2 *)&menuPcs->field_0x870 = 1;
            }
            else {
              *(undefined2 *)(iVar3 + 0x16) = 2;
            }
          }
          else {
            *(undefined2 *)(iVar3 + 0x16) = 0x16;
          }
        }
      }
      if ((int)sVar7 != (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x16)) {
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0;
      }
    }
    else if (sVar7 == 2) {
      if ((sVar7 == 2) && (*(short *)(iVar3 + 0x18) != 0)) {
        *(short *)(iVar3 + 0x18) = *(short *)(iVar3 + 0x18) + -1;
        iVar3 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar3 + 0x18) < 1) {
          *(short *)(iVar3 + 0x10) = *(short *)(iVar3 + 0x10) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          PlaySe__6CSoundFiiii
                    (&Sound,0x31 - ((int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) >> 0x1f),
                     0x40,0x7f,0);
        }
      }
    }
    else {
      *(short *)(iVar3 + 0x22) = *(short *)(iVar3 + 0x22) + 1;
      iVar3 = *(int *)&menuPcs->field_0x82c;
      if ((*(short *)(iVar3 + 0x10) == 3) && (*(short *)(iVar3 + 0x16) != 0)) {
        sVar7 = 0x13;
      }
      else {
        sVar7 = 10;
      }
      if (sVar7 <= *(short *)(iVar3 + 0x22)) {
        *(short *)(iVar3 + 0x10) = *(short *)(iVar3 + 0x10) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        iVar3 = *(int *)&menuPcs->field_0x82c;
        if (4 < *(short *)(iVar3 + 0x10)) {
          if (*(short *)(iVar3 + 0x1c) != 8) {
            *(undefined2 *)(iVar3 + 0x20) = *(undefined2 *)(iVar3 + 0x1e);
          }
          menuPcs->field_0x86e = 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0;
        }
      }
    }
  }
  return;
}

