// Function: IsCompleted__5CFileFPQ25CFile7CHandle
// Entry: 80013658
// Size: 20 bytes

uint IsCompleted__5CFileFPQ25CFile7CHandle(CFile *param_1,CFileCHandle *fileHandle)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(3 - fileHandle->mCompletionStatus);
  return uVar1 >> 5 & 0xff;
}

