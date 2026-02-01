// Function: SaveDataBuffer__6McCtrlFPc
// Entry: 800e7430
// Size: 1224 bytes

int SaveDataBuffer__6McCtrlFPc(McCtrl *mcCtrl,undefined4 param_2)

{
  uint8_t *puVar1;
  uint uVar2;
  undefined4 uVar3;
  char cVar6;
  int32_t iVar4;
  int iVar5;
  uint32_t local_18;
  uint32_t local_14;
  
  if (mcCtrl->m_state < 0) {
    return -1000;
  }
  mcCtrl->m_previousState = mcCtrl->m_state;
  switch(mcCtrl->m_state) {
  case 0:
    McMount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    iVar4 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
    mcCtrl->m_lastResult = iVar4;
    mcCtrl->m_state = 1;
    mcCtrl->m_iteration = 0;
    break;
  case 1:
    cVar6 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar6 == '\x01') {
      iVar4 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar4;
      iVar5 = mcCtrl->m_lastResult;
      if (iVar5 < 0) {
        MemoryCardMan.m_opDoneFlag = '\x01';
        MemoryCardMan.m_currentSlot = 0xff;
        if (iVar5 == -6) {
          mcCtrl->m_state = 2;
        }
        else {
          if (iVar5 == -0xd) {
            mcCtrl->m_state = -1;
            return -0xd;
          }
          if (iVar5 == -5) {
            mcCtrl->m_state = -1;
            return -5;
          }
          mcCtrl->m_state = -1;
        }
      }
      else {
        mcCtrl->m_state = 7;
      }
    }
    break;
  case 2:
    McCheck__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    iVar4 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
    mcCtrl->m_lastResult = iVar4;
    mcCtrl->m_state = 3;
    break;
  case 3:
    cVar6 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar6 == '\x01') {
      iVar4 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar4;
      if (mcCtrl->m_lastResult != 0) {
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        mcCtrl->m_state = -1;
        uVar2 = countLeadingZeros(-5 - mcCtrl->m_lastResult);
        return (uVar2 >> 5) - 6;
      }
      mcCtrl->m_state = 7;
    }
    break;
  case 7:
    iVar4 = McOpen__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    mcCtrl->m_lastResult = iVar4;
    if (mcCtrl->m_lastResult == -4) {
      mcCtrl->m_state = -1;
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      return -4;
    }
    if (mcCtrl->m_lastResult == -5) {
      mcCtrl->m_state = -1;
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      return -5;
    }
    CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
    mcCtrl->m_state = 0x10;
    break;
  case 0x10:
    iVar5 = CARDGetSerialNo(mcCtrl->m_cardChannel,&local_18);
    if (iVar5 != 0) {
      McClose__14CMemoryCardManFv(&MemoryCardMan);
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_state = -1;
      return -999;
    }
    mcCtrl->m_serialHi = local_14;
    mcCtrl->m_serialLo = local_18;
    puVar1 = MemoryCardMan.m_saveBuffer;
    memcpy(MemoryCardMan.m_saveBuffer,param_2,0x8bd0);
    iVar5 = *(int *)(puVar1 + 0x30);
    if (*(int *)(puVar1 + iVar5 * 0x9c0 + 0x1a84) == 0) {
      puVar1[0x30] = 0xff;
      puVar1[0x31] = 0xff;
      puVar1[0x32] = 0xff;
      puVar1[0x33] = 0xff;
    }
    if (puVar1[iVar5 * 0x9c0 + 0x1d90] != '\0') {
      puVar1[0x30] = 0xff;
      puVar1[0x31] = 0xff;
      puVar1[0x32] = 0xff;
      puVar1[0x33] = 0xff;
    }
    iVar5 = *(int *)(puVar1 + 0x34);
    if (*(int *)(puVar1 + iVar5 * 0x9c0 + 0x1a84) == 0) {
      puVar1[0x34] = 0xff;
      puVar1[0x35] = 0xff;
      puVar1[0x36] = 0xff;
      puVar1[0x37] = 0xff;
    }
    if (puVar1[iVar5 * 0x9c0 + 0x1d90] != '\0') {
      puVar1[0x34] = 0xff;
      puVar1[0x35] = 0xff;
      puVar1[0x36] = 0xff;
      puVar1[0x37] = 0xff;
    }
    iVar5 = *(int *)(puVar1 + 0x38);
    if (*(int *)(puVar1 + iVar5 * 0x9c0 + 0x1a84) == 0) {
      puVar1[0x38] = 0xff;
      puVar1[0x39] = 0xff;
      puVar1[0x3a] = 0xff;
      puVar1[0x3b] = 0xff;
    }
    if (puVar1[iVar5 * 0x9c0 + 0x1d90] != '\0') {
      puVar1[0x38] = 0xff;
      puVar1[0x39] = 0xff;
      puVar1[0x3a] = 0xff;
      puVar1[0x3b] = 0xff;
    }
    iVar5 = *(int *)(puVar1 + 0x3c);
    if (*(int *)(puVar1 + iVar5 * 0x9c0 + 0x1a84) == 0) {
      puVar1[0x3c] = 0xff;
      puVar1[0x3d] = 0xff;
      puVar1[0x3e] = 0xff;
      puVar1[0x3f] = 0xff;
    }
    if (puVar1[iVar5 * 0x9c0 + 0x1d90] != '\0') {
      puVar1[0x3c] = 0xff;
      puVar1[0x3d] = 0xff;
      puVar1[0x3e] = 0xff;
      puVar1[0x3f] = 0xff;
    }
    uVar3 = CalcCrc__14CMemoryCardManFPQ22Mc7SaveDat(&MemoryCardMan,puVar1);
    *(undefined4 *)(puVar1 + 0x1c) = uVar3;
    EncodeData__14CMemoryCardManFv(&MemoryCardMan);
    McWrite__14CMemoryCardManFPcii(&MemoryCardMan,0,0xa000,mcCtrl->m_saveIndex * 0xa000 + 0x4000);
    mcCtrl->m_state = 0x11;
    break;
  case 0x11:
    cVar6 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar6 == '\x01') {
      iVar4 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar4;
      if (mcCtrl->m_lastResult < 0) {
        mcCtrl->m_state = -1;
        if (mcCtrl->m_lastResult == -5) {
          McClose__14CMemoryCardManFv(&MemoryCardMan);
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
          DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
          return -5;
        }
      }
      else {
        mcCtrl->m_state = 0x12;
      }
      iVar5 = McClose__14CMemoryCardManFv(&MemoryCardMan);
      if (iVar5 == 0) {
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      }
      else {
        mcCtrl->m_lastResult = iVar5;
        mcCtrl->m_state = -1;
      }
    }
  }
  if (mcCtrl->m_state == -1) {
    iVar5 = -999;
  }
  else if (mcCtrl->m_state == 0x12) {
    iVar5 = 1;
  }
  else {
    iVar5 = 0;
  }
  return iVar5;
}

