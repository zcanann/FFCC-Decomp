// Function: BlockSem__6JoyBusFi
// Entry: 800b1d24
// Size: 48 bytes

void BlockSem__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  OSWaitSemaphore(joyBus->m_accessSemaphores + portIndex);
  return;
}

