// Function: SetMType__6JoyBusFii
// Entry: 800a6b90
// Size: 188 bytes

undefined4 SetMType__6JoyBusFii(JoyBus *joyBus,int portIndex,undefined4 param_3)

{
  undefined4 uVar1;
  uint uVar2;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  uVar2 = (uint)joyBus->m_threadParams[portIndex].m_state;
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  if (uVar2 < 5) {
    uVar1 = 0xffffffff;
  }
  else if ((uVar2 < 0x14) || (0x16 < uVar2)) {
    if (uVar2 < 900) {
      uVar1 = SendMType__6JoyBusFP11ThreadParami(joyBus,joyBus->m_threadParams + portIndex,param_3);
    }
    else {
      uVar1 = 0xffffffff;
    }
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

