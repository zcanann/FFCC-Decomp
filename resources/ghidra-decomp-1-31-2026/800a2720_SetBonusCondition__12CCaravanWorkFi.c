// Function: SetBonusCondition__12CCaravanWorkFi
// Entry: 800a2720
// Size: 144 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetBonusCondition__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  caravanWork->m_bonusCondition = (uint8_t)param_2;
  memset(caravanWork->m_artifactRelated,0,10);
  caravanWork->m_artifactRelated[3] =
       *(uint16_t *)
        (Game.game.m_bossArtifactBase + Game.game.m_gameWork.m_bossArtifactStageIndex * 0x168 +
         param_2 * 8 + 0x62);
  caravanWork->m_artifactRelated[4] =
       *(uint16_t *)
        (Game.game.m_bossArtifactBase + Game.game.m_gameWork.m_bossArtifactStageIndex * 0x168 +
         param_2 * 8 + 100);
  return;
}

