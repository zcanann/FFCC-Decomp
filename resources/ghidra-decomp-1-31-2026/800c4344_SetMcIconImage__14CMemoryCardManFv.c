// Function: SetMcIconImage__14CMemoryCardManFv
// Entry: 800c4344
// Size: 776 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetMcIconImage__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  bool bVar1;
  uint8_t *puVar2;
  char *pcVar3;
  CFileCHandle *fileHandle;
  int count;
  undefined4 count_00;
  undefined auStack_98 [136];
  
  bVar1 = memoryCardMan->m_saveBuffer == (uint8_t *)0x0;
  if (bVar1) {
    if (bVar1) {
      puVar2 = (uint8_t *)
               __nwa__FUlPQ27CMemory6CStagePci
                         (0xa000,memoryCardMan->mStage,s_memorycard_cpp_801daea8,0x2ab);
      memoryCardMan->m_saveBuffer = puVar2;
      if (memoryCardMan->m_saveBuffer == (uint8_t *)0x0) {
        if (System.m_execParam != 0) {
          Printf__7CSystemFPce
                    (&System,s__s__d___Error__memory_allocation_801daeb8,s_memorycard_cpp_801daea8,
                     0x2ad);
        }
      }
    }
    memset(memoryCardMan->m_saveBuffer,0,0xa000);
  }
  pcVar3 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_98,s_dvd__smenu__s_801daff4,pcVar3,PTR_s_icon_dat_8032e850);
  fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_98,0,0);
  if ((fileHandle == (CFileCHandle *)0x0) && (System.m_execParam != 0)) {
    Printf__7CSystemFPce
              (&System,s__s__d___Error___s_open_error_801db004,s_memorycard_cpp_801daea8,0x2ef,
               auStack_98);
  }
  Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  count = GetLength__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  if ((count != 0x2a00) && (System.m_execParam != 0)) {
    Printf__7CSystemFPce
              (&System,s__s__d___Error____s__data_error_801db024,s_memorycard_cpp_801daea8,0x2f6,
               auStack_98);
  }
  puVar2 = memoryCardMan->m_saveBuffer;
  memcpy(puVar2 + 0x40,File.m_readBuffer,count);
  Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  (memoryCardMan->mcardStat).commentAddr = 0;
  (memoryCardMan->mcardStat).iconAddr = 0x40;
  (memoryCardMan->mcardStat).bannerFormat = (memoryCardMan->mcardStat).bannerFormat & 0xfc | 2;
  (memoryCardMan->mcardStat).iconFormat = (memoryCardMan->mcardStat).iconFormat & 0xfffc | 1;
  (memoryCardMan->mcardStat).iconSpeed = (memoryCardMan->mcardStat).iconSpeed & 0xfffc | 2;
  (memoryCardMan->mcardStat).iconFormat = (memoryCardMan->mcardStat).iconFormat & 0xfff3 | 4;
  (memoryCardMan->mcardStat).iconSpeed = (memoryCardMan->mcardStat).iconSpeed & 0xfff3 | 8;
  (memoryCardMan->mcardStat).iconFormat = (memoryCardMan->mcardStat).iconFormat & 0xffcf | 0x10;
  (memoryCardMan->mcardStat).iconSpeed = (memoryCardMan->mcardStat).iconSpeed & 0xffcf | 0x20;
  (memoryCardMan->mcardStat).iconFormat = (memoryCardMan->mcardStat).iconFormat & 0xff3f | 0x40;
  (memoryCardMan->mcardStat).iconSpeed = (memoryCardMan->mcardStat).iconSpeed & 0xff3f | 0x80;
  (memoryCardMan->mcardStat).iconFormat = (memoryCardMan->mcardStat).iconFormat & 0xfcff;
  (memoryCardMan->mcardStat).iconSpeed = (memoryCardMan->mcardStat).iconSpeed & 0xfcff;
  (memoryCardMan->mcardStat).offsetIcon[4] = 0xffffffff;
  (memoryCardMan->mcardStat).iconFormat = (memoryCardMan->mcardStat).iconFormat & 0xf3ff;
  (memoryCardMan->mcardStat).iconSpeed = (memoryCardMan->mcardStat).iconSpeed & 0xf3ff;
  (memoryCardMan->mcardStat).offsetIcon[5] = 0xffffffff;
  (memoryCardMan->mcardStat).iconFormat = (memoryCardMan->mcardStat).iconFormat & 0xcfff;
  (memoryCardMan->mcardStat).iconSpeed = (memoryCardMan->mcardStat).iconSpeed & 0xcfff;
  (memoryCardMan->mcardStat).offsetIcon[6] = 0xffffffff;
  (memoryCardMan->mcardStat).iconFormat = (memoryCardMan->mcardStat).iconFormat & 0x3fff;
  (memoryCardMan->mcardStat).iconSpeed = (memoryCardMan->mcardStat).iconSpeed & 0x3fff;
  (memoryCardMan->mcardStat).offsetIcon[7] = 0xffffffff;
  (memoryCardMan->mcardStat).bannerFormat = (memoryCardMan->mcardStat).bannerFormat & 0xfb;
  (memoryCardMan->mcardStat).offsetIconTlut = 0x2840;
  (memoryCardMan->mcardStat).offsetIconTlut = 0x2a40;
  count_00 = strlen(PTR_s_FF_Crystal_Chronicles_8032e858);
  memcpy(puVar2,PTR_s_FF_Crystal_Chronicles_8032e858,count_00);
  return;
}

