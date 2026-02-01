// Function: ReadFrame__12CMapKeyFrameFR10CChunkFilei
// Entry: 800338d8
// Size: 96 bytes

void ReadFrame__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame *mapKeyFrame,CChunkFile *chunkFile)

{
  int iVar1;
  undefined uVar2;
  
  iVar1 = Get4__10CChunkFileFv(chunkFile);
  mapKeyFrame->field6_0xc = iVar1;
  mapKeyFrame->field5_0x8 = iVar1;
  iVar1 = Get4__10CChunkFileFv(chunkFile);
  mapKeyFrame->field7_0x10 = iVar1;
  *(int *)&mapKeyFrame->field_0x14 = iVar1;
  uVar2 = Get4__10CChunkFileFv(chunkFile);
  *(undefined *)mapKeyFrame = uVar2;
  return;
}

