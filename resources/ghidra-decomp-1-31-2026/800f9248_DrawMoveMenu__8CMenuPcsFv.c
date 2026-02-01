// Function: DrawMoveMenu__8CMenuPcsFv
// Entry: 800f9248
// Size: 1652 bytes

/* WARNING: Removing unreachable block (ram,0x800f98a0) */
/* WARNING: Removing unreachable block (ram,0x800f9258) */

void DrawMoveMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  Vec *targetPosition;
  undefined4 cameraUp;
  undefined4 *puVar3;
  float *pfVar4;
  undefined4 *puVar5;
  double dVar6;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined auStack_150 [4];
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  CVector CStack_12c;
  CVector CStack_120;
  pppFVector4 pStack_110;
  Mat4x4 MStack_100;
  Mat4x4 MStack_c0;
  Mtx MStack_80;
  undefined8 local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (((sVar1 != 0) || (menuPcs->field_0x12 != '\0')) && (sVar1 < 4)) {
    DrawFukidashi__8CMenuPcsFv(menuPcs);
    iVar2 = *(int *)&menuPcs->field_0x82c;
    sVar1 = *(short *)(iVar2 + 0x10);
    if (sVar1 == 1) {
      local_50 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar2 + 0x22)) ^ 0x80000000);
      dVar6 = (double)(float)((local_50 - DOUBLE_80331408) / DOUBLE_803316e8);
    }
    else if ((sVar1 == 2) && (menuPcs->field_0x13 != '\0')) {
      local_50 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar2 + 0x22)) ^ 0x80000000);
      dVar6 = (double)(float)(DOUBLE_80331420 - (local_50 - DOUBLE_80331408) / DOUBLE_803316e8);
    }
    else {
      dVar6 = (double)FLOAT_803313e8;
    }
    if ((0 < sVar1) && (sVar1 < 3)) {
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      local_50 = (double)(longlong)(int)((double)FLOAT_80331458 * dVar6);
      local_14c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331458 * dVar6));
      local_148 = local_14c;
      GXSetChanMatColor(4,&local_148);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x23);
      dVar6 = (double)FLOAT_803313dc;
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar6,(double)(float)(DOUBLE_803314d0 - (double)FLOAT_80331440),
                 (double)FLOAT_803313e0,(double)FLOAT_80331440,dVar6,dVar6,(double)FLOAT_803313e8,
                 (double)FLOAT_803313e8,&MenuPcs,0);
    }
    DrawWMFrame__8CMenuPcsFv(menuPcs);
    sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
    if ((0 < sVar1) && (sVar1 < 3)) {
      iVar2 = *(int *)&menuPcs->field_0x814;
      C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,(Mtx *)&MStack_c0
                      );
      GXSetProjection(&MStack_c0,0);
      PSMTX44Copy(&MStack_c0,&CameraPcs.m_screenMatrix);
      targetPosition =
           (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_120);
      cameraUp = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_12c);
      C_MTXLookAt(&MStack_80,(Vec *)(iVar2 + 0x1a0),cameraUp,targetPosition);
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
      PSMTXCopy(&MStack_80,&CameraPcs.m_cameraMatrix);
      InitEnv__9CCharaPcsFi(&CharaPcs,5);
      GXSetColorUpdate(0);
      GXSetAlphaUpdate(0);
      puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_150,0,0,0,0);
      local_154 = *puVar3;
      GXSetCopyClear(&local_154,0xffffff);
      GXSetColorUpdate(1);
      GXSetAlphaUpdate(1);
      uStack_44 = (int)*(short *)(iVar2 + 0x19a) ^ 0x80000000;
      uStack_3c = (int)*(short *)(iVar2 + 0x19c) ^ 0x80000000;
      uStack_34 = (int)*(short *)(iVar2 + 0x19e) ^ 0x80000000;
      local_50 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar2 + 0x198) ^ 0x80000000);
      local_48 = 0x43300000;
      local_40 = 0x43300000;
      local_38 = 0x43300000;
      GXSetViewport((double)(float)(local_50 - DOUBLE_80331408),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331408),
                    (double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331408),
                    (double)FLOAT_803313dc,(double)FLOAT_803313e8);
      GXSetScissor(*(undefined4 *)(iVar2 + 0x1d0),*(undefined4 *)(iVar2 + 0x1d4),
                   *(undefined4 *)(iVar2 + 0x1d8),*(undefined4 *)(iVar2 + 0x1dc));
      SetFog__8CGraphicFii(&Graphic,1,0);
      local_15c = DAT_80210830;
      SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_15c);
      SetNumDiffuse__9CLightPcsFUl(&LightPcs,DAT_8021082c);
      puVar5 = &DAT_8021082c;
      puVar3 = puVar5;
      for (iVar2 = 0; iVar2 < DAT_8021082c; iVar2 = iVar2 + 1) {
        local_158 = puVar3[2];
        SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs,iVar2,&local_158,puVar5 + 5,0);
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 3;
      }
      SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
      *(undefined4 *)(*(int *)&menuPcs->field_0x840 + 0x1e70) =
           *(undefined4 *)(*(int *)(*(int *)&menuPcs->field_0x788 + 0x168) + 0x9c);
      Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)&menuPcs->field_0x788,5);
      sVar1 = *(short *)&menuPcs->field_0x88;
      GetParColIdx__8CPartPcsFiR11pppFVECTOR4(&PartPcs,(int)sVar1,&pStack_110);
      pStack_110.m_vector[3] = *(float *)(*(int *)(*(int *)&menuPcs->field_0x788 + 0x168) + 0x9c);
      SetParColIdx__8CPartPcsFiR11pppFVECTOR4(&PartPcs,(int)sVar1,&pStack_110);
      if (menuPcs->field_0x80 == '\0') {
        menuPcs->field_0x80 = 1;
      }
      else {
        DrawMenu__8CPartPcsFi(&PartPcs,*(undefined2 *)&menuPcs->field_0x8a);
      }
      PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
      local_160 = DAT_802381a7;
      GXSetCopyClear(&local_160,0xffffff);
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_100);
      GXSetProjection(&MStack_100,0);
      SetViewport__8CGraphicFv(&Graphic);
      GXSetScissor(0,0,0x280,0x1c0);
      DrawInit__8CMenuPcsFv(menuPcs);
    }
    iVar2 = *(int *)&menuPcs->field_0x82c;
    if ((*(short *)(iVar2 + 0x10) != 2) || (menuPcs->field_0x13 != '\0')) {
      *(short *)(iVar2 + 0x22) = *(short *)(iVar2 + 0x22) + 1;
    }
    pfVar4 = *(float **)&menuPcs->field_0x82c;
    sVar1 = *(short *)(pfVar4 + 4);
    if ((sVar1 == 0) || ((sVar1 == 2 && (menuPcs->field_0x13 != '\0')))) {
      if ((double)*pfVar4 <= DOUBLE_803314f0) {
        *(short *)(pfVar4 + 4) = *(short *)(pfVar4 + 4) + 1;
        *(undefined4 *)(*(int *)&menuPcs->field_0x81c + 4) = 0;
        *(undefined4 *)(*(int *)&menuPcs->field_0x81c + 8) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      }
    }
    else if ((sVar1 == 1) && (9 < *(short *)((int)pfVar4 + 0x22))) {
      *(short *)(pfVar4 + 4) = *(short *)(pfVar4 + 4) + 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      local_138 = 3;
      local_134 = 0;
      local_130 = 0;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,0,1,4,3,&local_138,(CStack *)0x0);
    }
    else if ((sVar1 == 2) && (9 < *(short *)((int)pfVar4 + 0x22))) {
      *(short *)(pfVar4 + 4) = *(short *)(pfVar4 + 4) + 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    }
    else if ((sVar1 == 3) && (9 < *(short *)((int)pfVar4 + 0x22))) {
      *(short *)(pfVar4 + 4) = *(short *)(pfVar4 + 4) + 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      local_144 = 4;
      local_140 = 0;
      local_13c = 0;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,0,1,4,3,&local_144,(CStack *)0x0);
    }
  }
  return;
}

