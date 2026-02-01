// Function: SaveDat__6McCtrlFv
// Entry: 800e8738
// Size: 2292 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int SaveDat__6McCtrlFv(McCtrl *mcCtrl)

{
  char cVar3;
  int32_t iVar1;
  int iVar2;
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
        mcCtrl->m_state = 7;
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
        mcCtrl->m_state = -1;
        return ((int)~(mcCtrl->m_lastResult + 5U | -mcCtrl->m_lastResult - 5U) >> 0x1f) + -3;
      }
      mcCtrl->m_state = 7;
    }
    break;
  case 7:
    iVar1 = McOpen__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    mcCtrl->m_lastResult = iVar1;
    if (mcCtrl->m_lastResult == -4) {
      mcCtrl->m_state = 10;
    }
    else {
      if (mcCtrl->m_lastResult == -5) {
        mcCtrl->m_state = -1;
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        return -4;
      }
      cVar3 = IsBrokenFile__14CMemoryCardManFv(&MemoryCardMan);
      if (cVar3 == '\0') {
        CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_state = 0xc;
      }
      else {
        mcCtrl->m_state = 8;
      }
    }
    break;
  case 8:
    McDelFile__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
    mcCtrl->m_lastResult = iVar1;
    mcCtrl->m_state = 9;
    break;
  case 9:
    cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar3 == '\x01') {
      iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar1;
      iVar2 = mcCtrl->m_lastResult;
      if (iVar2 < 0) {
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
        memset(&local_60,0,0x48);
        iVar5 = 0;
        local_1e = 0;
        iVar2 = 0;
        do {
          puVar4 = (undefined4 *)((int)MenuPcs.m_unk0x838 + iVar2);
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
          iVar2 = iVar2 + 0x48;
          *(undefined *)((int)puVar4 + 0x41) = local_1f;
          *(undefined *)((int)puVar4 + 0x42) = local_1e;
          *(undefined *)((int)puVar4 + 0x43) = local_1d;
        } while (iVar5 < 4);
        mcCtrl->m_state = 10;
      }
    }
    break;
  case 10:
    mcCtrl->m_createFlag = 1;
    McCreate__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    mcCtrl->m_state = 0xb;
    break;
  case 0xb:
    cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar3 == '\x01') {
      iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar1;
      if (mcCtrl->m_lastResult < 0) {
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        mcCtrl->m_state = -1;
        if (mcCtrl->m_lastResult == -5) {
          return -4;
        }
      }
      else {
        mcCtrl->m_state = 0x10;
      }
    }
    break;
  case 0xc:
    iVar1 = McGetStat__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    mcCtrl->m_lastResult = iVar1;
    if (mcCtrl->m_lastResult == 0) {
      mcCtrl->m_state = 0xd;
    }
    else {
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      mcCtrl->m_state = -1;
      if (mcCtrl->m_lastResult == -5) {
        return -4;
      }
    }
    break;
  case 0xd:
    CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
    SetMcIconImage__14CMemoryCardManFv(&MemoryCardMan);
    McWrite__14CMemoryCardManFPcii(&MemoryCardMan,0,0x4000,0);
    mcCtrl->m_state = 0xe;
    break;
  case 0xe:
    cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar3 == '\x01') {
      iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar1;
      if (mcCtrl->m_lastResult < 0) {
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
        mcCtrl->m_state = -1;
        if (mcCtrl->m_lastResult == -5) {
          return -4;
        }
      }
      else {
        mcCtrl->m_state = 0xf;
      }
    }
    break;
  case 0xf:
    iVar1 = McSetStat__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
    mcCtrl->m_lastResult = iVar1;
    if (mcCtrl->m_lastResult == 0) {
      mcCtrl->m_state = 0x12;
    }
    else {
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_state = -1;
      if (mcCtrl->m_lastResult == -5) {
        return -4;
      }
    }
    break;
  case 0x10:
    CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
    McWrite__14CMemoryCardManFPcii(&MemoryCardMan,0,0xa000,mcCtrl->m_iteration * 0xa000 + 0x4000);
    mcCtrl->m_state = 0x11;
    break;
  case 0x11:
    cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar3 == '\x01') {
      mcCtrl->m_iteration = mcCtrl->m_iteration + 1;
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
      else if (mcCtrl->m_iteration < 4) {
        mcCtrl->m_state = 0x10;
      }
      else {
        mcCtrl->m_state = 0xc;
      }
    }
    break;
  case 0x12:
    iVar2 = CARDGetSerialNo(mcCtrl->m_cardChannel,&local_68);
    if (iVar2 != 0) {
      McClose__14CMemoryCardManFv(&MemoryCardMan);
      McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
      DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_state = -1;
      return -1;
    }
    if (Game.game.m_gameWork.m_mcHasSerial._0_1_ == '\0') {
      Game.game.m_gameWork.m_mcSerial0 = local_68;
      Game.game.m_gameWork.m_mcSerial1 = local_64;
      Game.game.m_gameWork.m_mcRandom = Rand__5CMathFUl(&Math,0x7fffffff);
      Game.game.m_gameWork.m_mcHasSerial._0_1_ = '\x01';
    }
    else {
      mcCtrl->m_serialHi = local_64;
      mcCtrl->m_serialLo = local_68;
    }
    CreateMcBuff__14CMemoryCardManFv(&MemoryCardMan);
    if (mcCtrl->m_userBuffer == (void *)0x0) {
      MakeSaveData__14CMemoryCardManFv(&MemoryCardMan);
    }
    else {
      memcpy(MemoryCardMan.m_saveBuffer,mcCtrl->m_userBuffer,0x8bd0);
    }
    McWrite__14CMemoryCardManFPcii(&MemoryCardMan,0,0xa000,mcCtrl->m_saveIndex * 0xa000 + 0x4000);
    mcCtrl->m_state = 0x13;
    break;
  case 0x13:
    cVar3 = AsyncFinished__14CMemoryCardManFv(&MemoryCardMan);
    if (cVar3 == '\x01') {
      iVar1 = GetResult__14CMemoryCardManFv(&MemoryCardMan);
      mcCtrl->m_lastResult = iVar1;
      if (mcCtrl->m_lastResult < 0) {
        mcCtrl->m_state = -1;
        if (mcCtrl->m_lastResult == -5) {
          McClose__14CMemoryCardManFv(&MemoryCardMan);
          McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
          DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
          return -4;
        }
      }
      else {
        DecodeData__14CMemoryCardManFv(&MemoryCardMan);
        SetListDat__6McCtrlFii(mcCtrl,mcCtrl->m_saveIndex,1);
        BindMcObj__8CMenuPcsFi(&MenuPcs,mcCtrl->m_saveIndex);
        mcCtrl->m_state = 0x14;
      }
      iVar2 = McClose__14CMemoryCardManFv(&MemoryCardMan);
      if (iVar2 == 0) {
        McUnmount__14CMemoryCardManFi(&MemoryCardMan,mcCtrl->m_cardChannel);
        DestroyMcBuff__14CMemoryCardManFv(&MemoryCardMan);
      }
      else {
        mcCtrl->m_lastResult = iVar2;
        mcCtrl->m_state = -1;
      }
    }
  }
  if (mcCtrl->m_state == -1) {
    iVar2 = -1;
  }
  else if (mcCtrl->m_state == 0x14) {
    iVar2 = 1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

