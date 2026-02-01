// Function: SetLoadData__14CMemoryCardManFv
// Entry: 800c2dbc
// Size: 2272 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetLoadData__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  uint16_t *puVar1;
  byte *pbVar2;
  int iVar3;
  int32_t iVar4;
  int32_t iVar5;
  int32_t iVar6;
  int32_t iVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  uint8_t *puVar12;
  int iVar13;
  undefined2 uVar14;
  CCaravanWork *pCVar15;
  CCaravanWork *caravanWork;
  uint8_t *puVar16;
  uint8_t *puVar17;
  int iVar18;
  uint8_t *puVar19;
  int iVar20;
  
  puVar19 = memoryCardMan->m_saveBuffer;
  uVar10 = strlen(PTR_DAT_8032e85c);
  iVar11 = memcmp(puVar19,PTR_DAT_8032e85c,uVar10);
  if (iVar11 == 0) {
    uVar10 = strlen(PTR_DAT_8032e860);
    iVar11 = memcmp(puVar19 + 4,PTR_DAT_8032e860,uVar10);
    if (iVar11 == 0) {
      uVar10 = strlen(PTR_DAT_8032e864);
      iVar11 = memcmp(puVar19 + 8,PTR_DAT_8032e864,uVar10);
      if (iVar11 == 0) {
        uVar10 = strlen(PTR_DAT_8032e868);
        iVar11 = memcmp(puVar19 + 0xc,PTR_DAT_8032e868,uVar10);
        if (iVar11 == 0) {
          if (puVar19[0x10] == 'E') {
            Game.game.m_gameWork.m_scriptSysVal0 = puVar19[0x20];
            Game.game.m_gameWork.m_scriptSysVal1 = puVar19[0x21];
            Game.game.m_gameWork.m_scriptSysVal2 = puVar19[0x22];
            Game.game.m_gameWork.m_scriptSysVal3 = puVar19[0x23];
            Game.game.m_gameWork.m_timerA = *(int32_t *)(puVar19 + 0x24);
            Game.game.m_gameWork.m_scriptGlobalTime = *(int32_t *)(puVar19 + 0x28);
            Game.game.m_gameWork.m_frameCounter = *(int32_t *)(puVar19 + 0x2c);
            memcpy(Game.game.m_gameWork.m_wmBackupParams,puVar19 + 0x30,0x10);
            memcpy(Game.game.m_gameWork.m_bossArtifactStageTable,puVar19 + 0x40,0x3c);
            memcpy(Game.game.m_gameWork.m_unkStageTable,puVar19 + 0x7c,0x3c);
            Game.game.m_gameWork.m_chaliceElement = *(int32_t *)(puVar19 + 0xb8);
            memcpy(Game.game.m_gameWork.m_linkTable,puVar19 + 0xc0,0x1000);
            memcpy(Game.game.m_gameWork.m_townName,puVar19 + 0x10c0,0x10);
            memcpy(Game.game.m_gameWork.m_eventFlags + 8,puVar19 + 0x10d0,0x100);
            memcpy(Game.game.m_gameWork.m_eventWork + 4,puVar19 + 0x11d0,0x200);
            Game.game.m_gameWork.m_mcSerial0 = *(uint32_t *)(puVar19 + 0x13d0);
            Game.game.m_gameWork.m_mcSerial1 = *(uint32_t *)(puVar19 + 0x13d4);
            Game.game.m_gameWork.m_mcRandom = *(uint32_t *)(puVar19 + 0x13d8);
            Game.game.m_gameWork.m_mcHasSerial._0_1_ = puVar19[0x13dc];
            SetBgmMasterVolume__6CSoundFi(&Sound,(int)(char)puVar19[0x13dd]);
            SetSeMasterVolume__6CSoundFi(&Sound,(int)(char)puVar19[0x13de]);
            uVar10 = GetSoundMode__9CRedSoundFv(0x802f26dc);
            uVar8 = countLeadingZeros(uVar10);
            SetStereo__6CSoundFi(&Sound,uVar8 >> 5);
            iVar18 = -0x7fde1140;
            Game.game.m_gameWork.m_gameInitFlag =
                 (byte)((byte)((uint)-(int)(char)puVar19[0x13e0] >> 0x18) |
                       (char)puVar19[0x13e0] >> 7) >> 7;
            iVar11 = 0;
            Game.game.m_gameWork.m_spModeFlags[0] =
                 (byte)((byte)((uint)-(int)(char)puVar19[0x13e1] >> 0x18) |
                       (char)puVar19[0x13e1] >> 7) >> 7;
            Game.game.m_gameWork.m_spModeFlags[1] =
                 (byte)((byte)((uint)-(int)(char)puVar19[0x13e2] >> 0x18) |
                       (char)puVar19[0x13e2] >> 7) >> 7;
            Game.game.m_gameWork.m_spModeFlags[2] =
                 (byte)((byte)((uint)-(int)(char)puVar19[0x13e3] >> 0x18) |
                       (char)puVar19[0x13e3] >> 7) >> 7;
            Game.game.m_gameWork.m_spModeFlags[3] =
                 (byte)((byte)((uint)-(int)(char)puVar19[0x13e4] >> 0x18) |
                       (char)puVar19[0x13e4] >> 7) >> 7;
            puVar17 = puVar19;
            do {
              uVar8 = 0;
              puVar16 = puVar17 + 0x14d0;
              caravanWork = (CCaravanWork *)(iVar18 + 0x13f0);
              iVar9 = 0x40;
              puVar12 = puVar16;
              do {
                if (*(short *)(puVar12 + 0x3c) != -1) {
                  uVar8 = uVar8 + 1;
                }
                puVar12 = puVar12 + 2;
                iVar9 = iVar9 + -1;
              } while (iVar9 != 0);
              if (uVar8 != *(ushort *)(puVar17 + 0x14f8)) {
                if (System.m_execParam != 0) {
                  Printf__7CSystemFPce(&System,&DAT_801dafb4,iVar11);
                }
                *(short *)(puVar17 + 0x14f8) = (short)uVar8;
              }
              *(undefined2 *)(iVar18 + 0x1404) = *(undefined2 *)puVar16;
              *(undefined2 *)(iVar18 + 0x1406) = *(undefined2 *)(puVar17 + 0x14d2);
              *(undefined2 *)(iVar18 + 0x1408) = *(undefined2 *)(puVar17 + 0x14d4);
              *(undefined2 *)(iVar18 + 0x140a) = *(undefined2 *)(puVar17 + 0x14d6);
              *(undefined2 *)(iVar18 + 0x140c) = *(undefined2 *)(puVar17 + 0x14d8);
              *(undefined2 *)(iVar18 + 0x140e) = *(undefined2 *)(puVar17 + 0x14da);
              *(undefined2 *)(iVar18 + 0x1410) = *(undefined2 *)(puVar17 + 0x14dc);
              *(undefined2 *)(iVar18 + 0x1412) = *(undefined2 *)(puVar17 + 0x14de);
              *(undefined2 *)(iVar18 + 0x17a8) = *(undefined2 *)(puVar17 + 0x14e2);
              *(undefined2 *)(iVar18 + 0x17aa) = *(undefined2 *)(puVar17 + 0x14e4);
              *(undefined2 *)(iVar18 + 0x17ac) = *(undefined2 *)(puVar17 + 0x14e6);
              *(undefined2 *)(iVar18 + 0x17ae) = *(undefined2 *)(puVar17 + 0x14e8);
              *(undefined2 *)(iVar18 + 0x17b0) = *(undefined2 *)(puVar17 + 0x14ea);
              *(undefined2 *)(iVar18 + 0x17b2) = *(undefined2 *)(puVar17 + 0x14ec);
              *(undefined2 *)(iVar18 + 0x17b4) = *(undefined2 *)(puVar17 + 0x14ee);
              *(undefined2 *)(iVar18 + 0x17b6) = *(undefined2 *)(puVar17 + 0x14f0);
              *(undefined2 *)(iVar18 + 0x17b8) = *(undefined2 *)(puVar17 + 0x14f4);
              *(undefined2 *)(iVar18 + 0x14a4) = *(undefined2 *)(puVar17 + 0x14f8);
              *(undefined2 *)(iVar18 + 0x17cc) = *(undefined2 *)(puVar17 + 0x14fa);
              *(undefined2 *)(iVar18 + 0x17ce) = *(undefined2 *)(puVar17 + 0x14fc);
              *(undefined2 *)(iVar18 + 0x17d0) = *(undefined2 *)(puVar17 + 0x14fe);
              *(undefined2 *)(iVar18 + 0x17d2) = *(undefined2 *)(puVar17 + 0x1500);
              *(undefined2 *)(iVar18 + 0x17d4) = *(undefined2 *)(puVar17 + 0x1502);
              *(undefined2 *)(iVar18 + 0x149c) = *(undefined2 *)(puVar17 + 0x1504);
              *(undefined2 *)(iVar18 + 0x149e) = *(undefined2 *)(puVar17 + 0x1506);
              *(undefined2 *)(iVar18 + 0x14a0) = *(undefined2 *)(puVar17 + 0x1508);
              *(undefined2 *)(iVar18 + 0x14a2) = *(undefined2 *)(puVar17 + 0x150a);
              iVar9 = 4;
              puVar12 = puVar16;
              pCVar15 = caravanWork;
              do {
                pCVar15->m_inventoryItems[0] = *(uint16_t *)(puVar12 + 0x3c);
                pCVar15->m_inventoryItems[1] = *(uint16_t *)(puVar12 + 0x3e);
                pCVar15->m_inventoryItems[2] = *(uint16_t *)(puVar12 + 0x40);
                pCVar15->m_inventoryItems[3] = *(uint16_t *)(puVar12 + 0x42);
                pCVar15->m_inventoryItems[4] = *(uint16_t *)(puVar12 + 0x44);
                pCVar15->m_inventoryItems[5] = *(uint16_t *)(puVar12 + 0x46);
                pCVar15->m_inventoryItems[6] = *(uint16_t *)(puVar12 + 0x48);
                pCVar15->m_inventoryItems[7] = *(uint16_t *)(puVar12 + 0x4a);
                pCVar15->m_inventoryItems[8] = *(uint16_t *)(puVar12 + 0x4c);
                pCVar15->m_inventoryItems[9] = *(uint16_t *)(puVar12 + 0x4e);
                pCVar15->m_inventoryItems[10] = *(uint16_t *)(puVar12 + 0x50);
                pCVar15->m_inventoryItems[0xb] = *(uint16_t *)(puVar12 + 0x52);
                pCVar15->m_inventoryItems[0xc] = *(uint16_t *)(puVar12 + 0x54);
                pCVar15->m_inventoryItems[0xd] = *(uint16_t *)(puVar12 + 0x56);
                pCVar15->m_inventoryItems[0xe] = *(uint16_t *)(puVar12 + 0x58);
                puVar1 = (uint16_t *)(puVar12 + 0x5a);
                puVar12 = puVar12 + 0x20;
                pCVar15->m_inventoryItems[0xf] = *puVar1;
                pCVar15 = (CCaravanWork *)&(pCVar15->gObjWork).m_magic;
                iVar9 = iVar9 + -1;
              } while (iVar9 != 0);
              *(undefined4 *)(iVar18 + 0x17a4) = *(undefined4 *)(puVar17 + 0x15b8);
              *(undefined4 *)(iVar18 + 0x15f0) = *(undefined4 *)(puVar17 + 0x15bc);
              memcpy((void *)(iVar18 + 0x17ba),puVar17 + 0x15c0,0x10);
              iVar9 = 0;
              *(undefined4 *)(iVar18 + 0x17d8) = *(undefined4 *)(puVar17 + 0x15d0);
              pCVar15 = caravanWork;
              puVar12 = puVar16;
              do {
                pCVar15->m_letter0[0] =
                     (byte)((puVar12[0x104] >> 3 & 1) << 3) | pCVar15->m_letter0[0] & 0xf7;
                *(ushort *)pCVar15->m_letter0 =
                     *(ushort *)(puVar12 + 0x104) & 0x7fc | *(ushort *)pCVar15->m_letter0 & 0xf803;
                *(uint *)pCVar15->m_letter0 =
                     *(uint *)(puVar12 + 0x104) & 0x3fe00 | *(uint *)pCVar15->m_letter0 & 0xfffc01ff
                ;
                *(ushort *)(pCVar15->m_letter0 + 2) =
                     *(ushort *)(puVar12 + 0x106) & 0x1ff |
                     *(ushort *)(pCVar15->m_letter0 + 2) & 0xfe00;
                memcpy(pCVar15->m_letter0 + 4,puVar12 + 0x108,8);
                iVar9 = iVar9 + 1;
                pCVar15->m_letter0[0] = puVar12[0x104] & 0x80 | pCVar15->m_letter0[0] & 0x7f;
                pCVar15->m_letter0[0] = puVar12[0x104] & 0x40 | pCVar15->m_letter0[0] & 0xbf;
                pCVar15->m_letter0[0] = puVar12[0x104] & 0x20 | pCVar15->m_letter0[0] & 0xdf;
                pbVar2 = puVar12 + 0x104;
                puVar12 = puVar12 + 0xc;
                pCVar15->m_letter0[0] = *pbVar2 & 0x10 | pCVar15->m_letter0[0] & 0xef;
                pCVar15 = (CCaravanWork *)&(pCVar15->gObjWork).m_ownerObj;
              } while (iVar9 < 100);
              iVar9 = 0;
              iVar20 = 0x30;
              do {
                iVar3 = iVar9 >> 0x1f;
                if ((*(uint *)(puVar16 + (iVar9 >> 5) * 4 + 0xbc) &
                    1 << (iVar3 * 0x20 | (uint)(iVar9 * 0x8000000 + iVar3) >> 0x1b) - iVar3) == 0) {
                  caravanWork->m_artifacts[iVar9] = 0xffff;
                }
                else {
                  caravanWork->m_artifacts[iVar9] = (short)iVar9 + 0x9f;
                }
                iVar13 = iVar9 + 1;
                iVar3 = iVar13 >> 0x1f;
                if ((*(uint *)(puVar16 + (iVar13 >> 5) * 4 + 0xbc) &
                    1 << (iVar3 * 0x20 | (uint)(iVar13 * 0x8000000 + iVar3) >> 0x1b) - iVar3) == 0)
                {
                  caravanWork->m_artifacts[iVar9 + 1] = 0xffff;
                }
                else {
                  caravanWork->m_artifacts[iVar9 + 1] = (short)iVar9 + 0xa0;
                }
                iVar9 = iVar9 + 2;
                iVar20 = iVar20 + -1;
              } while (iVar20 != 0);
              *(undefined2 *)(iVar18 + 0x15f4) = *(undefined2 *)(puVar17 + 0x1598);
              *(undefined2 *)(iVar18 + 0x1604) = *(undefined2 *)(puVar17 + 0x15a8);
              *(undefined2 *)(iVar18 + 0x15f6) = *(undefined2 *)(puVar17 + 0x159a);
              *(undefined2 *)(iVar18 + 0x1606) = *(undefined2 *)(puVar17 + 0x15aa);
              *(undefined2 *)(iVar18 + 0x15f8) = *(undefined2 *)(puVar17 + 0x159c);
              *(undefined2 *)(iVar18 + 0x1608) = *(undefined2 *)(puVar17 + 0x15ac);
              *(undefined2 *)(iVar18 + 0x15fa) = *(undefined2 *)(puVar17 + 0x159e);
              *(undefined2 *)(iVar18 + 0x160a) = *(undefined2 *)(puVar17 + 0x15ae);
              *(undefined2 *)(iVar18 + 0x15fc) = *(undefined2 *)(puVar17 + 0x15a0);
              *(undefined2 *)(iVar18 + 0x160c) = *(undefined2 *)(puVar17 + 0x15b0);
              *(undefined2 *)(iVar18 + 0x15fe) = *(undefined2 *)(puVar17 + 0x15a2);
              *(undefined2 *)(iVar18 + 0x160e) = *(undefined2 *)(puVar17 + 0x15b2);
              *(undefined2 *)(iVar18 + 0x1600) = *(undefined2 *)(puVar17 + 0x15a4);
              *(undefined2 *)(iVar18 + 0x1610) = *(undefined2 *)(puVar17 + 0x15b4);
              *(undefined2 *)(iVar18 + 0x1602) = *(undefined2 *)(puVar17 + 0x15a6);
              *(undefined2 *)(iVar18 + 0x1612) = *(undefined2 *)(puVar17 + 0x15b6);
              *(undefined4 *)(iVar18 + 0x1794) = *(undefined4 *)(puVar17 + 0x1a84);
              memcpy((void *)(iVar18 + 0x1c94),puVar17 + 0x1a88,0x100);
              memcpy((void *)(iVar18 + 0x1d94),puVar17 + 0x1b88,0x200);
              *(undefined4 *)(iVar18 + 0x1798) = *(undefined4 *)(puVar17 + 0x1d88);
              *(undefined4 *)(iVar18 + 0x179c) = *(undefined4 *)(puVar17 + 0x1d8c);
              *(uint8_t *)(iVar18 + 0x1f95) = puVar17[0x1d90];
              *(uint8_t *)(iVar18 + 0x1f96) = puVar17[0x1d91];
              *(uint8_t *)(iVar18 + 0x200e) = puVar17[0x1d92];
              *(undefined4 *)(iVar18 + 0x2010) = *(undefined4 *)(puVar17 + 0x1d94);
              *(undefined4 *)(iVar18 + 0x2014) = *(undefined4 *)(puVar17 + 0x1da0);
              uVar10 = *(undefined4 *)(puVar17 + 0x1d98);
              *(undefined4 *)(iVar18 + 0x201c) = *(undefined4 *)(puVar17 + 0x1d9c);
              *(undefined4 *)(iVar18 + 0x2018) = uVar10;
              *(undefined4 *)(iVar18 + 0x1400) = *(undefined4 *)(puVar17 + 0x1da4);
              uVar14 = GetArtifactIncludeHpMax__12CCaravanWorkFv(caravanWork);
              iVar11 = iVar11 + 1;
              *(undefined2 *)(iVar18 + 0x140a) = uVar14;
              iVar7 = Game.game.m_gameWork.m_wmBackupParams[3];
              iVar6 = Game.game.m_gameWork.m_wmBackupParams[2];
              iVar5 = Game.game.m_gameWork.m_wmBackupParams[1];
              iVar4 = Game.game.m_gameWork.m_wmBackupParams[0];
              puVar17 = puVar17 + 0x9c0;
              iVar18 = iVar18 + 0xc30;
            } while (iVar11 < 8);
            if (Game.game.m_caravanWorkArr[Game.game.m_gameWork.m_wmBackupParams[0]].m_shopState ==
                0) {
              Game.game.m_gameWork.m_wmBackupParams[0] = -1;
            }
            if (Game.game.m_caravanWorkArr[iVar4].m_shopBusyFlag != '\0') {
              Game.game.m_gameWork.m_wmBackupParams[0] = -1;
            }
            if (Game.game.m_caravanWorkArr[Game.game.m_gameWork.m_wmBackupParams[1]].m_shopState ==
                0) {
              Game.game.m_gameWork.m_wmBackupParams[1] = -1;
            }
            if (Game.game.m_caravanWorkArr[iVar5].m_shopBusyFlag != '\0') {
              Game.game.m_gameWork.m_wmBackupParams[1] = -1;
            }
            if (Game.game.m_caravanWorkArr[Game.game.m_gameWork.m_wmBackupParams[2]].m_shopState ==
                0) {
              Game.game.m_gameWork.m_wmBackupParams[2] = -1;
            }
            if (Game.game.m_caravanWorkArr[iVar6].m_shopBusyFlag != '\0') {
              Game.game.m_gameWork.m_wmBackupParams[2] = -1;
            }
            if (Game.game.m_caravanWorkArr[Game.game.m_gameWork.m_wmBackupParams[3]].m_shopState ==
                0) {
              Game.game.m_gameWork.m_wmBackupParams[3] = -1;
            }
            if (Game.game.m_caravanWorkArr[iVar7].m_shopBusyFlag != '\0') {
              Game.game.m_gameWork.m_wmBackupParams[3] = -1;
            }
            LoadScript__5CGameFPc(&Game.game,puVar19 + 0x62d0);
            LoadFurTexBuffer__6CCharaFPUs(&Chara,puVar19 + 0x6ad0);
          }
          else if (System.m_execParam != 0) {
            Printf__7CSystemFPce(&System,s_Bloken_load_data___801daf78);
          }
        }
        else if (System.m_execParam != 0) {
          Printf__7CSystemFPce(&System,s_The_version_of_load_data_is_diff_801daf8c);
        }
      }
      else if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_Bloken_load_data___801daf78);
      }
    }
    else if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_Bloken_load_data___801daf78);
    }
  }
  else if (System.m_execParam != 0) {
    Printf__7CSystemFPce(&System,s_Bloken_load_data___801daf78);
  }
  return;
}

