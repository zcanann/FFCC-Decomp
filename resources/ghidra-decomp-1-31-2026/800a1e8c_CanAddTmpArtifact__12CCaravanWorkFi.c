// Function: CanAddTmpArtifact__12CCaravanWorkFi
// Entry: 800a1e8c
// Size: 92 bytes

int CanAddTmpArtifact__12CCaravanWorkFi(CCaravanWork *caravanWork,uint param_2)

{
  uint uVar1;
  
  uVar1 = (uint)(caravanWork->m_treasures[0] == 0xffff);
  if (caravanWork->m_treasures[1] == 0xffff) {
    uVar1 = uVar1 + 1;
  }
  if (caravanWork->m_treasures[2] == 0xffff) {
    uVar1 = uVar1 + 1;
  }
  if (caravanWork->m_treasures[3] == 0xffff) {
    uVar1 = uVar1 + 1;
  }
  return (uint)(param_2 <= uVar1) - ((int)param_2 >> 0x1f);
}

