// Function: SyncCompleted__5CFileFPQ25CFile7CHandle
// Entry: 8001360c
// Size: 76 bytes

void SyncCompleted__5CFileFPQ25CFile7CHandle(CFile *file,CFileCHandle *fileHandle)

{
  while (fileHandle->mCompletionStatus != 3) {
    kick__5CFileFv(file);
  }
  return;
}

