// Function: LockBuffer__5CFileFv
// Entry: 80013750
// Size: 96 bytes

void LockBuffer__5CFileFv(CFile *file)

{
  CFileCHandle *fileHandle;
  
  while( true ) {
    fileHandle = CheckQueue__5CFileFv(file);
    if (fileHandle == (CFileCHandle *)0x0) break;
    SyncCompleted__5CFileFPQ25CFile7CHandle(file,fileHandle);
    fileHandle->mCompletionStatus = 1;
  }
  return;
}

