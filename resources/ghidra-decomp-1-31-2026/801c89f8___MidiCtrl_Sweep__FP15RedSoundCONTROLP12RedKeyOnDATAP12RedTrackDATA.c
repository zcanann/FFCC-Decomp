// Function: __MidiCtrl_Sweep__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c89f8
// Size: 212 bytes

void __MidiCtrl_Sweep__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  char *pcVar2;
  undefined4 *puVar3;
  undefined4 local_18;
  int local_14 [2];
  
  local_14[0] = DeltaTimeSumup__FPPUc(param_3);
  if (local_14[0] == 0) {
    local_14[0] = 1;
  }
  pcVar2 = (char *)*param_3;
  *param_3 = pcVar2 + 1;
  local_18 = 0;
  uVar1 = DataAddCompute__FPiiPi(&local_18,(int)*pcVar2 << 8,local_14);
  param_3[0x45] = uVar1;
  param_3[0x44] = local_14[0];
  param_3[0x48] = param_3[0x48] & 0xfffff000;
  puVar3 = DAT_8032f444;
  do {
    if ((undefined4 *)*puVar3 == param_3) {
      puVar3[0x28] = puVar3[0x28] & 0xfffff000;
    }
    puVar3 = puVar3 + 0x30;
  } while (puVar3 < DAT_8032f444 + 0xc00);
  return;
}

