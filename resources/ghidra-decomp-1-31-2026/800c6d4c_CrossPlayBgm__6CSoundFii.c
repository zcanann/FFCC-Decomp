// Function: CrossPlayBgm__6CSoundFii
// Entry: 800c6d4c
// Size: 128 bytes

void CrossPlayBgm__6CSoundFii(CSound *sound,int param_2,int param_3)

{
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    SetMusicPhraseStop__9CRedSoundFi(&sound->m_redSound,0);
    MusicCrossPlay__9CRedSoundFiii(&sound->m_redSound,param_2,0x7f,param_3);
  }
  return;
}

