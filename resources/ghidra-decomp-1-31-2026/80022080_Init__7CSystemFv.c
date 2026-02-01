// Function: Init__7CSystemFv
// Entry: 80022080
// Size: 856 bytes

void Init__7CSystemFv(CSystem *system)

{
  COrder *pCVar1;
  OSThread *pOVar2;
  CStage *pCVar3;
  CFileCHandle *fileHandle;
  uint32_t uVar4;
  void *pvVar5;
  int64_t *piVar6;
  CSystem *pCVar7;
  int iVar8;
  uint32_t uVar9;
  uint32_t count;
  int iVar10;
  
  system->m_initialized = 1;
  system->m_currentOrder = (COrder *)0x0;
  system->m_currentOrderIndex = 0;
  OSInit();
  system->m_execParam = 3;
  Init__7CMemoryFv(&Memory);
  Init__6CSoundFv(&Sound);
  Init__5CMathFv(&Math);
  Init__5CFileFv(&File);
  Init__4CPadFv(&Pad);
  Init__8CGraphicFv(&Graphic);
  Init__11CTextureManFv(&TextureMan);
  Init__12CMaterialManFv(&MaterialMan);
  Init__8CFontManFv(&FontMan);
  Init__14CMemoryCardManFv(&MemoryCardMan);
  piVar6 = &(system->m_stopwatch).total;
  system->m_orderCount = 0;
  *(int64_t **)&(system->m_stopwatch).max = piVar6;
  iVar8 = 0;
  *(int64_t **)((int)&(system->m_stopwatch).max + 4) = piVar6;
  *(undefined4 *)&(system->m_stopwatch).total = 0xff;
  (system->m_freeOrderHead).mNext = system->m_orderPool;
  iVar10 = 0x20;
  pCVar7 = system;
  do {
    if (iVar8 == 0x7f) {
      pCVar1 = &system->m_freeOrderHead;
    }
    else {
      pCVar1 = system->m_orderPool + iVar8 + 1;
    }
    pCVar7->m_orderPool[0].mNext = pCVar1;
    if (iVar8 == 0x7e) {
      pCVar1 = &system->m_freeOrderHead;
    }
    else {
      pCVar1 = system->m_orderPool + iVar8 + 2;
    }
    pCVar7->m_orderPool[1].mNext = pCVar1;
    if (iVar8 == 0x7d) {
      pCVar1 = &system->m_freeOrderHead;
    }
    else {
      pCVar1 = system->m_orderPool + iVar8 + 3;
    }
    pCVar7->m_orderPool[2].mNext = pCVar1;
    if (iVar8 == 0x7c) {
      pCVar1 = &system->m_freeOrderHead;
    }
    else {
      pCVar1 = system->m_orderPool + iVar8 + 4;
    }
    pCVar7->m_orderPool[3].mNext = pCVar1;
    pCVar7 = (CSystem *)&pCVar7->m_orderPool[1].mDescBlock;
    iVar8 = iVar8 + 4;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  pOVar2 = (OSThread *)OSGetCurrentThread();
  system->m_ownerThread = pOVar2;
  system->m_scenegraphStepMode = 0;
  system->m_frameCounter = 0;
  system->m_mapStage = (CStage *)0x0;
  system->m_mapBuffer = (void *)0x0;
  system->m_mapSize = 0;
  OSSetErrorHandler(0,errorHandler__7CSystemFUsP9OSContextUlUl);
  OSSetErrorHandler(1,errorHandler__7CSystemFUsP9OSContextUlUl);
  OSSetErrorHandler(2,errorHandler__7CSystemFUsP9OSContextUlUl);
  OSSetErrorHandler(3,errorHandler__7CSystemFUsP9OSContextUlUl);
  OSSetErrorHandler(5,errorHandler__7CSystemFUsP9OSContextUlUl);
  OSSetErrorHandler(0xb,errorHandler__7CSystemFUsP9OSContextUlUl);
  OSSetErrorHandler(0xd,errorHandler__7CSystemFUsP9OSContextUlUl);
  OSSetErrorHandler(0xe,errorHandler__7CSystemFUsP9OSContextUlUl);
  OSSetErrorHandler(0xf,errorHandler__7CSystemFUsP9OSContextUlUl);
  iVar8 = OSGetConsoleSimulatedMemSize();
  if (iVar8 == 0x3000000) {
    pCVar3 = CreateStage__7CMemoryFUlPci(&Memory,0x400000,s_CSystem_8032f868,1);
    system->m_mapStage = pCVar3;
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,s_gamePalM_map_801d6f2c,0,0);
    if (fileHandle != (CFileCHandle *)0x0) {
      uVar4 = GetLength__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      system->m_mapSize = uVar4;
      pvVar5 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                 (uVar4,system->m_mapStage,s_system_cpp_801d6f20,0x123);
      system->m_mapBuffer = pvVar5;
      uVar9 = 0;
      for (; uVar4 != 0; uVar4 = uVar4 - count) {
        count = 0x100000;
        if (uVar4 < 0x100000) {
          count = uVar4;
        }
        fileHandle->mFileSize = count;
        fileHandle->mCurrentOffset = uVar9;
        Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
        memcpy((void *)((int)system->m_mapBuffer + uVar9),File.m_readBuffer,count);
        uVar9 = uVar9 + count;
      }
      Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      Printf__7CSystemFPce(system,&DAT_801d6f3c);
    }
  }
  return;
}

