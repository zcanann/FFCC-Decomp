// Function: Attach__Fll
// Entry: 800c4a8c
// Size: 48 bytes

void Attach__Fll(uint8_t currentSlot,int result)

{
  MemoryCardMan.mResult = result;
  MemoryCardMan.m_opDoneFlag = '\x01';
  if (MemoryCardMan.mState != '\x01') {
    return;
  }
  if (result != 0) {
    return;
  }
  MemoryCardMan.m_currentSlot = currentSlot;
  return;
}

