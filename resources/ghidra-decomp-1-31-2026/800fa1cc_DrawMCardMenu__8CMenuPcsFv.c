// Function: DrawMCardMenu__8CMenuPcsFv
// Entry: 800fa1cc
// Size: 4724 bytes

/* WARNING: Removing unreachable block (ram,0x800fb424) */
/* WARNING: Removing unreachable block (ram,0x800fb41c) */
/* WARNING: Removing unreachable block (ram,0x800fa1e4) */
/* WARNING: Removing unreachable block (ram,0x800fa1dc) */

void DrawMCardMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  Vec *targetPosition;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint32_t *puVar6;
  short sVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  int iVar13;
  int iVar14;
  double dVar15;
  double dVar16;
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
  CVector CStack_15c;
  CVector CStack_150;
  Mat4x4 MStack_144;
  Mtx MStack_104;
  Mat4x4 MStack_d4;
  undefined8 local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined4 local_70;
  uint uStack_6c;
  undefined8 local_68;
  
  iVar8 = *(int *)&menuPcs->field_0x82c;
  sVar7 = *(short *)(iVar8 + 0x10);
  if ((0 < sVar7) && (sVar7 < 4)) {
    if (sVar7 == 1) {
      local_90 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x22)) ^ 0x80000000);
      dVar15 = (double)(float)(DOUBLE_803314e8 * (local_90 - DOUBLE_80331408));
    }
    else if (sVar7 == 2) {
      dVar15 = (double)FLOAT_803313e8;
    }
    else {
      local_90 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x22)) ^ 0x80000000);
      dVar15 = (double)(float)-(DOUBLE_803314e8 * (local_90 - DOUBLE_80331408) - DOUBLE_80331420);
    }
    if (DOUBLE_803314f0 < dVar15) {
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      local_90 = (double)(longlong)(int)((double)FLOAT_80331458 * dVar15);
      local_164 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331458 * dVar15));
      local_160 = local_164;
      GXSetChanMatColor(4,&local_160);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1f);
      dVar15 = (double)FLOAT_803313dc;
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar15,(double)(float)(DOUBLE_803314d0 - (double)FLOAT_80331440),
                 (double)FLOAT_803313e0,(double)FLOAT_80331440,dVar15,dVar15,(double)FLOAT_803313e8,
                 (double)FLOAT_803313e8,&MenuPcs,0);
    }
  }
  DrawMCList__8CMenuPcsFv(menuPcs);
  iVar8 = *(int *)&menuPcs->field_0x82c;
  if ((*(short *)(iVar8 + 0x10) == 2) && (0x10 < *(short *)(iVar8 + 0x16))) {
    dVar15 = (double)(float)((double)FLOAT_803314d8 - DOUBLE_803317d8);
    if (*(short *)(iVar8 + 0x16) == 0x11) {
      uVar3 = (uint)*(short *)(iVar8 + 0x26);
    }
    else {
      uVar3 = (menuPcs->m_mcCtrl).m_saveIndex;
    }
    local_90 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
    dVar16 = (double)(float)(DOUBLE_80331498 * (local_90 - DOUBLE_80331408) +
                            (double)(float)((double)FLOAT_803314d8 + (double)FLOAT_80331410));
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_16c = 0xffffffff;
    local_168 = 0xffffffff;
    GXSetChanMatColor(4,&local_168);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
    local_88 = (double)(longlong)(int)dVar15;
    local_78 = (double)(longlong)(int)dVar16;
    uStack_6c = (int)dVar16 ^ 0x80000000;
    local_80 = (double)(CONCAT44(0x43300000,(int)dVar15) ^ 0x80000000);
    local_70 = 0x43300000;
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(local_80 - DOUBLE_80331408),
               (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408),
               (double)FLOAT_80331410,(double)FLOAT_80331410,(double)FLOAT_803313dc,
               (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
    iVar14 = 0;
    piVar12 = (int *)(*(int *)&menuPcs->field_0x814 + 0x550);
    iVar13 = 0;
    puVar6 = &(menuPcs->m_mcCtrl).m_serialHi;
    iVar8 = 0x550;
    do {
      if (*piVar12 != 0) {
        iVar10 = *(int *)&menuPcs->field_0x814 + iVar8;
        C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,
                         (Mtx *)&MStack_144);
        GXSetProjection(&MStack_144,0);
        PSMTX44Copy(&MStack_144,&CameraPcs.m_screenMatrix);
        targetPosition =
             (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_150);
        uVar4 = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_15c);
        C_MTXLookAt(&MStack_104,(Vec *)(iVar10 + 0x10),uVar4,targetPosition);
        PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
        PSMTXCopy(&MStack_104,&CameraPcs.m_cameraMatrix);
        InitEnv__9CCharaPcsFi(&CharaPcs,5);
        GXSetColorUpdate(0);
        GXSetAlphaUpdate(0);
        puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_184,0,0,0,0);
        local_188 = *puVar5;
        GXSetCopyClear(&local_188,0xffffff);
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(1);
        uStack_6c = (int)*(short *)(iVar10 + 8) ^ 0x80000000;
        local_70 = 0x43300000;
        local_78 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar10 + 10) ^ 0x80000000);
        local_80 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar10 + 0xc) ^ 0x80000000);
        local_88 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar10 + 0xe) ^ 0x80000000);
        GXSetViewport((double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408),
                      (double)(float)(local_78 - DOUBLE_80331408),
                      (double)(float)(local_80 - DOUBLE_80331408),
                      (double)(float)(local_88 - DOUBLE_80331408),(double)FLOAT_803313dc,
                      (double)FLOAT_803313e8);
        GXSetScissor(*(undefined4 *)(iVar10 + 0x40),*(undefined4 *)(iVar10 + 0x44),
                     *(undefined4 *)(iVar10 + 0x48),*(undefined4 *)(iVar10 + 0x4c));
        SetFog__8CGraphicFii(&Graphic,1,0);
        local_190 = DAT_80210830;
        SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_190);
        SetNumDiffuse__9CLightPcsFUl(&LightPcs,DAT_8021082c);
        puVar11 = &DAT_8021082c;
        puVar5 = puVar11;
        for (iVar10 = 0; iVar10 < DAT_8021082c; iVar10 = iVar10 + 1) {
          local_18c = puVar5[2];
          SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs,iVar10,&local_18c,puVar11 + 5,0);
          puVar5 = puVar5 + 1;
          puVar11 = puVar11 + 3;
        }
        SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
        Draw__Q29CCharaPcs7CHandleFi(puVar6[0x1dd],5);
        if (-1 < *(int *)(*(int *)&menuPcs->field_0x840 + iVar13 + 0x5768)) {
          DrawMenuIdx__8CPartPcsFi(&PartPcs);
        }
        if (-1 < *(int *)(*(int *)&menuPcs->field_0x840 + iVar13 + 0x6bf8)) {
          DrawMenuIdx__8CPartPcsFi(&PartPcs);
        }
      }
      iVar14 = iVar14 + 1;
      iVar8 = iVar8 + 0x50;
      puVar6 = puVar6 + 1;
      piVar12 = piVar12 + 0x14;
      iVar13 = iVar13 + 0x524;
    } while (iVar14 < 4);
    DrawInit__8CMenuPcsFv(menuPcs);
    PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
    local_170 = DAT_802381a7;
    GXSetCopyClear(&local_170,0xffffff);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_d4);
    GXSetProjection(&MStack_d4,0);
    SetViewport__8CGraphicFv(&Graphic);
    GXSetScissor(0,0,0x280,0x1c0);
    DrawInit__8CMenuPcsFv(menuPcs);
  }
  iVar8 = *(int *)&menuPcs->field_0x82c;
  sVar7 = *(short *)(iVar8 + 0x10);
  if ((sVar7 == 2) && (*(short *)(iVar8 + 0x18) == 0)) {
    sVar7 = *(short *)(iVar8 + 0x16);
    switch((int)sVar7) {
    case 0:
    case 2:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
      DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
      if (sVar1 == 1) {
        DrawMcWinMess__8CMenuPcsFii(menuPcs,0,0);
        local_70 = 0x43300000;
        uStack_6c = (int)*(short *)(*(int *)&menuPcs->field_0x848 + 2) +
                    *(short *)(*(int *)&menuPcs->field_0x848 + 6) + -0x3e ^ 0x80000000;
        dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408);
        uVar3 = GetSlotABXPos__8CMenuPcsFi
                          (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26));
        local_78 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
        dVar16 = (double)(float)(local_78 - DOUBLE_80331408);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
        local_178 = 0xffffffff;
        local_174 = 0xffffffff;
        GXSetChanMatColor(4,&local_174);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
        local_80 = (double)(longlong)(int)dVar16;
        local_90 = (double)(longlong)(int)dVar15;
        local_88 = (double)(CONCAT44(0x43300000,(int)dVar16) ^ 0x80000000);
        local_68 = (double)CONCAT44(0x43300000,(int)dVar15 ^ 0x80000000);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)(local_88 - DOUBLE_80331408),
                   (double)(float)(local_68 - DOUBLE_80331408),(double)FLOAT_80331410,
                   (double)FLOAT_80331410,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
                   (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
      }
      if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
        iVar8 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar8 + 0xe) < 0) {
          *(undefined2 *)(iVar8 + 0x1e) = 0xffff;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
          *(undefined2 *)&menuPcs->field_0x870 = 1;
        }
        else if (*(short *)(iVar8 + 0x16) == 2) {
          *(undefined2 *)(iVar8 + 0x16) = 3;
        }
        else {
          *(undefined2 *)(iVar8 + 0x16) = 1;
        }
      }
      break;
    case 1:
      if (0x12 < *(short *)(iVar8 + 0x22)) {
        *(undefined2 *)(iVar8 + 0x16) = 3;
      }
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
      break;
    case 3:
      if (*(short *)(iVar8 + 0x2e) != 1) {
        memset(menuPcs->m_unk0x838,0,0x120);
        iVar8 = *(int *)&menuPcs->field_0x82c;
        sVar1 = *(short *)(iVar8 + 0x2e);
        if (sVar1 == -1) {
          *(undefined2 *)(iVar8 + 0x16) = 5;
        }
        else if (sVar1 == -2) {
          *(undefined2 *)(iVar8 + 0x16) = 8;
        }
        else if (sVar1 == -3) {
          *(undefined2 *)(iVar8 + 0x16) = 6;
        }
        else if (sVar1 == -4) {
          *(undefined2 *)(iVar8 + 0x16) = 7;
        }
        else if (sVar1 == 0) {
          *(undefined2 *)(iVar8 + 0x16) = 4;
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
        iVar8 = *(int *)&menuPcs->field_0x82c;
        sVar1 = *(short *)(iVar8 + 0x2e);
        if (sVar1 == -2) {
          *(undefined2 *)(iVar8 + 0x16) = 9;
        }
        else if (sVar1 == -3) {
          *(undefined2 *)(iVar8 + 0x16) = 8;
        }
        else if (sVar1 == -4) {
          *(undefined2 *)(iVar8 + 0x16) = 8;
        }
        else if (sVar1 == -5) {
          *(undefined2 *)(iVar8 + 0x16) = 7;
        }
        else {
          *(undefined2 *)(iVar8 + 0x16) = 10;
        }
      }
      break;
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 0xe:
    case 0xf:
    case 0x14:
    case 0x15:
    case 0x1b:
    case 0x1c:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
      DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
      if (sVar1 == 1) {
        uVar4 = 0;
        sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
        if (sVar2 == 5) {
          uVar9 = 1;
        }
        else if (sVar2 == 6) {
          uVar9 = 2;
        }
        else if (sVar2 == 7) {
          uVar9 = 3;
        }
        else if (sVar2 == 9) {
          uVar9 = 10;
        }
        else if (sVar2 == 10) {
          uVar9 = 0xb;
        }
        else if (sVar2 == 0xe) {
          uVar9 = 0xc;
        }
        else if (sVar2 == 0xf) {
          uVar9 = 0xd;
        }
        else if (sVar2 == 0x1c) {
          uVar9 = 0x1b;
          uVar4 = 1;
        }
        else if (sVar2 == 0x1b) {
          uVar9 = 0x1c;
          uVar4 = 1;
        }
        else if (sVar2 == 0x15) {
          uVar9 = 0xe;
        }
        else {
          uVar9 = 0xf;
        }
        DrawMcWinMess__8CMenuPcsFii(menuPcs,uVar9,uVar4);
      }
      if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
        iVar8 = *(int *)&menuPcs->field_0x82c;
        if ((*(short *)(iVar8 + 0xe) < 0) ||
           (((sVar1 = *(short *)(iVar8 + 0x16), sVar1 == 0x14 || (sVar1 == 0x1c)) || (sVar1 == 0x1b)
            ))) {
          *(undefined2 *)(iVar8 + 0x16) = 3;
        }
        else if (sVar1 == 0xe) {
          memset(menuPcs->m_unk0x838,0,0x120);
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 0x11;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
        }
        else if (sVar1 == 0x15) {
          *(undefined2 *)(iVar8 + 0x16) = 0x11;
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)(menuPcs->m_mcCtrl).m_saveIndex;
          if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 8) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0xb;
            *(undefined2 *)&menuPcs->field_0x870 = 3;
          }
        }
        else {
          *(undefined2 *)(iVar8 + 0x16) = 2;
        }
      }
      break;
    case 8:
    case 0xb:
    case 0x12:
    case 0x19:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
      DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
      if (sVar1 == 1) {
        uVar4 = 0;
        sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
        if (sVar2 == 8) {
          uVar9 = 4;
        }
        else if (sVar2 == 0xb) {
          uVar9 = 5;
        }
        else if (sVar2 == 0x19) {
          uVar9 = 0x19;
          uVar4 = 1;
        }
        else {
          uVar9 = 0x12;
        }
        DrawMcWinMess__8CMenuPcsFii(menuPcs,uVar9,uVar4);
        local_68 = (double)(CONCAT44(0x43300000,
                                     (int)*(short *)(*(int *)&menuPcs->field_0x848 + 2) +
                                     *(short *)(*(int *)&menuPcs->field_0x848 + 6) + -0x3e) ^
                           0x80000000);
        dVar15 = (double)(float)(local_68 - DOUBLE_80331408);
        uStack_6c = GetYesNoXPos__8CMenuPcsFi
                              (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26));
        uStack_6c = uStack_6c ^ 0x80000000;
        iVar8 = *(int *)&menuPcs->field_0x82c;
        local_70 = 0x43300000;
        dVar16 = (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408);
        if (*(short *)(iVar8 + 0x16) == 0x19) {
          sVar2 = *(short *)(iVar8 + 0x2e);
          if (sVar2 < 0) {
            if (sVar2 == -1) {
              *(undefined2 *)(iVar8 + 0x16) = 5;
            }
            else if (sVar2 == -2) {
              *(undefined2 *)(iVar8 + 0x16) = 8;
            }
            else if (sVar2 == -3) {
              *(undefined2 *)(iVar8 + 0x16) = 6;
            }
            else {
              *(undefined2 *)(iVar8 + 0x16) = 7;
            }
          }
        }
        else {
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
          local_180 = 0xffffffff;
          local_17c = 0xffffffff;
          GXSetChanMatColor(4,&local_17c);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
          local_68 = (double)(longlong)(int)dVar16;
          local_78 = (double)(longlong)(int)dVar15;
          uStack_6c = (int)dVar16 ^ 0x80000000;
          local_70 = 0x43300000;
          local_80 = (double)CONCAT44(0x43300000,(int)dVar15 ^ 0x80000000);
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408),
                     (double)(float)(local_80 - DOUBLE_80331408),(double)FLOAT_80331410,
                     (double)FLOAT_80331410,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
                     (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
        }
      }
      if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
        iVar8 = *(int *)&menuPcs->field_0x82c;
        sVar1 = *(short *)(iVar8 + 0x16);
        if (sVar1 == 0x12) {
          if (*(short *)(iVar8 + 0xe) < 0) {
            *(undefined2 *)(iVar8 + 0x16) = 0x11;
            *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) =
                 (short)(menuPcs->m_mcCtrl).m_saveIndex;
          }
          else {
            *(undefined2 *)(iVar8 + 0x16) = 0x13;
          }
        }
        else {
          sVar2 = *(short *)(iVar8 + 0x2e);
          if (sVar2 < 0) {
            if (sVar2 == -1) {
              *(undefined2 *)(iVar8 + 0x16) = 5;
            }
            else if (sVar2 == -2) {
              *(undefined2 *)(iVar8 + 0x16) = 8;
            }
            else if (sVar2 == -3) {
              *(undefined2 *)(iVar8 + 0x16) = 6;
            }
            else {
              *(undefined2 *)(iVar8 + 0x16) = 7;
            }
          }
          else if (*(short *)(iVar8 + 0xe) < 0) {
            if (sVar1 == 0x19) {
              *(undefined2 *)(iVar8 + 0x16) = 0x11;
              *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) =
                   (short)(menuPcs->m_mcCtrl).m_saveIndex;
            }
            else {
              *(undefined2 *)(iVar8 + 0x16) = 2;
            }
          }
          else if (sVar1 == 8) {
            *(undefined2 *)(iVar8 + 0x16) = 0xb;
          }
          else if (sVar1 == 0x19) {
            *(undefined2 *)(iVar8 + 0x16) = 0x1a;
          }
          else {
            *(undefined2 *)(iVar8 + 0x16) = 0xd;
          }
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
        iVar8 = *(int *)&menuPcs->field_0x82c;
        sVar1 = *(short *)(iVar8 + 0x2e);
        if (sVar1 == -1) {
          *(undefined2 *)(iVar8 + 0x16) = 10;
        }
        else if (sVar1 == -2) {
          *(undefined2 *)(iVar8 + 0x16) = 8;
        }
        else if (sVar1 == -3) {
          *(undefined2 *)(iVar8 + 0x16) = 8;
        }
        else if (sVar1 == -4) {
          *(undefined2 *)(iVar8 + 0x16) = 7;
        }
        else if (sVar1 == -999) {
          *(undefined2 *)(iVar8 + 0x1e) = 0xffff;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 1;
          *(undefined2 *)&menuPcs->field_0x870 = 2;
        }
        else {
          BindMcObj__8CMenuPcsFv(menuPcs);
          puVar6 = menuPcs->m_unk0x838;
          uVar3 = 0;
          if (((*(char *)((int)puVar6 + 0x42) == '\0') &&
              (uVar3 = 1, *(char *)((int)puVar6 + 0x8a) == '\0')) &&
             ((uVar3 = 2, *(char *)((int)puVar6 + 0xd2) == '\0' &&
              (uVar3 = 3, *(char *)((int)puVar6 + 0x11a) == '\0')))) {
            uVar3 = 4;
          }
          if (uVar3 < 4) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 0x19;
          }
          else {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 0x11;
          }
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)(menuPcs->m_mcCtrl).m_saveIndex;
        }
      }
      break;
    case 0xd:
    case 0x13:
    case 0x1a:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
      DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
      if (sVar1 == 1) {
        uVar4 = 0;
        sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
        if (sVar1 == 0xd) {
          uVar9 = 7;
        }
        else if (sVar1 == 0x1a) {
          uVar9 = 0x1a;
          uVar4 = 1;
        }
        else {
          uVar9 = 8;
        }
        DrawMcWinMess__8CMenuPcsFii(menuPcs,uVar9,uVar4);
      }
      else if ((sVar1 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
        iVar8 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar8 + 0x16) == 0xd) {
          if (*(short *)(iVar8 + 0x2e) == 1) {
            *(undefined2 *)(iVar8 + 0x16) = 0xe;
          }
          else if (*(short *)(iVar8 + 0x2e) == -2) {
            *(undefined2 *)(iVar8 + 0x16) = 7;
          }
          else {
            *(undefined2 *)(iVar8 + 0x16) = 0xf;
          }
        }
        else if (*(short *)(iVar8 + 0x16) == 0x1a) {
          if (*(short *)(iVar8 + 0x2e) == 1) {
            *(undefined2 *)(iVar8 + 0x16) = 0x1c;
          }
          else if (*(short *)(iVar8 + 0x2e) == -2) {
            *(undefined2 *)(iVar8 + 0x16) = 7;
          }
          else {
            *(undefined2 *)(iVar8 + 0x16) = 0x1b;
          }
        }
        else if (*(short *)(iVar8 + 0x2e) == 1) {
          *(undefined *)(iVar8 + 10) = 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 0x15;
          PlaySe__6CSoundFiiii(&Sound,0x41,0x40,0x7f,0);
        }
        else if (*(short *)(iVar8 + 0x2e) == -4) {
          *(undefined2 *)(iVar8 + 0x16) = 7;
        }
        else {
          *(undefined2 *)(iVar8 + 0x16) = 0x14;
        }
      }
      break;
    case 0x11:
      if (*(short *)(iVar8 + 0x2e) < 0) {
        *(undefined2 *)(iVar8 + 0x16) = 3;
      }
      else if (*(short *)(iVar8 + 0xe) != 0) {
        if (*(short *)(iVar8 + 0xe) < 0) {
          if (*(char *)(iVar8 + 10) == '\0') {
            *(undefined2 *)(iVar8 + 0x16) = 2;
          }
          else {
            *(undefined2 *)(iVar8 + 0x1e) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 10;
          }
        }
        else if (*(char *)((int)menuPcs->m_unk0x838 + (menuPcs->m_mcCtrl).m_saveIndex * 0x48 + 0x41)
                 == '\0') {
          *(undefined2 *)(iVar8 + 0x16) = 0x13;
        }
        else {
          *(undefined2 *)(iVar8 + 0x16) = 0x12;
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
    if ((sVar7 == 2) && (*(short *)(iVar8 + 0x18) != 0)) {
      *(short *)(iVar8 + 0x18) = *(short *)(iVar8 + 0x18) + -1;
      iVar8 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar8 + 0x18) < 1) {
        *(short *)(iVar8 + 0x10) = *(short *)(iVar8 + 0x10) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        PlaySe__6CSoundFiiii(&Sound,0x32,0x40,0x7f,0);
      }
    }
  }
  else {
    *(short *)(iVar8 + 0x22) = *(short *)(iVar8 + 0x22) + 1;
    iVar8 = *(int *)&menuPcs->field_0x82c;
    if ((*(short *)(iVar8 + 0x10) == 3) && (*(short *)(iVar8 + 0x16) != 0)) {
      sVar7 = 0x13;
    }
    else {
      sVar7 = 10;
    }
    if (sVar7 <= *(short *)(iVar8 + 0x22)) {
      *(short *)(iVar8 + 0x10) = *(short *)(iVar8 + 0x10) + 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      iVar8 = *(int *)&menuPcs->field_0x82c;
      if (4 < *(short *)(iVar8 + 0x10)) {
        *(undefined2 *)(iVar8 + 0x20) = *(undefined2 *)(iVar8 + 0x1e);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0;
      }
    }
  }
  return;
}

