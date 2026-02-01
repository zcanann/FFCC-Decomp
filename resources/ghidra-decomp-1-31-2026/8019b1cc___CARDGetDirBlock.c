// Function: __CARDGetDirBlock
// Entry: 8019b1cc
// Size: 8 bytes

CARDDir * __CARDGetDirBlock(CARDControl *cardControl)

{
  return cardControl->currentDir;
}

