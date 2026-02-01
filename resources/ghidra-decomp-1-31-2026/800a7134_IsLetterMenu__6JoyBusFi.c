// Function: IsLetterMenu__6JoyBusFi
// Entry: 800a7134
// Size: 108 bytes

uint IsLetterMenu__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  byte bVar1;
  uint uVar2;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  bVar1 = joyBus->m_stateCodeArr[portIndex];
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  uVar2 = countLeadingZeros(9 - (uint)bVar1);
  return uVar2 >> 5;
}

