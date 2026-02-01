// Function: ClrRecvBuffer__6JoyBusFi
// Entry: 800a9c8c
// Size: 112 bytes

void ClrRecvBuffer__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  memset(joyBus->m_recvBuffer + portIndex,0,0x408);
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  return;
}

