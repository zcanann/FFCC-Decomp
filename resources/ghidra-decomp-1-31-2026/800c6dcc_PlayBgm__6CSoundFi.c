// Function: PlayBgm__6CSoundFi
// Entry: 800c6dcc
// Size: 128 bytes

void PlayBgm__6CSoundFi(CSound *sound,int param_2)

{
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    MusicStop__9CRedSoundFi(&sound->m_redSound,-1);
    SetMusicPhraseStop__9CRedSoundFi(&sound->m_redSound,0);
    MusicPlay__9CRedSoundFiii(&sound->m_redSound,param_2,0x7f,0);
  }
  return;
}

