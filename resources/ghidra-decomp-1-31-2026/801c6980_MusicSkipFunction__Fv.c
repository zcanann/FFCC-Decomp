// Function: MusicSkipFunction__Fv
// Entry: 801c6980
// Size: 308 bytes

void MusicSkipFunction__Fv(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  do {
    DAT_8032f4b8 = RedNew__Fi(0x600);
    if (DAT_8032f4b8 == 0) {
      RedSleep__Fi(10000);
    }
    iVar4 = DAT_8032f3f0;
  } while (DAT_8032f4b8 == 0);
  puVar9 = (undefined4 *)(DAT_8032f3f0 + 0x928);
  memset(DAT_8032f4b8,0,0x600);
  iVar5 = _MusicMidiNoteSkipExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi(puVar9,DAT_8032f4b8,1);
  while( true ) {
    if ((iVar5 != 0) || ((*(uint *)(iVar4 + 0xd94) & 1) == 0)) break;
    *(short *)(iVar4 + 0xdb6) = (short)*(undefined4 *)(iVar4 + 0xd5c);
    memcpy((void *)(iVar4 + 0x934),iVar4 + 0xd60,0x10);
    memcpy((void *)(iVar4 + 0xd70),iVar4 + 0xd50,0xc);
    puVar8 = (undefined4 *)*puVar9;
    iVar7 = iVar4 + 0x950;
    uVar6 = (uint)*(byte *)(iVar4 + 0xdb9);
    iVar5 = 0;
    do {
      iVar1 = iVar5 * 4;
      iVar2 = iVar5 * 4;
      iVar3 = iVar5 * 4;
      *puVar8 = *(undefined4 *)(iVar7 + iVar5 * 4);
      uVar6 = uVar6 - 1;
      iVar5 = iVar5 + 1;
      puVar8[0x42] = *(undefined4 *)(iVar7 + iVar1 + 0x100);
      puVar8[0x41] = *(undefined4 *)(iVar7 + iVar2 + 0x200);
      puVar8[9] = *(undefined4 *)(iVar7 + iVar3 + 0x300);
      puVar8 = puVar8 + 0x55;
    } while (uVar6 != 0);
    iVar5 = _MusicMidiNoteSkipExecute__FP15RedSoundCONTROLP12RedKeyOnDATAi(puVar9,DAT_8032f4b8,1);
  }
  DAT_8032f470 = 1;
  return;
}

