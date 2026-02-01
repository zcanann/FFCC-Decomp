// Function: _ExecuteExtraData__Fv
// Entry: 801c5a3c
// Size: 688 bytes

void _ExecuteExtraData__Fv(void)

{
  uint uVar1;
  int *piVar2;
  uint *puVar3;
  uint *puVar4;
  
  puVar4 = DAT_8032f3f0;
  do {
    if ((puVar4[0x117] != 0) && (*puVar4 != 0)) {
      puVar4[0x117] = puVar4[0x117] - 1;
      puVar4[0x115] = puVar4[0x115] + puVar4[0x116];
      if ((puVar4[0x117] == 0) && ((int)puVar4[0x116] < 0)) {
        MusicStop__Fi(puVar4[0x11c]);
      }
      if (*puVar4 != 0) {
        uVar1 = *puVar4;
        puVar3 = DAT_8032f444;
        do {
          if ((uVar1 <= *puVar3) && (*puVar3 < uVar1 + (uint)*(byte *)((int)puVar4 + 0x491) * 0x154)
             ) {
            puVar3[0x2e] = puVar3[0x2e] | 2;
          }
          puVar3 = puVar3 + 0x30;
        } while (puVar3 < DAT_8032f444 + 0xc00);
      }
    }
    puVar3 = DAT_8032f3f0;
    puVar4 = puVar4 + 0x125;
  } while (puVar4 < DAT_8032f3f0 + 0x24a);
  if (DAT_8032f41c[2] != 0) {
    DAT_8032f41c[2] = DAT_8032f41c[2] + -1;
    *DAT_8032f41c = *DAT_8032f41c + DAT_8032f41c[1];
  }
  if (DAT_8032f420[2] != 0) {
    DAT_8032f420[2] = DAT_8032f420[2] + -1;
    *DAT_8032f420 = *DAT_8032f420 + DAT_8032f420[1];
    puVar4 = DAT_8032f444;
    do {
      if ((*(byte *)((int)puVar4 + 0x1a) & 3) == 0) {
        uVar1 = PitchCompute__Fiiii(puVar4[0x28] + *DAT_8032f420,
                                    (int)*(short *)(*puVar4 + 0x142) +
                                    (int)*(short *)(*puVar4 + 0x13e),
                                    *(undefined4 *)(puVar4[1] + 0x14),
                                    (int)*(char *)(*puVar4 + 0x148));
        puVar4[0x26] = uVar1;
        puVar4[0x2e] = puVar4[0x2e] | 1;
      }
      puVar4 = puVar4 + 0x30;
    } while (puVar4 < DAT_8032f444 + 0xc00);
  }
  do {
    if ((*(short *)((int)puVar3 + 0x48e) != 0) && (puVar3[9] != 0)) {
      puVar3[9] = puVar3[9] - 1;
      puVar3[7] = puVar3[7] + puVar3[8];
      if ((puVar3[0x11b] & 0x10000) == 0) {
        piVar2 = (int *)*puVar3;
        do {
          puVar4 = DAT_8032f444;
          if (*piVar2 != 0) {
            do {
              if ((int *)*puVar4 == piVar2) {
                puVar4[0x2e] = puVar4[0x2e] | 2;
              }
              puVar4 = puVar4 + 0x30;
            } while (puVar4 < DAT_8032f444 + 0xc00);
          }
          piVar2 = piVar2 + 0x55;
        } while (piVar2 < (int *)(*puVar3 + (uint)*(byte *)((int)puVar3 + 0x491) * 0x154));
      }
      else if ((puVar3[9] == 0) && (-1 < (int)puVar3[0x11c])) {
        MusicStop__Fi(puVar3[0x11c]);
      }
    }
    puVar3 = puVar3 + 0x125;
  } while (puVar3 < DAT_8032f3f0 + 0x36f);
  return;
}

