// Function: _MusicMidiNoteExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi
// Entry: 801c63c4
// Size: 236 bytes

int _MusicMidiNoteExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi
              (int param_1,undefined4 param_2,int param_3)

{
  param_3 = param_3 << DAT_8032f40c;
  *(int *)(param_1 + 0x484) = param_3;
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_3;
  while (*(int *)(param_1 + 0x14) <= *(int *)(param_1 + 0x10)) {
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) - *(int *)(param_1 + 0x14);
  }
  if (*(short *)(param_1 + 0x48e) != 0) {
    _MidiTrackExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi(param_1,param_2,param_3);
  }
  *(undefined4 *)(param_1 + 0x474) = 1;
  if (DAT_8032f424 == 0) {
    if (((*(uint *)(param_1 + 0x46c) & 2) != 0) &&
       (*(uint *)(param_1 + 0x46c) = *(uint *)(param_1 + 0x46c) & 0xfffffffd,
       (*(uint *)(param_1 + 0x46c) & 1) != 0)) {
      *(undefined2 *)(param_1 + 0x48e) = 0;
    }
  }
  return (int)*(short *)(param_1 + 0x48e);
}

