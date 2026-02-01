// Function: _MusicNoteExecute__Fv
// Entry: 801c64b0
// Size: 340 bytes

void _MusicNoteExecute__Fv(void)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  iVar2 = _MusicMidiNoteExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi(DAT_8032f3f4,DAT_8032f3fc,1);
  while (iVar2 == 0) {
    if ((DAT_8032f424 != 0) || ((DAT_8032f3f4[0x11b] & 1) == 0)) break;
    *(short *)((int)DAT_8032f3f4 + 0x48e) = (short)DAT_8032f3f4[0x10d];
    memcpy(DAT_8032f3f4 + 3,DAT_8032f3f4 + 0x10e,0x10);
    memcpy(DAT_8032f3f4 + 0x112,DAT_8032f3f4 + 0x10a,0xc);
    puVar1 = DAT_8032f3f4;
    puVar4 = (undefined4 *)*DAT_8032f3f4;
    uVar3 = (uint)*(byte *)((int)DAT_8032f3f4 + 0x491);
    iVar2 = 0;
    do {
      *puVar4 = puVar1[iVar2 + 10];
      uVar3 = uVar3 - 1;
      puVar4[0x42] = puVar1[iVar2 + 0x4a];
      puVar4[0x41] = puVar1[iVar2 + 0x8a];
      puVar4[9] = puVar1[iVar2 + 0xca];
      puVar4 = puVar4 + 0x55;
      iVar2 = iVar2 + 1;
    } while (uVar3 != 0);
    iVar2 = _MusicMidiNoteExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi(DAT_8032f3f4,DAT_8032f3fc,1);
  }
  if (((*(int *)(DAT_8032f3f0 + 0x470) < 0) && (*(int *)(DAT_8032f3f0 + 0x904) < 0)) &&
     (*(int *)(DAT_8032f3f0 + 0xd98) < 0)) {
    DAT_8032f424 = 0;
  }
  return;
}

