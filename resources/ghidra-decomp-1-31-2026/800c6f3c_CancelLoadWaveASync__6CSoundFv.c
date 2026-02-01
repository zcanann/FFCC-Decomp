// Function: CancelLoadWaveASync__6CSoundFv
// Entry: 800c6f3c
// Size: 116 bytes

void CancelLoadWaveASync__6CSoundFv(CSound *sound)

{
  CFileCHandle *handle;
  
  handle = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
  if (handle != (CFileCHandle *)0x0) {
    Close__5CFileFPQ25CFile7CHandle(&File,handle);
    *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
    Printf__7CSystemFPce(&System,&DAT_801db190);
  }
  SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
  return;
}

