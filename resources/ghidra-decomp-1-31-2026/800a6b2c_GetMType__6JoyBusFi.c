// Function: GetMType__6JoyBusFi
// Entry: 800a6b2c
// Size: 100 bytes

uint8_t GetMType__6JoyBusFi(JoyBus *joyBus,int port)

{
  uint8_t uVar1;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + port);
  uVar1 = joyBus->m_nextModeTypeArr[port];
  OSSignalSemaphore(joyBus->m_accessSemaphores + port);
  return uVar1;
}

