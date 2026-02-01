// Function: reset__6CAStarFv
// Entry: 80142f84
// Size: 80 bytes

void reset__6CAStarFv(CAStar *aStar)

{
  aStar->m_portalCount = 0;
  memset(aStar->m_portals,0,0x400);
  memset(aStar->m_routeTable,0,0x2000);
  return;
}

