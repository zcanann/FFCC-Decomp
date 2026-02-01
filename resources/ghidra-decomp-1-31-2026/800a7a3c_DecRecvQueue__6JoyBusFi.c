// Function: DecRecvQueue__6JoyBusFi
// Entry: 800a7a3c
// Size: 136 bytes

void DecRecvQueue__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  joyBus->m_recvQueueEntriesArr[portIndex][joyBus->m_secCmdCount[portIndex]] = 0;
  joyBus->m_secCmdCount[portIndex] = joyBus->m_secCmdCount[portIndex] - 1;
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  return;
}

