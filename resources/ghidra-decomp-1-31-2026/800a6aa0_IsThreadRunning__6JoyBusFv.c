// Function: IsThreadRunning__6JoyBusFv
// Entry: 800a6aa0
// Size: 24 bytes

uint IsThreadRunning__6JoyBusFv(JoyBus *joyBus)

{
  return (uint)(-(int)(char)joyBus->m_threadRunningMask | (int)(char)joyBus->m_threadRunningMask) >>
         0x1f;
}

