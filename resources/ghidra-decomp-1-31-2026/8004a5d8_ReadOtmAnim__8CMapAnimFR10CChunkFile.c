// Function: ReadOtmAnim__8CMapAnimFR10CChunkFile
// Entry: 8004a5d8
// Size: 728 bytes

void ReadOtmAnim__8CMapAnimFR10CChunkFile(CMapAnim *mapAnim,CChunkFile *chunkFile)

{
  undefined4 uVar1;
  void *pvVar2;
  int *item;
  int iVar3;
  uint32_t local_38;
  uint8_t *local_2c;
  uint8_t *local_28;
  
  PushChunk__10CChunkFileFv(chunkFile);
  while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)&local_28), iVar3 != 0) {
    if (local_28 == (uint8_t *)0x4652414d) {
      uVar1 = Get4__10CChunkFileFv(chunkFile);
      *(undefined4 *)&mapAnim->field_0x1c = uVar1;
      pvVar2 = (void *)Get4__10CChunkFileFv(chunkFile);
      mapAnim[1].mapAnimNodes.vtable = pvVar2;
    }
    else if (local_28 == (uint8_t *)0x4e4f4445) {
      item = (int *)__nw__FUlPQ27CMemory6CStagePci(0xc,MapMng._0_4_,s_mapanim_cpp_801d7cb8,0xc2);
      if (item != (int *)0x0) {
        item[2] = 0;
      }
      item[1] = (int)mapAnim;
      PushChunk__10CChunkFileFv(chunkFile);
      while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                               (chunkFile,(CChunkFile *)&local_38), iVar3 != 0) {
        if (local_38 == 0x4e494458) {
          iVar3 = Get4__10CChunkFileFv(chunkFile);
          *item = iVar3 * 0xf0 + -0x7fdb9f48;
        }
        else if (local_38 == 0x5452414e) {
          iVar3 = __nw__FUlPQ27CMemory6CStagePci(0x18,MapMng._0_4_,s_mapanim_cpp_801d7cb8,0x4c);
          if (iVar3 != 0) {
            *(undefined4 *)(iVar3 + 4) = 0;
            *(undefined4 *)(iVar3 + 0xc) = 0;
            *(undefined4 *)(iVar3 + 0x14) = 0;
          }
          item[2] = iVar3;
          Add__27CPtrArray<P13CMapAnimKeyDt>FP13CMapAnimKeyDt(&MapMng.g_CMapAnimKeyDtArray,item[2]);
          *(uint *)item[2] = (uint)local_2c >> 4;
          uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                            (*(int *)item[2] << 4,MapMng._0_4_,s_mapanim_cpp_801d7cb8,0x4f);
          *(undefined4 *)(item[2] + 4) = uVar1;
          uVar1 = GetAddress__10CChunkFileFv(chunkFile);
          memcpy(*(void **)(item[2] + 4),uVar1,local_2c);
        }
        else if (local_38 == 0x524f5420) {
          *(uint *)(item[2] + 8) = (uint)local_2c >> 4;
          uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                            (*(int *)(item[2] + 8) << 4,MapMng._0_4_,s_mapanim_cpp_801d7cb8,0x55);
          *(undefined4 *)(item[2] + 0xc) = uVar1;
          uVar1 = GetAddress__10CChunkFileFv(chunkFile);
          memcpy(*(void **)(item[2] + 0xc),uVar1,local_2c);
        }
        else if (local_38 == 0x5343414c) {
          *(uint *)(item[2] + 0x10) = (uint)local_2c >> 4;
          uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                            (*(int *)(item[2] + 0x10) << 4,MapMng._0_4_,s_mapanim_cpp_801d7cb8,0x5b)
          ;
          *(undefined4 *)(item[2] + 0x14) = uVar1;
          uVar1 = GetAddress__10CChunkFileFv(chunkFile);
          memcpy(*(void **)(item[2] + 0x14),uVar1,local_2c);
        }
      }
      PopChunk__10CChunkFileFv(chunkFile);
      Add__26CPtrArray<P12CMapAnimNode>FP12CMapAnimNode(&mapAnim->mapAnimNodes,item);
    }
  }
  PopChunk__10CChunkFileFv(chunkFile);
  return;
}

