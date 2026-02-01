// Function: __MidiCtrl_ReverbDepthChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8158
// Size: 180 bytes

void __MidiCtrl_ReverbDepthChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  char *pcVar1;
  int iVar2;
  char cVar3;
  uint local_18 [2];
  
  if (*(char *)*param_3 == '\0') {
    local_18[0] = 0x100;
  }
  else {
    local_18[0] = (uint)*(byte *)*param_3;
  }
  pcVar1 = (char *)*param_3;
  *param_3 = (int)(pcVar1 + 1);
  cVar3 = *pcVar1;
  if (cVar3 != '\0') {
    cVar3 = -1;
  }
  iVar2 = DataAddCompute__FPiiPi(param_3 + 0x1a,(int)cVar3,local_18);
  param_3[0x1b] = iVar2;
  param_3[0x1c] = local_18[0];
  *param_3 = *param_3 + 2;
  return;
}

