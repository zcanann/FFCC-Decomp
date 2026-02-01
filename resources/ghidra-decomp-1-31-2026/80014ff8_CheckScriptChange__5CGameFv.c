// Function: CheckScriptChange__5CGameFv
// Entry: 80014ff8
// Size: 648 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CheckScriptChange__5CGameFv(CGame *game)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  if (game->m_newGameFlag != 0) {
    game->m_newGameFlag = 0;
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_game_cpp_801d6190,0x205);
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d619c);
    }
    ScriptChanging__7CSystemFPc(&System,(game->m_nextScript).m_name);
    iVar1 = strcmp((game->m_nextScript).m_name,&DAT_8032f698);
    if (iVar1 != 0) {
      if (game->m_cfdLoadedFlag == '\0') {
        Destroy__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        loadCfd__5CGameFv(game);
        game->m_cfdLoadedFlag = '\x01';
        if (2 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,&DAT_801d61b8);
        }
      }
      if (game->m_assetsLoadedFlag == '\0') {
        createLoad__9CSoundPcsFv(&SoundPcs);
        createLoad__9CCharaPcsFv(&CharaPcs);
        createLoad__8CPartPcsFv(&PartPcs);
        game->m_assetsLoadedFlag = '\x01';
        if (2 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,&DAT_801d61dc);
        }
      }
    }
    uVar2 = Load__13CFlatRuntime2FPc((CFlatRuntime2 *)&CFlat,(game->m_nextScript).m_name);
    strcpy(game->m_currentScriptName,(game->m_nextScript).m_name);
    if ((game->m_nextScript).m_flags != 0) {
      Printf__7CSystemFPce(&System,&DAT_8032f6a0);
      Printf__7CSystemFPce(&System,&DAT_801d6214);
      Printf__7CSystemFPce(&System,&DAT_8032f6a0);
      memset(0x8021eecf,0,0x13e1);
      memset(0x8021eee0,0xff,0x10);
      puVar3 = &DAT_8032f6ac;
      Game.game.m_gameWork.m_scriptSysVal0 = '\0';
      Game.game.m_gameWork.m_scriptSysVal1 = '\0';
      Game.game.m_gameWork.m_scriptSysVal2 = '\0';
      Game.game.m_gameWork.m_scriptSysVal3 = '\x01';
      Game.game.m_gameWork.m_chaliceElement = 1;
      if (Game.game.m_gameWork.m_languageId == '\x03') {
        puVar3 = &DAT_8032f6a4;
      }
      strcpy(0x8021ff68,puVar3);
      ResetNewGame__13CFlatRuntime2Fv(&CFlat);
      InitFurTexBuffer__6CCharaFv(&Chara);
      (game->m_nextScript).m_flags = 0;
    }
    ScriptChanged__7CSystemFPci(&System,(game->m_nextScript).m_name,uVar2);
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d6234);
    }
  }
  return;
}

