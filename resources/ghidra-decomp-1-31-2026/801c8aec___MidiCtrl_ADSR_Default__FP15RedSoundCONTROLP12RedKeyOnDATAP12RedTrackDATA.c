// Function: __MidiCtrl_ADSR_Default__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8aec
// Size: 160 bytes

void __MidiCtrl_ADSR_Default__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  
  *(undefined4 *)(param_3 + 0xd4) = 0xffffffff;
  *(undefined4 *)(param_3 + 0xd8) = 0xffffffff;
  memset(param_3 + 0xd4,0xffffffff,0xc);
  piVar1 = DAT_8032f444;
  do {
    if ((*piVar1 == param_3) && (piVar1[1] != 0)) {
      memcpy(piVar1 + 0x14,piVar1[1] + 0x50,0xc);
      piVar1[0x24] = piVar1[0x24] | 0x3c0;
    }
    piVar1 = piVar1 + 0x30;
  } while (piVar1 < DAT_8032f444 + 0xc00);
  return;
}

