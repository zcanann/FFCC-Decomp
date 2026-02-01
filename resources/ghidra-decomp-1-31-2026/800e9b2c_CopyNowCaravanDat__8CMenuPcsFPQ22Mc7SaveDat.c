// Function: CopyNowCaravanDat__8CMenuPcsFPQ22Mc7SaveDat
// Entry: 800e9b2c
// Size: 116 bytes

void CopyNowCaravanDat__8CMenuPcsFPQ22Mc7SaveDat(CMenuPcs *menuPcs,void *param_2)

{
  CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
  MakeSaveData__14CMemoryCardManFv(&MemoryCardMan);
  DecodeData__14CMemoryCardManFv(&MemoryCardMan);
  memcpy(param_2,MemoryCardMan.m_saveBuffer,0x8bd0);
  DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
  return;
}

