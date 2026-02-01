// Function: drawShadow__9CCharaPcsFv
// Entry: 80078da8
// Size: 300 bytes

void drawShadow__9CCharaPcsFv(int param_1)

{
  undefined4 *puVar1;
  CCharaPcsCHandle *handle;
  undefined4 local_18;
  undefined auStack_14 [8];
  
  if (CameraPcs._1028_1_ != '\0') {
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (0,0,1,2,3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (1,0,1,2,3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (2,0,1,2,3);
    puVar1 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_14,0,0,0,0xff);
    local_18 = *puVar1;
    SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_18);
    SetNumDiffuse__9CLightPcsFUl(&LightPcs,0);
    SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
    handle = *(CCharaPcsCHandle **)(*(int *)(param_1 + 0x4c) + 0x160);
    while( true ) {
      if (*(CCharaPcsCHandle **)(param_1 + 0x4c) == handle) break;
      if ((MiniGamePcs._25732_4_ & 0x8000) != 0) {
        draw__Q29CCharaPcs7CHandleFii(handle,1,1);
      }
      handle = handle->m_next;
    }
  }
  return;
}

