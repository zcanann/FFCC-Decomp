// Function: KeyOffSet__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c75f4
// Size: 220 bytes

void KeyOffSet__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (int param_1,int *param_2,int param_3)

{
  char cVar1;
  int *piVar2;
  
  if ((param_1 == DAT_8032f3f0 + 0x928) || ((*(uint *)(param_3 + 0x104) & 0x80000) == 0)) {
    *(undefined4 *)(param_3 + 0x110) = 0;
    cVar1 = *(char *)(param_3 + 0x24);
    piVar2 = param_2;
    do {
      if ((*piVar2 == param_3) && (*(char *)(piVar2 + 1) == cVar1)) {
        *piVar2 = 0;
      }
      piVar2 = piVar2 + 2;
    } while (piVar2 < param_2 + 0x180);
    cVar1 = *(char *)(param_3 + 0x24);
    piVar2 = DAT_8032f444;
    do {
      if ((*piVar2 == param_3) && (*(char *)(piVar2 + 6) == cVar1)) {
        piVar2[0x24] = piVar2[0x24] & 0xfffffffe;
        piVar2[0x24] = piVar2[0x24] | 2;
      }
      piVar2 = piVar2 + 0x30;
    } while (piVar2 < DAT_8032f444 + 0xc00);
  }
  return;
}

