// Function: __MidiCtrl_ADSR_DL__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8c70
// Size: 104 bytes

void __MidiCtrl_ADSR_DL__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined uVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined *)*param_3;
  *param_3 = puVar2 + 1;
  uVar1 = *puVar2;
  *(undefined *)((int)param_3 + 0xdd) = uVar1;
  puVar3 = DAT_8032f444;
  do {
    if ((undefined4 *)*puVar3 == param_3) {
      *(undefined *)((int)puVar3 + 0x59) = uVar1;
      puVar3[0x24] = puVar3[0x24] | 0x3c0;
    }
    puVar3 = puVar3 + 0x30;
  } while (puVar3 < DAT_8032f444 + 0xc00);
  return;
}

