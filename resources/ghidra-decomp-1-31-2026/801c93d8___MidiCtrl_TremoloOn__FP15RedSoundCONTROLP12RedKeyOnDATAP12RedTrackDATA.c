// Function: __MidiCtrl_TremoloOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c93d8
// Size: 288 bytes

void __MidiCtrl_TremoloOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  param_3[0x28] = (uint)*(byte *)*param_3 << 0xc;
  if (*(char *)(*param_3 + 1) == '\0') {
    uVar1 = 0x100;
  }
  else {
    uVar1 = (uint)*(byte *)(*param_3 + 1);
  }
  param_3[0x26] = 0x100000 / uVar1;
  param_3[0x25] = (int)(&PTR_SineSwing__Fi_8021e9d0)[*(byte *)(*param_3 + 2) & 0xf];
  *(undefined2 *)((int)param_3 + 0xae) = 0;
  *(undefined2 *)(param_3 + 0x2b) = 0;
  *param_3 = *param_3 + 3;
  puVar3 = DAT_8032f444;
  do {
    if ((int *)*puVar3 == param_3) {
      iVar2 = 0x100;
      *(undefined2 *)(puVar3 + 0xe) = *(undefined2 *)(param_3 + 0x2c);
      if (param_3[0x26] >> 0xc != 0) {
        iVar2 = 0x100 / (param_3[0x26] >> 0xc);
      }
      if (*(short *)((int)param_3 + 0xb2) == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = (int)*(short *)((int)param_3 + 0xb2) * iVar2 * 4;
      }
      puVar3[0xc] = iVar2;
      puVar3[0xd] = 0;
      puVar3[0xb] = 0;
    }
    puVar3 = puVar3 + 0x30;
  } while (puVar3 < DAT_8032f444 + 0xc00);
  return;
}

