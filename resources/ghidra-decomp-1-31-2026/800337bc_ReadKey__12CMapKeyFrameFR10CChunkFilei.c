// Function: ReadKey__12CMapKeyFrameFR10CChunkFilei
// Entry: 800337bc
// Size: 284 bytes

void ReadKey__12CMapKeyFrameFR10CChunkFilei
               (CMapKeyFrame *mapKeyFrame,CChunkFile *chunkFile,byte param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  double dVar4;
  
  *(undefined *)&mapKeyFrame->isRun = 1;
  mapKeyFrame->field2_0x2 = param_3;
  iVar1 = __nwa__FUlPQ27CMemory6CStagePci
                    ((uint)mapKeyFrame->field2_0x2 << 2,MapMng._0_4_,&DAT_8032f9d0,0xd5);
  mapKeyFrame->field16_0x1c = iVar1;
  iVar1 = __nwa__FUlPQ27CMemory6CStagePci
                    ((uint)mapKeyFrame->field2_0x2 << 2,MapMng._0_4_,&DAT_8032f9d0,0xd6);
  mapKeyFrame->field17_0x20 = iVar1;
  iVar3 = 0;
  for (iVar1 = 0; iVar1 < (int)(uint)mapKeyFrame->field2_0x2; iVar1 = iVar1 + 1) {
    dVar4 = (double)GetF4__10CChunkFileFv(chunkFile);
    *(float *)(mapKeyFrame->field16_0x1c + iVar3) = (float)dVar4;
    dVar4 = (double)GetF4__10CChunkFileFv(chunkFile);
    *(float *)(mapKeyFrame->field17_0x20 + iVar3) = (float)dVar4;
    iVar3 = iVar3 + 4;
  }
  if (*(char *)mapKeyFrame == '\x01') {
    uVar2 = __nwa__FUlPQ27CMemory6CStagePci
                      ((uint)mapKeyFrame->field2_0x2 << 2,MapMng._0_4_,&DAT_8032f9d0,0xde);
    *(undefined4 *)(mapKeyFrame + 1) = uVar2;
    MakeSpline1Dtable__5CMathFiPfPfPf
              (&Math,mapKeyFrame->field2_0x2 - 1,mapKeyFrame->field17_0x20,mapKeyFrame->field16_0x1c
               ,*(undefined4 *)(mapKeyFrame + 1));
  }
  return;
}

