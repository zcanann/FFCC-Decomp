// Function: MusicStop__Fi
// Entry: 801cb5f0
// Size: 480 bytes

uint MusicStop__Fi(uint param_1)

{
  uint uVar1;
  int *piVar2;
  uint *puVar3;
  uint *puVar4;
  
  puVar4 = DAT_8032f3f0;
  do {
    if ((param_1 == 0xffffffff) || ((-1 < (int)puVar4[0x11c] && (puVar4[0x11c] == param_1)))) {
      uVar1 = puVar4[0x11c];
      puVar4[0x122] = 0;
      puVar4[0x11c] = 0xffffffff;
      puVar3 = DAT_8032f444;
      if (*(short *)((int)puVar4 + 0x48e) != 0) {
        do {
          if ((*puVar4 <= *puVar3) &&
             (*puVar3 < *puVar4 + (uint)*(byte *)((int)puVar4 + 0x491) * 0x154)) {
            puVar3[0x25] = puVar3[0x25] & 0xfffffff3;
            puVar3[0x24] = puVar3[0x24] & 0xfffffffe;
            puVar3[0x24] = puVar3[0x24] | 2;
            *(byte *)((int)puVar3 + 0x1a) = *(byte *)((int)puVar3 + 0x1a) & 0xfb;
            *puVar3 = 0;
            puVar3[0x23] = 0;
          }
          puVar3 = puVar3 + 0x30;
        } while (puVar3 < DAT_8032f444 + 0xc00);
        piVar2 = (int *)*puVar4;
        do {
          if (*piVar2 != 0) {
            KeyOnReserveClear__FP12RedKeyOnDATAP12RedTrackDATA(DAT_8032f3fc,piVar2);
            *piVar2 = 0;
          }
          piVar2 = piVar2 + 0x55;
        } while (piVar2 < (int *)(*puVar4 + (uint)*(byte *)((int)puVar4 + 0x491) * 0x154));
        *(undefined2 *)((int)puVar4 + 0x48e) = 0;
        *(undefined *)((int)puVar4 + 0x491) = 0;
        RedDelete__FPv(*puVar4);
        *puVar4 = 0;
        WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,0,puVar4[0x11f]);
        MusicHistoryManager__9CRedEntryFii(&DAT_8032e154,0,uVar1);
      }
    }
    puVar3 = DAT_8032f3f0;
    puVar4 = puVar4 + 0x125;
  } while (puVar4 < DAT_8032f3f0 + 0x24a);
  if (((int)DAT_8032f3f0[0x11c] < 0) && (-1 < (int)DAT_8032f3f0[0x241])) {
    memcpy(DAT_8032f3f0,DAT_8032f3f0 + 0x125,0x494);
    *(undefined2 *)((int)puVar3 + 0x922) = 0;
    *(undefined *)((int)puVar3 + 0x925) = 0;
    puVar3[0x241] = 0xffffffff;
    puVar3[0x125] = 0;
  }
  return param_1;
}

