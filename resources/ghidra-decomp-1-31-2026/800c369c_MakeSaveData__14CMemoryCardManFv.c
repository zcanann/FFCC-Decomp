// Function: MakeSaveData__14CMemoryCardManFv
// Entry: 800c369c
// Size: 2576 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void MakeSaveData__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  undefined2 *puVar1;
  byte bVar2;
  uint uVar3;
  uint8_t uVar4;
  uint8_t uVar5;
  int32_t iVar6;
  int32_t iVar7;
  int32_t iVar8;
  int32_t iVar9;
  uint32_t uVar10;
  uint uVar11;
  uint8_t *puVar12;
  undefined4 uVar13;
  uint8_t uVar15;
  int iVar14;
  uint8_t *puVar16;
  int iVar17;
  int iVar18;
  uint *puVar19;
  int iVar20;
  int iVar21;
  byte *pbVar22;
  int iVar23;
  uint8_t *puVar24;
  int iVar25;
  uint8_t *puVar26;
  int iVar27;
  undefined8 local_40 [2];
  
  puVar12 = memoryCardMan->m_saveBuffer;
  if (puVar12 != (uint8_t *)0x0) {
    memset(puVar12,0,0xa000);
  }
  else {
    if (puVar12 == (uint8_t *)0x0) {
      puVar12 = (uint8_t *)
                __nwa__FUlPQ27CMemory6CStagePci
                          (0xa000,memoryCardMan->mStage,s_memorycard_cpp_801daea8,0x2ab);
      memoryCardMan->m_saveBuffer = puVar12;
      if ((memoryCardMan->m_saveBuffer == (uint8_t *)0x0) && (System.m_execParam != 0)) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801daeb8,s_memorycard_cpp_801daea8,
                   0x2ad);
      }
    }
    memset(memoryCardMan->m_saveBuffer,0,0xa000);
  }
  puVar12 = memoryCardMan->m_saveBuffer;
  local_40[0] = OSGetTime();
  memcpy(puVar12 + 0x8ad0,local_40,8);
  uVar13 = strlen(PTR_DAT_8032e85c);
  memcpy(puVar12,PTR_DAT_8032e85c,uVar13);
  uVar13 = strlen(PTR_DAT_8032e860);
  memcpy(puVar12 + 4,PTR_DAT_8032e860,uVar13);
  uVar13 = strlen(PTR_DAT_8032e864);
  memcpy(puVar12 + 8,PTR_DAT_8032e864,uVar13);
  uVar13 = strlen(PTR_DAT_8032e868);
  memcpy(puVar12 + 0xc,PTR_DAT_8032e868,uVar13);
  puVar12[0x10] = 'E';
  uVar13 = Rand__5CMathFUl(&Math,0x7fffffff);
  *(undefined4 *)(puVar12 + 0x18) = uVar13;
  uVar15 = Rand__5CMathFUl(&Math,0xff);
  puVar12[0x11] = uVar15;
  puVar12[0x12] = '\0';
  iVar9 = Game.game.m_gameWork.m_wmBackupParams[3];
  iVar8 = Game.game.m_gameWork.m_wmBackupParams[2];
  iVar7 = Game.game.m_gameWork.m_wmBackupParams[1];
  iVar6 = Game.game.m_gameWork.m_wmBackupParams[0];
  if (Game.game.m_caravanWorkArr[Game.game.m_gameWork.m_wmBackupParams[0]].m_shopState == 0) {
    Game.game.m_gameWork.m_wmBackupParams[0] = -1;
  }
  if (Game.game.m_caravanWorkArr[iVar6].m_shopBusyFlag != '\0') {
    Game.game.m_gameWork.m_wmBackupParams[0] = -1;
  }
  if (Game.game.m_caravanWorkArr[Game.game.m_gameWork.m_wmBackupParams[1]].m_shopState == 0) {
    Game.game.m_gameWork.m_wmBackupParams[1] = -1;
  }
  if (Game.game.m_caravanWorkArr[iVar7].m_shopBusyFlag != '\0') {
    Game.game.m_gameWork.m_wmBackupParams[1] = -1;
  }
  if (Game.game.m_caravanWorkArr[Game.game.m_gameWork.m_wmBackupParams[2]].m_shopState == 0) {
    Game.game.m_gameWork.m_wmBackupParams[2] = -1;
  }
  if (Game.game.m_caravanWorkArr[iVar8].m_shopBusyFlag != '\0') {
    Game.game.m_gameWork.m_wmBackupParams[2] = -1;
  }
  if (Game.game.m_caravanWorkArr[Game.game.m_gameWork.m_wmBackupParams[3]].m_shopState == 0) {
    Game.game.m_gameWork.m_wmBackupParams[3] = -1;
  }
  if (Game.game.m_caravanWorkArr[iVar9].m_shopBusyFlag != '\0') {
    Game.game.m_gameWork.m_wmBackupParams[3] = -1;
  }
  uVar15 = Game.game.m_gameWork.m_scriptSysVal1;
  uVar4 = Game.game.m_gameWork.m_scriptSysVal2;
  uVar5 = Game.game.m_gameWork.m_scriptSysVal3;
  puVar12[0x20] = Game.game.m_gameWork.m_scriptSysVal0;
  puVar12[0x21] = uVar15;
  puVar12[0x22] = uVar4;
  puVar12[0x23] = uVar5;
  *(int32_t *)(puVar12 + 0x24) = Game.game.m_gameWork.m_timerA;
  *(int32_t *)(puVar12 + 0x28) = Game.game.m_gameWork.m_scriptGlobalTime;
  *(int32_t *)(puVar12 + 0x2c) = Game.game.m_gameWork.m_frameCounter;
  memcpy(puVar12 + 0x30,0x8021eee0,0x10);
  memcpy(puVar12 + 0x40,0x8021eef0,0x3c);
  memcpy(puVar12 + 0x7c,0x8021ef2c,0x3c);
  *(int32_t *)(puVar12 + 0xb8) = Game.game.m_gameWork.m_chaliceElement;
  memcpy(puVar12 + 0xc0,0x8021ef68,0x1000);
  memcpy(puVar12 + 0x10c0,0x8021ff68,0x10);
  memcpy(puVar12 + 0x10d0,0x8021ff94,0x100);
  memcpy(puVar12 + 0x11d0,0x80220094,0x200);
  memcpy(puVar12 + 0x11d0,0x80220094,0x200);
  uVar10 = Game.game.m_gameWork.m_mcSerial0;
  *(uint32_t *)(puVar12 + 0x13d4) = Game.game.m_gameWork.m_mcSerial1;
  *(uint32_t *)(puVar12 + 0x13d0) = uVar10;
  *(uint32_t *)(puVar12 + 0x13d8) = Game.game.m_gameWork.m_mcRandom;
  puVar12[0x13dc] = Game.game.m_gameWork.m_mcHasSerial._0_1_;
  puVar12[0x13dd] = (uint8_t)Sound._8880_4_;
  puVar12[0x13de] = (uint8_t)Sound._8884_4_;
  puVar12[0x13de] = (uint8_t)Sound._8884_4_;
  uVar13 = GetSoundMode__9CRedSoundFv(0x802f26dc);
  uVar11 = countLeadingZeros(uVar13);
  iVar25 = 0;
  puVar12[0x13df] = (byte)(-(uVar11 >> 5) >> 0x1f);
  puVar12[0x13e0] = (byte)(-(uint)Game.game.m_gameWork.m_gameInitFlag >> 0x1f);
  puVar12[0x13e1] = (byte)(-(uint)Game.game.m_gameWork.m_spModeFlags[0] >> 0x1f);
  puVar12[0x13e2] = (byte)(-(uint)Game.game.m_gameWork.m_spModeFlags[1] >> 0x1f);
  puVar12[0x13e3] = (byte)(-(uint)Game.game.m_gameWork.m_spModeFlags[2] >> 0x1f);
  puVar12[0x13e4] = (byte)(-(uint)Game.game.m_gameWork.m_spModeFlags[3] >> 0x1f);
  iVar21 = -0x7fde1140;
  puVar26 = puVar12;
  do {
    iVar23 = iVar21 + 0x13f0;
    puVar24 = puVar26 + 0x14d0;
    if ((*(int *)(iVar21 + 0x1794) == 0) || (*(char *)(iVar21 + 0x200e) != '\0')) {
      if (*(int *)(iVar21 + 0x1794) == 0) {
        *(undefined4 *)(iVar21 + 0x2010) = 0;
        *(undefined *)(iVar21 + 0x200e) = 0;
      }
    }
    else {
      uVar13 = Rand__5CMathFUl(&Math,0x7fffffff);
      *(undefined4 *)(iVar21 + 0x2010) = uVar13;
      *(undefined *)(iVar21 + 0x200e) = 1;
    }
    *(undefined2 *)puVar24 = *(undefined2 *)(iVar21 + 0x1404);
    *(undefined2 *)(puVar26 + 0x14d2) = *(undefined2 *)(iVar21 + 0x1406);
    *(undefined2 *)(puVar26 + 0x14d4) = *(undefined2 *)(iVar21 + 0x1408);
    *(undefined2 *)(puVar26 + 0x14d6) = *(undefined2 *)(iVar21 + 0x140a);
    *(undefined2 *)(puVar26 + 0x14d8) = *(undefined2 *)(iVar21 + 0x140c);
    *(undefined2 *)(puVar26 + 0x14da) = *(undefined2 *)(iVar21 + 0x140e);
    *(undefined2 *)(puVar26 + 0x14dc) = *(undefined2 *)(iVar21 + 0x1410);
    *(undefined2 *)(puVar26 + 0x14de) = *(undefined2 *)(iVar21 + 0x1412);
    *(undefined2 *)(puVar26 + 0x14e2) = *(undefined2 *)(iVar21 + 0x17a8);
    *(undefined2 *)(puVar26 + 0x14e4) = *(undefined2 *)(iVar21 + 0x17aa);
    *(undefined2 *)(puVar26 + 0x14e6) = *(undefined2 *)(iVar21 + 0x17ac);
    *(undefined2 *)(puVar26 + 0x14e8) = *(undefined2 *)(iVar21 + 0x17ae);
    *(undefined2 *)(puVar26 + 0x14ea) = *(undefined2 *)(iVar21 + 0x17b0);
    *(undefined2 *)(puVar26 + 0x14ec) = *(undefined2 *)(iVar21 + 0x17b2);
    *(undefined2 *)(puVar26 + 0x14ee) = *(undefined2 *)(iVar21 + 0x17b4);
    *(undefined2 *)(puVar26 + 0x14f0) = *(undefined2 *)(iVar21 + 0x17b6);
    *(undefined2 *)(puVar26 + 0x14f4) = *(undefined2 *)(iVar21 + 0x17b8);
    *(undefined2 *)(puVar26 + 0x14f8) = *(undefined2 *)(iVar21 + 0x14a4);
    *(undefined2 *)(puVar26 + 0x14fa) = *(undefined2 *)(iVar21 + 0x17cc);
    *(undefined2 *)(puVar26 + 0x14fc) = *(undefined2 *)(iVar21 + 0x17ce);
    *(undefined2 *)(puVar26 + 0x14fe) = *(undefined2 *)(iVar21 + 0x17d0);
    *(undefined2 *)(puVar26 + 0x1500) = *(undefined2 *)(iVar21 + 0x17d2);
    *(undefined2 *)(puVar26 + 0x1502) = *(undefined2 *)(iVar21 + 0x17d4);
    *(undefined2 *)(puVar26 + 0x1504) = *(undefined2 *)(iVar21 + 0x149c);
    *(undefined2 *)(puVar26 + 0x1506) = *(undefined2 *)(iVar21 + 0x149e);
    *(undefined2 *)(puVar26 + 0x1508) = *(undefined2 *)(iVar21 + 0x14a0);
    *(undefined2 *)(puVar26 + 0x150a) = *(undefined2 *)(iVar21 + 0x14a2);
    iVar27 = 4;
    iVar14 = iVar23;
    puVar16 = puVar24;
    do {
      *(undefined2 *)(puVar16 + 0x3c) = *(undefined2 *)(iVar14 + 0xb6);
      *(undefined2 *)(puVar16 + 0x3e) = *(undefined2 *)(iVar14 + 0xb8);
      *(undefined2 *)(puVar16 + 0x40) = *(undefined2 *)(iVar14 + 0xba);
      *(undefined2 *)(puVar16 + 0x42) = *(undefined2 *)(iVar14 + 0xbc);
      *(undefined2 *)(puVar16 + 0x44) = *(undefined2 *)(iVar14 + 0xbe);
      *(undefined2 *)(puVar16 + 0x46) = *(undefined2 *)(iVar14 + 0xc0);
      *(undefined2 *)(puVar16 + 0x48) = *(undefined2 *)(iVar14 + 0xc2);
      *(undefined2 *)(puVar16 + 0x4a) = *(undefined2 *)(iVar14 + 0xc4);
      *(undefined2 *)(puVar16 + 0x4c) = *(undefined2 *)(iVar14 + 0xc6);
      *(undefined2 *)(puVar16 + 0x4e) = *(undefined2 *)(iVar14 + 200);
      *(undefined2 *)(puVar16 + 0x50) = *(undefined2 *)(iVar14 + 0xca);
      *(undefined2 *)(puVar16 + 0x52) = *(undefined2 *)(iVar14 + 0xcc);
      *(undefined2 *)(puVar16 + 0x54) = *(undefined2 *)(iVar14 + 0xce);
      *(undefined2 *)(puVar16 + 0x56) = *(undefined2 *)(iVar14 + 0xd0);
      *(undefined2 *)(puVar16 + 0x58) = *(undefined2 *)(iVar14 + 0xd2);
      puVar1 = (undefined2 *)(iVar14 + 0xd4);
      iVar14 = iVar14 + 0x20;
      *(undefined2 *)(puVar16 + 0x5a) = *puVar1;
      puVar16 = puVar16 + 0x20;
      iVar27 = iVar27 + -1;
    } while (iVar27 != 0);
    *(undefined4 *)(puVar26 + 0x15b8) = *(undefined4 *)(iVar21 + 0x17a4);
    *(undefined4 *)(puVar26 + 0x15bc) = *(undefined4 *)(iVar21 + 0x15f0);
    memcpy(puVar26 + 0x15c0,iVar21 + 0x17ba,0x10);
    iVar27 = 0;
    *(undefined4 *)(puVar26 + 0x15d0) = *(undefined4 *)(iVar21 + 0x17d8);
    puVar16 = puVar24;
    iVar14 = iVar23;
    do {
      puVar16[0x104] = (byte)((*(byte *)(iVar14 + 0x3ec) >> 3 & 1) << 3) | puVar16[0x104] & 0xf7;
      *(ushort *)(puVar16 + 0x104) =
           *(ushort *)(iVar14 + 0x3ec) & 0x7fc | *(ushort *)(puVar16 + 0x104) & 0xf803;
      *(uint *)(puVar16 + 0x104) =
           *(uint *)(iVar14 + 0x3ec) & 0x3fe00 | *(uint *)(puVar16 + 0x104) & 0xfffc01ff;
      *(ushort *)(puVar16 + 0x106) =
           *(ushort *)(iVar14 + 0x3ee) & 0x1ff | *(ushort *)(puVar16 + 0x106) & 0xfe00;
      memcpy(puVar16 + 0x108,iVar14 + 0x3f0,8);
      iVar27 = iVar27 + 1;
      puVar16[0x104] = *(byte *)(iVar14 + 0x3ec) & 0x80 | puVar16[0x104] & 0x7f;
      puVar16[0x104] = *(byte *)(iVar14 + 0x3ec) & 0x40 | puVar16[0x104] & 0xbf;
      puVar16[0x104] = *(byte *)(iVar14 + 0x3ec) & 0x20 | puVar16[0x104] & 0xdf;
      pbVar22 = (byte *)(iVar14 + 0x3ec);
      iVar14 = iVar14 + 0xc;
      puVar16[0x104] = *pbVar22 & 0x10 | puVar16[0x104] & 0xef;
      puVar16 = puVar16 + 0xc;
    } while (iVar27 < 100);
    iVar14 = 0;
    iVar27 = 0x20;
    do {
      if (0 < *(short *)(iVar23 + (iVar14 + 0x40) * 2 + 0xb6)) {
        iVar20 = iVar14 >> 0x1f;
        iVar17 = (iVar14 >> 5) * 4 + 0xbc;
        *(uint *)(puVar24 + iVar17) =
             *(uint *)(puVar24 + iVar17) |
             1 << (iVar20 * 0x20 | (uint)(iVar14 * 0x8000000 + iVar20) >> 0x1b) - iVar20;
      }
      iVar20 = iVar14 + 1;
      if (0 < *(short *)(iVar23 + (iVar14 + 0x41) * 2 + 0xb6)) {
        iVar17 = iVar20 >> 0x1f;
        iVar18 = (iVar20 >> 5) * 4 + 0xbc;
        *(uint *)(puVar24 + iVar18) =
             *(uint *)(puVar24 + iVar18) |
             1 << (iVar17 * 0x20 | (uint)(iVar20 * 0x8000000 + iVar17) >> 0x1b) - iVar17;
      }
      iVar20 = iVar14 + 2;
      if (0 < *(short *)(iVar23 + (iVar14 + 0x42) * 2 + 0xb6)) {
        iVar17 = iVar20 >> 0x1f;
        iVar18 = (iVar20 >> 5) * 4 + 0xbc;
        *(uint *)(puVar24 + iVar18) =
             *(uint *)(puVar24 + iVar18) |
             1 << (iVar17 * 0x20 | (uint)(iVar20 * 0x8000000 + iVar17) >> 0x1b) - iVar17;
      }
      iVar14 = iVar14 + 3;
      iVar27 = iVar27 + -1;
    } while (iVar27 != 0);
    *(undefined2 *)(puVar26 + 0x1598) = *(undefined2 *)(iVar21 + 0x15f4);
    *(undefined2 *)(puVar26 + 0x15a8) = *(undefined2 *)(iVar21 + 0x1604);
    *(undefined2 *)(puVar26 + 0x159a) = *(undefined2 *)(iVar21 + 0x15f6);
    *(undefined2 *)(puVar26 + 0x15aa) = *(undefined2 *)(iVar21 + 0x1606);
    *(undefined2 *)(puVar26 + 0x159c) = *(undefined2 *)(iVar21 + 0x15f8);
    *(undefined2 *)(puVar26 + 0x15ac) = *(undefined2 *)(iVar21 + 0x1608);
    *(undefined2 *)(puVar26 + 0x159e) = *(undefined2 *)(iVar21 + 0x15fa);
    *(undefined2 *)(puVar26 + 0x15ae) = *(undefined2 *)(iVar21 + 0x160a);
    *(undefined2 *)(puVar26 + 0x15a0) = *(undefined2 *)(iVar21 + 0x15fc);
    *(undefined2 *)(puVar26 + 0x15b0) = *(undefined2 *)(iVar21 + 0x160c);
    *(undefined2 *)(puVar26 + 0x15a2) = *(undefined2 *)(iVar21 + 0x15fe);
    *(undefined2 *)(puVar26 + 0x15b2) = *(undefined2 *)(iVar21 + 0x160e);
    *(undefined2 *)(puVar26 + 0x15a4) = *(undefined2 *)(iVar21 + 0x1600);
    *(undefined2 *)(puVar26 + 0x15b4) = *(undefined2 *)(iVar21 + 0x1610);
    *(undefined2 *)(puVar26 + 0x15a6) = *(undefined2 *)(iVar21 + 0x1602);
    *(undefined2 *)(puVar26 + 0x15b6) = *(undefined2 *)(iVar21 + 0x1612);
    *(undefined4 *)(puVar26 + 0x1a84) = *(undefined4 *)(iVar21 + 0x1794);
    memcpy(puVar26 + 0x1a88,iVar21 + 0x1c94,0x100);
    memcpy(puVar26 + 0x1b88,iVar21 + 0x1d94,0x200);
    iVar25 = iVar25 + 1;
    *(undefined4 *)(puVar26 + 0x1d88) = *(undefined4 *)(iVar21 + 0x1798);
    *(undefined4 *)(puVar26 + 0x1d8c) = *(undefined4 *)(iVar21 + 0x179c);
    puVar26[0x1d90] = *(uint8_t *)(iVar21 + 0x1f95);
    puVar26[0x1d91] = *(uint8_t *)(iVar21 + 0x1f96);
    puVar26[0x1d92] = *(uint8_t *)(iVar21 + 0x200e);
    *(undefined4 *)(puVar26 + 0x1d94) = *(undefined4 *)(iVar21 + 0x2010);
    *(undefined4 *)(puVar26 + 0x1da0) = *(undefined4 *)(iVar21 + 0x2014);
    uVar13 = *(undefined4 *)(iVar21 + 0x2018);
    *(undefined4 *)(puVar26 + 0x1d9c) = *(undefined4 *)(iVar21 + 0x201c);
    *(undefined4 *)(puVar26 + 0x1d98) = uVar13;
    *(undefined4 *)(puVar26 + 0x1da4) = *(undefined4 *)(iVar21 + 0x1400);
    iVar21 = iVar21 + 0xc30;
    puVar26 = puVar26 + 0x9c0;
  } while (iVar25 < 8);
  SaveScript__5CGameFPc(&Game.game,puVar12 + 0x62d0);
  SaveFurTexBuffer__6CCharaFPUs(&Chara,puVar12 + 0x6ad0);
  uVar11 = 0xffffffff;
  iVar21 = 0x1c;
  pbVar22 = memoryCardMan->m_saveBuffer;
  while( true ) {
    iVar21 = iVar21 + -1;
    if (iVar21 < 0) break;
    bVar2 = *pbVar22;
    pbVar22 = pbVar22 + 1;
    uVar11 = uVar11 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar11 >> 0x18 ^ (uint)bVar2) * 4);
  }
  pbVar22 = memoryCardMan->m_saveBuffer + 0x20;
  iVar21 = 0x8bb0;
  while( true ) {
    iVar21 = iVar21 + -1;
    if (iVar21 < 0) break;
    bVar2 = *pbVar22;
    pbVar22 = pbVar22 + 1;
    uVar11 = uVar11 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar11 >> 0x18 ^ (uint)bVar2) * 4);
  }
  *(uint *)(puVar12 + 0x1c) = ~uVar11;
  puVar19 = (uint *)(memoryCardMan->m_saveBuffer + 0x18);
  uVar11 = memoryCardMan->m_saveBuffer[0x11] & 0x1f;
  iVar21 = 0x5b6;
  do {
    uVar3 = *puVar19 << uVar11 | *puVar19 >> 0x20 - uVar11;
    *puVar19 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
               uVar3 >> 0x18;
    uVar3 = puVar19[1] << uVar11 | puVar19[1] >> 0x20 - uVar11;
    puVar19[1] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                 uVar3 >> 0x18;
    uVar3 = puVar19[2] << uVar11 | puVar19[2] >> 0x20 - uVar11;
    puVar19[2] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                 uVar3 >> 0x18;
    uVar3 = puVar19[3] << uVar11 | puVar19[3] >> 0x20 - uVar11;
    puVar19[3] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                 uVar3 >> 0x18;
    uVar3 = puVar19[4] << uVar11 | puVar19[4] >> 0x20 - uVar11;
    puVar19[4] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                 uVar3 >> 0x18;
    uVar3 = puVar19[5] << uVar11 | puVar19[5] >> 0x20 - uVar11;
    puVar19[5] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                 uVar3 >> 0x18;
    uVar3 = puVar19[6] << uVar11 | puVar19[6] >> 0x20 - uVar11;
    puVar19[6] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                 uVar3 >> 0x18;
    puVar19 = puVar19 + 7;
    iVar21 = iVar21 + -1;
  } while (iVar21 != 0);
  return;
}

