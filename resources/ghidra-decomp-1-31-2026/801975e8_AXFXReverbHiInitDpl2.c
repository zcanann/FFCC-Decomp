// Function: AXFXReverbHiInitDpl2
// Entry: 801975e8
// Size: 108 bytes

undefined4 AXFXReverbHiInitDpl2(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = OSDisableInterrupts();
  *(undefined *)(param_1 + 0x254) = 0;
  uVar2 = ReverbHICreateDpl2((double)*(float *)(param_1 + 600),(double)*(float *)(param_1 + 0x260),
                             (double)*(float *)(param_1 + 0x25c),(double)*(float *)(param_1 + 0x264)
                             ,(double)*(float *)(param_1 + 0x268),param_1);
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

