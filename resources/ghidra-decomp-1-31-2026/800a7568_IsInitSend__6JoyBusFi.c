// Function: IsInitSend__6JoyBusFi
// Entry: 800a7568
// Size: 248 bytes

uint IsInitSend__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  byte bVar1;
  uint uVar2;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  uVar2 = (uint)joyBus->m_threadParams[portIndex].m_state;
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  if ((joyBus->m_threadParams[portIndex].m_sentStartFlag == '\0') && (uVar2 < 0x385)) {
    if (uVar2 < 2) {
      uVar2 = 0;
    }
    else if (uVar2 == 2) {
      uVar2 = -(uint)joyBus->m_threadParams[portIndex].m_flags[0] >> 0x1f;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  if (joyBus->m_threadParams[portIndex].m_flags[2] == uVar2) {
    joyBus->m_threadParams[portIndex].m_flags[3] = '\0';
  }
  else {
    bVar1 = joyBus->m_threadParams[portIndex].m_flags[3];
    if (bVar1 < 8) {
      joyBus->m_threadParams[portIndex].m_flags[3] = bVar1 + 1;
      uVar2 = (uint)joyBus->m_threadParams[portIndex].m_flags[2];
    }
    else {
      joyBus->m_threadParams[portIndex].m_flags[2] = (uint8_t)uVar2;
      joyBus->m_threadParams[portIndex].m_flags[3] = '\0';
    }
  }
  return uVar2;
}

