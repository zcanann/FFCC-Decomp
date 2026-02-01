// Function: _ClearReverb__Fi
// Entry: 801c3628
// Size: 240 bytes

void _ClearReverb__Fi(uint param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(DAT_8032f4ac + (param_1 & 1) * 0xc);
  if (*piVar2 != 0) {
    if (param_1 == 0) {
      AXRegisterAuxACallback(_ReverbNullCallback__FP17AXFX_BUFFERUPDATEPv,0);
    }
    else {
      AXRegisterAuxBCallback(_ReverbNullCallback__FP17AXFX_BUFFERUPDATEPv,0);
    }
    iVar1 = piVar2[2];
    if (iVar1 == 3) {
      AXFXDelayShutdown(piVar2[1]);
    }
    else if (iVar1 < 3) {
      if (iVar1 == 1) {
        AXFXReverbStdShutdown(piVar2[1]);
      }
      else if (0 < iVar1) {
        AXFXReverbHiShutdown(piVar2[1]);
      }
    }
    else if (iVar1 == 5) {
      AXFXReverbHiShutdownDpl2(piVar2[1]);
    }
    else if (iVar1 < 5) {
      AXFXChorusShutdown(piVar2[1]);
    }
    *piVar2 = 0;
    RedDelete__Fi(piVar2[1]);
  }
  return;
}

