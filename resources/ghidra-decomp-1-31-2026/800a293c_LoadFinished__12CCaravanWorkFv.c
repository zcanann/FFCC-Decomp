// Function: LoadFinished__12CCaravanWorkFv
// Entry: 800a293c
// Size: 88 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadFinished__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  if (caravanWork->m_shopState == 0) {
    return;
  }
  (caravanWork->gObjWork).m_baseDataIndex = (caravanWork->gObjWork).m_id / 100 - 1;
  (caravanWork->gObjWork).m_romWorkPtr =
       (uint16_t *)
       (Game.game.unkCFlatData0[0] + (caravanWork->gObjWork).m_baseDataIndex * 0x1d0 + 0x10);
  return;
}

