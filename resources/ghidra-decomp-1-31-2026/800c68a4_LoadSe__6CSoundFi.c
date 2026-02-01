// Function: LoadSe__6CSoundFi
// Entry: 800c68a4
// Size: 276 bytes

void LoadSe__6CSoundFi(CSound *sound,int param_2)

{
  int iVar1;
  CFileCHandle *fileHandle;
  undefined auStack_118 [264];
  
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    iVar1 = ReentrySeSepData__9CRedSoundFi(&sound->m_redSound,param_2);
    if (iVar1 == -1) {
      sprintf(auStack_118,s_dvd_sound_se_sep_se_06d_sep_801db20c,param_2);
      fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_118,0,0);
      if (fileHandle != (CFileCHandle *)0x0) {
        Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        SetSeSepData__9CRedSoundFPv(&sound->m_redSound,File.m_readBuffer);
        Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        if (System.m_execParam != 0) {
          Printf__7CSystemFPce(&System,&DAT_801db228,param_2);
        }
      }
    }
  }
  return;
}

