// Function: ReadJun__12CMapKeyFrameFR10CChunkFilei
// Entry: 80033938
// Size: 136 bytes

void ReadJun__12CMapKeyFrameFR10CChunkFilei
               (CMapKeyFrame *mapKeyFrame,CChunkFile *chunkFile,undefined param_3)

{
  undefined4 uVar1;
  undefined uVar2;
  int iVar3;
  
  mapKeyFrame->field_0x1 = param_3;
  uVar1 = __nwa__FUlPQ27CMemory6CStagePci(mapKeyFrame->field_0x1,MapMng._0_4_,&DAT_8032f9d0,0xc1);
  *(undefined4 *)&mapKeyFrame->field_0x18 = uVar1;
  for (iVar3 = 0; iVar3 < (int)(uint)(byte)mapKeyFrame->field_0x1; iVar3 = iVar3 + 1) {
    uVar2 = Get1__10CChunkFileFv(chunkFile);
    *(undefined *)(*(int *)&mapKeyFrame->field_0x18 + iVar3) = uVar2;
  }
  return;
}

