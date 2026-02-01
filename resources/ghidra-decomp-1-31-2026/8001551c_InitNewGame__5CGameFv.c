// Function: InitNewGame__5CGameFv
// Entry: 8001551c
// Size: 212 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void InitNewGame__5CGameFv(void)

{
  undefined *puVar1;
  
  Printf__7CSystemFPce(&System,&DAT_8032f6a0);
  Printf__7CSystemFPce(&System,&DAT_801d6214);
  Printf__7CSystemFPce(&System,&DAT_8032f6a0);
  memset(0x8021eecf,0,0x13e1);
  memset(0x8021eee0,0xff,0x10);
  puVar1 = &DAT_8032f6ac;
  Game.game.m_gameWork.m_scriptSysVal0 = '\0';
  Game.game.m_gameWork.m_scriptSysVal1 = '\0';
  Game.game.m_gameWork.m_scriptSysVal2 = '\0';
  Game.game.m_gameWork.m_scriptSysVal3 = '\x01';
  Game.game.m_gameWork.m_chaliceElement = 1;
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    puVar1 = &DAT_8032f6a4;
  }
  strcpy(0x8021ff68,puVar1);
  ResetNewGame__13CFlatRuntime2Fv(&CFlat);
  InitFurTexBuffer__6CCharaFv(&Chara);
  return;
}

