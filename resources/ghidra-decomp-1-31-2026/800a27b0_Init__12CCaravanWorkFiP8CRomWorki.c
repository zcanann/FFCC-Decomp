// Function: Init__12CCaravanWorkFiP8CRomWorki
// Entry: 800a27b0
// Size: 396 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Init__12CCaravanWorkFiP8CRomWorki
               (CCaravanWork *caravanWork,int32_t param_2,short *param_3,short param_4)

{
  int iVar1;
  
  (caravanWork->gObjWork).m_baseDataIndex = param_2;
  (caravanWork->gObjWork).m_id = *param_3 + param_4;
  (caravanWork->gObjWork).m_param1 = param_3[1];
  (caravanWork->gObjWork).m_param2 = param_3[2];
  (caravanWork->gObjWork).m_maxHp = param_3[3];
  (caravanWork->gObjWork).m_strength = param_3[4];
  (caravanWork->gObjWork).m_magic = param_3[5];
  (caravanWork->gObjWork).m_defense = param_3[6];
  (caravanWork->gObjWork).m_romWorkPtr = (uint16_t *)(param_3 + 8);
  memcpy((caravanWork->gObjWork).m_elementResistances,(caravanWork->gObjWork).m_romWorkPtr + 0x6f,
         0x16);
  memset((caravanWork->gObjWork).m_statusTimers + 3,0,0x4e);
  (caravanWork->gObjWork).m_statusValues[0] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[1] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[2] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[3] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[4] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[5] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[6] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[7] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[8] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[9] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[10] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[0xb] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[0xc] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[0xd] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[0xe] = 0xffff;
  (caravanWork->gObjWork).m_statusValues[0xf] = 0xffff;
  (caravanWork->gObjWork).m_hp = (caravanWork->gObjWork).m_maxHp;
  caravanWork->m_shopState = 1;
  iVar1 = (caravanWork->gObjWork).m_id - 100;
  iVar1 = iVar1 / 200 + (iVar1 >> 0x1f);
  caravanWork->m_tribeId = (short)iVar1 - (short)(iVar1 >> 0x1f);
  iVar1 = (caravanWork->gObjWork).m_id - 100;
  iVar1 = iVar1 / 100 + (iVar1 >> 0x1f);
  caravanWork->m_genderFlag = (short)iVar1 - (short)(iVar1 >> 0x1f) & 1;
  clearCaravanWork__12CCaravanWorkFv(caravanWork);
  caravanWork->m_bonusCondition = '\0';
  memset(caravanWork->m_artifactRelated,0,10);
  caravanWork->m_artifactRelated[3] =
       *(uint16_t *)
        (Game.game.m_bossArtifactBase + Game.game.m_gameWork.m_bossArtifactStageIndex * 0x168 + 0x62
        );
  caravanWork->m_artifactRelated[4] =
       *(uint16_t *)
        (Game.game.m_bossArtifactBase + Game.game.m_gameWork.m_bossArtifactStageIndex * 0x168 + 100)
  ;
  return;
}

