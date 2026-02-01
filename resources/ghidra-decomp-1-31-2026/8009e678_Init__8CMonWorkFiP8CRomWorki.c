// Function: Init__8CMonWorkFiP8CRomWorki
// Entry: 8009e678
// Size: 828 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Init__8CMonWorkFiP8CRomWorki(CMonWork *monWork,int32_t param_2,uint16_t *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined8 local_28;
  undefined8 local_18;
  
  (monWork->gObjWork).m_baseDataIndex = param_2;
  (monWork->gObjWork).m_id = *param_3;
  (monWork->gObjWork).m_param1 = param_3[1];
  (monWork->gObjWork).m_param2 = param_3[2];
  (monWork->gObjWork).m_maxHp = param_3[3];
  (monWork->gObjWork).m_strength = param_3[4];
  (monWork->gObjWork).m_magic = param_3[5];
  (monWork->gObjWork).m_defense = param_3[6];
  (monWork->gObjWork).m_romWorkPtr = param_3 + 8;
  memcpy((monWork->gObjWork).m_elementResistances,(monWork->gObjWork).m_romWorkPtr + 0x6f,0x16);
  memset((monWork->gObjWork).m_statusTimers + 3,0,0x4e);
  (monWork->gObjWork).m_statusValues[0] = 0xffff;
  (monWork->gObjWork).m_statusValues[1] = 0xffff;
  (monWork->gObjWork).m_statusValues[2] = 0xffff;
  (monWork->gObjWork).m_statusValues[3] = 0xffff;
  (monWork->gObjWork).m_statusValues[4] = 0xffff;
  (monWork->gObjWork).m_statusValues[5] = 0xffff;
  (monWork->gObjWork).m_statusValues[6] = 0xffff;
  (monWork->gObjWork).m_statusValues[7] = 0xffff;
  (monWork->gObjWork).m_statusValues[8] = 0xffff;
  (monWork->gObjWork).m_statusValues[9] = 0xffff;
  (monWork->gObjWork).m_statusValues[10] = 0xffff;
  (monWork->gObjWork).m_statusValues[0xb] = 0xffff;
  (monWork->gObjWork).m_statusValues[0xc] = 0xffff;
  (monWork->gObjWork).m_statusValues[0xd] = 0xffff;
  (monWork->gObjWork).m_statusValues[0xe] = 0xffff;
  (monWork->gObjWork).m_statusValues[0xf] = 0xffff;
  (monWork->gObjWork).m_hp = (monWork->gObjWork).m_maxHp;
  memcpy(monWork->unk_0xac,param_3 + 0x56,8);
  memcpy(monWork->unk_0xb4,param_3 + 0x5a,0x1c);
  memset(monWork->unk_0xd0,0,0x20);
  memset(monWork->unk_0xf0,0,0x20);
  if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
    iVar1 = Game.game.m_gameWork.m_bossArtifactStageTable
            [Game.game.m_gameWork.m_bossArtifactStageIndex];
    iVar3 = 2;
    if (iVar1 < 2) {
      iVar3 = iVar1;
    }
  }
  else {
    iVar3 = 0;
  }
  if (0 < iVar3) {
    local_28 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_maxHp);
    (monWork->gObjWork).m_maxHp =
         (uint16_t)
         (int)((float)(local_28 - DOUBLE_803309a0) *
              (FLOAT_8033099c *
               (float)((double)CONCAT44(0x43300000,
                                        (uint)*(ushort *)
                                               (Game.game.unk_flat3_field_8_0xc7dc + iVar3 * 2 +
                                               0x44)) - DOUBLE_803309a0) + FLOAT_80330998));
  }
  uVar2 = (uint)(-1 < Game.game.m_gameWork.m_wmBackupParams[0]);
  if (-1 < Game.game.m_gameWork.m_wmBackupParams[1]) {
    uVar2 = uVar2 + 1;
  }
  if (-1 < Game.game.m_gameWork.m_wmBackupParams[2]) {
    uVar2 = uVar2 + 1;
  }
  if (-1 < Game.game.m_gameWork.m_wmBackupParams[3]) {
    uVar2 = uVar2 + 1;
  }
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar2 = 1;
  }
  if (1 < uVar2) {
    local_18 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_maxHp);
    (monWork->gObjWork).m_maxHp =
         (uint16_t)
         (int)((float)(local_18 - DOUBLE_803309a0) *
              (FLOAT_8033099c *
               (float)((double)CONCAT44(0x43300000,
                                        (uint)*(ushort *)
                                               (Game.game.unk_flat3_field_8_0xc7dc + uVar2 * 2 +
                                               0x5e)) - DOUBLE_803309a0) + FLOAT_80330998));
  }
  if ((Game.game.m_gameWork._8_4_ == 1) && (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) {
    local_18 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_maxHp);
    (monWork->gObjWork).m_maxHp =
         (uint16_t)
         (int)((float)(local_18 - DOUBLE_803309a0) *
              (FLOAT_8033099c *
               (float)((double)CONCAT44(0x43300000,
                                        (uint)*(ushort *)
                                               (Game.game.m_bossArtifactBase +
                                                Game.game.m_gameWork.m_bossArtifactStageIndex *
                                                0x168 + 0x60)) - DOUBLE_803309a0) + FLOAT_80330998))
    ;
  }
  (monWork->gObjWork).m_hp = (monWork->gObjWork).m_maxHp;
  return;
}

