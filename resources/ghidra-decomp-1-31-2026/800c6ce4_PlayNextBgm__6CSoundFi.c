// Function: PlayNextBgm__6CSoundFi
// Entry: 800c6ce4
// Size: 104 bytes

void PlayNextBgm__6CSoundFi(CSound *sound,int param_2)

{
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    MusicNextPlay__9CRedSoundFiii(&sound->m_redSound,param_2,0x7f,0);
    SetMusicPhraseStop__9CRedSoundFi(&sound->m_redSound,1);
  }
  return;
}

