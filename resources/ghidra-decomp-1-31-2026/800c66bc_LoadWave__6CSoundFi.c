// Function: LoadWave__6CSoundFi
// Entry: 800c66bc
// Size: 404 bytes

void LoadWave__6CSoundFi(CSound *sound,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  CFileCHandle *pCVar4;
  undefined auStack_118 [268];
  
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    iVar2 = ReentryWaveData__9CRedSoundFi(&sound->m_redSound,param_2);
    if (iVar2 == -1) {
      if (param_2 < 0) {
        Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
      }
      else {
        iVar2 = ReentryWaveData__9CRedSoundFi(&sound->m_redSound,param_2);
        if (iVar2 == -1) {
          pCVar4 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
          if (pCVar4 != (CFileCHandle *)0x0) {
            Close__5CFileFPQ25CFile7CHandle(&File,pCVar4);
            *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
            Printf__7CSystemFPce(&System,&DAT_801db190);
          }
          SetWaveData__9CRedSoundFiPvi(&sound->m_redSound,-1,(void *)0x0,0);
          sprintf(auStack_118,s_dvd_sound_wave_wave_04d_wd_801db1bc,param_2);
          uVar3 = Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_118,0,0);
          *(undefined4 *)&(sound->m_redSound).field_0x8 = uVar3;
          pCVar4 = *(CFileCHandle **)&(sound->m_redSound).field_0x8;
          if (pCVar4 != (CFileCHandle *)0x0) {
            uVar3 = GetLength__5CFileFPQ25CFile7CHandle(&File,pCVar4);
            *(undefined4 *)&sound->field_0x14 = uVar3;
            *(undefined4 *)&sound->field_0x18 = 0;
            *(undefined4 *)&sound->field_0x20 = 0;
            *(undefined4 *)&sound->field_0x1c = 0xffffffff;
            *(undefined4 *)&sound->field_0x24 = 1;
            while( true ) {
              uVar1 = countLeadingZeros(*(undefined4 *)&(sound->m_redSound).field_0x8);
              if (uVar1 >> 5 != 0) break;
              loadWaveFrame__6CSoundFv(sound);
            }
          }
        }
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801db1d8,param_2);
      }
    }
  }
  return;
}

