// Function: GetOthers__Q26CAStar5CAPosFi
// Entry: 80142b94
// Size: 24 bytes

uint GetOthers__Q26CAStar5CAPosFi(CAPos *aPos,uint param_2)

{
  uint uVar1;
  
  uVar1 = (uint)aPos->m_groupA;
  if (uVar1 == param_2) {
    uVar1 = (uint)aPos->m_groupB;
  }
  return uVar1;
}

