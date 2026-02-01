// Function: CopyToAMemorySync__7CMemoryFPvPvUl
// Entry: 8001e620
// Size: 176 bytes

void CopyToAMemorySync__7CMemoryFPvPvUl(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined auStack_38 [48];
  
  iVar1 = DMAEntry__9CRedSoundFiiiiiPFPv_vPv(&Sound.m_redSound,0,0,param_2,param_3,param_4,0,0);
  DumpMapFile__7CSystemFPv((CSystem *)auStack_38);
  Start__10CStopWatchFv(auStack_38);
  while (iVar2 = DMACheck__9CRedSoundFi(&Sound.m_redSound,iVar1), iVar2 != 0) {
    Stop__10CStopWatchFv(auStack_38);
    Get__10CStopWatchFv(auStack_38);
    Start__10CStopWatchFv(auStack_38);
  }
  __ct__10CStopWatchFPc(auStack_38,0xffffffff);
  return;
}

