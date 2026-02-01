// Function: drawBefore__9CCharaPcsFv
// Entry: 80079210
// Size: 328 bytes

void drawBefore__9CCharaPcsFv(int param_1)

{
  uint uVar1;
  int iVar2;
  CCharaPcsCHandle *handle;
  int iVar3;
  uint uVar4;
  undefined4 local_28;
  undefined4 local_24 [4];
  
  SetStdProjectionMatrix__10CCameraPcsFv(&CameraPcs);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (0,0,1,2,3);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (1,0,1,2,3);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (2,0,1,2,3);
  SetFog__8CGraphicFii(&Graphic,1,0);
  local_28 = *(undefined4 *)(param_1 + 0xe8);
  SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_28);
  SetNumDiffuse__9CLightPcsFUl(&LightPcs,3);
  uVar4 = 0;
  iVar2 = param_1;
  iVar3 = param_1;
  do {
    local_24[0] = *(undefined4 *)(iVar3 + 0xf0);
    uVar1 = countLeadingZeros(2 - uVar4);
    SetDiffuse__9CLightPcsFUl8_GXColorP3Veci
              (&LightPcs,uVar4,local_24,iVar2 + 0x108,uVar1 >> 5 & 0xff);
    uVar4 = uVar4 + 1;
    iVar2 = iVar2 + 0xc;
    iVar3 = iVar3 + 4;
  } while (uVar4 < 3);
  handle = *(CCharaPcsCHandle **)(*(int *)(param_1 + 0x4c) + 0x160);
  while( true ) {
    if (*(CCharaPcsCHandle **)(param_1 + 0x4c) == handle) break;
    if ((MiniGamePcs._25732_4_ & 0x8000) != 0) {
      draw__Q29CCharaPcs7CHandleFii(handle,3,1);
    }
    handle = handle->m_next;
  }
  return;
}

