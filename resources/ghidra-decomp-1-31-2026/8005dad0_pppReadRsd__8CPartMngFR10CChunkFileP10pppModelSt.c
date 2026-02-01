// Function: pppReadRsd__8CPartMngFR10CChunkFileP10pppModelSt
// Entry: 8005dad0
// Size: 296 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
pppReadRsd__8CPartMngFR10CChunkFileP10pppModelSt
          (CPartMng *partMng,CChunkFile *chunkFile,pppModelSt *pppModelSt)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined local_438 [1044];
  
  uVar4 = 0;
  while (iVar2 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)local_438), iVar2 != 0) {
    PushChunk__10CChunkFileFv(chunkFile);
    if (local_438._0_4_ == 0x52534420) {
      while (iVar2 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                               (chunkFile,(CChunkFile *)local_438), iVar2 != 0) {
        if (local_438._0_4_ == 0x54584e4d) {
          puVar5 = (undefined4 *)(local_438 + 0x10);
          for (uVar3 = 0; uVar3 < (uint)local_438._4_4_; uVar3 = uVar3 + 1) {
            uVar1 = GetString__10CChunkFileFv(chunkFile);
            *puVar5 = uVar1;
            puVar5 = puVar5 + 1;
          }
        }
        else if (((int)local_438._0_4_ < 0x54584e4d) && (local_438._0_4_ == 0x4d455348)) {
          uVar4 = ReadOtmMesh__8CMapMeshFR10CChunkFilePQ27CMemory6CStageii
                            (&pppModelSt->m_mapMesh,chunkFile,PartPcs.m_usbStreamData.m_stageLoad,0,
                             0);
          SetDisplayListMaterial__8CMapMeshFP12CMaterialSetPPcP13CAmemCacheSet
                    (&pppModelSt->m_mapMesh,partMng->m_materialSet,
                     (CAmemCacheSet *)(local_438 + 0x10));
        }
      }
    }
    PopChunk__10CChunkFileFv(chunkFile);
  }
  return uVar4;
}

