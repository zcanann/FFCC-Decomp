// Function: GetGBAStat__6JoyBusFP11ThreadParam
// Entry: 800a79d0
// Size: 108 bytes

uint32_t GetGBAStat__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  char cVar2;
  uint32_t uVar1;
  
  cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
  if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
    uVar1 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
    threadParam->m_gbaStatus = uVar1;
  }
  else {
    threadParam->m_gbaStatus = 0;
  }
  return threadParam->m_gbaStatus;
}

