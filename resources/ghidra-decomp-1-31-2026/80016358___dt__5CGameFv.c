// Function: __dt__5CGameFv
// Entry: 80016358
// Size: 168 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CGame * __dt__5CGameFv(CGame *game,short param_2)

{
  if (game != (CGame *)0x0) {
    game->vtable = &__vt__5CGame;
    __destroy_arr(game->m_cFlatDataArr,__dt__9CFlatDataFv,0x14d4,4);
    __destroy_arr(game->m_monWorkArr,__dt__8CMonWorkFv,0x110,0x40);
    __destroy_arr(game->m_caravanWorkArr,__dt__12CCaravanWorkFv,0xc30,9);
    if (0 < param_2) {
      __dl__FPv(game);
    }
  }
  return game;
}

