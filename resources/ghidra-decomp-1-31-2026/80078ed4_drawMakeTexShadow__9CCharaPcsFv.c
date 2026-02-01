// Function: drawMakeTexShadow__9CCharaPcsFv
// Entry: 80078ed4
// Size: 828 bytes

void drawMakeTexShadow__9CCharaPcsFv(int param_1)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  CCharaPcsCHandle *handle;
  double dVar8;
  undefined4 local_54;
  undefined auStack_50 [4];
  undefined4 local_4c;
  undefined auStack_48 [4];
  undefined4 local_44;
  undefined auStack_40 [32];
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  iVar7 = 0;
  iVar6 = *(int *)(*(int *)(param_1 + 0x4c) + 0x160);
  while( true ) {
    if (*(int *)(param_1 + 0x4c) == iVar6) break;
    if ((*(uint *)(iVar6 + 8) & 0x200) != 0) {
      iVar7 = iVar7 + 1;
    }
    iVar6 = *(int *)(iVar6 + 0x160);
  }
  if (iVar7 != 0) {
    GXSetZMode(0,7,0);
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238030,auStack_40,0,0,*(undefined4 *)(param_1 + 0x44),
               *(undefined4 *)(param_1 + 0x44),0,0,6,0);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (0,0,1,2,3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (1,0,1,2,3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (2,0,1,2,3);
    puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_50,0,0,0,0xff);
    local_54 = *puVar5;
    SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_54);
    SetNumDiffuse__9CLightPcsFUl(&LightPcs,0);
    SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
    GXSetPixelFmt(1,0);
    uVar1 = DAT_802381a7;
    GXSetAlphaUpdate(1);
    dVar8 = (double)FLOAT_80330288;
    uStack_1c = *(uint *)(param_1 + 0x44) ^ 0x80000000;
    local_20 = 0x43300000;
    local_18 = 0x43300000;
    uStack_14 = uStack_1c;
    GXSetViewport(dVar8,dVar8,
                  (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_803302b8),
                  (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_803302b8),dVar8,
                  (double)FLOAT_8033028c);
    GXSetScissor(0,0,*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x44));
    puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_48,0,0,0,0);
    local_44 = *puVar5;
    SetCopyClear__8CGraphicF8_GXColori(&Graphic,&local_44);
    fVar3 = FLOAT_80330300;
    *(undefined4 *)(param_1 + 0x148) = 0;
    *(undefined4 *)(param_1 + 0x140) = DAT_80238030;
    fVar2 = FLOAT_803302fc;
    *(undefined4 *)(param_1 + 0x144) = 0xd2000;
    fVar4 = FLOAT_80330304;
    *(int *)(param_1 + 0x148) =
         *(int *)(param_1 + 0x148) + *(int *)(param_1 + 0x44) * *(int *)(param_1 + 0x44) * 4;
    C_MTXLightPerspective
              ((float)CameraPcs._252_4_,fVar2,fVar3,fVar4,fVar3,fVar3,(Mtx *)(param_1 + 0x14c));
    handle = *(CCharaPcsCHandle **)(*(int *)(param_1 + 0x4c) + 0x160);
    while( true ) {
      if (*(CCharaPcsCHandle **)(param_1 + 0x4c) == handle) break;
      if ((MiniGamePcs._25732_4_ & 0x8000) != 0) {
        draw__Q29CCharaPcs7CHandleFii(handle,2,1);
      }
      handle = handle->m_next;
    }
    SetViewport__8CGraphicFv(&Graphic);
    SetStdPixelFmt__8CGraphicFv(&Graphic);
    local_4c = uVar1;
    SetCopyClear__8CGraphicF8_GXColori(&Graphic,&local_4c);
    uStack_1c = *(uint *)(param_1 + 0x44) ^ 0x80000000;
    local_18 = 0x43300000;
    local_20 = 0x43300000;
    uStack_14 = uStack_1c;
    RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)FLOAT_80330288,(double)FLOAT_80330288,
               (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_803302b8),
               (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_803302b8),
               &DAT_8032ec70,auStack_40,0,0,0,4,5);
  }
  return;
}

