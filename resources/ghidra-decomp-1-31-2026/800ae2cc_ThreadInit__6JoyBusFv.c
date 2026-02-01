// Function: ThreadInit__6JoyBusFv
// Entry: 800ae2cc
// Size: 228 bytes

void ThreadInit__6JoyBusFv(JoyBus *joyBus)

{
  int iVar1;
  uint32_t uVar2;
  JoyBus *pJVar3;
  JoyBus *pJVar4;
  
  memset(joyBus->m_threadParams,0,0xf0);
  joyBus->m_threadInitFlag = '\0';
  joyBus->m_threadRunningMask = '\0';
  uVar2 = 0;
  pJVar3 = joyBus;
  pJVar4 = joyBus;
  do {
    pJVar4->m_threadParams[0].m_portIndex = uVar2;
    pJVar4->m_threadParams[0].m_gbaStatus = 1;
    OSCreateThread(pJVar3->m_threads,_ThreadMain__6JoyBusFPv,pJVar4->m_threadParams,
                   joyBus->m_sendBuffer + uVar2 + 1,0x1000,8,1);
    OSResumeThread(pJVar3->m_threads);
    iVar1 = 1 << uVar2;
    uVar2 = uVar2 + 1;
    pJVar3 = (JoyBus *)(pJVar3->m_recvBuffer[0].m_payload + 0x290);
    joyBus->m_threadRunningMask = joyBus->m_threadRunningMask | (byte)iVar1;
    pJVar4 = (JoyBus *)(pJVar4->m_pathBuf + 0x3c);
  } while ((int)uVar2 < 4);
  if (1 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_JoyBus__ThreadInit_end_801da2d8);
  }
  return;
}

