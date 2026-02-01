// Function: GetPadData__6JoyBusFi
// Entry: 800ae020
// Size: 164 bytes

short GetPadData__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  char cVar1;
  short sVar2;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  sVar2 = joyBus->m_stageFlags[portIndex];
  joyBus->m_stageFlags[portIndex] = 0;
  if (joyBus->m_threadInitFlag != '\0') {
    sVar2 = 0;
  }
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  cVar1 = IsSingleMode__8GbaQueueFi(&GbaQue,portIndex);
  if (cVar1 != '\0') {
    sVar2 = 0;
  }
  return sVar2;
}

