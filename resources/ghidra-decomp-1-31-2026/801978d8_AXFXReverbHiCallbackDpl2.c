// Function: AXFXReverbHiCallbackDpl2
// Entry: 801978d8
// Size: 128 bytes

void AXFXReverbHiCallbackDpl2(undefined4 *param_1,int param_2)

{
  if (*(char *)(param_2 + 0x254) == '\0') {
    HandleReverbDpl2(*param_1,param_2,0);
    HandleReverbDpl2(param_1[1],param_2,1);
    HandleReverbDpl2(param_1[2],param_2,2);
    HandleReverbDpl2(param_1[3],param_2,3);
  }
  return;
}

