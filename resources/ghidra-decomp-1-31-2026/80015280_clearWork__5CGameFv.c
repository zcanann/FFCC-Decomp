// Function: clearWork__5CGameFv
// Entry: 80015280
// Size: 668 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void clearWork__5CGameFv(CGame *game)

{
  undefined4 uVar1;
  uint uVar2;
  CGame *pCVar3;
  uint uVar4;
  int iVar5;
  CCharaPcs *pCVar6;
  CCharaPcs *pCVar7;
  CCharaPcs *pCVar8;
  CCharaPcs *pCVar9;
  undefined local_38;
  undefined local_37;
  undefined local_36;
  undefined local_35;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  Destroy__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
  iVar5 = 0;
  pCVar3 = game;
  do {
    Destroy__9CFlatDataFv(pCVar3->m_cFlatDataArr);
    iVar5 = iVar5 + 1;
    pCVar3 = (CGame *)(pCVar3->m_caravanWorkArr[0].m_inventoryItems + 0x17);
  } while (iVar5 < 4);
  game->unkCFlatData0[0] = 0;
  game->unkCFlatData0[1] = 0;
  game->unkCFlatData0[2] = 0;
  game->m_partyObjArr[0] = (CGPartyObj *)0x0;
  game->m_scriptFoodBase[0] = 0;
  game->m_partyObjArr[1] = (CGPartyObj *)0x0;
  game->m_scriptFoodBase[1] = 0;
  game->m_partyObjArr[2] = (CGPartyObj *)0x0;
  game->m_scriptFoodBase[2] = 0;
  game->m_partyObjArr[3] = (CGPartyObj *)0x0;
  game->m_scriptFoodBase[3] = 0;
  game->unk_flat3_0xc7d0 = 0;
  iVar5 = 4;
  pCVar3 = game;
  do {
    pCVar3->m_scriptWork[0][0][0] = 0;
    pCVar3->m_scriptWork[2][0][0] = 0;
    pCVar3->m_scriptWork[0][0][1] = 0;
    pCVar3->m_scriptWork[2][0][1] = 0;
    pCVar3->m_scriptWork[0][1][0] = 0;
    pCVar3->m_scriptWork[2][1][0] = 0;
    pCVar3->m_scriptWork[0][1][1] = 0;
    pCVar3->m_scriptWork[2][1][1] = 0;
    pCVar3->m_scriptWork[0][2][0] = 0;
    pCVar3->m_scriptWork[2][2][0] = 0;
    pCVar3->m_scriptWork[0][2][1] = 0;
    pCVar3->m_scriptWork[2][2][1] = 0;
    pCVar3->m_scriptWork[0][3][0] = 0;
    pCVar3->m_scriptWork[2][3][0] = 0;
    pCVar3->m_scriptWork[0][3][1] = 0;
    pCVar3->m_scriptWork[2][3][1] = 0;
    pCVar3->m_scriptWork[0][4][0] = 0;
    pCVar3->m_scriptWork[2][4][0] = 0;
    pCVar3->m_scriptWork[0][4][1] = 0;
    pCVar3->m_scriptWork[2][4][1] = 0;
    pCVar3->m_scriptWork[0][5][0] = 0;
    pCVar3->m_scriptWork[2][5][0] = 0;
    pCVar3->m_scriptWork[0][5][1] = 0;
    pCVar3->m_scriptWork[2][5][1] = 0;
    pCVar3->m_scriptWork[0][6][0] = 0;
    pCVar3->m_scriptWork[2][6][0] = 0;
    pCVar3->m_scriptWork[0][6][1] = 0;
    pCVar3->m_scriptWork[2][6][1] = 0;
    pCVar3->m_scriptWork[0][7][0] = 0;
    pCVar3->m_scriptWork[2][7][0] = 0;
    pCVar3->m_scriptWork[0][7][1] = 0;
    pCVar3->m_scriptWork[2][7][1] = 0;
    iVar5 = iVar5 + -1;
    pCVar3 = (CGame *)((pCVar3->m_gameWork).m_bossArtifactStageTable + 4);
  } while (iVar5 != 0);
  (game->m_gameWork).m_soundOptionFlag = '\0';
  (game->m_gameWork).m_gameOverFlag = '\0';
  DestroyMap__7CMapMngFv(&MapMng);
  Reset__9CCharaPcsFQ29CCharaPcs5RESET(&CharaPcs,0);
  StopAndFreeAllSe__6CSoundFi(&Sound,0);
  ClearAll__5CWindFv(&Wind);
  Sound._8892_4_ = 0x7f;
  iVar5 = GetSize__29CPtrArray<P15CMapLightHolder>Fv(MapMng.mapLightHolderArr);
  if (iVar5 != 0) {
    iVar5 = GetSize__29CPtrArray<P15CMapLightHolder>Fv(MapMng.mapLightHolderArr);
    if (iVar5 != 0) {
      uVar1 = __vc__29CPtrArray<P15CMapLightHolder>FUl(0x80266bb4,0);
      GetLightHolder__15CMapLightHolderFP8_GXColorP3Vec(uVar1,&local_38,0);
    }
    iVar5 = 0;
    pCVar6 = &CharaPcs;
    pCVar7 = &CharaPcs;
    do {
      pCVar7->field_0xe8 = local_38;
      uVar4 = 0;
      pCVar7->field_0xe9 = local_37;
      pCVar7->field_0xea = local_36;
      pCVar7->field_0xeb = local_35;
      pCVar8 = &CharaPcs;
      pCVar9 = pCVar6;
      do {
        uVar2 = GetSize__29CPtrArray<P15CMapLightHolder>Fv(MapMng.mapLightHolderArr);
        if (uVar4 + 1 < uVar2) {
          uVar1 = __vc__29CPtrArray<P15CMapLightHolder>FUl(0x80266bb4);
          GetLightHolder__15CMapLightHolderFP8_GXColorP3Vec(uVar1,&local_38,&local_34);
        }
        pCVar9->field_0xf0 = local_38;
        pCVar9->field_0xf1 = local_37;
        pCVar9->field_0xf2 = local_36;
        pCVar9->field_0xf3 = local_35;
        if (iVar5 == 0) {
          *(undefined4 *)&pCVar8->field_0x108 = local_34;
          *(undefined4 *)&pCVar8->field_0x10c = local_30;
          *(undefined4 *)&pCVar8->field_0x110 = local_2c;
        }
        uVar4 = uVar4 + 1;
        pCVar8 = (CCharaPcs *)&pCVar8->field_0xc;
        pCVar9 = (CCharaPcs *)&pCVar9->field_0x4;
      } while (uVar4 < 3);
      iVar5 = iVar5 + 1;
      pCVar6 = (CCharaPcs *)&pCVar6->field_0xc;
      pCVar7 = (CCharaPcs *)&pCVar7->field_0x4;
    } while (iVar5 < 2);
  }
  return;
}

