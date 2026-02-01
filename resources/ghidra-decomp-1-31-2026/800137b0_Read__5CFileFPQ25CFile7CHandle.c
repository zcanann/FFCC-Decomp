// Function: Read__5CFileFPQ25CFile7CHandle
// Entry: 800137b0
// Size: 192 bytes

void Read__5CFileFPQ25CFile7CHandle(CFile *file,CFileCHandle *fileHandle)

{
  uint uVar1;
  
  BackAllFilesToQueue__5CFileFPQ25CFile7CHandle();
  fileHandle->mCompletionStatus = 2;
  uVar1 = fileHandle->mFileSize + 0x1f & 0xffffffe0;
  if ((0x100000 < uVar1) && (System.m_execParam != 0)) {
    Printf__7CSystemFPce(&System,&DAT_801d5dcc,fileHandle->mName,uVar1);
  }
  DVDReadAsyncPrio(&fileHandle->mDvdFileInfo,file->m_readBuffer,uVar1,fileHandle->mCurrentOffset,0,2
                  );
  fileHandle->mNextOffset = fileHandle->mCurrentOffset + uVar1;
  SyncCompleted__5CFileFPQ25CFile7CHandle(file,fileHandle);
  return;
}

