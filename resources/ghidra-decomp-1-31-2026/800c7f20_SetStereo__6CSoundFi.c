// Function: SetStereo__6CSoundFi
// Entry: 800c7f20
// Size: 44 bytes

void SetStereo__6CSoundFi(CSound *sound,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(param_2);
  SetSoundMode__9CRedSoundFi(&sound->m_redSound,uVar1 >> 5);
  return;
}

