// Function: GetData__13CAmemCacheSetFsPci
// Entry: 8001d278
// Size: 456 bytes

/* WARNING: Removing unreachable block (ram,0x8001d424) */
/* WARNING: Removing unreachable block (ram,0x8001d288) */

int GetData__13CAmemCacheSetFsPci
              (CAmemCacheSet *amemCacheSet,short param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  double dVar5;
  double dVar6;
  undefined auStack_68 [56];
  
  while( true ) {
    piVar4 = (int *)(*(int *)&amemCacheSet->field_0x58 + param_2 * 0x1c);
    if (*piVar4 == 0) {
      if (*(char *)((int)piVar4 + 0x1a) == '\0') {
        *piVar4 = piVar4[1];
        iVar1 = *piVar4;
      }
      else {
        pcVar3 = param_3;
        if (param_3 == (char *)0x0) {
          pcVar3 = &DAT_8032f7d4;
        }
        iVar1 = alloc__Q27CMemory6CStageFUlPcUli(amemCacheSet->m_stage,piVar4[2],pcVar3,param_4,1);
        *piVar4 = iVar1;
        if (*piVar4 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = DMAEntry__9CRedSoundFiiiiiPFPv_vPv
                            (&Sound.m_redSound,0,1,*piVar4,piVar4[1],piVar4[2],0,0);
          DumpMapFile__7CSystemFPv((CSystem *)auStack_68);
          Start__10CStopWatchFv(auStack_68);
          dVar6 = (double)FLOAT_8032f7d8;
          while (iVar2 = DMACheck__9CRedSoundFi(&Sound.m_redSound,iVar1), iVar2 != 0) {
            Stop__10CStopWatchFv(auStack_68);
            dVar5 = (double)Get__10CStopWatchFv(auStack_68);
            if (dVar5 < dVar6) {
              Start__10CStopWatchFv(auStack_68);
            }
            else {
              if (System.m_execParam != 0) {
                Printf__7CSystemFPce(&System,s__________________________________801d669c);
              }
              CheckDriver__6CSoundFi(&Sound,1);
              Reset__10CStopWatchFv(auStack_68);
              Start__10CStopWatchFv(auStack_68);
            }
          }
          iVar1 = *piVar4;
          __ct__10CStopWatchFPc(auStack_68,0xffffffff);
        }
      }
    }
    else {
      iVar1 = 0;
    }
    if (iVar1 != 0) break;
    AmemFreeLowPrio__13CAmemCacheSetFi
              (amemCacheSet,*(undefined4 *)(param_2 * 0x1c + *(int *)&amemCacheSet->field_0x58 + 8))
    ;
  }
  return iVar1;
}

