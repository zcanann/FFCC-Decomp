// Function: GetGBAConnect__6JoyBusFi
// Entry: 800a7660
// Size: 152 bytes

undefined4 GetGBAConnect__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  undefined4 uVar1;
  uint uVar2;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  uVar2 = (uint)joyBus->m_threadParams[portIndex].m_state;
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  if ((uVar2 < 5) || (899 < uVar2)) {
    uVar1 = 0;
  }
  else if ((uVar2 < 0x14) || (0x16 < uVar2)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

