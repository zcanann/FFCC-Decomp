// Function: FadeOutSe__6CSoundFii
// Entry: 800c6328
// Size: 72 bytes

void FadeOutSe__6CSoundFii(CSound *int,int param_2)

{
  int in_r5;
  
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
  }
  else {
    SeFadeOut__9CRedSoundFii(&int->m_redSound,param_2,in_r5);
  }
  return;
}

