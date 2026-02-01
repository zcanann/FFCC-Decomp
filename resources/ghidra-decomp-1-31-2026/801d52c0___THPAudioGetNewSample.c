// Function: __THPAudioGetNewSample
// Entry: 801d52c0
// Size: 144 bytes

int __THPAudioGetNewSample(int *param_1)

{
  byte bVar1;
  uint uVar2;
  
  if ((param_1[1] & 0xfU) == 0) {
    *(byte *)(param_1 + 2) = *(byte *)*param_1 >> 4 & 7;
    *(byte *)((int)param_1 + 9) = *(byte *)*param_1 & 0xf;
    *param_1 = *param_1 + 1;
    param_1[1] = param_1[1] + 2;
  }
  if ((param_1[1] & 1U) == 0) {
    uVar2 = (uint)*(byte *)*param_1 << 0x18;
  }
  else {
    bVar1 = *(byte *)*param_1;
    *param_1 = (int)((byte *)*param_1 + 1);
    uVar2 = (uint)bVar1 << 0x1c | (uint)(bVar1 >> 4);
  }
  param_1[1] = param_1[1] + 1;
  return (int)uVar2 >> 0x1c;
}

