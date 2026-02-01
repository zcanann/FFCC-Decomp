// Function: CheckQueue__5CFileFv
// Entry: 80013258
// Size: 668 bytes

CFileCHandle * CheckQueue__5CFileFv(CFile *file)

{
  int iVar1;
  CFileCHandle *pCVar2;
  
  pCVar2 = (file->m_fileHandle).mPrevious;
  do {
    if (pCVar2->mCompletionStatus == 2) {
      iVar1 = DVDGetCommandBlockStatus(&pCVar2->mDvdFileInfo);
      if (((iVar1 != 0xb) && (2 < iVar1 - 4U)) && (iVar1 != -1)) {
        if (iVar1 != 0) {
          if (-1 < iVar1) {
            return pCVar2;
          }
          pCVar2->mCompletionStatus = 4;
          goto LAB_800134d0;
        }
        pCVar2->mCompletionStatus = 3;
        pCVar2 = (file->m_fileHandle).mPrevious;
        break;
      }
      DrawError__5CFileFR11DVDFileInfoi(file,&pCVar2->mDvdFileInfo,iVar1);
    }
    else {
      if (pCVar2->mCompletionStatus == 3) {
        return pCVar2;
      }
LAB_800134d0:
      pCVar2 = pCVar2->mPrevious;
    }
    if (pCVar2 == &file->m_fileHandle) {
      return (CFileCHandle *)0x0;
    }
  } while( true );
LAB_800132d8:
  if (pCVar2->mCompletionStatus == 2) {
    iVar1 = DVDGetCommandBlockStatus(&pCVar2->mDvdFileInfo);
    if (((iVar1 != 0xb) && (2 < iVar1 - 4U)) && (iVar1 != -1)) {
      if (iVar1 != 0) {
        if (-1 < iVar1) {
          return pCVar2;
        }
        pCVar2->mCompletionStatus = 4;
        goto LAB_80013494;
      }
      pCVar2->mCompletionStatus = 3;
      pCVar2 = (file->m_fileHandle).mPrevious;
      goto LAB_80013338;
    }
    DrawError__5CFileFR11DVDFileInfoi(file,&pCVar2->mDvdFileInfo,iVar1);
  }
  else {
    if (pCVar2->mCompletionStatus == 3) {
      return pCVar2;
    }
LAB_80013494:
    pCVar2 = pCVar2->mPrevious;
  }
  if (pCVar2 == &file->m_fileHandle) {
    return (CFileCHandle *)0x0;
  }
  goto LAB_800132d8;
LAB_80013338:
  if (pCVar2->mCompletionStatus == 2) {
    iVar1 = DVDGetCommandBlockStatus(&pCVar2->mDvdFileInfo);
    if (((iVar1 != 0xb) && (2 < iVar1 - 4U)) && (iVar1 != -1)) {
      if (iVar1 != 0) {
        if (-1 < iVar1) {
          return pCVar2;
        }
        pCVar2->mCompletionStatus = 4;
        goto LAB_8001345c;
      }
      pCVar2->mCompletionStatus = 3;
      pCVar2 = (file->m_fileHandle).mPrevious;
      goto LAB_80013398;
    }
    DrawError__5CFileFR11DVDFileInfoi(file,&pCVar2->mDvdFileInfo,iVar1);
  }
  else {
    if (pCVar2->mCompletionStatus == 3) {
      return pCVar2;
    }
LAB_8001345c:
    pCVar2 = pCVar2->mPrevious;
  }
  if (pCVar2 == &file->m_fileHandle) {
    return (CFileCHandle *)0x0;
  }
  goto LAB_80013338;
LAB_80013398:
  if (pCVar2->mCompletionStatus == 2) {
    iVar1 = DVDGetCommandBlockStatus(&pCVar2->mDvdFileInfo);
    if (((iVar1 != 0xb) && (2 < iVar1 - 4U)) && (iVar1 != -1)) {
      if (iVar1 == 0) {
        pCVar2->mCompletionStatus = 3;
        pCVar2 = CheckQueue__5CFileFv(file);
        return pCVar2;
      }
      if (-1 < iVar1) {
        return pCVar2;
      }
      pCVar2->mCompletionStatus = 4;
      goto LAB_80013424;
    }
    DrawError__5CFileFR11DVDFileInfoi(file,&pCVar2->mDvdFileInfo,iVar1);
  }
  else {
    if (pCVar2->mCompletionStatus == 3) {
      return pCVar2;
    }
LAB_80013424:
    pCVar2 = pCVar2->mPrevious;
  }
  if (pCVar2 == &file->m_fileHandle) {
    return (CFileCHandle *)0x0;
  }
  goto LAB_80013398;
}

