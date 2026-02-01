// Function: SetOpenMenu__6JoyBusFic
// Entry: 800a6094
// Size: 656 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 SetOpenMenu__6JoyBusFic(JoyBus *joyBus,int playerIndex,char menuId)

{
  char cVar2;
  undefined4 uVar1;
  uint32_t uVar3;
  uint32_t local_18;
  
  if (((playerIndex == 0) && (cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,0), cVar2 != '\0')) &&
     (menuId != '\0')) {
    MenuPcs._2148_2_ = menuId + -1;
    Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = '\x01';
    uVar1 = 0;
    joyBus->m_ctrlModeArr[0] = '\x01';
  }
  else if (((playerIndex == 1) && (cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,1), cVar2 != '\0')) &&
          (menuId == '\0')) {
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,joyBus->m_threadParams[1].m_portIndex);
    if (cVar2 == '\0') {
      if (joyBus->m_threadRunningMask == '\0') {
        uVar1 = 0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[1].m_portIndex);
        uVar3 = joyBus->m_threadParams[1].m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
          joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = 0x140f0000;
          uVar3 = joyBus->m_threadParams[1].m_portIndex;
          joyBus->m_cmdCount[uVar3] = joyBus->m_cmdCount[uVar3] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[1].m_portIndex);
          uVar1 = 0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
          uVar1 = 0xffffffff;
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,joyBus->m_threadParams[playerIndex].m_portIndex);
    if (cVar2 == '\0') {
      local_18 = (uint)CONCAT21(0x140f,menuId) << 8;
      if (joyBus->m_threadRunningMask == '\0') {
        uVar1 = 0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[playerIndex].m_portIndex
                       );
        uVar3 = joyBus->m_threadParams[playerIndex].m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
          joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = local_18;
          uVar3 = joyBus->m_threadParams[playerIndex].m_portIndex;
          joyBus->m_cmdCount[uVar3] = joyBus->m_cmdCount[uVar3] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores +
                            joyBus->m_threadParams[playerIndex].m_portIndex);
          uVar1 = 0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
          uVar1 = 0xffffffff;
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

