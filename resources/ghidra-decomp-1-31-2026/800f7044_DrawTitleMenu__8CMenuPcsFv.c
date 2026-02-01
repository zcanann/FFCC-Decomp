// Function: DrawTitleMenu__8CMenuPcsFv
// Entry: 800f7044
// Size: 3768 bytes

/* WARNING: Removing unreachable block (ram,0x800f7ee0) */
/* WARNING: Removing unreachable block (ram,0x800f7ed8) */
/* WARNING: Removing unreachable block (ram,0x800f7ed0) */
/* WARNING: Removing unreachable block (ram,0x800f7ec8) */
/* WARNING: Removing unreachable block (ram,0x800f706c) */
/* WARNING: Removing unreachable block (ram,0x800f7064) */
/* WARNING: Removing unreachable block (ram,0x800f705c) */
/* WARNING: Removing unreachable block (ram,0x800f7054) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawTitleMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  Vec *targetPosition;
  undefined4 cameraUp;
  undefined4 *puVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  uint local_1c0;
  uint local_1bc;
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined auStack_194 [4];
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  int local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  CVector CStack_158;
  CVector CStack_14c;
  Vec local_140;
  Mat4x4 MStack_134;
  Mtx MStack_f4;
  Mat4x4 MStack_c4;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined4 local_60;
  uint uStack_5c;
  
  if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 0) &&
     (*(char *)(*(int *)&menuPcs->field_0x82c + 8) != '\0')) {
    if (menuPcs->field_0x858 != '\0') {
      THPSimpleDrawCurrentFrame(DAT_80238028,0,0,0x280,0x1c0);
      _WaitDrawDone__8CGraphicFPci(&Graphic,s_wm_menu_cpp_801dc418,0x12a2);
    }
    sVar4 = *(short *)(*(int *)&menuPcs->field_0x82c + 0xe);
    if ((sVar4 != 0) || (0xb42 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x22))) {
      if (sVar4 != -1) {
        THPSimpleAudioStop();
        THPSimpleLoadStop();
        THPSimpleClose();
        THPSimpleQuit();
        if (*(int *)&menuPcs->field_0x854 != 0) {
          Free__7CMemoryFPv(&Memory);
          *(undefined4 *)&menuPcs->field_0x854 = 0;
        }
        menuPcs->field_0x858 = 0;
      }
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x10) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x10) + 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
      local_164 = 9;
      local_160 = 0;
      local_15c = 0;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,0,1,4,3,&local_164,(CStack *)0x0);
    }
  }
  else {
    C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,(Mtx *)&MStack_c4);
    GXSetProjection(&MStack_c4,0);
    PSMTX44Copy(&MStack_c4,&CameraPcs.m_screenMatrix);
    local_140.x = FLOAT_803313dc;
    local_140.y = FLOAT_803313dc;
    local_140.z = FLOAT_80331768;
    targetPosition =
         (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_158);
    cameraUp = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_14c);
    C_MTXLookAt(&MStack_f4,&local_140,cameraUp,targetPosition);
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
    PSMTXCopy(&MStack_f4,&CameraPcs.m_cameraMatrix);
    InitEnv__9CCharaPcsFi(&CharaPcs,5);
    GXSetColorUpdate(0);
    GXSetAlphaUpdate(0);
    puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_194,0,0,0,0);
    local_190 = *puVar2;
    GXSetCopyClear(&local_190,0xffffff);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    dVar8 = (double)FLOAT_803313dc;
    GXSetViewport(dVar8,dVar8,(double)FLOAT_803313e0,(double)FLOAT_803313e4,dVar8,
                  (double)FLOAT_803313e8);
    DrawMenuIdx__8CPartPcsFi(&PartPcs,*(undefined4 *)(*(int *)&menuPcs->field_0x840 + 0x7640));
    PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
    local_1b0 = DAT_802381a7;
    GXSetCopyClear(&local_1b0,0xffffff);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_134);
    GXSetProjection(&MStack_134,0);
    SetViewport__8CGraphicFv(&Graphic);
    GXSetScissor(0,0,0x280,0x1c0);
    DrawInit__8CMenuPcsFv(menuPcs);
    if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 1) && (DAT_8032e8ac == '\0')) {
      local_80 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22))
                         ^ 0x80000000);
      dVar8 = (double)(float)-(DOUBLE_80331770 * (local_80 - DOUBLE_80331408) - DOUBLE_80331420);
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(menuPcs,2);
      local_78 = (double)(longlong)(int)((double)FLOAT_80331458 * dVar8);
      local_1b8 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331458 * dVar8));
      local_1b4 = local_1b8;
      GXSetChanMatColor(4,&local_1b4);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0xffffffff);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
      GXBegin(0x80,0,4);
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313e0;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313e0;
      DAT_cc008000 = FLOAT_803313e4;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313e4;
      DAT_cc008000 = FLOAT_803313dc;
    }
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    dVar8 = (double)SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x43);
    iVar5 = *(int *)&menuPcs->field_0x82c;
    if (1 < *(short *)(iVar5 + 0x10)) {
      dVar11 = (double)(FLOAT_80331778 - FLOAT_80331414);
      fVar1 = FLOAT_8033177c;
      if (*(short *)(iVar5 + 0x26) != 0) {
        local_78 = (double)(CONCAT44(0x43300000,*(short *)(iVar5 + 0x26) * 0x28 + -8) ^ 0x80000000);
        fVar1 = FLOAT_8033177c + (float)(local_78 - DOUBLE_80331408);
        dVar8 = DOUBLE_80331408;
      }
      dVar12 = (double)(fVar1 - FLOAT_80331780);
      fVar1 = FLOAT_803313e8;
      if ((*(short *)(iVar5 + 0x10) == 2) && (*(short *)(iVar5 + 0x12) == 0)) {
        local_80 = (double)(CONCAT44(0x43300000,5 - *(short *)(iVar5 + 0x24)) ^ 0x80000000);
        local_78 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar5 + 0x24) ^ 0x80000000);
        dVar11 = (double)(float)-(DOUBLE_80331790 * ((local_80 - DOUBLE_80331408) / DOUBLE_80331798)
                                 - dVar11);
        dVar8 = DOUBLE_80331790;
        fVar1 = (float)(DOUBLE_80331788 * (local_78 - DOUBLE_80331408) + DOUBLE_803314e8);
      }
      dVar9 = (double)fVar1;
      local_78 = (double)(longlong)(int)((double)FLOAT_80331458 * dVar9);
      local_18c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331458 * dVar9));
      local_198 = local_18c;
      GXSetChanMatColor(dVar8,4,&local_198);
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar11,dVar12,(double)FLOAT_80331568,(double)FLOAT_80331554,(double)FLOAT_803313dc,
                 (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
      dVar8 = (double)_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp
                                (1,4,1,5);
      iVar5 = *(int *)&menuPcs->field_0x82c;
      sVar4 = *(short *)(iVar5 + 0x10);
      dVar11 = (double)(FLOAT_80331778 - FLOAT_80331414);
      if ((sVar4 == 2) && (*(short *)(iVar5 + 0x12) == 0)) {
        local_78 = (double)(CONCAT44(0x43300000,5 - *(short *)(iVar5 + 0x24)) ^ 0x80000000);
        dVar8 = local_78 - DOUBLE_80331408;
        dVar11 = (double)(float)(DOUBLE_80331790 * (dVar8 / DOUBLE_80331798) + dVar11);
      }
      else if (((sVar4 == 2) && (*(short *)(iVar5 + 0x18) == 0)) ||
              ((sVar4 == 3 && (*(short *)(iVar5 + 0xe) == 0)))) {
        iVar3 = (int)*(short *)(iVar5 + 0x24);
        iVar5 = iVar3 / 0x28 + (iVar3 >> 0x1f);
        uVar7 = (iVar3 + (iVar5 - (iVar5 >> 0x1f)) * -0x28) - 0x14;
        uVar6 = (int)uVar7 >> 0x1f;
        local_78 = (double)(CONCAT44(0x43300000,(uVar6 ^ uVar7) - uVar6) ^ 0x80000000);
        dVar8 = local_78 - DOUBLE_80331408;
        dVar9 = (double)(float)-(DOUBLE_803317a0 * dVar8 - DOUBLE_80331420);
      }
      else {
        dVar9 = (double)FLOAT_803313e8;
      }
      local_78 = (double)(longlong)(int)((double)FLOAT_80331458 * dVar9);
      local_18c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331458 * dVar9));
      local_19c = local_18c;
      GXSetChanMatColor(dVar8,4,&local_19c);
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar11,dVar12,(double)FLOAT_80331568,(double)FLOAT_80331554,(double)FLOAT_803313dc,
                 (double)FLOAT_80331554,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    }
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    dVar11 = (double)FLOAT_80331458;
    dVar12 = (double)FLOAT_803313dc;
    iVar5 = 0;
    uVar7 = 0xfffffff8;
    uVar6 = 0x70;
    dVar8 = DOUBLE_80331408;
    do {
      fVar1 = FLOAT_803313e8;
      if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 1) {
        local_78 = (double)(CONCAT44(0x43300000,
                                     (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22)) ^
                           0x80000000);
        fVar1 = (float)(DOUBLE_80331770 * (local_78 - DOUBLE_80331408));
      }
      local_80 = (double)(longlong)(int)(dVar11 * (double)fVar1);
      local_18c = CONCAT31(0xffffff,(char)(int)(dVar11 * (double)fVar1));
      local_1a0 = local_18c;
      GXSetChanMatColor(4,&local_1a0);
      dVar9 = (double)FLOAT_8033177c;
      if (iVar5 != 0) {
        local_70 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
        dVar9 = (double)(float)(dVar9 + (double)(float)(local_70 - DOUBLE_80331408));
      }
      local_68 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)FLOAT_80331778,dVar9,(double)FLOAT_80331568,(double)FLOAT_80331440,dVar12,
                 (double)(float)(local_68 - dVar8),(double)FLOAT_803313e8,(double)FLOAT_803313e8,
                 &MenuPcs,0);
      iVar3 = *(int *)&menuPcs->field_0x82c;
      if ((*(char *)(iVar3 + 9) == '\0') && (iVar5 == *(short *)(iVar3 + 0x26))) {
        local_70 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x24)) ^ 0x80000000);
        local_68 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x24) ^ 0x80000000);
        dVar10 = (double)(float)(DOUBLE_803317a8 * (local_68 - DOUBLE_80331408) +
                                (double)FLOAT_803313e8);
        iVar3 = (int)(FLOAT_80331458 *
                     (float)-(DOUBLE_803317b0 * (local_70 - DOUBLE_80331408) - DOUBLE_80331420));
        local_78 = (double)(longlong)iVar3;
        local_18c = CONCAT31(0xffffff,(char)iVar3);
        local_1a4 = local_18c;
        GXSetChanMatColor(local_68 - DOUBLE_80331408,DOUBLE_803317a8,4,&local_1a4);
        dVar9 = (double)(FLOAT_8033177c -
                        (float)((double)FLOAT_80331440 * dVar10 - (double)FLOAT_80331440));
        if (iVar5 != 0) {
          local_80 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
          dVar9 = (double)(float)(dVar9 + (double)(float)(local_80 - DOUBLE_80331408));
        }
        uStack_5c = uVar6 ^ 0x80000000;
        local_60 = 0x43300000;
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)(-(double)(float)((double)FLOAT_80331568 * dVar10 -
                                                   (double)FLOAT_803313e0) * DOUBLE_803313f8),dVar9,
                   (double)FLOAT_80331568,(double)FLOAT_80331440,(double)FLOAT_803313dc,
                   (double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408),dVar10,
                   dVar10,&MenuPcs,0);
      }
      iVar5 = iVar5 + 1;
      uVar6 = uVar6 + 0x28;
      uVar7 = uVar7 + 0x28;
    } while (iVar5 < 2);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_18c = 0xffffffff;
    local_1a8 = 0xffffffff;
    GXSetChanMatColor(4,&local_1a8);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x42);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_803317b8,(double)FLOAT_803317bc,(double)FLOAT_803317c0,
               (double)FLOAT_803315b4,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
               (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x44);
    fVar1 = FLOAT_803313e8;
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 1) {
      local_60 = 0x43300000;
      uStack_5c = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^ 0x80000000;
      fVar1 = (float)(DOUBLE_80331770 * ((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408));
    }
    local_68 = (double)(longlong)(int)(FLOAT_80331458 * fVar1);
    local_18c = CONCAT31(0xffffff,(char)(int)(FLOAT_80331458 * fVar1));
    local_1ac = local_18c;
    GXSetChanMatColor(4,&local_1ac);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_803317c4,(double)FLOAT_803317c8,(double)FLOAT_803317cc,
               (double)FLOAT_80331440,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
               (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
    iVar5 = *(int *)&menuPcs->field_0x82c;
    if (1 < *(short *)(iVar5 + 0x10)) {
      *(short *)(iVar5 + 0x24) = *(short *)(iVar5 + 0x24) + 1;
      iVar5 = *(int *)&menuPcs->field_0x82c;
      if ((*(short *)(iVar5 + 0x12) == 0) && (4 < *(short *)(iVar5 + 0x24))) {
        *(undefined *)(iVar5 + 9) = 1;
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0x14;
      }
    }
    iVar5 = *(int *)&menuPcs->field_0x82c;
    sVar4 = *(short *)(iVar5 + 0x10);
    if ((sVar4 == 3) || ((sVar4 == 1 && (DAT_8032e8ac != '\0')))) {
      if (sVar4 == 3) {
        local_60 = 0x43300000;
        uStack_5c = (int)*(short *)(iVar5 + 0x22) + 1U ^ 0x80000000;
        dVar8 = DOUBLE_803314e8 * ((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408);
      }
      else {
        local_68 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar5 + 0x22)) ^ 0x80000000);
        dVar8 = -(DOUBLE_80331770 * (local_68 - DOUBLE_80331408) - DOUBLE_80331420);
      }
      dVar11 = (double)(float)dVar8;
      if ((double)FLOAT_803313e8 <= (double)(float)dVar8) {
        dVar11 = (double)FLOAT_803313e8;
      }
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(menuPcs,2);
      local_70 = (double)(longlong)(int)((double)FLOAT_80331458 * dVar11);
      local_1c0 = (int)((double)FLOAT_80331458 * dVar11) & 0xff;
      local_1bc = local_1c0;
      GXSetChanMatColor(4,&local_1bc);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0xffffffff);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
      GXBegin(0x80,0,4);
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313e0;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313e0;
      DAT_cc008000 = FLOAT_803313e4;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313dc;
      DAT_cc008000 = FLOAT_803313e4;
      DAT_cc008000 = FLOAT_803313dc;
    }
    iVar5 = *(int *)&menuPcs->field_0x82c;
    sVar4 = *(short *)(iVar5 + 0x10);
    if ((sVar4 == 3) && (9 < *(short *)(iVar5 + 0x22))) {
      pppDeletePart__8CPartMngFi(&PartMng,*(undefined4 *)(*(int *)&menuPcs->field_0x840 + 0x7640));
      if (*(short *)(*(int *)&menuPcs->field_0x82c + 0xe) == 0) {
        DAT_8032e8ac = '\0';
      }
      else {
        DAT_8032e8ac = '\x01';
        local_16c = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x20) = 1;
        local_170 = 7;
        local_168 = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,4,3,&local_170,(CStack *)0x0);
        menuPcs->field_0xd = 0;
      }
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
    }
    else if (sVar4 == 2) {
      if ((sVar4 == 2) && (*(short *)(iVar5 + 0x18) != 0)) {
        *(short *)(iVar5 + 0x18) = *(short *)(iVar5 + 0x18) + -1;
        iVar5 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar5 + 0x18) < 1) {
          *(short *)(iVar5 + 0x10) = *(short *)(iVar5 + 0x10) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
          local_17c = 9;
          local_178 = 1;
          local_174 = 0;
          SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                    (&CFlat,0,1,4,3,&local_17c,(CStack *)0x0);
        }
      }
      else if ((*(short *)(iVar5 + 0x18) == 0) && (0x991 < *(short *)(iVar5 + 0x22))) {
        *(undefined2 *)(iVar5 + 0xe) = 0;
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x10) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x10) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
        local_188 = 9;
        local_184 = 1;
        local_180 = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,4,3,&local_188,(CStack *)0x0);
      }
    }
    else {
      sVar4 = 10;
      *(short *)(iVar5 + 0x22) = *(short *)(iVar5 + 0x22) + 1;
      iVar5 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar5 + 0x10) == 1) {
        sVar4 = 0x28;
      }
      if (sVar4 < *(short *)(iVar5 + 0x22)) {
        *(undefined2 *)(iVar5 + 0x22) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x10) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x10) + 1;
      }
    }
  }
  return;
}

