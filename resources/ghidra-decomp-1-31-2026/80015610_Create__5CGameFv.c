// Function: Create__5CGameFv
// Entry: 80015610
// Size: 408 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Create__5CGameFv(CGame *game)

{
  uint32_t *puVar1;
  uint32_t uVar2;
  int iVar3;
  undefined *puVar4;
  uint32_t *puVar5;
  CNextScript *pCVar6;
  uint32_t uVar7;
  uint32_t uStack_11c;
  uint32_t local_118 [67];
  
  (game->m_nextScript).m_flags = 1;
  clearWork__5CGameFv(game);
  memset(&(game->m_gameWork).m_gameDataStartMarker,0,0x13e1);
  memset((game->m_gameWork).m_wmBackupParams,0xff,0x10);
  (game->m_gameWork).m_scriptSysVal0 = '\0';
  (game->m_gameWork).m_scriptSysVal1 = '\0';
  (game->m_gameWork).m_scriptSysVal2 = '\0';
  (game->m_gameWork).m_scriptSysVal3 = '\x01';
  puVar4 = &DAT_8032f6ac;
  (game->m_gameWork).m_chaliceElement = 1;
  if ((game->m_gameWork).m_languageId == '\x03') {
    puVar4 = &DAT_8032f6a4;
  }
  strcpy((game->m_gameWork).m_townName,puVar4);
  (game->m_gameWork).m_gameInitFlag = '\x01';
  iVar3 = strlen(game->m_startScriptName);
  if (iVar3 != 0) {
    strcpy(local_118,game->m_startScriptName);
    pCVar6 = &game->m_nextScript;
    puVar5 = &uStack_11c;
    iVar3 = 0x20;
    do {
      puVar1 = puVar5 + 1;
      puVar5 = puVar5 + 2;
      uVar2 = *puVar5;
      *(uint32_t *)pCVar6->m_name = *puVar1;
      pCVar6 = (CNextScript *)(pCVar6->m_name + 4);
      pCVar6->m_flags = uVar2;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    game->m_newGameFlag = 1;
  }
  if (game->m_newGameFlag == 0) {
    uVar2 = game->m_currentMapVariantId;
    uVar7 = game->m_currentMapId;
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_game_cpp_801d6190,0x24e);
    MapChanging__7CSystemFii(&System,uVar7,uVar2);
    game->m_currentMapId = uVar7;
    game->m_currentMapVariantId = uVar2;
    LoadMap__7CMapPcsFiiPvUlUc(&MapPcs,uVar7,uVar2,0,0,0);
    LoadFieldPdt__8CPartPcsFiiPvUlUc(&PartPcs,uVar7,uVar2,0,0,0);
    MapChanged__7CSystemFiii(&System,uVar7,uVar2,1);
  }
  return;
}

