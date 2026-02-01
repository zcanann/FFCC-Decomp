// Function: GetEvtFlag__12CCaravanWorkFi
// Entry: 800b92dc
// Size: 64 bytes

uint GetEvtFlag__12CCaravanWorkFi(CCaravanWork *caravanWork,uint param_2)

{
  int iVar1;
  
  iVar1 = (int)param_2 >> 0x1f;
  return -((uint)*(byte *)((int)caravanWork->m_evtWorkArr +
                          ((int)param_2 >> 3) + (uint)((int)param_2 < 0 && (param_2 & 7) != 0)) &
          1 << (iVar1 * 8 | param_2 * 0x20000000 + iVar1 >> 0x1d) - iVar1) >> 0x1f;
}

