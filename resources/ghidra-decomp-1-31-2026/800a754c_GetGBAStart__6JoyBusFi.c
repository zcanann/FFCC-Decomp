// Function: GetGBAStart__6JoyBusFi
// Entry: 800a754c
// Size: 28 bytes

uint GetGBAStart__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  return -(uint)joyBus->m_threadParams[portIndex].m_sentStartFlag >> 0x1f;
}

