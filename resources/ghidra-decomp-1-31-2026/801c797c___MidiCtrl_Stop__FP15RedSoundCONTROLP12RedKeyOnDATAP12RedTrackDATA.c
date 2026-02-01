// Function: __MidiCtrl_Stop__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c797c
// Size: 456 bytes

void __MidiCtrl_Stop__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (uint *param_1,undefined4 param_2,undefined4 *param_3)

{
  uint *puVar1;
  
  param_3[0x41] = 0;
  KeyOffSet__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA(param_1,param_2);
  puVar1 = DAT_8032f444;
  do {
    if ((undefined4 *)*puVar1 == param_3) {
      *(byte *)((int)puVar1 + 0x1a) = *(byte *)((int)puVar1 + 0x1a) & 0xfa;
    }
    puVar1 = puVar1 + 0x30;
  } while (puVar1 < DAT_8032f444 + 0xc00);
  *param_3 = 0;
  if (param_1 < (uint *)(DAT_8032f3f0 + 0xdbc)) {
    *(short *)((int)param_1 + 0x48e) = *(short *)((int)param_1 + 0x48e) + -1;
    if ((*(short *)((int)param_1 + 0x48e) == 0) &&
       ((puVar1 = DAT_8032f444, DAT_8032f424 == 1 || ((param_1[0x11b] & 1) == 0)))) {
      do {
        if ((*param_1 <= *puVar1) &&
           (*puVar1 < *param_1 + (uint)*(byte *)((int)param_1 + 0x491) * 0x154)) {
          puVar1[0x25] = puVar1[0x25] & 0xfffffff3;
          puVar1[0x24] = puVar1[0x24] & 0xfffffffe;
          puVar1[0x24] = puVar1[0x24] | 2;
          *puVar1 = 0;
        }
        puVar1 = puVar1 + 0x30;
      } while (puVar1 < DAT_8032f444 + 0xc00);
      MusicHistoryManager__9CRedEntryFii(&DAT_8032e154,0,param_1[0x11c]);
      WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,0,param_1[0x11f]);
      param_1[0x11c] = 0xffffffff;
      param_1[0x122] = 0;
      RedDelete__Fi(*param_1);
      *param_1 = 0;
    }
  }
  else {
    if (param_3[6] != 0) {
      WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,0,(int)*(short *)(param_3[6] + 2));
    }
    SeSepHistoryManager__9CRedEntryFii(&DAT_8032e154,0,param_3[0x3d]);
    param_3[0x3e] = 0;
  }
  return;
}

