// Function: DrawMainMenuSub__8CMenuPcsFv
// Entry: 800ecff0
// Size: 2396 bytes

/* WARNING: Removing unreachable block (ram,0x800ed930) */
/* WARNING: Removing unreachable block (ram,0x800ed928) */
/* WARNING: Removing unreachable block (ram,0x800ed920) */
/* WARNING: Removing unreachable block (ram,0x800ed918) */
/* WARNING: Removing unreachable block (ram,0x800ed910) */
/* WARNING: Removing unreachable block (ram,0x800ed908) */
/* WARNING: Removing unreachable block (ram,0x800ed900) */
/* WARNING: Removing unreachable block (ram,0x800ed030) */
/* WARNING: Removing unreachable block (ram,0x800ed028) */
/* WARNING: Removing unreachable block (ram,0x800ed020) */
/* WARNING: Removing unreachable block (ram,0x800ed018) */
/* WARNING: Removing unreachable block (ram,0x800ed010) */
/* WARNING: Removing unreachable block (ram,0x800ed008) */
/* WARNING: Removing unreachable block (ram,0x800ed000) */

void DrawMainMenuSub__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  int iVar3;
  Vec *pVVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  uint *puVar10;
  int iVar11;
  uint *puVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  float *pfVar17;
  uint uVar18;
  CMenuPcs *pCVar19;
  undefined4 *puVar20;
  MMenuPos *pMVar21;
  int iVar22;
  int iVar23;
  uint *puVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  double dVar31;
  undefined4 local_340;
  undefined auStack_33c [4];
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined auStack_32c [4];
  undefined4 local_328;
  undefined auStack_324 [4];
  undefined4 local_320;
  undefined4 local_31c;
  CVector CStack_318;
  CVector CStack_30c;
  CVector CStack_300;
  CVector CStack_2f4;
  CVector CStack_2e8;
  CVector CStack_2dc;
  Vec4d local_2d0;
  Vec local_2c0;
  float local_2b4 [5];
  uint local_2a0 [5];
  Mat4x4 MStack_28c;
  Mtx MStack_24c;
  Mat4x4 MStack_21c;
  Mtx MStack_1dc;
  Mat4x4 MStack_1ac;
  Mtx MStack_16c;
  Mat4x4 MStack_13c;
  Mtx MStack_fc;
  undefined4 local_c8;
  uint uStack_c4;
  undefined4 local_c0;
  uint uStack_bc;
  undefined8 local_b8;
  undefined8 local_b0;
  
  iVar22 = *(int *)&menuPcs->field_0x814;
  C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,(Mtx *)&MStack_1ac);
  GXSetProjection(&MStack_1ac,0);
  PSMTX44Copy(&MStack_1ac,&CameraPcs.m_screenMatrix);
  pVVar4 = (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_2dc);
  uVar5 = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_2e8);
  C_MTXLookAt(&MStack_16c,(Vec *)(iVar22 + 0x740),uVar5,pVVar4);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
  PSMTXCopy(&MStack_16c,&CameraPcs.m_cameraMatrix);
  InitEnv__9CCharaPcsFi(&CharaPcs,5);
  GXSetColorUpdate(0);
  GXSetAlphaUpdate(0);
  puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_324,0,0,0,0);
  local_328 = *puVar6;
  GXSetCopyClear(&local_328,0xffffff);
  GXSetColorUpdate(1);
  GXSetAlphaUpdate(1);
  uStack_c4 = (int)*(short *)(iVar22 + 0x738) ^ 0x80000000;
  uStack_bc = (int)*(short *)(iVar22 + 0x73a) ^ 0x80000000;
  local_c8 = 0x43300000;
  local_c0 = 0x43300000;
  local_b8 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar22 + 0x73c) ^ 0x80000000);
  local_b0 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar22 + 0x73e) ^ 0x80000000);
  GXSetViewport((double)(float)((double)CONCAT44(0x43300000,uStack_c4) - DOUBLE_80331408),
                (double)(float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_80331408),
                (double)(float)(local_b8 - DOUBLE_80331408),
                (double)(float)(local_b0 - DOUBLE_80331408),(double)FLOAT_803313dc,
                (double)FLOAT_803313e8);
  GXSetScissor(*(undefined4 *)(iVar22 + 0x770),*(undefined4 *)(iVar22 + 0x774),
               *(undefined4 *)(iVar22 + 0x778),*(undefined4 *)(iVar22 + 0x77c));
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_13c);
  dVar29 = (double)FLOAT_80331598;
  pMVar21 = &s_MMenuPos;
  iVar23 = 0;
  iVar22 = 0;
  dVar26 = (double)FLOAT_803315b0;
  dVar27 = (double)FLOAT_803315b4;
  dVar28 = (double)FLOAT_803313dc;
  dVar25 = DOUBLE_803315a8;
  dVar30 = DOUBLE_803315a0;
  dVar31 = DOUBLE_80331420;
  do {
    local_2c0.x = ((Vec *)&pMVar21->field0_0x0[0].x)->x;
    local_2c0.z = (float)((double)pMVar21->field0_0x0[0].z - dVar29);
    local_2c0.y = pMVar21->field0_0x0[0].y;
    MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d(&Math,&MStack_13c,&local_2c0,&local_2d0);
    iVar23 = iVar23 + 1;
    iVar16 = iVar22 + 8;
    iVar15 = iVar22 + 10;
    iVar13 = iVar22 + 0xc;
    iVar11 = iVar22 + 0xe;
    iVar9 = iVar22 + 0x10;
    iVar7 = iVar22 + 0x14;
    iVar3 = iVar22 + 0x18;
    iVar22 = iVar22 + 0x50;
    pMVar21 = (MMenuPos *)((int)pMVar21 + 0xc);
    local_2d0.x = (float)(dVar30 * (dVar31 + (double)(local_2d0.x / local_2d0.w)));
    local_2d0.y = (float)(dVar25 * (dVar31 + -(double)(local_2d0.y / local_2d0.w)));
    local_b0 = (double)(longlong)(int)((double)local_2d0.x - dVar26);
    *(short *)(*(int *)&menuPcs->field_0x814 + iVar16) = (short)(int)((double)local_2d0.x - dVar26);
    local_b8 = (double)(longlong)(int)((double)local_2d0.y - dVar27);
    *(short *)(*(int *)&menuPcs->field_0x814 + iVar15) = (short)(int)((double)local_2d0.y - dVar27);
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar13) = 0x280;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar11) = 0x1c0;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar9) = (float)dVar28;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar7) = (float)dVar28;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar3) = (float)dVar29;
  } while (iVar23 < 5);
  pfVar17 = local_2b4;
  puVar24 = local_2a0;
  uVar18 = 0;
  pCVar19 = menuPcs;
  pfVar8 = pfVar17;
  puVar12 = puVar24;
  do {
    PSMTXCopy((Mtx *)(*(int *)(*(int *)&pCVar19->field_0x774 + 0x168) + 8),&MStack_fc);
    *puVar12 = uVar18;
    uVar18 = uVar18 + 1;
    pCVar19 = (CMenuPcs *)&pCVar19->field_0x4;
    puVar12 = puVar12 + 1;
    *pfVar8 = MStack_fc.value[2][3];
    pfVar8 = pfVar8 + 1;
  } while ((int)uVar18 < 5);
  iVar22 = 0;
  puVar12 = puVar24;
  do {
    iVar3 = iVar22 + 1;
    iVar23 = 5 - iVar3;
    pfVar8 = local_2b4 + iVar3;
    puVar10 = local_2a0 + iVar3;
    if (iVar3 < 5) {
      do {
        fVar1 = *pfVar17;
        if (*pfVar8 < fVar1) {
          uVar14 = *puVar12;
          uVar18 = *puVar10;
          *pfVar17 = *pfVar8;
          *puVar12 = uVar18;
          *pfVar8 = fVar1;
          *puVar10 = uVar14;
        }
        pfVar8 = pfVar8 + 1;
        puVar10 = puVar10 + 1;
        iVar23 = iVar23 + -1;
      } while (iVar23 != 0);
    }
    iVar22 = iVar22 + 1;
    puVar12 = puVar12 + 1;
    pfVar17 = pfVar17 + 1;
  } while (iVar22 < 5);
  iVar22 = 0;
  local_31c = 0xffffffff;
  do {
    sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
    if ((sVar2 < 1) || (3 < sVar2)) {
      if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) == 1) && (iVar22 == 1)) {
        *puVar24 = 1;
        goto LAB_800ed430;
      }
    }
    else {
LAB_800ed430:
      iVar23 = *(int *)&menuPcs->field_0x814 + *puVar24 * 0x50;
      C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,
                       (Mtx *)&MStack_21c);
      GXSetProjection(&MStack_21c,0);
      PSMTX44Copy(&MStack_21c,&CameraPcs.m_screenMatrix);
      pVVar4 = (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_2f4);
      uVar5 = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_300);
      C_MTXLookAt(&MStack_1dc,(Vec *)(iVar23 + 0x10),uVar5,pVVar4);
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
      PSMTXCopy(&MStack_1dc,&CameraPcs.m_cameraMatrix);
      InitEnv__9CCharaPcsFi(&CharaPcs,5);
      GXSetColorUpdate(0);
      GXSetAlphaUpdate(0);
      puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_32c,0,0,0,0);
      local_330 = *puVar6;
      GXSetCopyClear(&local_330,0xffffff);
      GXSetColorUpdate(1);
      GXSetAlphaUpdate(1);
      uStack_bc = (int)*(short *)(iVar23 + 0xc) ^ 0x80000000;
      uStack_c4 = (int)*(short *)(iVar23 + 0xe) ^ 0x80000000;
      local_b0 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar23 + 8) ^ 0x80000000);
      local_b8 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar23 + 10) ^ 0x80000000);
      local_c0 = 0x43300000;
      local_c8 = 0x43300000;
      GXSetViewport((double)(float)(local_b0 - DOUBLE_80331408),
                    (double)(float)(local_b8 - DOUBLE_80331408),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_80331408),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_c4) - DOUBLE_80331408),
                    (double)FLOAT_803313dc,(double)FLOAT_803313e8);
      GXSetScissor(*(undefined4 *)(iVar23 + 0x40),*(undefined4 *)(iVar23 + 0x44),
                   *(undefined4 *)(iVar23 + 0x48),*(undefined4 *)(iVar23 + 0x4c));
      SetFog__8CGraphicFii(&Graphic,1,0);
      local_338 = DAT_80210830;
      SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_338);
      SetNumDiffuse__9CLightPcsFUl(&LightPcs,DAT_8021082c);
      puVar20 = &DAT_8021082c;
      puVar6 = puVar20;
      for (iVar23 = 0; iVar23 < DAT_8021082c; iVar23 = iVar23 + 1) {
        local_334 = puVar6[2];
        SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs,iVar23,&local_334,puVar20 + 5,0);
        puVar6 = puVar6 + 1;
        puVar20 = puVar20 + 3;
      }
      SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
      Draw__Q29CCharaPcs7CHandleFi
                (*(undefined4 *)((int)(&menuPcs->m_cameraMatrix + 1) + *puVar24 * 4),5);
      DrawInit__8CMenuPcsFv(menuPcs);
      GXSetZMode(1,7,0);
      iVar23 = *(int *)&menuPcs->field_0x814 + *puVar24 * 0x50;
      C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,
                       (Mtx *)&MStack_28c);
      GXSetProjection(&MStack_28c,0);
      PSMTX44Copy(&MStack_28c,&CameraPcs.m_screenMatrix);
      pVVar4 = (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_30c);
      uVar5 = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_318);
      C_MTXLookAt(&MStack_24c,(Vec *)(iVar23 + 0x10),uVar5,pVVar4);
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
      PSMTXCopy(&MStack_24c,&CameraPcs.m_cameraMatrix);
      InitEnv__9CCharaPcsFi(&CharaPcs,5);
      GXSetColorUpdate(0);
      GXSetAlphaUpdate(0);
      puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_33c,0,0,0,0);
      local_340 = *puVar6;
      GXSetCopyClear(&local_340,0xffffff);
      GXSetColorUpdate(1);
      GXSetAlphaUpdate(1);
      uStack_bc = (int)*(short *)(iVar23 + 0xc) ^ 0x80000000;
      uStack_c4 = (int)*(short *)(iVar23 + 0xe) ^ 0x80000000;
      local_b0 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar23 + 8) ^ 0x80000000);
      local_b8 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar23 + 10) ^ 0x80000000);
      local_c0 = 0x43300000;
      local_c8 = 0x43300000;
      GXSetViewport((double)(float)(local_b0 - DOUBLE_80331408),
                    (double)(float)(local_b8 - DOUBLE_80331408),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_80331408),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_c4) - DOUBLE_80331408),
                    (double)FLOAT_803313dc,(double)FLOAT_803313e8);
      GXSetScissor(*(undefined4 *)(iVar23 + 0x40),*(undefined4 *)(iVar23 + 0x44),
                   *(undefined4 *)(iVar23 + 0x48),*(undefined4 *)(iVar23 + 0x4c));
      if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) {
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
        local_320 = local_31c;
        GXSetChanMatColor(4,&local_320);
        uVar18 = *puVar24;
        dVar25 = (double)*(float *)(uVar18 * 4 + -0x7fe23d6c);
        local_b0 = (double)CONCAT44(0x43300000,uVar18 ^ 0x80000000);
        DrawRect3d__8CMenuPcsFUlfffffffff
                  (-(double)(FLOAT_80331414 * (float)(dVar25 / (double)FLOAT_803315b8) -
                            FLOAT_803313dc),(double)FLOAT_803315bc,
                   (double)(float)((DOUBLE_80331418 + (double)s_MMenuPos.field0_0x0[uVar18].z) -
                                  DOUBLE_803315c0),dVar25,(double)FLOAT_80331554,
                   (double)FLOAT_803313dc,
                   (double)(float)((double)FLOAT_80331554 *
                                   (double)(float)(local_b0 - DOUBLE_80331408) +
                                  (double)FLOAT_80331528),&MenuPcs,0);
      }
    }
    iVar22 = iVar22 + 1;
    puVar24 = puVar24 + 1;
    if (4 < iVar22) {
      return;
    }
  } while( true );
}

