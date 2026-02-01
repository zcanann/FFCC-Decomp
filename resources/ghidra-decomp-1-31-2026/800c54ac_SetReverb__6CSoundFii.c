// Function: SetReverb__6CSoundFii
// Entry: 800c54ac
// Size: 92 bytes

void SetReverb__6CSoundFii(CSound *sound,int param_2,int param_3)

{
  SetReverb__9CRedSoundFii(&sound->m_redSound,1,param_2);
  SetReverbDepth__9CRedSoundFiii(&sound->m_redSound,1,param_3,0xf);
  return;
}

