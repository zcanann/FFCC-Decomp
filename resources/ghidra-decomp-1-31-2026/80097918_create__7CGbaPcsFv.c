// Function: create__7CGbaPcsFv
// Entry: 80097918
// Size: 156 bytes

void create__7CGbaPcsFv(int param_1)

{
  CStage *pCVar1;
  int iVar2;
  
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x56000,s_CGbaPcs_80330870,0);
  *(CStage **)(param_1 + 4) = pCVar1;
  CreateInit__6JoyBusFv(&Joybus);
  iVar2 = LoadBin__6JoyBusFv(&Joybus);
  if ((iVar2 != 0) && (1 < (uint)System.m_execParam)) {
    Printf__7CSystemFPce(&System,s_JoyBus__LoadBin___error_801d9de0);
  }
  ThreadInit__6JoyBusFv(&Joybus);
  return;
}

