// Function: GetRecvBuffer__6JoyBusFiPUc
// Entry: 800a9c0c
// Size: 128 bytes

void GetRecvBuffer__6JoyBusFiPUc(JoyBus *joyBus,int playerIndex,uchar *outBuffer)

{
  OSWaitSemaphore(joyBus->m_accessSemaphores + playerIndex);
  memcpy(outBuffer,joyBus->m_recvBuffer[playerIndex].m_payload,
         joyBus->m_recvBuffer[playerIndex].m_length);
  OSSignalSemaphore(joyBus->m_accessSemaphores + playerIndex);
  return;
}

