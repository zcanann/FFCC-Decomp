// Function: Init__5CFileFv
// Entry: 80013bb8
// Size: 408 bytes

void Init__5CFileFv(CFile *file)

{
  int iVar1;
  CStage *pCVar2;
  void *pvVar3;
  undefined4 uVar4;
  uint32_t uVar5;
  void **ppvVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  DVDInit();
  pCVar2 = CreateStage__7CMemoryFUlPci(&Memory,0x10ac00,s_CFile_8032f604,0);
  file->m_stage = pCVar2;
  file->fatal_diskErrorFlag = 0;
  file->isDiskError = 0;
  pvVar3 = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x100000,file->m_stage,s_file_cpp_801d5dc0,0x2b);
  file->m_readBuffer = pvVar3;
  uVar4 = __nwa__FUlPQ27CMemory6CStagePci(0x5610,file->m_stage,s_file_cpp_801d5dc0,0x2e);
  uVar5 = __construct_new_array(uVar4,0,0,0xac,0x80);
  (file->m_fileHandle2).mNextOffset = uVar5;
  (file->m_fileHandle).mNext = &file->m_fileHandle;
  iVar8 = 0;
  iVar7 = 0;
  (file->m_fileHandle).mPrevious = &file->m_fileHandle;
  (file->m_fileHandle).mPriority = 4;
  (file->m_fileHandle2).mNext = (CFileCHandle *)(file->m_fileHandle2).mNextOffset;
  iVar9 = 0x20;
  do {
    if (iVar8 == 0x7f) {
      ppvVar6 = &file->m_freeListSentinelDummy;
    }
    else {
      ppvVar6 = (void **)((file->m_fileHandle2).mNextOffset + (iVar8 + 1) * 0xac);
    }
    *(void ***)((file->m_fileHandle2).mNextOffset + iVar7 + 4) = ppvVar6;
    if (iVar8 == 0x7e) {
      ppvVar6 = &file->m_freeListSentinelDummy;
    }
    else {
      ppvVar6 = (void **)((file->m_fileHandle2).mNextOffset + (iVar8 + 2) * 0xac);
    }
    *(void ***)((file->m_fileHandle2).mNextOffset + iVar7 + 0xb0) = ppvVar6;
    if (iVar8 == 0x7d) {
      ppvVar6 = &file->m_freeListSentinelDummy;
    }
    else {
      ppvVar6 = (void **)((file->m_fileHandle2).mNextOffset + (iVar8 + 3) * 0xac);
    }
    *(void ***)((file->m_fileHandle2).mNextOffset + iVar7 + 0x15c) = ppvVar6;
    if (iVar8 == 0x7c) {
      ppvVar6 = &file->m_freeListSentinelDummy;
    }
    else {
      ppvVar6 = (void **)((file->m_fileHandle2).mNextOffset + (iVar8 + 4) * 0xac);
    }
    iVar1 = iVar7 + 0x208;
    iVar7 = iVar7 + 0x2b0;
    iVar8 = iVar8 + 4;
    *(void ***)((file->m_fileHandle2).mNextOffset + iVar1) = ppvVar6;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  return;
}

