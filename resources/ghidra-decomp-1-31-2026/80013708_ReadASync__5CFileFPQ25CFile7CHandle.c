// Function: ReadASync__5CFileFPQ25CFile7CHandle
// Entry: 80013708
// Size: 40 bytes

void ReadASync__5CFileFPQ25CFile7CHandle(CFile *file,CFileCHandle *fileHandle)

{
  fileHandle->mCompletionStatus = 1;
  kick__5CFileFv(file);
  return;
}

