// Function: PauseDiscError__6CSoundFi
// Entry: 800c7924
// Size: 112 bytes

void PauseDiscError__6CSoundFi(CSound *sound,uint param_2)

{
  if (*(int *)&sound->field_0x22d0 == 0) {
    SePause__9CRedSoundFii(&sound->m_redSound,-1,(-param_2 | param_2) >> 0x1f);
    StreamPause__9CRedSoundFii(&sound->m_redSound,-1,(-param_2 | param_2) >> 0x1f);
  }
  return;
}

