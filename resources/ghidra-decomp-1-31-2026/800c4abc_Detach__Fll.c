// Function: Detach__Fll
// Entry: 800c4abc
// Size: 24 bytes

void Detach__Fll(undefined4 param_1,int32_t result)

{
  MemoryCardMan.mResult = result;
  MemoryCardMan.m_opDoneFlag = '\x01';
  return;
}

