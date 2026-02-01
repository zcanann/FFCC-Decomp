// Function: LoadDat__6McCtrlFv
// Entry: 800e8300
// Size: 1080 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int LoadDat__6McCtrlFv(McCtrl *mcCtrl)

{
  char cVar3;
  int32_t iVar1;
  int iVar2;
  uint32_t local_18;
  uint32_t local_14;
  
  if (mcCtrl->m_state < 0) {
    return -1;
  }
  mcCtrl->m_previousState = mcCtrl->m_state;
  switch(mcCtrl->m_state) {
  case 0:
    McMount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
    mcCtrl->m_lastResult = iVar1;
    mcCtrl->m_state = 1;
    mcCtrl->m_iteration = 0;
    break;
  case 1:
    cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar3 == '\x01') {
      iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar1;
      iVar2 = mcCtrl->m_lastResult;
      if (iVar2 < 0) {
        MemoryCardMan.m_opDoneFlag = '\x01';
        MemoryCardMan.m_currentSlot = 0xff;
        if (iVar2 == -6) {
          mcCtrl->m_state = 2;
        }
        else {
          if (iVar2 == -0xd) {
            mcCtrl->m_state = -1;
            return -2;
          }
          if (iVar2 == -5) {
            mcCtrl->m_state = -1;
            return -4;
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
    iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
    mcCtrl->m_lastResult = iVar1;
    mcCtrl->m_state = 3;
    break;
  case 3:
    cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar3 == '\x01') {
      iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar1;
      if (mcCtrl->m_lastResult != 0) {
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_state = 7;
        return ((int)~(mcCtrl->m_lastResult + 5U | -mcCtrl->m_lastResult - 5U) >> 0x1f) + -3;
      }
      mcCtrl->m_state = 4;
    }
    break;
  case 4:
    iVar1 = McOpen__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    mcCtrl->m_lastResult = iVar1;
    if (mcCtrl->m_lastResult < 0) {
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      if (mcCtrl->m_lastResult == -4) {
        mcCtrl->m_state = 7;
      }
      else {
        if (mcCtrl->m_lastResult == -5) {
          mcCtrl->m_state = -1;
          return -4;
        }
        mcCtrl->m_state = -1;
      }
    }
    else {
      mcCtrl->m_state = 5;
    }
    break;
  case 5:
    iVar2 = CARDGetSerialNo(mcCtrl->m_cardChannel,&local_18);
    if (iVar2 != 0) {
      McClose__14CMemoryCardManFv(&MemoryCardMan);
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_state = -1;
      return -1;
    }
    mcCtrl->m_serialHi = local_14;
    mcCtrl->m_serialLo = local_18;
    CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
    McRead__14CMemoryCardManFPcii(&MemoryCardMan,0,0xa000,mcCtrl->m_saveIndex * 0xa000 + 0x4000);
    mcCtrl->m_state = 6;
    break;
  case 6:
    cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar3 == '\x01') {
      iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar1;
      if (mcCtrl->m_lastResult < 0) {
        McClose__14CMemoryCardManFv(&MemoryCardMan);
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_state = -1;
        if (mcCtrl->m_lastResult == -5) {
          return -4;
        }
      }
      else {
        DecodeData__14CMemoryCardManFv(&MemoryCardMan);
        McClose__14CMemoryCardManFv(&MemoryCardMan);
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        if (mcCtrl->m_userBuffer == (void *)0x0) {
          LoadInit__5CGameFv(&Game.game);
          SetLoadData__14CMemoryCardManFv(&MemoryCardMan);
          LoadFinished__5CGameFv(&Game.game);
        }
        else {
          memcpy(mcCtrl->m_userBuffer,MemoryCardMan.m_saveBuffer,0x8bd0);
          CalcSaveDatHpMax__14CMemoryCardManFPQ22Mc7SaveDat(&MemoryCardMan,mcCtrl->m_userBuffer);
        }
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_state = 7;
      }
    }
  }
  if (mcCtrl->m_state == -1) {
    iVar2 = -1;
  }
  else if (mcCtrl->m_state == 7) {
    iVar2 = 1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

