// Function: _StreamStop__FP13RedStreamDATA
// Entry: 801cb980
// Size: 272 bytes

void _StreamStop__FP13RedStreamDATA(int *param_1)

{
  fflush(&DAT_8021d1a8);
  if (param_1[0x43] != 0) {
    param_1[0x43] = 0;
    param_1[0x44] = 0;
    if (param_1[3] != 0) {
      RedDelete__FPv(param_1[3]);
      param_1[3] = 0;
    }
    if (param_1[0x4b] != 0) {
      RedDeleteA__Fi(param_1[0x4b]);
      param_1[0x4b] = 0;
    }
    *(uint *)(param_1[1] + 0x90) = *(uint *)(param_1[1] + 0x90) | 2;
    *(byte *)(*param_1 + 0x26) = *(byte *)(*param_1 + 0x26) & 0xfd;
    *(byte *)(param_1[1] + 0x1a) = *(byte *)(param_1[1] + 0x1a) & 0xfd;
    *(undefined4 *)(param_1[1] + 0x8c) = 0;
    if (*(short *)((int)param_1 + 0x2a) == 2) {
      *(uint *)(param_1[1] + 0x150) = *(uint *)(param_1[1] + 0x150) | 2;
      *(byte *)(*param_1 + 0x17a) = *(byte *)(*param_1 + 0x17a) & 0xfd;
      *(byte *)(param_1[1] + 0xda) = *(byte *)(param_1[1] + 0xda) & 0xfd;
      *(undefined4 *)(param_1[1] + 0x14c) = 0;
    }
  }
  return;
}

