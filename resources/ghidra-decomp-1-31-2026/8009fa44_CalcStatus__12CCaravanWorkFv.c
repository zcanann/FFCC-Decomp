// Function: CalcStatus__12CCaravanWorkFv
// Entry: 8009fa44
// Size: 1996 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcStatus__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  short sVar6;
  ushort uVar7;
  uint uVar5;
  ushort uVar8;
  short sVar10;
  CCaravanWork *pCVar9;
  uint16_t uVar11;
  ushort *puVar12;
  short sVar13;
  short sVar14;
  short sVar15;
  int iVar16;
  int iVar17;
  undefined auStack_68 [4];
  int local_64 [13];
  undefined8 local_30;
  undefined8 local_20;
  
  iVar16 = Game.game.unkCFlatData0[0] + (caravanWork->gObjWork).m_baseDataIndex * 0x1d0;
  memcpy((caravanWork->gObjWork).m_elementResistances,(caravanWork->gObjWork).m_romWorkPtr + 0x6f,
         0x16);
  uVar11 = *(uint16_t *)(iVar16 + 8);
  (caravanWork->gObjWork).m_strength = uVar11;
  caravanWork->m_baseStrength = uVar11;
  uVar11 = *(uint16_t *)(iVar16 + 10);
  (caravanWork->gObjWork).m_magic = uVar11;
  caravanWork->m_baseMagic = uVar11;
  uVar11 = *(uint16_t *)(iVar16 + 0xc);
  (caravanWork->gObjWork).m_defense = uVar11;
  caravanWork->m_baseDefense = uVar11;
  (caravanWork->gObjWork).m_maxHp = *(uint16_t *)(iVar16 + 6);
  caravanWork->m_equipEffectFlags = 0;
  caravanWork->m_numCmdListSlots = caravanWork->m_baseCmdListSlots;
  memset(caravanWork->m_equipEffectParams,0,7);
  if (caravanWork->m_tempStatBuffTimer != 0) {
    iVar16 = caravanWork->m_tempStatBuffId;
    if (iVar16 < 0x183) {
      if (iVar16 < 0x180) {
        if (0x17c < iVar16) {
          (caravanWork->gObjWork).m_magic =
               (caravanWork->gObjWork).m_magic +
               *(short *)(Game.game.unk_flat3_field_8_0xc7dc + 0x6e);
        }
      }
      else {
        (caravanWork->gObjWork).m_defense =
             (caravanWork->gObjWork).m_defense +
             *(short *)(Game.game.unk_flat3_field_8_0xc7dc + 0x6c);
      }
    }
    else if (iVar16 < 0x185) {
      (caravanWork->gObjWork).m_strength =
           (caravanWork->gObjWork).m_strength +
           *(short *)(Game.game.unk_flat3_field_8_0xc7dc + 0x6a);
    }
    caravanWork->m_tempStatBuffTimer = caravanWork->m_tempStatBuffTimer + -1;
  }
  if (Game.game.m_gameWork.m_chaliceElement == 4) {
    (caravanWork->gObjWork).m_elementResistances[3] =
         (caravanWork->gObjWork).m_elementResistances[3] + 1;
  }
  else if (Game.game.m_gameWork.m_chaliceElement < 4) {
    if (Game.game.m_gameWork.m_chaliceElement == 2) {
      (caravanWork->gObjWork).m_elementResistances[2] =
           (caravanWork->gObjWork).m_elementResistances[2] + 1;
    }
    else if ((Game.game.m_gameWork.m_chaliceElement < 2) &&
            (0 < Game.game.m_gameWork.m_chaliceElement)) {
      (caravanWork->gObjWork).m_elementResistances[1] =
           (caravanWork->gObjWork).m_elementResistances[1] + 1;
    }
  }
  else if (Game.game.m_gameWork.m_chaliceElement == 8) {
    (caravanWork->gObjWork).m_statusTimers[0] = (caravanWork->gObjWork).m_statusTimers[0] + 1;
    (caravanWork->gObjWork).m_statusTimers[2] = (caravanWork->gObjWork).m_statusTimers[2] + 1;
  }
  sVar10 = 0;
  sVar6 = 0;
  sVar15 = 0;
  sVar14 = 0;
  sVar13 = 0;
  iVar16 = 100;
  pCVar9 = caravanWork;
  do {
    if (0 < (short)pCVar9->m_artifacts[0]) {
      puVar12 = (ushort *)(Game.game.unkCFlatData0[2] + (short)pCVar9->m_artifacts[0] * 0x48);
      uVar8 = *puVar12;
      uVar7 = puVar12[3];
      if (uVar8 == 0xdb) {
        sVar6 = sVar6 + uVar7;
      }
      else if (uVar8 < 0xdb) {
        if (uVar8 == 0xb6) {
          sVar14 = sVar14 + uVar7;
        }
        else if (uVar8 < 0xb6) {
          if (uVar8 == 0x9f) {
            sVar13 = sVar13 + uVar7;
          }
        }
        else if (uVar8 == 0xcc) {
          sVar15 = sVar15 + uVar7;
        }
      }
      else if (uVar8 == 0xe4) {
        sVar10 = sVar10 + uVar7;
      }
      else if ((uVar8 < 0xe4) && (uVar8 == 0xdf)) {
        sVar14 = sVar14 + uVar7;
      }
    }
    pCVar9 = (CCaravanWork *)((int)&(pCVar9->gObjWork).vtable + 2);
    iVar16 = iVar16 + -1;
  } while (iVar16 != 0);
  (caravanWork->gObjWork).m_strength = (caravanWork->gObjWork).m_strength + sVar13;
  caravanWork->m_baseStrength = caravanWork->m_baseStrength + sVar13;
  (caravanWork->gObjWork).m_magic = (caravanWork->gObjWork).m_magic + sVar14;
  caravanWork->m_baseMagic = caravanWork->m_baseMagic + sVar14;
  (caravanWork->gObjWork).m_defense = (caravanWork->gObjWork).m_defense + sVar15;
  caravanWork->m_baseDefense = caravanWork->m_baseDefense + sVar15;
  caravanWork->m_numCmdListSlots = caravanWork->m_numCmdListSlots + sVar6;
  (caravanWork->gObjWork).m_maxHp = (caravanWork->gObjWork).m_maxHp + sVar10;
  uVar11 = 8;
  if ((short)caravanWork->m_numCmdListSlots < 8) {
    uVar11 = caravanWork->m_numCmdListSlots;
  }
  caravanWork->m_numCmdListSlots = uVar11;
  uVar8 = (caravanWork->gObjWork).m_maxHp;
  uVar7 = 0x10;
  if (uVar8 < 0x10) {
    uVar7 = uVar8;
  }
  (caravanWork->gObjWork).m_maxHp = uVar7;
  iVar16 = 0;
  pCVar9 = caravanWork;
  do {
    if (-1 < pCVar9->m_equipment[0]) {
      iVar17 = (int)(short)caravanWork->m_inventoryItems[pCVar9->m_equipment[0]];
      uVar8 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar17 * 0x48);
      if ((uVar8 == 1) &&
         (_GetCurrentWeaponItem__12CCaravanWorkFRiRi(caravanWork,auStack_68,local_64),
         0 < local_64[0])) {
        iVar17 = local_64[0];
      }
      sVar6 = *(short *)(Game.game.unkCFlatData0[2] + iVar17 * 0x48 + 6);
      if (uVar8 == 0x45) {
        (caravanWork->gObjWork).m_defense = (caravanWork->gObjWork).m_defense + sVar6;
        caravanWork->m_baseDefense = caravanWork->m_baseDefense + sVar6;
LAB_8009fe14:
        uVar5 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar17 * 0x48 + 8);
        cVar1 = (char)sVar6;
        switch(uVar5) {
        case 1:
          (caravanWork->gObjWork).m_elementResistances[1] =
               (caravanWork->gObjWork).m_elementResistances[1] + 1;
          break;
        case 2:
          (caravanWork->gObjWork).m_elementResistances[2] =
               (caravanWork->gObjWork).m_elementResistances[2] + 1;
          break;
        case 3:
          (caravanWork->gObjWork).m_elementResistances[3] =
               (caravanWork->gObjWork).m_elementResistances[3] + 1;
          break;
        case 4:
          (caravanWork->gObjWork).m_elementResistances[4] =
               (caravanWork->gObjWork).m_elementResistances[4] + 1;
          break;
        case 5:
          (caravanWork->gObjWork).m_elementResistances[5] =
               (caravanWork->gObjWork).m_elementResistances[5] + 1;
          break;
        case 6:
          (caravanWork->gObjWork).m_statusTimers[0] = (caravanWork->gObjWork).m_statusTimers[0] + 1;
          break;
        case 7:
          (caravanWork->gObjWork).m_statusTimers[1] = (caravanWork->gObjWork).m_statusTimers[1] + 1;
          break;
        case 8:
          (caravanWork->gObjWork).m_statusTimers[2] = (caravanWork->gObjWork).m_statusTimers[2] + 1;
          break;
        case 9:
          caravanWork->m_equipEffectParams[0] = caravanWork->m_equipEffectParams[0] + cVar1;
          break;
        case 10:
          caravanWork->m_equipEffectParams[1] = caravanWork->m_equipEffectParams[1] + cVar1;
          break;
        case 0xb:
          caravanWork->m_equipEffectParams[2] = caravanWork->m_equipEffectParams[2] + cVar1;
          break;
        case 0xc:
          caravanWork->m_equipEffectParams[3] = caravanWork->m_equipEffectParams[3] + cVar1;
          break;
        case 0x10:
          caravanWork->m_equipEffectParams[4] = caravanWork->m_equipEffectParams[4] + cVar1;
          break;
        case 0x11:
          caravanWork->m_equipEffectParams[5] = caravanWork->m_equipEffectParams[5] + cVar1;
          break;
        case 0x12:
          caravanWork->m_equipEffectParams[6] = caravanWork->m_equipEffectParams[6] + cVar1;
          break;
        case 0x13:
          (caravanWork->gObjWork).m_elementResistances[0] =
               (caravanWork->gObjWork).m_elementResistances[0] + 1;
        }
        caravanWork->m_equipEffectFlags = caravanWork->m_equipEffectFlags | 1 << uVar5;
      }
      else if (uVar8 < 0x45) {
        if (uVar8 == 1) {
          (caravanWork->gObjWork).m_strength = (caravanWork->gObjWork).m_strength + sVar6;
          caravanWork->m_baseStrength = caravanWork->m_baseStrength + sVar6;
        }
      }
      else if (uVar8 == 0x7f) goto LAB_8009fe14;
    }
    iVar16 = iVar16 + 1;
    pCVar9 = (CCaravanWork *)((int)&(pCVar9->gObjWork).vtable + 2);
    if (3 < iVar16) {
      iVar16 = 0xb;
      pCVar9 = caravanWork;
      do {
        uVar8 = (pCVar9->gObjWork).m_elementResistances[0];
        uVar7 = 2;
        if (uVar8 < 2) {
          uVar7 = uVar8;
        }
        (pCVar9->gObjWork).m_elementResistances[0] = uVar7;
        pCVar9 = (CCaravanWork *)((int)&(pCVar9->gObjWork).vtable + 2);
        iVar16 = iVar16 + -1;
      } while (iVar16 != 0);
      uVar8 = (caravanWork->gObjWork).m_maxHp;
      if (uVar8 < (caravanWork->gObjWork).m_hp) {
        (caravanWork->gObjWork).m_hp = uVar8;
      }
      dVar4 = DOUBLE_803309a0;
      fVar3 = FLOAT_8033099c;
      fVar2 = FLOAT_80330998;
      if ((caravanWork->gObjWork).m_statusTimers[9] != 0) {
        (caravanWork->gObjWork).m_strength =
             (uint16_t)
             (int)((float)((double)CONCAT44(0x43300000,(uint)(caravanWork->gObjWork).m_strength) -
                          DOUBLE_803309a0) *
                  (FLOAT_8033099c *
                   (float)((double)CONCAT44(0x43300000,
                                            (uint)*(ushort *)
                                                   (Game.game.unk_flat3_field_8_0xc7dc + 0x38)) -
                          DOUBLE_803309a0) + FLOAT_80330998));
        (caravanWork->gObjWork).m_magic =
             (uint16_t)
             (int)((float)((double)CONCAT44(0x43300000,(uint)(caravanWork->gObjWork).m_magic) -
                          dVar4) *
                  (fVar3 * (float)((double)CONCAT44(0x43300000,
                                                    (uint)*(ushort *)
                                                           (Game.game.unk_flat3_field_8_0xc7dc +
                                                           0x38)) - dVar4) + fVar2));
        local_30 = (double)CONCAT44(0x43300000,(uint)(caravanWork->gObjWork).m_defense);
        (caravanWork->gObjWork).m_defense =
             (uint16_t)
             (int)((float)(local_30 - dVar4) *
                  (fVar3 * (float)((double)CONCAT44(0x43300000,
                                                    (uint)*(ushort *)
                                                           (Game.game.unk_flat3_field_8_0xc7dc +
                                                           0x38)) - dVar4) + fVar2));
      }
      if ((caravanWork->gObjWork).m_statusTimers[4] != 0) {
        local_20 = (double)CONCAT44(0x43300000,(uint)(caravanWork->gObjWork).m_defense);
        (caravanWork->gObjWork).m_defense =
             (uint16_t)
             (int)((float)(local_20 - DOUBLE_803309a0) *
                  (FLOAT_8033099c *
                   (float)((double)CONCAT44(0x43300000,
                                            (uint)*(ushort *)
                                                   (Game.game.unk_flat3_field_8_0xc7dc + 0x3e)) -
                          DOUBLE_803309a0) + FLOAT_80330998));
      }
      if ((caravanWork->gObjWork).m_statusTimers[6] != 0) {
        local_20 = (double)CONCAT44(0x43300000,(uint)(caravanWork->gObjWork).m_defense);
        (caravanWork->gObjWork).m_defense =
             (uint16_t)
             (int)((float)(local_20 - DOUBLE_803309a0) *
                  (FLOAT_8033099c *
                   (float)((double)CONCAT44(0x43300000,
                                            (uint)*(ushort *)
                                                   (Game.game.unk_flat3_field_8_0xc7dc + 0x44)) -
                          DOUBLE_803309a0) + FLOAT_80330998));
      }
      uVar8 = (caravanWork->gObjWork).m_strength;
      uVar7 = 99;
      if (uVar8 < 100) {
        uVar7 = uVar8;
      }
      (caravanWork->gObjWork).m_strength = uVar7;
      uVar8 = (caravanWork->gObjWork).m_defense;
      uVar7 = 99;
      if (uVar8 < 100) {
        uVar7 = uVar8;
      }
      (caravanWork->gObjWork).m_defense = uVar7;
      uVar8 = (caravanWork->gObjWork).m_magic;
      uVar7 = 99;
      if (uVar8 < 100) {
        uVar7 = uVar8;
      }
      (caravanWork->gObjWork).m_magic = uVar7;
      uVar8 = 99;
      if (caravanWork->m_baseStrength < 100) {
        uVar8 = caravanWork->m_baseStrength;
      }
      caravanWork->m_baseStrength = uVar8;
      uVar8 = 99;
      if (caravanWork->m_baseDefense < 100) {
        uVar8 = caravanWork->m_baseDefense;
      }
      caravanWork->m_baseDefense = uVar8;
      uVar8 = 99;
      if (caravanWork->m_baseMagic < 100) {
        uVar8 = caravanWork->m_baseMagic;
      }
      caravanWork->m_baseMagic = uVar8;
      return;
    }
  } while( true );
}

