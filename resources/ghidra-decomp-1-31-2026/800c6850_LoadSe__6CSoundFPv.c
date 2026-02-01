// Function: LoadSe__6CSoundFPv
// Entry: 800c6850
// Size: 84 bytes

void LoadSe__6CSoundFPv(CSound *sound,void *param_2)

{
  int iVar1;
  
  iVar1 = ReentrySeSepData__9CRedSoundFi(&sound->m_redSound,*(undefined4 *)((int)param_2 + 8));
  if (iVar1 == -1) {
    SetSeSepData__9CRedSoundFPv(&sound->m_redSound,param_2);
  }
  return;
}

