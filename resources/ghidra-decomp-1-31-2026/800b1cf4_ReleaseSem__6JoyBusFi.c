// Function: ReleaseSem__6JoyBusFi
// Entry: 800b1cf4
// Size: 48 bytes

void ReleaseSem__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  OSSignalSemaphore(joyBus->m_accessSemaphores + portIndex);
  return;
}

