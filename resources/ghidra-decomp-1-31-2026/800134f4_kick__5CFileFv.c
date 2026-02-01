// Function: kick__5CFileFv
// Entry: 800134f4
// Size: 280 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void kick__5CFileFv(CFile *file)

{
  uint uVar1;
  CFileCHandle *pCVar2;
  
  pCVar2 = CheckQueue__5CFileFv(file);
  if (pCVar2 == (CFileCHandle *)0x0) {
    pCVar2 = (file->m_fileHandle).mPrevious;
    do {
      if (((Game.game.m_gameWork.m_gamePaused == '\0') || (pCVar2->mPriority == 3)) &&
         ((pCVar2->mCompletionStatus == 1 || (pCVar2->mCompletionStatus == 4)))) {
        pCVar2->mCompletionStatus = 2;
        uVar1 = pCVar2->mFileSize + 0x1f & 0xffffffe0;
        if ((0x100000 < uVar1) && (System.m_execParam != 0)) {
          Printf__7CSystemFPce(&System,&DAT_801d5dcc,pCVar2->mName,uVar1);
        }
        DVDReadAsyncPrio(&pCVar2->mDvdFileInfo,file->m_readBuffer,uVar1,pCVar2->mCurrentOffset,0,2);
        pCVar2->mNextOffset = pCVar2->mCurrentOffset + uVar1;
        if (pCVar2->mCompletionStatus != 3) {
          return;
        }
        kick__5CFileFv(file);
        return;
      }
      pCVar2 = pCVar2->mPrevious;
    } while (pCVar2 != &file->m_fileHandle);
  }
  return;
}

