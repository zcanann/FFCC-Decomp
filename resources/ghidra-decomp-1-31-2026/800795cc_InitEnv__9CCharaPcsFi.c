// Function: InitEnv__9CCharaPcsFi
// Entry: 800795cc
// Size: 392 bytes

void InitEnv__9CCharaPcsFi(int param_1,int param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_28;
  undefined4 local_24;
  undefined auStack_20 [4];
  undefined4 local_1c [2];
  
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (0,0,1,2,3);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (1,0,1,2,3);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (2,0,1,2,3);
  if ((param_2 == 1) || (param_2 == 2)) {
    puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_20,0,0,0,0xff);
    local_1c[0] = *puVar2;
    SetAmbient__9CLightPcsF8_GXColor(&LightPcs,local_1c);
    SetNumDiffuse__9CLightPcsFUl(&LightPcs,0);
    SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
  }
  else {
    SetFog__8CGraphicFii(&Graphic,1,0);
    local_24 = *(undefined4 *)(param_1 + 0xe8);
    SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_24);
    SetNumDiffuse__9CLightPcsFUl(&LightPcs,3);
    uVar3 = 0;
    iVar4 = param_1;
    do {
      local_28 = *(undefined4 *)(iVar4 + 0xf0);
      uVar1 = countLeadingZeros(2 - uVar3);
      SetDiffuse__9CLightPcsFUl8_GXColorP3Veci
                (&LightPcs,uVar3,&local_28,param_1 + 0x108,uVar1 >> 5 & 0xff);
      uVar3 = uVar3 + 1;
      param_1 = param_1 + 0xc;
      iVar4 = iVar4 + 4;
    } while (uVar3 < 3);
  }
  if (param_2 == 4) {
    GXSetProjection(0x8026883c,0);
  }
  return;
}

