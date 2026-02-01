// Function: SetLetterSize__6JoyBusFii
// Entry: 800a72a4
// Size: 16 bytes

void SetLetterSize__6JoyBusFii(JoyBus *joyBus,int portIndex,int letterSize)

{
  joyBus->m_letterSizeArr[portIndex] = letterSize;
  return;
}

