// Function: SetStreamVolume__6CSoundFii
// Entry: 800c5130
// Size: 52 bytes

void SetStreamVolume__6CSoundFii(CSound *sound,int param_2,int param_3)

{
  StreamVolume__9CRedSoundFiii(&sound->m_redSound,-1,param_2,param_3);
  return;
}

