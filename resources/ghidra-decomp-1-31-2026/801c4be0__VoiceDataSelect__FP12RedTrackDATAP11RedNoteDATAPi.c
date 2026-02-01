// Function: _VoiceDataSelect__FP12RedTrackDATAP11RedNoteDATAPi
// Entry: 801c4be0
// Size: 296 bytes

int * _VoiceDataSelect__FP12RedTrackDATAP11RedNoteDATAPi
                (int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = DAT_8032f444;
  if ((*(uint *)(param_1 + 0x104) & 0x80000) == 0) {
    piVar1 = (int *)EntryVoiceSearch__FP12RedTrackDATA(param_1);
  }
  else {
    do {
      if (*piVar1 == param_1) break;
      piVar1 = piVar1 + 0x30;
    } while (piVar1 < DAT_8032f444 + 0xc00);
    if (DAT_8032f444 + 0xc00 <= piVar1) {
      piVar1 = (int *)EntryVoiceSearch__FP12RedTrackDATA(param_1);
    }
  }
  if (piVar1 != (int *)0x0) {
    iVar2 = _WaveSplitSelect__FP11RedWaveDATAP11RedNoteDATA(*(undefined4 *)(param_1 + 0x1c),param_2)
    ;
    piVar1[1] = iVar2;
    _VoiceDataAsign__FP12RedTrackDATAP12RedVoiceDATAP11RedNoteDATAPi(param_1,piVar1,param_2,param_3)
    ;
    if (((*(uint *)piVar1[1] & 1) != 0) && ((*(byte *)(param_1 + 0x26) & 5) == 0)) {
      iVar2 = piVar1[1];
      piVar1[0x25] = piVar1[0x25] | 0x40;
      piVar1 = (int *)EntryVoiceSearch__FP12RedTrackDATA(param_1);
      if (piVar1 != (int *)0x0) {
        piVar1[0x25] = piVar1[0x25] | 0x80;
        piVar1[1] = iVar2 + 0x60;
        _VoiceDataAsign__FP12RedTrackDATAP12RedVoiceDATAP11RedNoteDATAPi
                  (param_1,piVar1,param_2,param_3);
      }
    }
  }
  return piVar1;
}

