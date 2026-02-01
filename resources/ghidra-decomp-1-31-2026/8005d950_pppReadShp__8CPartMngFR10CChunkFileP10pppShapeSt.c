// Function: pppReadShp__8CPartMngFR10CChunkFileP10pppShapeSt
// Entry: 8005d950
// Size: 384 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppReadShp__8CPartMngFR10CChunkFileP10pppShapeSt
               (CPartMng *partMng,CChunkFile *chunkFile,pppShapeSt *pppShapeSt)

{
  uint8_t *puVar1;
  void *pvVar2;
  int iVar3;
  uint8_t **ppuVar4;
  uint8_t **ppuVar5;
  CChunkFile local_438 [21];
  
  ppuVar4 = &local_438[0].m_headerPtr;
  while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk(chunkFile,local_438), iVar3 != 0)
  {
    PushChunk__10CChunkFileFv(chunkFile);
    ppuVar5 = ppuVar4;
    if (local_438[0].m_scopeSize == 0x46534850) {
      while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk(chunkFile,local_438),
            iVar3 != 0) {
        if (local_438[0].m_scopeSize == 0x444c5354) {
          pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                     (local_438[0].m_base,PartPcs.m_usbStreamData.m_stageLoad,
                                      s_partMng_cpp_801d8230,0x4b3);
          pppShapeSt->m_displayListData = pvVar2;
          Get__10CChunkFileFPvl(chunkFile,pppShapeSt->m_displayListData,local_438[0].m_base);
          DCFlushRange(pppShapeSt->m_displayListData,(uint)(local_438[0].m_base + 0x1f) & 0xffffffe0
                      );
        }
        else if ((int)local_438[0].m_scopeSize < 0x444c5354) {
          if (local_438[0].m_scopeSize == 0x414e494d) {
            pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                       (local_438[0].m_base,PartPcs.m_usbStreamData.m_stageLoad,
                                        s_partMng_cpp_801d8230,0x4b9);
            pppShapeSt->m_animData = pvVar2;
            Get__10CChunkFileFPvl(chunkFile,pppShapeSt->m_animData,local_438[0].m_base);
            pppSetShapeMaterial__FP10pppShapeStP12CMaterialSetPPc
                      (pppShapeSt,partMng->m_materialSet,(char **)&local_438[0].m_headerPtr);
          }
        }
        else if (local_438[0].m_scopeSize == 0x54584e4d) {
          PushChunk__10CChunkFileFv(chunkFile);
          puVar1 = (uint8_t *)GetString__10CChunkFileFv(chunkFile);
          *ppuVar5 = puVar1;
          PopChunk__10CChunkFileFv(chunkFile);
          ppuVar4 = ppuVar4 + 1;
          ppuVar5 = ppuVar5 + 1;
        }
      }
    }
    PopChunk__10CChunkFileFv(chunkFile);
  }
  return;
}

