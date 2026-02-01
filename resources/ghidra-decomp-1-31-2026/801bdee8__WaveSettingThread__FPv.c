// Function: _WaveSettingThread__FPv
// Entry: 801bdee8
// Size: 196 bytes

undefined4 _WaveSettingThread__FPv(undefined4 *param_1)

{
  int iVar1;
  
  DAT_8032f3c4 = DAT_8032f3c4 | 4;
  DAT_8032f460 = 0;
  while (DAT_8032f3c0 != 0) {
    OSWaitSemaphore((OSSemaphore *)&DAT_8032daa0);
    if (DAT_8032f3c0 != 0) {
      DAT_8032f460 = DAT_8032f460 + 1;
      SetWaveData__9CRedEntryFiPvi(&DAT_8032e154,param_1[1],param_1[2],param_1[3]);
      *(undefined4 *)*param_1 = 0;
      do {
        iVar1 = OSTryWaitSemaphore((OSSemaphore *)&DAT_8032daa0);
      } while (0 < iVar1);
      DAT_8032f460 = 0;
    }
  }
  DAT_8032f3c4 = DAT_8032f3c4 & 0xfffffffb;
  return 0;
}

