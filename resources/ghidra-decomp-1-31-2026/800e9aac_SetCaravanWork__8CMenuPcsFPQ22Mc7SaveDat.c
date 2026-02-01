// Function: SetCaravanWork__8CMenuPcsFPQ22Mc7SaveDat
// Entry: 800e9aac
// Size: 128 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetCaravanWork__8CMenuPcsFPQ22Mc7SaveDat(CMenuPcs *menuPcs,undefined4 param_2)

{
  CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
  memcpy(MemoryCardMan.m_saveBuffer,param_2,0x8bd0);
  LoadInit__5CGameFv(&Game.game);
  SetLoadData__14CMemoryCardManFv(&MemoryCardMan);
  LoadFinished__5CGameFv(&Game.game);
  DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
  return;
}

