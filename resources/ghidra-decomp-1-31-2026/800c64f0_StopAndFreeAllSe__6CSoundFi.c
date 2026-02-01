// Function: StopAndFreeAllSe__6CSoundFi
// Entry: 800c64f0
// Size: 220 bytes

void StopAndFreeAllSe__6CSoundFi(CSound *sound,int param_2)

{
  if (param_2 == 0) {
    SeStopMG__9CRedSoundFiiii
              (&sound->m_redSound,(int)*(short *)&sound->field_0x22c0,
               (int)*(short *)&sound->field_0x22c2,(int)*(short *)&sound->field_0x22c4,
               (int)*(short *)&sound->field_0x22c6);
    ClearSeSepDataMG__9CRedSoundFiiii
              (&sound->m_redSound,(int)*(short *)&sound->field_0x22c0,
               (int)*(short *)&sound->field_0x22c2,(int)*(short *)&sound->field_0x22c4,
               (int)*(short *)&sound->field_0x22c6);
    ClearWaveDataM__9CRedSoundFiiii
              (&sound->m_redSound,(int)*(short *)&sound->field_0x22c8,
               (int)*(short *)&sound->field_0x22ca,(int)*(short *)&sound->field_0x22cc,
               (int)*(short *)&sound->field_0x22ce);
  }
  else {
    SeStop__9CRedSoundFi(&sound->m_redSound,0xffffffff);
    ClearSeSepData__9CRedSoundFi(&sound->m_redSound,-1);
    ClearWaveData__9CRedSoundFi(&sound->m_redSound,-3);
  }
  *(undefined4 *)&sound->field_0x28 = 10000000;
  memset(&sound->field_0x2c,0,0x1400);
  memset(&sound->field_0x22c0,0xff,8);
  memset(&sound->field_0x22c8,0xff,8);
  return;
}

