// Function: _WaveSplitSelect__FP11RedWaveDATAP11RedNoteDATA
// Entry: 801c450c
// Size: 180 bytes

void _WaveSplitSelect__FP11RedWaveDATAP11RedNoteDATA(uint *param_1,char *param_2)

{
  uint *puVar1;
  
  if ((param_1 != (uint *)0x0) && ((*param_1 & 0x30000) != 0)) {
    for (; ((*param_1 & 0x200) == 0 && (*(char *)(param_1 + 6) < *param_2));
        param_1 = param_1 + 0x18) {
      if ((*param_1 & 1) != 0) {
        param_1 = param_1 + 0x18;
      }
    }
    puVar1 = param_1 + 6;
    for (; ((*param_1 & 0x200) == 0 && ((int)(uint)*(byte *)((int)param_1 + 0x19) < (int)param_2[1])
           ); param_1 = param_1 + 0x18) {
      if (*(char *)puVar1 != *(char *)(param_1 + 6)) {
        return;
      }
      if ((*param_1 & 1) != 0) {
        param_1 = param_1 + 0x18;
      }
    }
  }
  return;
}

