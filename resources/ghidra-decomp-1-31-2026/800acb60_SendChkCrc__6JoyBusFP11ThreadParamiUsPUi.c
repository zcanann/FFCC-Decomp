// Function: SendChkCrc__6JoyBusFP11ThreadParamiUsPUi
// Entry: 800acb60
// Size: 260 bytes

undefined4
SendChkCrc__6JoyBusFP11ThreadParamiUsPUi
          (JoyBus *joyBus,ThreadParam *threadParam,undefined param_3,undefined2 crc,uint32_t *outCmd
          )

{
  uint32_t uVar1;
  undefined4 uVar2;
  undefined local_18;
  undefined uStack_17;
  undefined4 local_14;
  
  uVar2 = 0;
  uStack_17 = (undefined)crc;
  local_18 = (undefined)((ushort)crc >> 8);
  local_14 = CONCAT22(CONCAT11(0xd,param_3),CONCAT11(uStack_17,local_18));
  *outCmd = local_14;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar1 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = local_14;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar2 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

