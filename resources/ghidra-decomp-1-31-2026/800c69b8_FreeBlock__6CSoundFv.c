// Function: FreeBlock__6CSoundFv
// Entry: 800c69b8
// Size: 104 bytes

void FreeBlock__6CSoundFv(CSound *sound)

{
  int iVar1;
  
  ClearWaveBank__9CRedSoundFi(&sound->m_redSound,500);
  ClearWaveBank__9CRedSoundFi(&sound->m_redSound,0);
  iVar1 = 0;
  do {
    SetSeBlockData__9CRedSoundFiPv(&sound->m_redSound,iVar1,(void *)0x0);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  return;
}

