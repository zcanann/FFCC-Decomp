// Function: Open__5CFileFPcUlQ25CFile3PRI
// Entry: 80013968
// Size: 416 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CFileCHandle *
Open__5CFileFPcUlQ25CFile3PRI(CFile *file,undefined4 param_2,uint32_t param_3,int priority)

{
  uint32_t uVar1;
  CFileCHandle *pCVar2;
  int iVar3;
  CFileCHandle *pCVar4;
  CFileCHandle *pCVar5;
  DVDCommandBlock *local_68;
  DVDCommandBlock *local_64;
  uint32_t local_60;
  int32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  void *local_50;
  uint32_t local_4c;
  uint32_t local_48;
  DVDDiskId *local_44;
  void *local_40;
  CFileCHandle *local_3c;
  uint32_t local_38;
  uint32_t local_34;
  void *local_30;
  
  if (Game.game.m_gameWork.m_gamePaused != '\0') {
    priority = 3;
  }
  pCVar5 = (CFileCHandle *)0x0;
  pCVar2 = (file->m_fileHandle).mPrevious;
  for (pCVar4 = pCVar2; (pCVar4 != pCVar2 && (pCVar4->mPriority <= priority));
      pCVar4 = pCVar4->mPrevious) {
  }
  pCVar4 = pCVar4->mNext;
  iVar3 = DVDConvertPathToEntrynum(param_2);
  if (iVar3 != -1) {
    DVDFastOpen(iVar3,&local_68);
    uVar1 = local_34;
    pCVar5 = (file->m_fileHandle2).mNext;
    (file->m_fileHandle2).mNext = pCVar5->mPrevious;
    pCVar5->mPrevious = pCVar4;
    pCVar5->mNext = pCVar4->mNext;
    pCVar4->mNext->mPrevious = pCVar5;
    pCVar4->mNext = pCVar5;
    pCVar5->mPriority = priority;
    pCVar5->mUserParam = param_3;
    pCVar5->mLength = local_34;
    pCVar5->mCompletionStatus = 0;
    pCVar5->mClosedFlag = 0;
    pCVar5->mFlags = 0;
    strcpy(pCVar5->mName,param_2);
    pCVar5->mFileSize = uVar1;
    pCVar5->mCurrentOffset = 0;
    pCVar5->mNextOffset = 0;
    (pCVar5->mDvdFileInfo).commandBlock.next = local_68;
    (pCVar5->mDvdFileInfo).commandBlock.prev = local_64;
    (pCVar5->mDvdFileInfo).commandBlock.command = local_60;
    (pCVar5->mDvdFileInfo).commandBlock.state = local_5c;
    (pCVar5->mDvdFileInfo).commandBlock.offset = local_58;
    (pCVar5->mDvdFileInfo).commandBlock.length = local_54;
    (pCVar5->mDvdFileInfo).commandBlock.addr = local_50;
    (pCVar5->mDvdFileInfo).commandBlock.currTransferSize = local_4c;
    (pCVar5->mDvdFileInfo).commandBlock.transferredSize = local_48;
    (pCVar5->mDvdFileInfo).commandBlock.id = local_44;
    (pCVar5->mDvdFileInfo).commandBlock.callback = local_40;
    (pCVar5->mDvdFileInfo).commandBlock.userData = pCVar5;
    (pCVar5->mDvdFileInfo).startAddress = local_38;
    (pCVar5->mDvdFileInfo).length = local_34;
    (pCVar5->mDvdFileInfo).callback = local_30;
    local_3c = pCVar5;
  }
  if ((pCVar5 == (CFileCHandle *)0x0) && (System.m_execParam != 0)) {
    Printf__7CSystemFPce(&System,&DAT_801d5f9c,param_2);
  }
  return pCVar5;
}

