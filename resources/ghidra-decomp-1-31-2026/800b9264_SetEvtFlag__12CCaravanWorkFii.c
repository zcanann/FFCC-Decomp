// Function: SetEvtFlag__12CCaravanWorkFii
// Entry: 800b9264
// Size: 120 bytes

void SetEvtFlag__12CCaravanWorkFii(CCaravanWork *caravanWork,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)param_2 >> 0x1f;
  if (param_3 != 0) {
    iVar2 = ((int)param_2 >> 3) + (uint)((int)param_2 < 0 && (param_2 & 7) != 0);
    *(byte *)((int)caravanWork->m_evtWorkArr + iVar2) =
         *(byte *)((int)caravanWork->m_evtWorkArr + iVar2) |
         (byte)(1 << (iVar1 * 8 | param_2 * 0x20000000 + iVar1 >> 0x1d) - iVar1);
    return;
  }
  iVar2 = ((int)param_2 >> 3) + (uint)((int)param_2 < 0 && (param_2 & 7) != 0);
  *(byte *)((int)caravanWork->m_evtWorkArr + iVar2) =
       *(byte *)((int)caravanWork->m_evtWorkArr + iVar2) &
       ~(byte)(1 << (iVar1 * 8 | param_2 * 0x20000000 + iVar1 >> 0x1d) - iVar1);
  return;
}

