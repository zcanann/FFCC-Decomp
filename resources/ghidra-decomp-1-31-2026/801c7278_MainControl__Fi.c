// Function: MainControl__Fi
// Entry: 801c7278
// Size: 512 bytes

void MainControl__Fi(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  
  _KeyOnControl__Fv();
  DAT_8032f3f8 = 0;
  memset(DAT_8032f3fc,0,0x600);
  DAT_8032f3f4 = (undefined4 *)((int)DAT_8032f3f0 + 0xdbc);
  _SeMidiNoteExecute__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATAii
            (DAT_8032f3f4,DAT_8032f3fc,*DAT_8032f3f4,*(undefined4 *)((int)DAT_8032f3f0 + 0x1230),
             param_1);
  DAT_8032f3f4 = (undefined4 *)DAT_8032f3f0;
  if (*(short *)((int)DAT_8032f3f0 + 0x48e) != 0) {
    if ((*(uint *)((int)DAT_8032f3f0 + 0x46c) & 0x10) == 0) {
      uVar1 = *DAT_8032f41c >> 0xc & 0xffff;
      iVar2 = *(int *)((int)DAT_8032f3f0 + 0x448) >> 0xc;
      if (uVar1 != 0) {
        if ((int)*DAT_8032f41c < 0) {
          iVar2 = (int)(iVar2 * uVar1) >> 0x10;
        }
        else {
          iVar2 = ((int)(iVar2 * (uVar1 + 1)) >> 0xf) + (*(int *)((int)DAT_8032f3f0 + 0x448) >> 0xc)
          ;
        }
      }
      *(short *)((int)DAT_8032f3f0 + 0x48c) =
           *(short *)((int)DAT_8032f3f0 + 0x48c) - (short)iVar2 * (short)param_1;
      while (*(short *)((int)DAT_8032f3f4 + 0x48c) < 1) {
        *(short *)((int)DAT_8032f3f4 + 0x48c) = *(short *)((int)DAT_8032f3f4 + 0x48c) + 0xfa;
        _MusicNoteExecute__Fv();
      }
    }
  }
  if (*(short *)((int)DAT_8032f3f0 + 0x922) != 0) {
    DAT_8032f3f4 = (undefined4 *)((int)DAT_8032f3f0 + 0x494);
    *(short *)((int)DAT_8032f3f0 + 0x920) =
         *(short *)((int)DAT_8032f3f0 + 0x920) -
         (short)(*(int *)((int)DAT_8032f3f0 + 0x8dc) >> 0xc) * (short)param_1;
    while (*(short *)((int)DAT_8032f3f4 + 0x48c) < 1) {
      *(short *)((int)DAT_8032f3f4 + 0x48c) = *(short *)((int)DAT_8032f3f4 + 0x48c) + 0xfa;
      _MusicNoteExecute__Fv();
    }
    if (*(short *)((int)DAT_8032f3f0 + 0x48e) == 0) {
      memcpy(DAT_8032f3f0,(int)DAT_8032f3f0 + 0x494,0x494);
      *(undefined2 *)((int)DAT_8032f3f4 + 0x48e) = 0;
      *(undefined *)((int)DAT_8032f3f4 + 0x491) = 0;
      *(undefined4 *)((int)DAT_8032f3f4 + 0x470) = 0xffffffff;
    }
    DAT_8032f3f4 = (undefined4 *)DAT_8032f3f0;
  }
  _ExecuteExtraData__Fv();
  if (DAT_8032f470 != 0) {
    _SkipMusicEntry__Fv();
  }
  return;
}

