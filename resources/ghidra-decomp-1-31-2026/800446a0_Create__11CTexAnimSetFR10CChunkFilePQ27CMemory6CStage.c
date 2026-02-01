// Function: Create__11CTexAnimSetFR10CChunkFilePQ27CMemory6CStage
// Entry: 800446a0
// Size: 900 bytes

void Create__11CTexAnimSetFR10CChunkFilePQ27CMemory6CStage
               (CTexAnimSet *texAnimSet,CChunkFile *chunkFile,CStage *stage)

{
  float fVar1;
  CRef *ref;
  int *piVar2;
  CRef *pCVar3;
  undefined4 uVar4;
  void *pvVar5;
  char cVar8;
  uint uVar6;
  int iVar7;
  CChunkFile local_58;
  
  SetStage__21CPtrArray<P8CTexAnim>FPQ27CMemory6CStage
            ((CPtrArray *)&(texAnimSet->texAnims).size,stage);
  PushChunk__10CChunkFileFv(chunkFile);
  while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)&local_58.m_chunkScopes[0].m_lastChunkSize),
        iVar7 != 0) {
    if (local_58.m_chunkScopes[0].m_lastChunkSize == 0x54414e4d) {
      ref = (CRef *)__nw__FUlPQ27CMemory6CStagePci(0x24,stage,s_texanim_cpp_801d7adc,0x3f);
      if (ref != (CRef *)0x0) {
        __ct__4CRefFv(ref);
        fVar1 = FLOAT_8032fb38;
        ref->vtable = &PTR_PTR_s_CTexAnim_801e9c54;
        ref[1].vtable = (void *)0x0;
        ref[1].refCount = 0;
        ref[2].vtable = (void *)fVar1;
        ref[2].refCount = -2;
        ref[4].vtable = (void *)fVar1;
        ref[3].refCount = (int)fVar1;
        ref[3].vtable = (void *)fVar1;
      }
      piVar2 = (int *)ref[1].vtable;
      if (piVar2 != (int *)0x0) {
        iVar7 = piVar2[1];
        piVar2[1] = iVar7 + -1;
        if ((iVar7 + -1 == 0) && (piVar2 != (int *)0x0)) {
          (**(code **)(*piVar2 + 8))(piVar2,1);
        }
        ref[1].vtable = (void *)0x0;
      }
      pCVar3 = (CRef *)__nw__FUlPQ27CMemory6CStagePci(300,stage,s_texanim_cpp_801d7adc,0xd3);
      if (pCVar3 != (CRef *)0x0) {
        __ct__4CRefFv(pCVar3);
        pCVar3->vtable = &PTR_PTR_s_CTexAnim_CRefData_801e9c3c;
        __ct__25CPtrArray<P11CTexAnimSeq>Fv((CPtrArray *)(pCVar3 + 0x22));
        pCVar3[0x21].vtable = (void *)0x0;
        pCVar3[0x21].refCount = 0;
      }
      ref[1].vtable = pCVar3;
      SetStage__25CPtrArray<P11CTexAnimSeq>FPQ27CMemory6CStage
                ((CPtrArray *)((int)ref[1].vtable + 0x110),stage);
      PushChunk__10CChunkFileFv(chunkFile);
      while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                               (chunkFile,(CChunkFile *)&local_58.m_headerPtr), iVar7 != 0) {
        if (local_58.m_headerPtr == (uint8_t *)0x53455120) {
          pCVar3 = (CRef *)__nw__FUlPQ27CMemory6CStagePci(0x118,stage,s_texanim_cpp_801d7adc,0xe2);
          if (pCVar3 != (CRef *)0x0) {
            __ct__4CRefFv(pCVar3);
            pCVar3->vtable = &PTR_PTR_s_CTexAnimSeq_801e9c24;
            pCVar3[0x21].refCount = 0;
            pCVar3[0x22].refCount = 0;
          }
          PushChunk__10CChunkFileFv(chunkFile);
          while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk(chunkFile,&local_58),
                iVar7 != 0) {
            if (local_58.m_scopeSize == 0x4b455920) {
              pCVar3[0x21].refCount = (uint)local_58.m_base / 0x30;
              iVar7 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                                (&Memory,local_58.m_base,stage,s_texanim_cpp_801d7adc,0x1d4,0);
              pCVar3[0x22].refCount = iVar7;
              uVar4 = GetAddress__10CChunkFileFv(chunkFile);
              memcpy((void *)pCVar3[0x22].refCount,uVar4,local_58.m_base);
            }
            else if ((int)local_58.m_scopeSize < 0x4b455920) {
              if (local_58.m_scopeSize == 0x494e464f) {
                pvVar5 = (void *)Get4__10CChunkFileFv(chunkFile);
                pCVar3[0x21].vtable = pvVar5;
                Get4__10CChunkFileFv(chunkFile);
                cVar8 = Get4__10CChunkFileFv(chunkFile);
                *(byte *)&pCVar3[0x22].vtable =
                     (byte)((int)cVar8 << 7) | *(byte *)&pCVar3[0x22].vtable & 0x7f;
                cVar8 = Get4__10CChunkFileFv(chunkFile);
                *(byte *)&pCVar3[0x22].vtable =
                     (byte)((int)cVar8 << 6) & 0x40 | *(byte *)&pCVar3[0x22].vtable & 0xbf;
                uVar4 = strcmp(pCVar3 + 1,&DAT_8032fb48);
                uVar6 = countLeadingZeros(uVar4);
                *(byte *)&pCVar3[0x22].vtable =
                     (byte)((int)(char)(uVar6 >> 5) << 5) & 0x20 |
                     *(byte *)&pCVar3[0x22].vtable & 0xdf;
              }
            }
            else if (local_58.m_scopeSize == 0x4e414d45) {
              uVar4 = GetString__10CChunkFileFv(chunkFile);
              strcpy(pCVar3 + 1,uVar4);
            }
          }
          PopChunk__10CChunkFileFv(chunkFile);
          Add__25CPtrArray<P11CTexAnimSeq>FP11CTexAnimSeq
                    ((CPtrArray *)((int)ref[1].vtable + 0x110),pCVar3);
        }
        else if (((int)local_58.m_headerPtr < 0x53455120) &&
                (local_58.m_headerPtr == (uint8_t *)0x4e414d45)) {
          *(uint8_t **)((int)ref[1].vtable + 0x10c) = local_58.m_cursor;
          uVar4 = GetString__10CChunkFileFv(chunkFile);
          strcpy((int)ref[1].vtable + 8,uVar4);
        }
      }
      PopChunk__10CChunkFileFv(chunkFile);
      Add__21CPtrArray<P8CTexAnim>FP8CTexAnim((CPtrArray *)&(texAnimSet->texAnims).size,ref);
    }
  }
  PopChunk__10CChunkFileFv(chunkFile);
  return;
}

