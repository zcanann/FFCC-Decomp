// Function: ?LoadPlayerStat__8GbaQueueFv
// Entry: 800cef70
// Size: 1916 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void _LoadPlayerStat__8GbaQueueFv(GbaQueue *gbaQueue)

{
  char cVar1;
  undefined uVar2;
  undefined uVar3;
  undefined uVar4;
  undefined uVar5;
  undefined uVar6;
  undefined uVar7;
  undefined uVar8;
  byte bVar10;
  ushort uVar9;
  undefined uVar11;
  undefined uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  CGPartyObj *pCVar17;
  GbaQueue *pGVar18;
  undefined *puVar19;
  CCaravanWork *caravanWork;
  undefined unaff_r27;
  uint uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  undefined auStack_428 [128];
  undefined local_3a8 [880];
  longlong local_38;
  longlong local_30;
  
  memset(local_3a8,0,0x370);
  memset(auStack_428,0,0x80);
  puVar19 = auStack_428;
  iVar22 = -0x7fde1140;
  iVar21 = 0;
  iVar16 = iVar22;
  do {
    memcpy(puVar19,iVar16 + 0x17ba,0x10);
    iVar21 = iVar21 + 1;
    puVar19 = puVar19 + 0x10;
    iVar16 = iVar16 + 0xc30;
  } while (iVar21 < 8);
  if (CFlat._66564_4_ != 0) {
    puVar19 = local_3a8;
    uVar20 = 0;
    iVar16 = 0;
    do {
      cVar1 = gbaQueue->field_0x2d56;
      if ((cVar1 == '\0') ||
         (pCVar17 = Game.game.m_partyObjArr[0],
         caravanWork = (CCaravanWork *)Game.game.m_scriptFoodBase[0], iVar16 != 1)) {
        pCVar17 = *(CGPartyObj **)(iVar22 + 0xc5b0);
        caravanWork = *(CCaravanWork **)(iVar22 + 0xc5c0);
      }
      if (caravanWork != (CCaravanWork *)0x0) {
        if ((cVar1 == '\0') || ((cVar1 != '\0' && (iVar16 == 0)))) {
          puVar19[3] = 1;
        }
        else if (((cVar1 != '\0') && (iVar16 == 1)) && (*(int *)(iVar22 + 0xc5c0) != 0)) {
          puVar19[3] = 1;
        }
        puVar19[0x16] = (char)(caravanWork->gObjWork).m_maxHp;
        puVar19[0x17] = (char)(caravanWork->gObjWork).m_hp;
        bVar10 = (byte)caravanWork->m_tribeId & 3 |
                 (byte)((caravanWork->m_appearanceVariant & 3) << 2);
        if (caravanWork->m_genderFlag != 0) {
          bVar10 = bVar10 | 0x80;
        }
        puVar19[2] = bVar10;
        *(int32_t *)(puVar19 + 0x24) = caravanWork->m_gil;
        uVar9 = 0xff;
        if (caravanWork->m_progressValue < 0x100) {
          uVar9 = caravanWork->m_progressValue;
        }
        *(ushort *)(puVar19 + 0x14) = uVar9;
        uVar11 = 99;
        puVar19[0x18] = (char)caravanWork->m_letterMeta[0];
        puVar19[0x19] = (char)caravanWork->m_letterMeta[1];
        puVar19[0x1a] = (char)caravanWork->m_letterMeta[2];
        puVar19[0x1b] = (char)caravanWork->m_letterMeta[3];
        puVar19[0x1c] = (char)caravanWork->m_letterMeta[4];
        puVar19[0x1d] = (char)caravanWork->m_letterMeta[5];
        puVar19[0x1e] = (char)caravanWork->m_letterMeta[6];
        puVar19[0x1f] = (char)caravanWork->m_letterMeta[7];
        iVar21 = *(int *)&(caravanWork->gObjWork).m_saveSlot;
        *puVar19 = (char)iVar21;
        iVar21 = iVar21 * 0x208;
        uVar12 = *(undefined *)((int)Game.game.m_gameWork.m_linkTable + iVar21);
        puVar19[4] = (char)caravanWork->m_evtWordArr[0x12];
        uVar2 = *(undefined *)((int)Game.game.m_gameWork.m_linkTable + iVar21 + 1);
        uVar3 = *(undefined *)((int)Game.game.m_gameWork.m_linkTable + iVar21 + 2);
        puVar19[5] = (char)caravanWork->m_evtWordArr[0x13];
        uVar4 = *(undefined *)((int)Game.game.m_gameWork.m_linkTable + iVar21 + 3);
        uVar5 = *(undefined *)((int)Game.game.m_gameWork.m_linkTable + iVar21 + 4);
        puVar19[6] = (char)caravanWork->m_evtWordArr[0x14];
        uVar6 = *(undefined *)((int)Game.game.m_gameWork.m_linkTable + iVar21 + 5);
        uVar7 = *(undefined *)((int)Game.game.m_gameWork.m_linkTable + iVar21 + 6);
        puVar19[7] = (char)caravanWork->m_evtWordArr[0x15];
        uVar8 = *(undefined *)((int)Game.game.m_gameWork.m_linkTable + iVar21 + 7);
        puVar19[8] = (char)caravanWork->m_evtWordArr[0x16];
        puVar19[9] = (char)caravanWork->m_evtWordArr[0x17];
        puVar19[10] = (char)caravanWork->m_evtWordArr[0x18];
        puVar19[0xb] = (char)caravanWork->m_evtWordArr[0x19];
        puVar19[0xc] = uVar12;
        puVar19[0xd] = uVar2;
        puVar19[0xe] = uVar3;
        puVar19[0xf] = uVar4;
        puVar19[0x10] = uVar5;
        puVar19[0x11] = uVar6;
        puVar19[0x12] = uVar7;
        puVar19[0x13] = uVar8;
        uVar9 = (caravanWork->gObjWork).m_strength;
        if (uVar9 < 100) {
          uVar11 = (undefined)uVar9;
        }
        puVar19[0x20] = uVar11;
        uVar12 = 99;
        uVar9 = (caravanWork->gObjWork).m_defense;
        if (uVar9 < 100) {
          uVar12 = (undefined)uVar9;
        }
        puVar19[0x21] = uVar12;
        uVar12 = 99;
        uVar9 = (caravanWork->gObjWork).m_magic;
        if (uVar9 < 100) {
          uVar12 = (undefined)uVar9;
        }
        puVar19[0x22] = uVar12;
        puVar19[0xd2] = caravanWork->m_bonusCondition;
        puVar19[0xd5] = (char)caravanWork->unk_0x3ac;
        memcpy(puVar19 + 0x3a,caravanWork->m_inventoryItems,0x80);
        iVar21 = 0;
        iVar23 = 0x20;
        do {
          if (0 < (short)caravanWork->m_artifacts[iVar21]) {
            iVar15 = iVar21 >> 0x1f;
            iVar13 = (iVar21 >> 5) * 4 + 0x28;
            *(uint *)(puVar19 + iVar13) =
                 *(uint *)(puVar19 + iVar13) |
                 1 << (iVar15 * 0x20 | (uint)(iVar21 * 0x8000000 + iVar15) >> 0x1b) - iVar15;
          }
          iVar15 = iVar21 + 1;
          if (0 < (short)caravanWork->m_artifacts[iVar21 + 1]) {
            iVar13 = iVar15 >> 0x1f;
            iVar14 = (iVar15 >> 5) * 4 + 0x28;
            *(uint *)(puVar19 + iVar14) =
                 *(uint *)(puVar19 + iVar14) |
                 1 << (iVar13 * 0x20 | (uint)(iVar15 * 0x8000000 + iVar13) >> 0x1b) - iVar13;
          }
          iVar15 = iVar21 + 2;
          if (0 < (short)caravanWork->m_artifacts[iVar21 + 2]) {
            iVar13 = iVar15 >> 0x1f;
            iVar14 = (iVar15 >> 5) * 4 + 0x28;
            *(uint *)(puVar19 + iVar14) =
                 *(uint *)(puVar19 + iVar14) |
                 1 << (iVar13 * 0x20 | (uint)(iVar15 * 0x8000000 + iVar13) >> 0x1b) - iVar13;
          }
          iVar21 = iVar21 + 3;
          iVar23 = iVar23 + -1;
        } while (iVar23 != 0);
        *(uint16_t *)(puVar19 + 0xba) = caravanWork->m_treasures[0];
        *(uint16_t *)(puVar19 + 0xbc) = caravanWork->m_treasures[1];
        *(uint16_t *)(puVar19 + 0xbe) = caravanWork->m_treasures[2];
        *(uint16_t *)(puVar19 + 0xc0) = caravanWork->m_treasures[3];
        puVar19[0xd3] = (char)caravanWork->m_numCmdListSlots;
        *(uint16_t *)(puVar19 + 0xc2) = caravanWork->m_commandListInventorySlotRef[0];
        *(uint16_t *)(puVar19 + 0xc4) = caravanWork->m_commandListInventorySlotRef[1];
        *(uint16_t *)(puVar19 + 0xc6) = caravanWork->m_commandListInventorySlotRef[2];
        *(uint16_t *)(puVar19 + 200) = caravanWork->m_commandListInventorySlotRef[3];
        *(uint16_t *)(puVar19 + 0xca) = caravanWork->m_commandListInventorySlotRef[4];
        *(uint16_t *)(puVar19 + 0xcc) = caravanWork->m_commandListInventorySlotRef[5];
        *(uint16_t *)(puVar19 + 0xce) = caravanWork->m_commandListInventorySlotRef[6];
        *(uint16_t *)(puVar19 + 0xd0) = caravanWork->m_commandListInventorySlotRef[7];
        puVar19[0xd7] = (char)caravanWork->m_equipment[0];
        puVar19[0xd8] = (char)caravanWork->m_equipment[1];
        puVar19[0xd9] = (char)caravanWork->m_equipment[2];
        puVar19[0xda] = (char)caravanWork->m_equipment[3];
        puVar19[0x23] = 1;
        iVar21 = (**(code **)((int)(pCVar17->gCharaObj).gPrgObj.object.base_object.object.m_vtable +
                             0x2c))(pCVar17);
        puVar19[0xd4] = (byte)((byte)((uint)-iVar21 >> 0x18) | (byte)((uint)iVar21 >> 0x18)) >> 7;
        iVar21 = IsOutOfShouki__12CCaravanWorkFv(caravanWork);
        if ((iVar21 != 0) && (puVar19[0x17] != '\0')) {
          uVar20 = uVar20 | 1 << iVar16;
        }
        iVar21 = CanPlayerUseItem__12CCaravanWorkFv(caravanWork);
        if (iVar21 != 0) {
          puVar19[0xd6] = puVar19[0xd6] | (byte)DAT_80330d70;
        }
        iVar21 = CanPlayerPutItem__12CCaravanWorkFv(caravanWork);
        if (iVar21 != 0) {
          puVar19[0xd6] = puVar19[0xd6] | (byte)DAT_80330d74;
        }
      }
      unaff_r27 = (undefined)uVar20;
      iVar21 = *(int *)(iVar22 + 0xc5b0);
      if (iVar21 != 0) {
        puVar19[1] = 1;
        iVar23 = (int)(*(float *)(iVar21 + 0x15c) / FLOAT_80330d54);
        local_30 = (longlong)iVar23;
        iVar21 = (int)(*(float *)(iVar21 + 0x164) / FLOAT_80330d54);
        local_38 = (longlong)iVar21;
        *(short *)(puVar19 + 0x36) = (short)iVar23;
        *(short *)(puVar19 + 0x38) = (short)iVar21;
      }
      iVar16 = iVar16 + 1;
      puVar19 = puVar19 + 0xdc;
      iVar22 = iVar22 + 4;
    } while (iVar16 < 4);
  }
  iVar16 = 0;
  pGVar18 = gbaQueue;
  do {
    OSWaitSemaphore(pGVar18->accessSemaphores);
    iVar16 = iVar16 + 1;
    pGVar18 = (GbaQueue *)(pGVar18->accessSemaphores + 1);
  } while (iVar16 < 4);
  memcpy(&gbaQueue->field_0x7c4,&gbaQueue->field_0x454,0x370);
  memcpy(&gbaQueue->field_0x454,local_3a8,0x370);
  memcpy(gbaQueue->caravanName,auStack_428,0x80);
  iVar16 = 0;
  puVar19 = local_3a8;
  gbaQueue->field_0x2d59 = gbaQueue->field_0x2d5a;
  iVar21 = 0;
  gbaQueue->field_0x2d5a = unaff_r27;
  pGVar18 = gbaQueue;
  do {
    iVar22 = memcmp(&pGVar18->field_0x7dc,&pGVar18->field_0x46c,8);
    if (iVar22 != 0) {
      gbaQueue->favoriteFlag = gbaQueue->favoriteFlag | (byte)(1 << iVar16);
    }
    if (*(int *)&pGVar18->field_0x7e8 != *(int *)&pGVar18->field_0x478) {
      gbaQueue->moneyFlg = gbaQueue->moneyFlg | (byte)(1 << iVar16);
    }
    iVar22 = 0;
    do {
      iVar23 = memcmp(&pGVar18->field_0x7c8,pGVar18->compatibilityStr,8);
      if (iVar23 != 0) {
        (&gbaQueue->compatibilityFlg)[iVar16] =
             (&gbaQueue->compatibilityFlg)[iVar16] | (byte)(1 << iVar22);
      }
      iVar22 = iVar22 + 1;
    } while (iVar22 < 8);
    if (pGVar18->field_0x7e7 != pGVar18->field_0x477) {
      gbaQueue->chgUseItemFlg = gbaQueue->chgUseItemFlg | (byte)(1 << iVar16);
    }
    iVar22 = memcmp(&pGVar18->field_0x7e4,&pGVar18->field_0x474,3);
    if (iVar22 != 0) {
      gbaQueue->strengthFlg = gbaQueue->strengthFlg | (byte)(1 << iVar16);
    }
    iVar22 = memcmp(&pGVar18->field_0x7ec,&pGVar18->field_0x47c,0xc);
    if (iVar22 != 0) {
      gbaQueue->artifactFlg = gbaQueue->artifactFlg | (byte)(1 << iVar16);
    }
    if (*(short *)&pGVar18->field_0x7d8 != *(short *)(puVar19 + 0x14)) {
      gbaQueue->memorysFlg = gbaQueue->memorysFlg | (byte)(1 << iVar16);
    }
    if ((pGVar18->field_0x897 != puVar19[0xd3]) &&
       (gbaQueue->cmdNumFlag = gbaQueue->cmdNumFlag | (byte)(1 << iVar21),
       (int)(char)puVar19[0xd3] - (int)(char)pGVar18->field_0x897 != 1)) {
      gbaQueue->cmdNumFlag = gbaQueue->cmdNumFlag | (byte)(2 << iVar21);
    }
    iVar16 = iVar16 + 1;
    puVar19 = puVar19 + 0xdc;
    iVar21 = iVar21 + 2;
    pGVar18 = (GbaQueue *)&pGVar18->field_0xdc;
  } while (iVar16 < 4);
  iVar16 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar16 = iVar16 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar16 < 4);
  return;
}

