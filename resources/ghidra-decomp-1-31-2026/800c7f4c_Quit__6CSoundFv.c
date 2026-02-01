// Function: Quit__6CSoundFv
// Entry: 800c7f4c
// Size: 448 bytes

void Quit__6CSoundFv(CSound *sound)

{
  bool bVar1;
  int iVar2;
  void *ptr;
  CFileCHandle *handle;
  
  handle = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
  if (handle != (CFileCHandle *)0x0) {
    Close__5CFileFPQ25CFile7CHandle(&File,handle);
    *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
    Printf__7CSystemFPce(&System,&DAT_801db190);
  }
  SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
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
  SeStop__9CRedSoundFi(&sound->m_redSound,0xffffffff);
  ClearSeSepData__9CRedSoundFi(&sound->m_redSound,-1);
  ClearWaveData__9CRedSoundFi(&sound->m_redSound,-3);
  *(undefined4 *)&sound->field_0x28 = 10000000;
  memset(&sound->field_0x2c,0,0x1400);
  memset(&sound->field_0x22c0,0xff,8);
  memset(&sound->field_0x22c8,0xff,8);
  ClearWaveBank__9CRedSoundFi(&sound->m_redSound,500);
  ClearWaveBank__9CRedSoundFi(&sound->m_redSound,0);
  iVar2 = 0;
  do {
    SetSeBlockData__9CRedSoundFiPv(&sound->m_redSound,iVar2,(void *)0x0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  End__9CRedSoundFv(&sound->m_redSound);
  if (*(void **)&sound->field_0x228c != (void *)0x0) {
    __dla__FPv(*(void **)&sound->field_0x228c);
    *(undefined4 *)&sound->field_0x228c = 0;
  }
  ptr = *(void **)&(sound->m_redSound).field_0x4;
  if (ptr != (void *)0x0) {
    __dla__FPv(ptr);
    *(undefined4 *)&(sound->m_redSound).field_0x4 = 0;
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&sound->field_0x4);
  return;
}

