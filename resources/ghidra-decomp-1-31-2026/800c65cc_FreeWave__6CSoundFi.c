// Function: FreeWave__6CSoundFi
// Entry: 800c65cc
// Size: 72 bytes

void FreeWave__6CSoundFi(CSound *sound,int param_2)

{
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    ClearWaveData__9CRedSoundFi(&sound->m_redSound,param_2);
  }
  return;
}

