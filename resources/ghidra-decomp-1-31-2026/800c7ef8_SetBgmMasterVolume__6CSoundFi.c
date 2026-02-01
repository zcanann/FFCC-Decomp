// Function: SetBgmMasterVolume__6CSoundFi
// Entry: 800c7ef8
// Size: 40 bytes

void SetBgmMasterVolume__6CSoundFi(CSound *sound,int param_2)

{
  *(int *)&sound->field_0x22b0 = param_2;
  MusicMasterVolume__9CRedSoundFi((int)&sound->m_redSound,param_2);
  return;
}

