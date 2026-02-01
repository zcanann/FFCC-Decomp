// Function: DrawChara__8CMenuPcsFv
// Entry: 800f2034
// Size: 1728 bytes

void DrawChara__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  undefined uVar2;
  Vec *pVVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined *puVar9;
  int *piVar10;
  int iVar11;
  CMenuPcs *pCVar12;
  int iVar13;
  uint uVar14;
  double dVar15;
  double dVar16;
  undefined4 local_1b0;
  undefined auStack_1ac [4];
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined auStack_19c [4];
  undefined4 local_198;
  undefined4 local_194;
  CVector CStack_190;
  CVector CStack_184;
  CVector CStack_178;
  CVector CStack_16c;
  Mat4x4 MStack_160;
  Mtx MStack_120;
  Mat4x4 MStack_f0;
  Mtx MStack_b0;
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  undefined4 local_68;
  uint uStack_64;
  longlong local_60;
  longlong local_58;
  longlong local_50;
  longlong local_48;
  
  iVar13 = 0;
  puVar9 = &menuPcs->field_0x80;
  iVar11 = 0xa00;
  piVar10 = (int *)(*(int *)&menuPcs->field_0x814 + 0xa00);
  pCVar12 = menuPcs;
  do {
    if (*piVar10 != 0) {
      uVar14 = 0;
      iVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + 4);
      if (((*(char *)(*(int *)&menuPcs->field_0x828 + 0xd) == '\x01') && (-1 < iVar6)) &&
         (iVar13 == iVar6)) {
        uVar14 = 1;
      }
      iVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x14);
      if (((*(char *)(*(int *)&menuPcs->field_0x828 + 0x1d) == '\x01') && (-1 < iVar6)) &&
         (iVar13 == iVar6)) {
        uVar14 = uVar14 | 2;
      }
      iVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x24);
      if (((*(char *)(*(int *)&menuPcs->field_0x828 + 0x2d) == '\x01') && (-1 < iVar6)) &&
         (iVar13 == iVar6)) {
        uVar14 = uVar14 | 4;
      }
      iVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x34);
      if (((*(char *)(*(int *)&menuPcs->field_0x828 + 0x3d) == '\x01') && (-1 < iVar6)) &&
         (iVar13 == iVar6)) {
        uVar14 = uVar14 | 8;
      }
      if ((**(int **)&pCVar12->field_0x7f4 == 3) || (-1 < (*(int **)&pCVar12->field_0x7f4)[0x44])) {
        iVar6 = *(int *)&menuPcs->field_0x814 + iVar11;
        C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,
                         (Mtx *)&MStack_f0);
        GXSetProjection(&MStack_f0,0);
        PSMTX44Copy(&MStack_f0,&CameraPcs.m_screenMatrix);
        pVVar3 = (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_16c)
        ;
        uVar4 = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_178);
        C_MTXLookAt(&MStack_b0,(Vec *)(iVar6 + 0x10),uVar4,pVVar3);
        PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
        PSMTXCopy(&MStack_b0,&CameraPcs.m_cameraMatrix);
        InitEnv__9CCharaPcsFi(&CharaPcs,5);
        GXSetColorUpdate(0);
        GXSetAlphaUpdate(0);
        puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_19c,0,0,0,0);
        local_1a0 = *puVar5;
        GXSetCopyClear(&local_1a0,0xffffff);
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(1);
        uStack_7c = (int)*(short *)(iVar6 + 8) ^ 0x80000000;
        uStack_74 = (int)*(short *)(iVar6 + 10) ^ 0x80000000;
        uStack_6c = (int)*(short *)(iVar6 + 0xc) ^ 0x80000000;
        uStack_64 = (int)*(short *)(iVar6 + 0xe) ^ 0x80000000;
        local_80 = 0x43300000;
        local_78 = 0x43300000;
        local_70 = 0x43300000;
        local_68 = 0x43300000;
        GXSetViewport((double)(float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331408),
                      (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331408),
                      (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408),
                      (double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408),
                      (double)FLOAT_803313dc,(double)FLOAT_803313e8);
        GXSetScissor(*(undefined4 *)(iVar6 + 0x40),*(undefined4 *)(iVar6 + 0x44),
                     *(undefined4 *)(iVar6 + 0x48),*(undefined4 *)(iVar6 + 0x4c));
        SetFog__8CGraphicFii(&Graphic,1,0);
        local_1a8 = DAT_80210830;
        SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_1a8);
        SetNumDiffuse__9CLightPcsFUl(&LightPcs,DAT_8021082c);
        puVar7 = &DAT_8021082c;
        puVar5 = puVar7;
        for (iVar6 = 0; iVar6 < DAT_8021082c; iVar6 = iVar6 + 1) {
          local_1a4 = puVar5[2];
          SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs,iVar6,&local_1a4,puVar7 + 5,0);
          puVar5 = puVar5 + 1;
          puVar7 = puVar7 + 3;
        }
        SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
        if (**(int **)&pCVar12->field_0x7f4 == 3) {
          DrawInit__8CMenuPcsFv(menuPcs);
          GXSetZMode(1,7,1);
          iVar6 = *(int *)&menuPcs->field_0x814 + iVar11;
          C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,
                           (Mtx *)&MStack_160);
          GXSetProjection(&MStack_160,0);
          PSMTX44Copy(&MStack_160,&CameraPcs.m_screenMatrix);
          pVVar3 = (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,
                                             &CStack_184);
          uVar4 = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_190);
          C_MTXLookAt(&MStack_120,(Vec *)(iVar6 + 0x10),uVar4,pVVar3);
          PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
          PSMTXCopy(&MStack_120,&CameraPcs.m_cameraMatrix);
          InitEnv__9CCharaPcsFi(&CharaPcs,5);
          GXSetColorUpdate(0);
          GXSetAlphaUpdate(0);
          puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_1ac,0,0,0,0);
          local_1b0 = *puVar5;
          GXSetCopyClear(&local_1b0,0xffffff);
          GXSetColorUpdate(1);
          GXSetAlphaUpdate(1);
          uStack_64 = (int)*(short *)(iVar6 + 8) ^ 0x80000000;
          uStack_6c = (int)*(short *)(iVar6 + 10) ^ 0x80000000;
          uStack_74 = (int)*(short *)(iVar6 + 0xc) ^ 0x80000000;
          uStack_7c = (int)*(short *)(iVar6 + 0xe) ^ 0x80000000;
          local_68 = 0x43300000;
          local_70 = 0x43300000;
          local_78 = 0x43300000;
          local_80 = 0x43300000;
          GXSetViewport((double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331408),
                        (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408),
                        (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331408),
                        (double)(float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331408),
                        (double)FLOAT_803313dc,(double)FLOAT_803313e8);
          GXSetScissor(*(undefined4 *)(iVar6 + 0x40),*(undefined4 *)(iVar6 + 0x44),
                       *(undefined4 *)(iVar6 + 0x48),*(undefined4 *)(iVar6 + 0x4c));
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x32);
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
          fVar1 = FLOAT_803313e8;
          if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) != 2) {
            fVar1 = *(float *)(*(int *)(*(int *)&pCVar12->field_0x7f4 + 0x168) + 0x9c);
          }
          dVar15 = DOUBLE_80331448;
          if (uVar14 != 0) {
            dVar15 = DOUBLE_80331420;
          }
          local_48 = (longlong)(int)(DOUBLE_80331508 * (double)fVar1);
          local_60 = (longlong)(int)(FLOAT_80331458 * (float)dVar15);
          uVar2 = (undefined)(int)(FLOAT_80331458 * (float)dVar15);
          local_198 = CONCAT31(CONCAT21(CONCAT11(uVar2,uVar2),uVar2),
                               (char)(int)(DOUBLE_80331508 * (double)fVar1));
          local_194 = local_198;
          local_58 = local_60;
          local_50 = local_60;
          GXSetChanMatColor(4,&local_198);
          dVar16 = (double)FLOAT_803314cc;
          dVar15 = (double)(FLOAT_8033161c - FLOAT_8033168c);
          if (uVar14 != 0) {
            dVar15 = (double)(float)(dVar15 * (double)FLOAT_803315d4);
            dVar16 = (double)(float)(dVar16 * (double)FLOAT_803315d4);
          }
          DrawRect3d__8CMenuPcsFUlfffffffff
                    (dVar15,dVar16,(double)FLOAT_80331694,(double)FLOAT_80331578,
                     (double)FLOAT_80331520,(double)FLOAT_803313dc,(double)FLOAT_803313dc,&MenuPcs,0
                    );
          GXSetZMode(1,3,1);
        }
        else {
          Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)(puVar9 + 0x774),5);
        }
        if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) && (uVar14 != 0)) {
          iVar6 = 3;
          iVar8 = 0xf6c;
          do {
            if ((uVar14 & 1 << iVar6) != 0) {
              DrawMenuIdx__8CPartPcsFi
                        (&PartPcs,*(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar8 + 0xa484));
            }
            iVar6 = iVar6 + -1;
            iVar8 = iVar8 + -0x524;
          } while (-1 < iVar6);
        }
      }
    }
    iVar13 = iVar13 + 1;
    iVar11 = iVar11 + 0x50;
    puVar9 = puVar9 + 4;
    piVar10 = piVar10 + 0x14;
    pCVar12 = (CMenuPcs *)&pCVar12->field_0x4;
  } while (iVar13 < 8);
  DrawInit__8CMenuPcsFv(menuPcs);
  return;
}

