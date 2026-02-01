// Function: CopyFromAMemorySync__7CMemoryFPvPvUl
// Entry: 8001e4f8
// Size: 296 bytes

/* WARNING: Removing unreachable block (ram,0x8001e5fc) */
/* WARNING: Removing unreachable block (ram,0x8001e508) */

void CopyFromAMemorySync__7CMemoryFPvPvUl(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  undefined auStack_58 [60];
  
  iVar1 = DMAEntry__9CRedSoundFiiiiiPFPv_vPv(&Sound.m_redSound,0,1,param_2,param_3,param_4,0,0);
  DumpMapFile__7CSystemFPv((CSystem *)auStack_58);
  Start__10CStopWatchFv(auStack_58);
  dVar4 = (double)FLOAT_8032f7d8;
  while (iVar2 = DMACheck__9CRedSoundFi(&Sound.m_redSound,iVar1), iVar2 != 0) {
    Stop__10CStopWatchFv(auStack_58);
    dVar3 = (double)Get__10CStopWatchFv(auStack_58);
    if (dVar3 < dVar4) {
      Start__10CStopWatchFv(auStack_58);
    }
    else {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s__________________________________801d6abc);
      }
      CheckDriver__6CSoundFi(&Sound,1);
      Reset__10CStopWatchFv(auStack_58);
      Start__10CStopWatchFv(auStack_58);
    }
  }
  __ct__10CStopWatchFPc(auStack_58,0xffffffff);
  return;
}

