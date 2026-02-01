// Function: LoadWave__6CSoundFPv
// Entry: 800c6614
// Size: 168 bytes

void LoadWave__6CSoundFPv(CSound *sound,void *param_2)

{
  int iVar1;
  CFileCHandle *handle;
  
  iVar1 = ReentryWaveData__9CRedSoundFi(&sound->m_redSound,(int)*(short *)((int)param_2 + 2));
  if (iVar1 == -1) {
    handle = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
    if (handle != (CFileCHandle *)0x0) {
      Close__5CFileFPQ25CFile7CHandle(&File,handle);
      *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
      Printf__7CSystemFPce(&System,&DAT_801db190);
    }
    SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
    SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,param_2,-1);
  }
  return;
}

