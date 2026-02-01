// Function: LoadFinished__5CGameFv
// Entry: 80014540
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadFinished__5CGameFv(CGame *game)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    LoadFinished__12CCaravanWorkFv(game->m_caravanWorkArr);
    iVar1 = iVar1 + 1;
    game = (CGame *)((game->m_gameWork).m_linkTable[5][6] + 1);
  } while (iVar1 < 8);
  return;
}

