// Function: CheckDriver__6CSoundFi
// Entry: 800c789c
// Size: 136 bytes

void CheckDriver__6CSoundFi(CSound *sound,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)&sound->field_0x22d4;
  *(undefined4 *)&sound->field_0x22d4 = 1;
  ReportPrint__9CRedSoundFi(&sound->m_redSound,1);
  TestProcess__9CRedSoundFi(&sound->m_redSound,param_2);
  DisplayWaveInfo__9CRedSoundFv(&sound->m_redSound);
  DisplaySePlayInfo__9CRedSoundFv(&sound->m_redSound);
  *(uint *)&sound->field_0x22d4 = uVar1;
  ReportPrint__9CRedSoundFi(&sound->m_redSound,(-uVar1 | uVar1) >> 0x1f);
  return;
}

