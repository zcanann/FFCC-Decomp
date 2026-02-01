// Function: IsLoadWaveASyncCompleted__6CSoundFv
// Entry: 800c6f2c
// Size: 16 bytes

uint IsLoadWaveASyncCompleted__6CSoundFv(CSound *sound)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(*(undefined4 *)&(sound->m_redSound).field_0x8);
  return uVar1 >> 5;
}

