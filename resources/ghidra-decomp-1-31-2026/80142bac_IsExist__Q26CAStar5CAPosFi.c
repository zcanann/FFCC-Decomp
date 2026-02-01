// Function: IsExist__Q26CAStar5CAPosFi
// Entry: 80142bac
// Size: 40 bytes

undefined4 IsExist__Q26CAStar5CAPosFi(CAPos *aPos,uint param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((aPos->m_groupA == param_2) || (aPos->m_groupB == param_2)) {
    uVar1 = 1;
  }
  return uVar1;
}

