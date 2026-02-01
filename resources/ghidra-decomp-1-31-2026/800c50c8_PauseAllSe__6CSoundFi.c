// Function: PauseAllSe__6CSoundFi
// Entry: 800c50c8
// Size: 104 bytes

void PauseAllSe__6CSoundFi(CSound *sound,uint param_2)

{
  SePause__9CRedSoundFii(&sound->m_redSound,-1,(-param_2 | param_2) >> 0x1f);
  StreamPause__9CRedSoundFii(&sound->m_redSound,-1,(-param_2 | param_2) >> 0x1f);
  *(uint *)&sound->field_0x22d0 = param_2;
  return;
}

