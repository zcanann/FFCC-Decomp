// Function: RemoveScenegraph__7CSystemFP8CProcessi
// Entry: 80021760
// Size: 204 bytes

void RemoveScenegraph__7CSystemFP8CProcessi(CSystem *system,CProcess *process,int arg)

{
  void *pvVar1;
  int iVar2;
  COrder *pCVar3;
  COrder *pCVar4;
  
  pvVar1 = (void *)(**(code **)((int)(process->manager).vtable + 0x10))(process,arg);
  pCVar4 = *(COrder **)((int)&(system->m_stopwatch).max + 4);
  do {
    pCVar3 = pCVar4->mNext;
    if (pCVar4->mDescBlock == pvVar1) {
      pCVar4->mPrevious->mNext = pCVar3;
      pCVar4->mNext->mPrevious = pCVar4->mPrevious;
      pCVar4->mNext = (system->m_freeOrderHead).mNext;
      (system->m_freeOrderHead).mNext = pCVar4;
      system->m_orderCount = system->m_orderCount + -1;
    }
    pCVar4 = pCVar3;
  } while (pCVar3 != (COrder *)&(system->m_stopwatch).total);
  iVar2 = __ptmf_test((int)pvVar1 + 0x10);
  if (iVar2 != 0) {
    __ptmf_scall(process);
  }
  return;
}

