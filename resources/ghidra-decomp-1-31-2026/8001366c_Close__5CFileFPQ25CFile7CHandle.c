// Function: Close__5CFileFPQ25CFile7CHandle
// Entry: 8001366c
// Size: 156 bytes

void Close__5CFileFPQ25CFile7CHandle(CFile *file,CFileCHandle *handle)

{
  if ((handle->mCompletionStatus == 2) && (1 < (uint)System.m_execParam)) {
    Printf__7CSystemFPce(&System,&DAT_801d5e04,handle->mName);
  }
  DVDClose(&handle->mDvdFileInfo);
  handle->mClosedFlag = 1;
  handle->mNext->mPrevious = handle->mPrevious;
  handle->mPrevious->mNext = handle->mNext;
  handle->mPrevious = (file->m_fileHandle2).mNext;
  (file->m_fileHandle2).mNext = handle;
  return;
}

