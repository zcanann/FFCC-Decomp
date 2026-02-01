// Function: __sinit_game_cpp
// Entry: 80016220
// Size: 312 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void __sinit_game_cpp(void)

{
  undefined *puVar1;
  
  Game.game.vtable = &__vt__5CGame;
  memset(0x8021eecf,0,0x13e1);
  memset(0x8021eee0,0xff,0x10);
  Game.game.m_gameWork.m_scriptSysVal0 = '\0';
  Game.game.m_gameWork.m_scriptSysVal1 = '\0';
  Game.game.m_gameWork.m_scriptSysVal2 = '\0';
  Game.game.m_gameWork.m_scriptSysVal3 = '\x01';
  puVar1 = &DAT_8032f6ac;
  Game.game.m_gameWork.m_chaliceElement = 1;
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    puVar1 = &DAT_8032f6a4;
  }
  strcpy(0x8021ff68,puVar1);
  Game.game.m_gameWork.m_gameInitFlag = '\x01';
  __construct_array(Game.game.m_caravanWorkArr,__ct__12CCaravanWorkFv,__dt__12CCaravanWorkFv,0xc30,9
                   );
  __construct_array(Game.game.m_monWorkArr,__ct__8CMonWorkFv,__dt__8CMonWorkFv,0x110,0x40);
  Game.game.m_partyMinZ = FLOAT_8032f688;
  Game.game.m_partyMinY = FLOAT_8032f688;
  Game.game.m_partyMinX = FLOAT_8032f688;
  Game.game.m_partyMaxZ = FLOAT_8032f68c;
  Game.game.m_partyMaxY = FLOAT_8032f68c;
  Game.game.m_partyMaxX = FLOAT_8032f68c;
  __construct_array(Game.game.m_cFlatDataArr,__ct__9CFlatDataFv,__dt__9CFlatDataFv,0x14d4,4);
  __register_global_object(0x8021eec0,__dt__5CGameFv,&Game);
  return;
}

