// Function: StopBgm__6CSoundFv
// Entry: 800c6cbc
// Size: 40 bytes

void StopBgm__6CSoundFv(CSound *sound)

{
  MusicStop__9CRedSoundFi(&sound->m_redSound,-1);
  return;
}

