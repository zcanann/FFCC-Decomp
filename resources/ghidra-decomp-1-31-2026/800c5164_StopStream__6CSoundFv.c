// Function: StopStream__6CSoundFv
// Entry: 800c5164
// Size: 148 bytes

void StopStream__6CSoundFv(CSound *sound)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = false;
  if (*(int *)&sound->field_0x22a0 != 0) {
    iVar2 = StreamPlayState__9CRedSoundFi(&sound->m_redSound,*(int *)&sound->field_0x2298);
    if (iVar2 != 0) {
      bVar1 = true;
    }
  }
  if (bVar1) {
    StreamStop__9CRedSoundFi(&sound->m_redSound,*(int *)&sound->field_0x2298);
  }
  if (*(CFileCHandle **)&sound->field_0x2290 != (CFileCHandle *)0x0) {
    Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&sound->field_0x2290);
    *(undefined4 *)&sound->field_0x2290 = 0;
  }
  *(undefined4 *)&sound->field_0x22a0 = 0;
  return;
}

