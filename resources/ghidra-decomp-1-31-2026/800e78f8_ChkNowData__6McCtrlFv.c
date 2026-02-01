// Function: ChkNowData__6McCtrlFv
// Entry: 800e78f8
// Size: 1108 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int ChkNowData__6McCtrlFv(McCtrl *mcCtrl)

{
  uint uVar1;
  char cVar4;
  int32_t iVar2;
  int iVar3;
  uint32_t local_18;
  uint32_t local_14;
  
  if (mcCtrl->m_state < 0) {
    return -999;
  }
  mcCtrl->m_previousState = mcCtrl->m_state;
  switch(mcCtrl->m_state) {
  case 0:
    McMount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
    mcCtrl->m_lastResult = iVar2;
    mcCtrl->m_state = 1;
    mcCtrl->m_iteration = 0;
    break;
  case 1:
    cVar4 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar4 == '\x01') {
      iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar2;
      iVar3 = mcCtrl->m_lastResult;
      if (iVar3 < 0) {
        MemoryCardMan.m_opDoneFlag = '\x01';
        MemoryCardMan.m_currentSlot = 0xff;
        if (iVar3 == -6) {
          mcCtrl->m_state = 2;
        }
        else {
          if (iVar3 == -0xd) {
            mcCtrl->m_state = -1;
            return -0xd;
          }
          if (iVar3 == -5) {
            mcCtrl->m_state = -1;
            return -5;
          }
          mcCtrl->m_state = -1;
        }
      }
      else {
        mcCtrl->m_state = 4;
      }
    }
    break;
  case 2:
    McCheck__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
    mcCtrl->m_lastResult = iVar2;
    mcCtrl->m_state = 3;
    break;
  case 3:
    cVar4 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar4 == '\x01') {
      iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar2;
      if (mcCtrl->m_lastResult != 0) {
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_state = 7;
        uVar1 = countLeadingZeros(-5 - mcCtrl->m_lastResult);
        return (uVar1 >> 5) - 6;
      }
      mcCtrl->m_state = 4;
    }
    break;
  case 4:
    iVar2 = McOpen__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    mcCtrl->m_lastResult = iVar2;
    if (mcCtrl->m_lastResult < 0) {
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      if (mcCtrl->m_lastResult == -4) {
        mcCtrl->m_state = -1;
        return -4;
      }
      if (mcCtrl->m_lastResult == -5) {
        mcCtrl->m_state = -1;
        return -5;
      }
      mcCtrl->m_state = -1;
    }
    else {
      mcCtrl->m_state = 5;
    }
    break;
  case 5:
    iVar3 = CARDGetSerialNo(mcCtrl->m_cardChannel,&local_18);
    if (iVar3 != 0) {
      McClose__14CMemoryCardManFv(&MemoryCardMan);
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_state = -1;
      return -999;
    }
    mcCtrl->m_serialHi = local_14;
    mcCtrl->m_serialLo = local_18;
    CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
    McRead__14CMemoryCardManFPcii(&MemoryCardMan,0,0xa000,mcCtrl->m_saveIndex * 0xa000 + 0x4000);
    mcCtrl->m_state = 6;
    break;
  case 6:
    cVar4 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar4 == '\x01') {
      iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar2;
      if (mcCtrl->m_lastResult < 0) {
        McClose__14CMemoryCardManFv(&MemoryCardMan);
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_state = -1;
        if (mcCtrl->m_lastResult == -5) {
          return -5;
        }
      }
      else {
        DecodeData__14CMemoryCardManFv(&MemoryCardMan);
        iVar3 = McClose__14CMemoryCardManFv(&MemoryCardMan);
        if (iVar3 == 0) {
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
          if ((*(uint32_t *)(MemoryCardMan.m_saveBuffer + 0x13d4) ==
               Game.game.m_gameWork.m_mcSerial1 &&
               *(uint32_t *)(MemoryCardMan.m_saveBuffer + 0x13d0) ==
               Game.game.m_gameWork.m_mcSerial0) &&
             (*(uint32_t *)(MemoryCardMan.m_saveBuffer + 0x13d8) == Game.game.m_gameWork.m_mcRandom)
             ) {
            iVar3 = 1;
          }
          else {
            iVar3 = -1000;
          }
          DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
          mcCtrl->m_state = 7;
          return iVar3;
        }
        mcCtrl->m_lastResult = iVar3;
        mcCtrl->m_state = -1;
      }
    }
  }
  if (mcCtrl->m_state == -1) {
    iVar3 = -999;
  }
  else if (mcCtrl->m_state == 7) {
    iVar3 = 1;
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}

