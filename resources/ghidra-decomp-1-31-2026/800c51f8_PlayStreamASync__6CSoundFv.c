// Function: PlayStreamASync__6CSoundFv
// Entry: 800c51f8
// Size: 288 bytes

void PlayStreamASync__6CSoundFv(CSound *sound)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined auStack_108 [260];
  
  sprintf(auStack_108,s_dvd_sound_stream_str_04d_str_801db110,*(undefined4 *)&sound->field_0x22ac);
  uVar3 = Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_108,0,0);
  *(undefined4 *)&sound->field_0x2290 = uVar3;
  if (*(int *)&sound->field_0x2290 == 0) {
    return;
  }
  iVar1 = *(int *)&sound->field_0x22ac;
  if (iVar1 == 5) {
LAB_800c5288:
    iVar2 = *(int *)&sound->field_0x22b0;
    if (iVar1 == 1) {
      iVar1 = (iVar2 * 0x19) / 0x7f + (iVar2 * 0x19 >> 0x1f);
      iVar2 = iVar2 - (iVar1 - (iVar1 >> 0x1f));
    }
  }
  else {
    if (iVar1 < 5) {
      if (iVar1 == 1) goto LAB_800c5288;
      if (0 < iVar1) goto LAB_800c5274;
    }
    else if (iVar1 < 7) {
LAB_800c5274:
      iVar2 = 0x7f;
      if (iVar1 == 6) {
        iVar2 = 0x70;
      }
      goto LAB_800c52c4;
    }
    iVar2 = *(int *)&sound->field_0x22b4;
  }
LAB_800c52c4:
  if (iVar2 < 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 0x7f;
    if (iVar2 < 0x80) {
      iVar1 = iVar2;
    }
  }
  uVar3 = StreamPlay__9CRedSoundFPviii
                    (&sound->m_redSound,*(undefined4 *)&sound->field_0x228c,0x20000,0x40,iVar1);
  *(undefined4 *)&sound->field_0x2298 = uVar3;
  *(undefined4 *)&sound->field_0x22a0 = 1;
  return;
}

