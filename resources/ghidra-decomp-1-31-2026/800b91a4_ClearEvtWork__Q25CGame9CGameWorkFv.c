// Function: ClearEvtWork__Q25CGame9CGameWorkFv
// Entry: 800b91a4
// Size: 72 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ClearEvtWork__Q25CGame9CGameWorkFv(CGame *game)

{
  memset((game->m_gameWork).m_eventFlags,0,0x100);
  memset((game->m_gameWork).m_eventWork,0,0x200);
  return;
}

