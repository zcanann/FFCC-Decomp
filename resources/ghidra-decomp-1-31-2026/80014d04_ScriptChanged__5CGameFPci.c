// Function: ScriptChanged__5CGameFPci
// Entry: 80014d04
// Size: 320 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ScriptChanged__5CGameFPci(CGame *game)

{
  CGame *pCVar1;
  int iVar2;
  
  game->m_partyObjArr[0] = (CGPartyObj *)0x0;
  game->m_scriptFoodBase[0] = 0;
  game->m_partyObjArr[1] = (CGPartyObj *)0x0;
  game->m_scriptFoodBase[1] = 0;
  game->m_partyObjArr[2] = (CGPartyObj *)0x0;
  game->m_scriptFoodBase[2] = 0;
  game->m_partyObjArr[3] = (CGPartyObj *)0x0;
  game->m_scriptFoodBase[3] = 0;
  game->unk_flat3_0xc7d0 = 0;
  iVar2 = 4;
  pCVar1 = game;
  do {
    pCVar1->m_scriptWork[0][0][0] = 0;
    pCVar1->m_scriptWork[2][0][0] = 0;
    pCVar1->m_scriptWork[0][0][1] = 0;
    pCVar1->m_scriptWork[2][0][1] = 0;
    pCVar1->m_scriptWork[0][1][0] = 0;
    pCVar1->m_scriptWork[2][1][0] = 0;
    pCVar1->m_scriptWork[0][1][1] = 0;
    pCVar1->m_scriptWork[2][1][1] = 0;
    pCVar1->m_scriptWork[0][2][0] = 0;
    pCVar1->m_scriptWork[2][2][0] = 0;
    pCVar1->m_scriptWork[0][2][1] = 0;
    pCVar1->m_scriptWork[2][2][1] = 0;
    pCVar1->m_scriptWork[0][3][0] = 0;
    pCVar1->m_scriptWork[2][3][0] = 0;
    pCVar1->m_scriptWork[0][3][1] = 0;
    pCVar1->m_scriptWork[2][3][1] = 0;
    pCVar1->m_scriptWork[0][4][0] = 0;
    pCVar1->m_scriptWork[2][4][0] = 0;
    pCVar1->m_scriptWork[0][4][1] = 0;
    pCVar1->m_scriptWork[2][4][1] = 0;
    pCVar1->m_scriptWork[0][5][0] = 0;
    pCVar1->m_scriptWork[2][5][0] = 0;
    pCVar1->m_scriptWork[0][5][1] = 0;
    pCVar1->m_scriptWork[2][5][1] = 0;
    pCVar1->m_scriptWork[0][6][0] = 0;
    pCVar1->m_scriptWork[2][6][0] = 0;
    pCVar1->m_scriptWork[0][6][1] = 0;
    pCVar1->m_scriptWork[2][6][1] = 0;
    pCVar1->m_scriptWork[0][7][0] = 0;
    pCVar1->m_scriptWork[2][7][0] = 0;
    pCVar1->m_scriptWork[0][7][1] = 0;
    pCVar1->m_scriptWork[2][7][1] = 0;
    iVar2 = iVar2 + -1;
    pCVar1 = (CGame *)((pCVar1->m_gameWork).m_bossArtifactStageTable + 4);
  } while (iVar2 != 0);
  (game->m_gameWork).m_soundOptionFlag = '\0';
  (game->m_gameWork).m_gameOverFlag = '\0';
  DestroyMap__7CMapMngFv(&MapMng);
  Reset__9CCharaPcsFQ29CCharaPcs5RESET(&CharaPcs,0);
  StopAndFreeAllSe__6CSoundFi(&Sound,0);
  ClearAll__5CWindFv(&Wind);
  Sound._8892_4_ = 0x7f;
  return;
}

