// Function: GetPerformance__6CSoundFv
// Entry: 800c7994
// Size: 148 bytes

double GetPerformance__6CSoundFv(CSound *sound)

{
  uint uVar1;
  
  uVar1 = GetProgramTime__9CRedSoundFv(&sound->m_redSound);
  return (double)(FLOAT_80330d00 *
                 ((float)((double)CONCAT44(0x43300000,uVar1 / 0xf) - DOUBLE_80330d08) /
                 (float)((double)CONCAT44(0x43300000,(DAT_800000f8 / 500000) * 0x8235 >> 3) -
                        DOUBLE_80330d08)));
}

