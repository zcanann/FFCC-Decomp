// Function: ChkEmpty__6McCtrlFi
// Entry: 800e7dc8
// Size: 808 bytes

undefined4 ChkEmpty__6McCtrlFi(McCtrl *mcCtrl,int param_2)

{
  int iVar1;
  char cVar4;
  int32_t iVar2;
  undefined4 uVar3;
  int local_18;
  int local_14 [3];
  
  if (mcCtrl->m_state < 0) {
    return 0xffffffff;
  }
  mcCtrl->m_previousState = mcCtrl->m_state;
  iVar1 = mcCtrl->m_state;
  if (iVar1 == 2) {
    iVar2 = McOpen__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    mcCtrl->m_lastResult = iVar2;
    iVar1 = mcCtrl->m_lastResult;
    if (iVar1 < 0) {
      if (iVar1 == -4) {
        if (param_2 != 0) {
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
          mcCtrl->m_state = -1;
          return 0xfffffffa;
        }
        mcCtrl->m_state = 3;
      }
      else {
        if (iVar1 == -5) {
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
          mcCtrl->m_state = -1;
          return 0xfffffffb;
        }
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        mcCtrl->m_state = -1;
      }
    }
    else {
      McClose__14CMemoryCardManFv(&MemoryCardMan);
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      mcCtrl->m_state = 4;
    }
  }
  else if (iVar1 < 2) {
    if (iVar1 == 0) {
      McMount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar2;
      mcCtrl->m_state = 1;
      mcCtrl->m_iteration = 0;
    }
    else if ((-1 < iVar1) &&
            (cVar4 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan), cVar4 == '\x01')) {
      iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar2;
      iVar1 = mcCtrl->m_lastResult;
      if (iVar1 == 0) {
        mcCtrl->m_state = 2;
      }
      else {
        if (iVar1 == -0xd) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
          mcCtrl->m_state = -1;
          return 0xfffffffd;
        }
        if (iVar1 == -6) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
          mcCtrl->m_state = -1;
          return 0xfffffffc;
        }
        if (iVar1 == -5) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
          mcCtrl->m_state = -1;
          return 0xfffffffb;
        }
        MemoryCardMan.m_opDoneFlag = '\x01';
        MemoryCardMan.m_currentSlot = 0xff;
        mcCtrl->m_state = -1;
      }
    }
  }
  else if ((iVar1 != 4) && (iVar1 < 4)) {
    iVar2 = McFreeBlocks__14CMemoryCardManFiPiPi
                      (&MemoryCardMan,mcCtrl->m_cardChannel,local_14,&local_18);
    mcCtrl->m_lastResult = iVar2;
    McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    if (mcCtrl->m_lastResult < 0) {
      if (mcCtrl->m_lastResult == -5) {
        mcCtrl->m_state = -1;
        return 0xfffffffb;
      }
      mcCtrl->m_state = -1;
    }
    else {
      if (local_18 == 0) {
        mcCtrl->m_state = -1;
        return 0xfffffffe;
      }
      if (local_14[0] < 0x2c000) {
        mcCtrl->m_state = -1;
        return 0xfffffffe;
      }
      mcCtrl->m_state = 4;
    }
  }
  if (mcCtrl->m_state == -1) {
    uVar3 = 0xffffffff;
  }
  else if (mcCtrl->m_state == 4) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

