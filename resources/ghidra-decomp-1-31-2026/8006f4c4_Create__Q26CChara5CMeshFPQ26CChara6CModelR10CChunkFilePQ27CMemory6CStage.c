// Function: Create__Q26CChara5CMeshFPQ26CChara6CModelR10CChunkFilePQ27CMemory6CStage
// Entry: 8006f4c4
// Size: 1676 bytes

void Create__Q26CChara5CMeshFPQ26CChara6CModelR10CChunkFilePQ27CMemory6CStage
               (CModel *model,int param_2,CChunkFile *chunkFile,CStage *stage)

{
  char cVar7;
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  undefined2 uVar6;
  uint uVar4;
  int iVar5;
  uint *puVar8;
  uint32_t local_28;
  uint local_24;
  uint8_t *local_1c;
  
  (model->m_localMtx).value[0][0] =
       (float)(*(int *)(*(int *)(param_2 + 0xa4) + 0x14) +
              *(int *)(*(int *)(param_2 + 0xa4) + 0xc) * 100);
  PushChunk__10CChunkFileFv(chunkFile);
  while (iVar5 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)&local_28), iVar5 != 0) {
    if (local_28 == 0x4e4f524d) {
      *(uint *)((int)(model->m_localMtx).value[0][0] + 0x1c) = (uint)local_1c / 6;
      uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                        (&Memory,local_1c,stage,s_chara_cpp_801d90c8,0x7de,0);
      *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x20) = uVar1;
      uVar1 = GetAddress__10CChunkFileFv(chunkFile);
      memcpy(*(void **)((int)(model->m_localMtx).value[0][0] + 0x20),uVar1,local_1c);
      fVar2 = (model->m_localMtx).value[0][0];
      DCFlushRange(*(undefined4 *)((int)fVar2 + 0x20),*(int *)((int)fVar2 + 0x1c) * 6);
    }
    else if ((int)local_28 < 0x4e4f524d) {
      if (local_28 == 0x494e464f) {
        uVar1 = Get4__10CChunkFileFv(chunkFile);
        *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x5c) = uVar1;
        uVar1 = Get4__10CChunkFileFv(chunkFile);
        *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x60) = uVar1;
        cVar7 = Get4__10CChunkFileFv(chunkFile);
        fVar2 = (model->m_localMtx).value[0][0];
        *(byte *)((int)fVar2 + 0x10) = (byte)((int)cVar7 << 7) | *(byte *)((int)fVar2 + 0x10) & 0x7f
        ;
        cVar7 = Get4__10CChunkFileFv(chunkFile);
        fVar2 = (model->m_localMtx).value[0][0];
        *(byte *)((int)fVar2 + 0x10) =
             (byte)((int)cVar7 << 6) & 0x40 | *(byte *)((int)fVar2 + 0x10) & 0xbf;
        Get4__10CChunkFileFv(chunkFile);
        Get4__10CChunkFileFv(chunkFile);
        Get4__10CChunkFileFv(chunkFile);
        Get4__10CChunkFileFv(chunkFile);
      }
      else if ((int)local_28 < 0x494e464f) {
        if (local_28 == 0x444c4844) {
          *(uint *)((int)(model->m_localMtx).value[0][0] + 0x4c) = local_24 & 0xffff;
          iVar5 = *(int *)((int)(model->m_localMtx).value[0][0] + 0x4c);
          uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                            (iVar5 * 0xc + 0x10,stage,s_chara_cpp_801d90c8,0x820);
          uVar1 = __construct_new_array
                            (uVar1,__ct__Q36CChara5CMesh12CDisplayListFv,
                             __dt__Q36CChara5CMesh12CDisplayListFv,0xc,iVar5);
          *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x50) = uVar1;
          puVar8 = *(uint **)((int)(model->m_localMtx).value[0][0] + 0x50);
          PushChunk__10CChunkFileFv(chunkFile);
          while (iVar5 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                   (chunkFile,(CChunkFile *)&local_28), iVar5 != 0) {
            if (local_28 == 0x444c5354) {
              uVar6 = Get2__10CChunkFileFv(chunkFile);
              *(undefined2 *)(puVar8 + 2) = uVar6;
              *puVar8 = local_24;
              Align__10CChunkFileFUl(chunkFile,0x20);
              if (*puVar8 != 0) {
                uVar4 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                                  (&Memory,*puVar8 + 0x1f & 0xffffffe0,stage,s_chara_cpp_801d90c8,
                                   0x830,0);
                puVar8[1] = uVar4;
                Get__10CChunkFileFPvl(chunkFile,puVar8[1],*puVar8);
                DCFlushRange(puVar8[1],*puVar8);
              }
              Align__10CChunkFileFUl(chunkFile,0x20);
              puVar8 = puVar8 + 3;
            }
          }
          PopChunk__10CChunkFileFv(chunkFile);
        }
        else if (((int)local_28 < 0x444c4844) && (local_28 == 0x434f4c52)) {
          *(uint *)((int)(model->m_localMtx).value[0][0] + 0x24) = (uint)local_1c >> 2;
          uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                            (&Memory,local_1c,stage,s_chara_cpp_801d90c8,0x7e6,0);
          *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x28) = uVar1;
          uVar1 = GetAddress__10CChunkFileFv(chunkFile);
          memcpy(*(void **)((int)(model->m_localMtx).value[0][0] + 0x28),uVar1,local_1c);
          fVar2 = (model->m_localMtx).value[0][0];
          DCFlushRange(*(undefined4 *)((int)fVar2 + 0x28),*(int *)((int)fVar2 + 0x24) << 2);
        }
      }
      else if (local_28 == 0x4d4e414d) {
        uVar1 = GetString__10CChunkFileFv(chunkFile);
        strcpy((model->m_localMtx).value[0][0],uVar1);
      }
    }
    else if (local_28 == 0x55562020) {
      *(uint *)((int)(model->m_localMtx).value[0][0] + 0x2c) = (uint)local_1c >> 2;
      uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                        (&Memory,local_1c,stage,s_chara_cpp_801d90c8,0x7ee,0);
      *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x30) = uVar1;
      uVar1 = GetAddress__10CChunkFileFv(chunkFile);
      memcpy(*(void **)((int)(model->m_localMtx).value[0][0] + 0x30),uVar1,local_1c);
      fVar2 = (model->m_localMtx).value[0][0];
      DCFlushRange(*(undefined4 *)((int)fVar2 + 0x30),*(int *)((int)fVar2 + 0x2c) << 2);
    }
    else if ((int)local_28 < 0x55562020) {
      if (local_28 == 0x534b494e) {
        *(uint *)((int)(model->m_localMtx).value[0][0] + 0x54) = local_24;
        iVar5 = *(int *)((int)(model->m_localMtx).value[0][0] + 0x54);
        uVar1 = __nwa__FUlPQ27CMemory6CStagePci(iVar5 * 100 + 0x10,stage,s_chara_cpp_801d90c8,0x7f8)
        ;
        uVar1 = __construct_new_array
                          (uVar1,__ct__Q26CChara5CSkinFv,__dt__Q26CChara5CSkinFv,100,iVar5);
        *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x58) = uVar1;
        PushChunk__10CChunkFileFv(chunkFile);
        iVar5 = 0;
        while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (chunkFile,(CChunkFile *)&local_28), iVar3 != 0) {
          if (local_28 == 0x4e4f4445) {
            iVar3 = *(int *)((int)(model->m_localMtx).value[0][0] + 0x58) + iVar5;
            iVar5 = iVar5 + 100;
            uVar1 = Get4__10CChunkFileFv(chunkFile);
            *(undefined4 *)(iVar3 + 0x60) = uVar1;
          }
          else if (local_28 == 0x4f4e4520) {
            *(uint8_t **)((int)(model->m_localMtx).value[0][0] + 0x34) = local_1c;
            uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                              (&Memory,*(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x34),
                               stage,s_chara_cpp_801d90c8,0x808,0);
            *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x38) = uVar1;
            uVar1 = GetAddress__10CChunkFileFv(chunkFile);
            memcpy(*(void **)((int)(model->m_localMtx).value[0][0] + 0x38),uVar1,local_1c);
          }
          else if (local_28 == 0x54574f20) {
            *(uint8_t **)((int)(model->m_localMtx).value[0][0] + 0x3c) = local_1c;
            uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                              (&Memory,*(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x3c),
                               stage,s_chara_cpp_801d90c8,0x80e,0);
            *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x40) = uVar1;
            uVar1 = GetAddress__10CChunkFileFv(chunkFile);
            memcpy(*(void **)((int)(model->m_localMtx).value[0][0] + 0x40),uVar1,local_1c);
          }
          else if (local_28 == 0x524d494e) {
            *(uint8_t **)((int)(model->m_localMtx).value[0][0] + 0x44) = local_1c;
            uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                              (&Memory,*(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x44),
                               stage,s_chara_cpp_801d90c8,0x814,0);
            *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x48) = uVar1;
            uVar1 = GetAddress__10CChunkFileFv(chunkFile);
            memcpy(*(void **)((int)(model->m_localMtx).value[0][0] + 0x48),uVar1,local_1c);
          }
        }
        PopChunk__10CChunkFileFv(chunkFile);
      }
    }
    else if (local_28 == 0x56455254) {
      *(uint *)((int)(model->m_localMtx).value[0][0] + 0x14) = (uint)local_1c / 6;
      uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                        (&Memory,local_1c,stage,s_chara_cpp_801d90c8,0x7d6,0);
      *(undefined4 *)((int)(model->m_localMtx).value[0][0] + 0x18) = uVar1;
      uVar1 = GetAddress__10CChunkFileFv(chunkFile);
      memcpy(*(void **)((int)(model->m_localMtx).value[0][0] + 0x18),uVar1,local_1c);
      fVar2 = (model->m_localMtx).value[0][0];
      DCFlushRange(*(undefined4 *)((int)fVar2 + 0x18),*(int *)((int)fVar2 + 0x14) * 6);
    }
  }
  PopChunk__10CChunkFileFv(chunkFile);
  return;
}

