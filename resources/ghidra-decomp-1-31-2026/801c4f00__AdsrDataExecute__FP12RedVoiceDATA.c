// Function: _AdsrDataExecute__FP12RedVoiceDATA
// Entry: 801c4f00
// Size: 212 bytes

undefined4 _AdsrDataExecute__FP12RedVoiceDATA(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x5c) < 4) {
    if (((*(uint *)(param_1 + 0x90) & 4) != 0) || (*(int *)(param_1 + 0x5c) < 3)) {
      uVar1 = 1;
      *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + -1;
      *(int *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + *(int *)(param_1 + 100);
      if ((*(int *)(param_1 + 0x60) == 0) && (*(int *)(param_1 + 0x5c) < 3)) {
        *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
        _AdsrDataCompute__FP12RedVoiceDATA(param_1);
      }
    }
  }
  else {
    *(undefined4 *)(param_1 + 0xac) = 0;
  }
  if (*(int *)(param_1 + 0xac) >> 0xc < 1) {
    *(undefined4 *)(param_1 + 0x5c) = 4;
    *(undefined4 *)(param_1 + 0xac) = 0;
  }
  return uVar1;
}

