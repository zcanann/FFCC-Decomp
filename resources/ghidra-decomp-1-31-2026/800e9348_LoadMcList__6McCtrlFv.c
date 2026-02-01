// Function: LoadMcList__6McCtrlFv
// Entry: 800e9348
// Size: 1404 bytes

int LoadMcList__6McCtrlFv(McCtrl *mcCtrl)

{
  int iVar1;
  char cVar3;
  int32_t iVar2;
  undefined4 *puVar4;
  int iVar5;
  uint32_t local_68;
  uint32_t local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined auStack_34 [21];
  undefined local_1f;
  undefined local_1e;
  undefined local_1d;
  
  if (mcCtrl->m_state < 0) {
    iVar1 = -1;
  }
  else {
    mcCtrl->m_previousState = mcCtrl->m_state;
    switch(mcCtrl->m_state) {
    case 0:
      memset(MenuPcs.m_unk0x838,0,0x120);
      McMount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar2;
      mcCtrl->m_state = 1;
      mcCtrl->m_iteration = 0;
      break;
    case 1:
      cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
      if (cVar3 == '\x01') {
        iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_lastResult = iVar2;
        iVar1 = mcCtrl->m_lastResult;
        if (iVar1 < 0) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
          if (iVar1 == -6) {
            mcCtrl->m_state = 2;
          }
          else if (iVar1 == -0xd) {
            mcCtrl->m_state = -1;
            return -2;
          }
          if (mcCtrl->m_lastResult == -5) {
            mcCtrl->m_state = -1;
            return -4;
          }
          mcCtrl->m_state = -1;
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
      cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
      if (cVar3 == '\x01') {
        iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_lastResult = iVar2;
        if (mcCtrl->m_lastResult != 0) {
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
          DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
          mcCtrl->m_state = -1;
          return ((int)~(mcCtrl->m_lastResult + 5U | -mcCtrl->m_lastResult - 5U) >> 0x1f) + -3;
        }
        mcCtrl->m_state = 4;
      }
      break;
    case 4:
      iVar2 = McOpen__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      mcCtrl->m_lastResult = iVar2;
      if (mcCtrl->m_lastResult < 0) {
        if (mcCtrl->m_lastResult == -4) {
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
          DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
          mcCtrl->m_state = 7;
          if (mcCtrl->m_lastResult == -5) {
            return -4;
          }
        }
        else {
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
          DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
          mcCtrl->m_state = -1;
        }
      }
      else {
        cVar3 = IsBrokenFile__14CMemoryCardManFv(&MemoryCardMan);
        if (cVar3 == '\0') {
          mcCtrl->m_state = 5;
        }
        else {
          iVar1 = McClose__14CMemoryCardManFv(&MemoryCardMan);
          if (iVar1 == 0) {
            McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
            DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
            memset(&local_60,0,0x48);
            iVar5 = 0;
            local_1e = 1;
            iVar1 = 0;
            do {
              puVar4 = (undefined4 *)((int)MenuPcs.m_unk0x838 + iVar1);
              puVar4[1] = local_5c;
              *puVar4 = local_60;
              puVar4[2] = local_58;
              puVar4[3] = local_54;
              puVar4[4] = local_50;
              puVar4[5] = local_4c;
              puVar4[6] = local_48;
              puVar4[7] = local_44;
              puVar4[8] = local_40;
              puVar4[9] = local_3c;
              puVar4[10] = local_38;
              __copy(puVar4 + 0xb,auStack_34,0x15);
              iVar5 = iVar5 + 1;
              iVar1 = iVar1 + 0x48;
              *(undefined *)((int)puVar4 + 0x41) = local_1f;
              *(undefined *)((int)puVar4 + 0x42) = local_1e;
              *(undefined *)((int)puVar4 + 0x43) = local_1d;
            } while (iVar5 < 4);
            mcCtrl->m_state = 7;
          }
          else {
            mcCtrl->m_lastResult = iVar1;
            mcCtrl->m_state = -1;
          }
        }
      }
      break;
    case 5:
      iVar1 = CARDGetSerialNo(mcCtrl->m_cardChannel,&local_68);
      if (iVar1 != 0) {
        McClose__14CMemoryCardManFv(&MemoryCardMan);
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_state = -1;
        return -1;
      }
      mcCtrl->m_serialHi = local_64;
      mcCtrl->m_serialLo = local_68;
      CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      McRead__14CMemoryCardManFPcii(&MemoryCardMan,0,0xa000,mcCtrl->m_iteration * 0xa000 + 0x4000);
      mcCtrl->m_state = 6;
      break;
    case 6:
      cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
      if (cVar3 == '\x01') {
        iVar2 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_lastResult = iVar2;
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
          iVar1 = mcCtrl->m_iteration;
          mcCtrl->m_iteration = iVar1 + 1;
          SetListDat__6McCtrlFii(mcCtrl,iVar1,0);
          if (mcCtrl->m_iteration < 4) {
            mcCtrl->m_state = 5;
          }
          else {
            iVar1 = McClose__14CMemoryCardManFv(&MemoryCardMan);
            if (iVar1 == 0) {
              McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
              DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
              mcCtrl->m_state = 7;
            }
            else {
              mcCtrl->m_lastResult = iVar1;
              mcCtrl->m_state = -1;
            }
          }
        }
      }
    }
    if (mcCtrl->m_state == -1) {
      iVar1 = -1;
    }
    else if (mcCtrl->m_state == 7) {
      iVar1 = 1;
    }
    else {
      iVar1 = 0;
    }
  }
  return iVar1;
}

