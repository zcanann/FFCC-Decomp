// Function: SetSeMasterVolume__6CSoundFi
// Entry: 800c7ed0
// Size: 40 bytes

void SetSeMasterVolume__6CSoundFi(CSound *sound,int param_2)

{
  *(int *)&sound->field_0x22b4 = param_2;
  SeMasterVolume__9CRedSoundFi(&sound->m_redSound,param_2);
  return;
}

