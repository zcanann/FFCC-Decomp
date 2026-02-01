// Function: GetPadType__6JoyBusFi
// Entry: 800a6ac4
// Size: 104 bytes

uint32_t GetPadType__6JoyBusFi(JoyBus *joyBus,int playerIndex)

{
  uint32_t uVar1;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + playerIndex);
  uVar1 = joyBus->m_threadParams[playerIndex].m_padType;
  OSSignalSemaphore(joyBus->m_accessSemaphores + playerIndex);
  return uVar1;
}

