// Function: SendHitEnemy__6JoyBusFics
// Entry: 800a6324
// Size: 260 bytes

undefined4 SendHitEnemy__6JoyBusFics(JoyBus *joyBus,int portIndex,char enemyId,short hitValue)

{
  uint32_t uVar1;
  undefined4 uVar2;
  undefined local_18;
  undefined uStack_17;
  undefined4 local_14;
  
  uVar2 = 0;
  uStack_17 = (undefined)hitValue;
  local_18 = (undefined)((ushort)hitValue >> 8);
  local_14 = CONCAT22(CONCAT11(0x22,enemyId),CONCAT11(uStack_17,local_18));
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
    uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = local_14;
      uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
      joyBus->m_cmdCount[uVar1] = joyBus->m_cmdCount[uVar1] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
      uVar2 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

