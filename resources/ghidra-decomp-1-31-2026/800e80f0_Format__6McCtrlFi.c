// Function: Format__6McCtrlFi
// Entry: 800e80f0
// Size: 528 bytes

undefined4 Format__6McCtrlFi(McCtrl *mcCtrl,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  char cVar4;
  int32_t iVar3;
  
  if (mcCtrl->m_state < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    mcCtrl->m_previousState = mcCtrl->m_state;
    iVar1 = mcCtrl->m_state;
    if (iVar1 == 2) {
      McFormat__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      mcCtrl->m_state = 3;
    }
    else if (iVar1 < 2) {
      if (iVar1 == 0) {
        McMount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        iVar3 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_lastResult = iVar3;
        mcCtrl->m_state = 1;
        mcCtrl->m_iteration = 0;
      }
      else if ((-1 < iVar1) &&
              (cVar4 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan), cVar4 == '\x01')) {
        iVar3 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_lastResult = iVar3;
        iVar1 = mcCtrl->m_lastResult;
        if ((iVar1 == -6) || ((iVar1 == -0xd || (iVar1 == 0)))) {
          mcCtrl->m_state = 2;
        }
        else {
          if (iVar1 == -5) {
            MemoryCardMan.m_opDoneFlag = '\x01';
            MemoryCardMan.m_currentSlot = 0xff;
            mcCtrl->m_state = -1;
            return 0xfffffffe;
          }
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
          mcCtrl->m_state = -1;
        }
      }
    }
    else if (((iVar1 != 4) && (iVar1 < 4)) &&
            (cVar4 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan), cVar4 == '\x01')) {
      iVar3 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar3;
      if (mcCtrl->m_lastResult < 0) {
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        mcCtrl->m_state = -1;
        if (mcCtrl->m_lastResult == -5) {
          return 0xfffffffe;
        }
      }
      else {
        if (param_2 != 0) {
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        }
        mcCtrl->m_state = 4;
      }
    }
    if (mcCtrl->m_state == -1) {
      uVar2 = 0xffffffff;
    }
    else if (mcCtrl->m_state == 4) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

