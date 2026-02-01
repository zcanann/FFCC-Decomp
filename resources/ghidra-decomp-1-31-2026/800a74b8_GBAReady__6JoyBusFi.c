// Function: GBAReady__6JoyBusFi
// Entry: 800a74b8
// Size: 148 bytes

uint GBAReady__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  uint uVar1;
  char cVar2;
  uint32_t uVar3;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  uVar3 = joyBus->m_threadParams[portIndex].m_padType;
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  uVar1 = countLeadingZeros(0x40000 - uVar3);
  uVar1 = uVar1 >> 5;
  cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,portIndex);
  if (cVar2 != '\0') {
    uVar1 = 0;
  }
  return uVar1;
}

