// Function: LoadBgm__6CSoundFi
// Entry: 800c6e4c
// Size: 224 bytes

void LoadBgm__6CSoundFi(CSound *sound,int param_2)

{
  int iVar1;
  CFileCHandle *fileHandle;
  undefined auStack_108 [256];
  
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    iVar1 = ReentryMusicData__9CRedSoundFi(&sound->m_redSound,param_2);
    if (iVar1 == -1) {
      sprintf(auStack_108,s_dvd_sound_music_music_03d_bgm_801db27c,param_2);
      fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_108,0,0);
      if (fileHandle != (CFileCHandle *)0x0) {
        Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        SetMusicData__9CRedSoundFPv(&sound->m_redSound,File.m_readBuffer);
        Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      }
    }
  }
  return;
}

