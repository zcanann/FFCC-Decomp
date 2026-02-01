// Function: SetWaveData__10CRedDriverFiiPvi
// Entry: 801bfc60
// Size: 276 bytes

void SetWaveData__10CRedDriverFiiPvi
               (CRedDriver *redDriver,int param_2,int param_3,char *param_4,int param_5)

{
  while (DAT_8032f460 != 0) {
    RedSleep__Fi(0);
  }
  DAT_8032dab8 = param_5;
  if (param_5 == -1) {
    if ((*param_4 == 'W') && (param_4[1] == 'D')) {
      DAT_8032dab8 = *(int *)(param_4 + 4) +
                     (*(int *)(param_4 + 8) * 4 + 0x3fU & 0xffffffc0) +
                     *(int *)(param_4 + 0xc) * 0x60 + 0x20;
    }
    else {
      DAT_8032dab8 = 0;
    }
  }
  DAT_8032daac = param_2;
  DAT_8032dab0 = param_3;
  DAT_8032dab4 = param_4;
  OSSignalSemaphore((OSSemaphore *)&DAT_8032daa0);
  return;
}

