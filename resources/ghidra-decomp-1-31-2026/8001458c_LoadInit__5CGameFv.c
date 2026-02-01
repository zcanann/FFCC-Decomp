// Function: LoadInit__5CGameFv
// Entry: 8001458c
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadInit__5CGameFv(CGame *game)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    LoadInit__12CCaravanWorkFv(game->m_caravanWorkArr);
    iVar1 = iVar1 + 1;
    game = (CGame *)((game->m_gameWork).m_linkTable[5][6] + 1);
  } while (iVar1 < 8);
  return;
}

