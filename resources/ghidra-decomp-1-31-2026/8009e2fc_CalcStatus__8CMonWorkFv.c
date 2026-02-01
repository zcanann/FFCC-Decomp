// Function: CalcStatus__8CMonWorkFv
// Entry: 8009e2fc
// Size: 892 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcStatus__8CMonWorkFv(CMonWork *monWork)

{
  float fVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  undefined8 local_58;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_18;
  
  iVar5 = Game.game.unkCFlatData0[1] + (monWork->gObjWork).m_baseDataIndex * 0x1d0;
  memcpy((monWork->gObjWork).m_elementResistances,(monWork->gObjWork).m_romWorkPtr + 0x6f,0x16);
  (monWork->gObjWork).m_strength = *(uint16_t *)(iVar5 + 8);
  (monWork->gObjWork).m_magic = *(uint16_t *)(iVar5 + 10);
  (monWork->gObjWork).m_defense = *(uint16_t *)(iVar5 + 0xc);
  dVar3 = DOUBLE_803309a0;
  fVar2 = FLOAT_8033099c;
  fVar1 = FLOAT_80330998;
  if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
    iVar4 = Game.game.m_gameWork.m_bossArtifactStageTable
            [Game.game.m_gameWork.m_bossArtifactStageIndex];
    iVar5 = 2;
    if (iVar4 < 2) {
      iVar5 = iVar4;
    }
  }
  else {
    iVar5 = 0;
  }
  if (0 < iVar5) {
    iVar5 = iVar5 * 2;
    local_58 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_strength);
    (monWork->gObjWork).m_strength =
         (uint16_t)
         (int)((float)(local_58 - DOUBLE_803309a0) *
              (FLOAT_8033099c *
               (float)((double)CONCAT44(0x43300000,
                                        (uint)*(ushort *)
                                               (Game.game.unk_flat3_field_8_0xc7dc + iVar5 + 0x48))
                      - DOUBLE_803309a0) + FLOAT_80330998));
    local_40 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_magic);
    (monWork->gObjWork).m_magic =
         (uint16_t)
         (int)((float)(local_40 - dVar3) *
              (fVar2 * (float)((double)CONCAT44(0x43300000,
                                                (uint)*(ushort *)
                                                       (Game.game.unk_flat3_field_8_0xc7dc + iVar5 +
                                                       0x4c)) - dVar3) + fVar1));
    local_28 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_defense);
    (monWork->gObjWork).m_defense =
         (uint16_t)
         (int)((float)(local_28 - dVar3) *
              (fVar2 * (float)((double)CONCAT44(0x43300000,
                                                (uint)*(ushort *)
                                                       (Game.game.unk_flat3_field_8_0xc7dc + iVar5 +
                                                       0x50)) - dVar3) + fVar1));
  }
  dVar3 = DOUBLE_803309a0;
  fVar2 = FLOAT_8033099c;
  fVar1 = FLOAT_80330998;
  if ((monWork->gObjWork).m_statusTimers[9] != 0) {
    local_18 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_strength);
    (monWork->gObjWork).m_strength =
         (uint16_t)
         (int)((float)(local_18 - DOUBLE_803309a0) *
              (FLOAT_8033099c *
               (float)((double)CONCAT44(0x43300000,
                                        (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x38)
                                       ) - DOUBLE_803309a0) + FLOAT_80330998));
    local_30 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_magic);
    (monWork->gObjWork).m_magic =
         (uint16_t)
         (int)((float)(local_30 - dVar3) *
              (fVar2 * (float)((double)CONCAT44(0x43300000,
                                                (uint)*(ushort *)
                                                       (Game.game.unk_flat3_field_8_0xc7dc + 0x38))
                              - dVar3) + fVar1));
    local_48 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_defense);
    (monWork->gObjWork).m_defense =
         (uint16_t)
         (int)((float)(local_48 - dVar3) *
              (fVar2 * (float)((double)CONCAT44(0x43300000,
                                                (uint)*(ushort *)
                                                       (Game.game.unk_flat3_field_8_0xc7dc + 0x38))
                              - dVar3) + fVar1));
  }
  if ((monWork->gObjWork).m_statusTimers[4] != 0) {
    local_18 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_defense);
    (monWork->gObjWork).m_defense =
         (uint16_t)
         (int)((float)(local_18 - DOUBLE_803309a0) *
              (FLOAT_8033099c *
               (float)((double)CONCAT44(0x43300000,
                                        (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x3e)
                                       ) - DOUBLE_803309a0) + FLOAT_80330998));
  }
  if ((monWork->gObjWork).m_statusTimers[6] != 0) {
    local_18 = (double)CONCAT44(0x43300000,(uint)(monWork->gObjWork).m_defense);
    (monWork->gObjWork).m_defense =
         (uint16_t)
         (int)((float)(local_18 - DOUBLE_803309a0) *
              (FLOAT_8033099c *
               (float)((double)CONCAT44(0x43300000,
                                        (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x44)
                                       ) - DOUBLE_803309a0) + FLOAT_80330998));
  }
  return;
}

