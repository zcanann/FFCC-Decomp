// Function: Init__5CGameFv
// Entry: 8001600c
// Size: 476 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Init__5CGameFv(CGame *game)

{
  byte bVar3;
  CStage *pCVar1;
  int iVar2;
  
  bVar3 = OSSetProgressiveMode();
  if (bVar3 == 3) {
    Game.game.m_gameWork.m_languageId = '\x05';
    goto LAB_80016078;
  }
  if (bVar3 < 3) {
    if (bVar3 == 1) {
      Game.game.m_gameWork.m_languageId = '\x02';
      goto LAB_80016078;
    }
    if (bVar3 != 0) {
      Game.game.m_gameWork.m_languageId = '\x04';
      goto LAB_80016078;
    }
  }
  else if ((bVar3 != 5) && (bVar3 < 5)) {
    Game.game.m_gameWork.m_languageId = '\x03';
    goto LAB_80016078;
  }
  Game.game.m_gameWork.m_languageId = '\x01';
LAB_80016078:
  Init__10CCameraPcsFv(&CameraPcs);
  Init__11CGraphicPcsFv(&GraphicsPcs);
  Init__6CCharaFv(&Chara);
  Init__9CLightPcsFv(&LightPcs);
  Init__9CCharaPcsFv(&CharaPcs);
  Init__7CMapPcsFv(&MapPcs);
  Init__18CMaterialEditorPcsFv(&MaterialEditorPcs);
  Init__14CFunnyShapePcsFv(&FunnyShapePcs);
  Init__7CUSBPcsFv(&USBPcs);
  Init__8CMenuPcsFv(&MenuPcs);
  Init__7CGbaPcsFv(&GbaPcs);
  Init__6CMcPcsFv(&McPcs);
  Init__11CDbgMenuPcsFv(0x80306708);
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x106000,&DAT_8032f6b4,0);
  game->m_mainStage = pCVar1;
  iVar2 = OSGetConsoleSimulatedMemSize();
  if (iVar2 == 0x3000000) {
    pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x220000,s_GameDebug_801d6284,1);
    game->m_debugStage = pCVar1;
  }
  game->m_sceneId = 4;
  game->m_mapId = 3;
  game->m_mapVariant = 0;
  memset(game->m_currentScriptName,0,0x100);
  memset(game->m_startScriptName,0,0x100);
  game->m_frameCounterEnable = 1;
  Init__12CFlatRuntimeFv((CFlatRuntime *)&CFlat);
  game->unkFloat_0xca10 = FLOAT_8032f6bc;
  return;
}

