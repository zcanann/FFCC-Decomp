// Function: SetArtifact__12CCaravanWorkFii
// Entry: 800a1ee8
// Size: 32 bytes

void SetArtifact__12CCaravanWorkFii(CCaravanWork *caravanWork,int artifactIndex,int param_3)

{
  uint16_t uVar1;
  
  uVar1 = 0xffff;
  if (param_3 != 0) {
    uVar1 = (short)artifactIndex + 0x9f;
  }
  caravanWork->m_artifacts[artifactIndex] = uVar1;
  return;
}

