// Function: RequestData__6JoyBusFP11ThreadParamii
// Entry: 800a9cfc
// Size: 244 bytes

int RequestData__6JoyBusFP11ThreadParamii
              (JoyBus *joyBus,ThreadParam *threadParam,int param_3,int param_4)

{
  uint32_t uVar1;
  int iVar2;
  uint32_t local_18;
  
  iVar2 = 0;
  local_18 = CONCAT13(0xc,(uint3)(byte)param_3 << 0x10);
  local_18 = (uint)CONCAT21(local_18._0_2_,(char)param_4) << 8;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar1 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = local_18;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      iVar2 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
      iVar2 = -1;
    }
  }
  return iVar2;
}

