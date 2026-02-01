// Function: PlaySe__6CSoundFiiii
// Entry: 800c63b8
// Size: 312 bytes

int PlaySe__6CSoundFiiii(CSound *sound,int param_2,int param_3,uint param_4,uint param_5)

{
  int iVar1;
  
  if (param_2 < 0) {
    Printf__7CSystemFPce(&System,s_Sound___1_n_B_801db130);
    iVar1 = -1;
  }
  else if (param_2 < 4000) {
    iVar1 = param_2 / 1000 + (param_2 >> 0x1f);
    iVar1 = SePlay__9CRedSoundFiiiii
                      (&sound->m_redSound,iVar1 - (iVar1 >> 0x1f),
                       param_2 + (iVar1 - (iVar1 >> 0x1f)) * -1000,param_3,
                       param_4 & ~((int)(-param_5 | param_5) >> 0x1f),0);
    if (param_5 != 0) {
      SeVolume__9CRedSoundFiii(&sound->m_redSound,iVar1,param_4,param_5);
    }
  }
  else {
    iVar1 = SePlay__9CRedSoundFiiiii
                      (&sound->m_redSound,-1,param_2,param_3,
                       param_4 & ~((int)(-param_5 | param_5) >> 0x1f),0);
    if (param_5 != 0) {
      SeVolume__9CRedSoundFiii(&sound->m_redSound,iVar1,param_4,param_5);
    }
  }
  return iVar1;
}

