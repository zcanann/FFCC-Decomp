// Function: AddScenegraph__7CSystemFP8CProcessi
// Entry: 8002182c
// Size: 264 bytes

undefined4 AddScenegraph__7CSystemFP8CProcessi(CSystem *system,CProcess *process,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  COrder *pCVar4;
  COrder *pCVar5;
  undefined4 *puVar6;
  
  puVar1 = (undefined4 *)(**(code **)((int)(process->manager).vtable + 0x10))(process,param_3);
  iVar2 = __ptmf_test(puVar1 + 1);
  if (iVar2 != 0) {
    __ptmf_scall(process);
  }
  puVar6 = puVar1 + 7;
  iVar2 = 0;
  do {
    iVar3 = __ptmf_test(puVar6);
    if (iVar3 == 0) {
      return 1;
    }
    pCVar4 = *(COrder **)((int)&(system->m_stopwatch).max + 4);
    pCVar5 = pCVar4;
    do {
      if ((uint)puVar6[3] < pCVar5->mPriority) {
        pCVar4 = (system->m_freeOrderHead).mNext;
        (system->m_freeOrderHead).mNext = pCVar4->mNext;
        pCVar4->mNext = pCVar5;
        pCVar4->mPrevious = pCVar5->mPrevious;
        pCVar5->mPrevious->mNext = pCVar4;
        pCVar5->mPrevious = pCVar4;
        pCVar4->mEntry = puVar6;
        pCVar4->mInsertIndex = iVar2;
        iVar2 = iVar2 + 1;
        pCVar4->mDescBlock = puVar1;
        pCVar4->mOwner = process;
        pCVar4->mPriority = puVar6[3];
        pCVar4->mDebugName = (void *)*puVar1;
        system->m_orderCount = system->m_orderCount + 1;
        break;
      }
      pCVar5 = pCVar5->mNext;
    } while (pCVar5 != pCVar4);
    puVar6 = puVar6 + 5;
  } while( true );
}

