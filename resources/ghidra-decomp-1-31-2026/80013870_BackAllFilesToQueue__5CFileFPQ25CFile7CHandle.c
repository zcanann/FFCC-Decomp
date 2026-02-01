// Function: BackAllFilesToQueue__5CFileFPQ25CFile7CHandle
// Entry: 80013870
// Size: 240 bytes

void BackAllFilesToQueue__5CFileFPQ25CFile7CHandle(CFile *file,CFileCHandle *fileHandle)

{
  CFileCHandle *fileHandle_00;
  
  while (fileHandle_00 = CheckQueue__5CFileFv(file), fileHandle_00 != (CFileCHandle *)0x0) {
    SyncCompleted__5CFileFPQ25CFile7CHandle(file,fileHandle_00);
    if ((fileHandle == (CFileCHandle *)0x0) || (fileHandle_00 != fileHandle)) {
      if (fileHandle == (CFileCHandle *)0x0) {
        if (2 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,&DAT_801d5efc,fileHandle_00->mName);
        }
      }
      else if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801d5e28,fileHandle_00->mName,fileHandle->mName);
      }
      fileHandle_00->mCompletionStatus = 1;
    }
    else {
      fileHandle_00->mCompletionStatus = 0;
    }
  }
  return;
}

