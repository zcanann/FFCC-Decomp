// Function: Create__14CMapTexAnimSetFR10CChunkFileP12CMaterialSetP11CTextureSet
// Entry: 80050064
// Size: 700 bytes

void Create__14CMapTexAnimSetFR10CChunkFileP12CMaterialSetP11CTextureSet
               (int param_1,CChunkFile *chunkFile,CMaterialSet *materialSet,CTextureSet *textureSet)

{
  float fVar1;
  float fVar2;
  undefined2 uVar5;
  short sVar6;
  undefined uVar7;
  void *pvVar3;
  int iVar4;
  int iVar8;
  CRef *ref;
  double dVar9;
  uint32_t local_38;
  int32_t local_34;
  int local_30;
  uint8_t *local_28;
  uint8_t *puStack_24;
  
  ref = (CRef *)0x0;
  *(CMaterialSet **)(param_1 + 0x10c) = materialSet;
  *(CTextureSet **)(param_1 + 0x110) = textureSet;
  PushChunk__10CChunkFileFv(chunkFile);
  while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)&local_38), iVar4 != 0) {
    if (local_38 == 0x4b455920) {
      ReadKey__12CMapKeyFrameFR10CChunkFilei
                ((CMapKeyFrame *)&ref[4].refCount,chunkFile,(char)local_34);
      *(undefined *)((int)&ref[2].refCount + 1) = 1;
    }
    else if ((int)local_38 < 0x4b455920) {
      if (local_38 == 0x4a554e20) {
        ReadJun__12CMapKeyFrameFR10CChunkFilei
                  ((CMapKeyFrame *)&ref[4].refCount,chunkFile,(char)local_34);
      }
      else if (((int)local_38 < 0x4a554e20) && (local_38 == 0x4652414d)) {
        ReadFrame__12CMapKeyFrameFR10CChunkFilei((CMapKeyFrame *)&ref[4].refCount,chunkFile);
      }
    }
    else if (local_38 == 0x54414e4d) {
      ref = (CRef *)__nw__FUlPQ27CMemory6CStagePci(0x4c,MapMng._0_4_,s_maptexanim_cpp_801d7ec4,0x24)
      ;
      if (ref != (CRef *)0x0) {
        __ct__4CRefFv(ref);
        ref->vtable = &PTR_PTR_s_CMapTexAnim_801ea9a4;
        fVar1 = FLOAT_8032fd48;
        ref[7].refCount = 0;
        fVar2 = FLOAT_8032fd4c;
        ref[8].vtable = (void *)0x0;
        ref[8].refCount = 0;
        ref[9].vtable = (void *)0x0;
        *(undefined *)((int)&ref[4].refCount + 3) = 1;
        *(undefined *)&ref[5].vtable = 0;
        ref[4].vtable = (void *)0x0;
        ref[3].vtable = (void *)fVar1;
        ref[3].refCount = (int)fVar2;
        *(undefined *)&ref[2].refCount = 0;
        *(undefined *)((int)&ref[2].refCount + 1) = 0;
        *(undefined2 *)((int)&ref[2].vtable + 2) = 0xffff;
        *(undefined *)((int)&ref[2].refCount + 2) = 1;
      }
      uVar5 = Get2__10CChunkFileFv(chunkFile);
      *(undefined2 *)&ref[1].vtable = uVar5;
      uVar5 = Get2__10CChunkFileFv(chunkFile);
      *(undefined2 *)((int)&ref[1].vtable + 2) = uVar5;
      uVar5 = Get2__10CChunkFileFv(chunkFile);
      *(undefined2 *)&ref[1].refCount = uVar5;
      *(undefined2 *)&ref[2].vtable = *(undefined2 *)&ref[1].refCount;
      sVar6 = Get2__10CChunkFileFv(chunkFile);
      puStack_24 = (uint8_t *)((int)sVar6 ^ 0x80000000);
      local_28 = (uint8_t *)0x43300000;
      ref[3].refCount = (int)(float)((double)CONCAT44(0x43300000,puStack_24) - DOUBLE_8032fd30);
      *(undefined2 *)((int)&ref[1].refCount + 2) = 0;
      dVar9 = (double)GetF4__10CChunkFileFv(chunkFile);
      ref[3].vtable = (void *)(float)dVar9;
      uVar7 = Get1__10CChunkFileFv(chunkFile);
      *(undefined *)&ref[2].refCount = uVar7;
      Get1__10CChunkFileFv(chunkFile);
      Get1__10CChunkFileFv(chunkFile);
      Get1__10CChunkFileFv(chunkFile);
      if (local_30 == 0) {
        Get4__10CChunkFileFv(chunkFile);
        *(undefined2 *)((int)&ref[2].vtable + 2) = 0xffff;
      }
      else {
        uVar5 = Get2__10CChunkFileFv(chunkFile);
        *(undefined2 *)((int)&ref[2].vtable + 2) = uVar5;
        Get2__10CChunkFileFv(chunkFile);
      }
      Get4__10CChunkFileFv(chunkFile);
      Get4__10CChunkFileFv(chunkFile);
      pvVar3 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                 ((int)*(short *)&ref[1].refCount << 1,MapMng._0_4_,
                                  s_maptexanim_cpp_801d7ec4,0x3b);
      ref[4].vtable = pvVar3;
      iVar8 = 0;
      for (iVar4 = 0; iVar4 < *(short *)&ref[1].refCount; iVar4 = iVar4 + 1) {
        uVar5 = Get2__10CChunkFileFv(chunkFile);
        *(undefined2 *)((int)ref[4].vtable + iVar8) = uVar5;
        iVar8 = iVar8 + 2;
      }
      sVar6 = *(short *)(param_1 + 8);
      *(short *)(param_1 + 8) = sVar6 + 1;
      *(CRef **)(param_1 + sVar6 * 4 + 0xc) = ref;
    }
  }
  PopChunk__10CChunkFileFv(chunkFile);
  return;
}

