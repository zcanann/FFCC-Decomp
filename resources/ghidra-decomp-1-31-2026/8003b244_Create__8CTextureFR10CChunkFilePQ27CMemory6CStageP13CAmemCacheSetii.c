// Function: Create__8CTextureFR10CChunkFilePQ27CMemory6CStageP13CAmemCacheSetii
// Entry: 8003b244
// Size: 1260 bytes

void Create__8CTextureFR10CChunkFilePQ27CMemory6CStageP13CAmemCacheSetii
               (CTexture *texture,CChunkFile *chunkFile,CStage *stage,CAmemCacheSet *amemCacheSet,
               undefined4 param_5,undefined param_6)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar5;
  undefined uVar6;
  byte bVar7;
  int iVar3;
  uint uVar4;
  uint uVar8;
  uint32_t local_40;
  uint8_t *local_34;
  uint8_t *local_30;
  uint8_t *puStack_2c;
  
  texture->field96_0x6c = 1;
  texture->field93_0x60 = 6;
  texture->field_0x71 = 0;
  texture->field_0x75 = param_6;
  PushChunk__10CChunkFileFv(chunkFile);
  while (iVar3 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)&local_40), iVar3 != 0) {
    if (local_40 == 0x4e414d45) {
      uVar1 = GetString__10CChunkFileFv(chunkFile);
      strcpy(&texture->field_0x8,uVar1);
    }
    else if ((int)local_40 < 0x4e414d45) {
      if (local_40 == 0x494d4147) {
        if (amemCacheSet == (CAmemCacheSet *)0x0) {
          if (texture->field_0x75 == '\0') {
            iVar3 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                              (&Memory,local_34,stage,s_textureman_cpp_801d7974,0x15c,0);
            texture->field105_0x78 = iVar3;
            Get__10CChunkFileFPvl(chunkFile,texture->field105_0x78,local_34);
          }
          else {
            iVar3 = GetAddress__10CChunkFileFv(chunkFile);
            texture->field105_0x78 = iVar3;
          }
          DCFlushRange(texture->field105_0x78,local_34);
          *(undefined2 *)&texture->field_0x72 = 0xffff;
        }
        else {
          uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                            (&Memory,local_34,stage,s_textureman_cpp_801d7974,0x150,0);
          Get__10CChunkFileFPvl(chunkFile,uVar1,local_34);
          uVar5 = SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi
                            (amemCacheSet,uVar1,local_34,0,param_5);
          *(undefined2 *)&texture->field_0x72 = uVar5;
          __dl__FPv(uVar1);
          texture->field105_0x78 = 0;
        }
      }
      else if (((int)local_40 < 0x494d4147) && (local_40 == 0x464d5420)) {
        uVar6 = Get1__10CChunkFileFv(chunkFile);
        switch(uVar6) {
        case 0:
          texture->field93_0x60 = 6;
          break;
        case 1:
          texture->field93_0x60 = 4;
          break;
        case 2:
          texture->field93_0x60 = 9;
          break;
        case 3:
          texture->field93_0x60 = 8;
          break;
        case 5:
          texture->field93_0x60 = 0;
          break;
        case 6:
          texture->field93_0x60 = 0xe;
          break;
        case 7:
          texture->field93_0x60 = 3;
          texture->field_0x70 = 1;
          break;
        case 8:
          texture->field93_0x60 = 3;
          break;
        case 9:
          texture->field93_0x60 = 1;
          break;
        case 10:
          texture->field93_0x60 = 0xe;
          texture->field_0x71 = 1;
        }
        bVar7 = Get1__10CChunkFileFv(chunkFile);
        texture->field101_0x74 = bVar7;
        uVar4 = Get1__10CChunkFileFv(chunkFile);
        if (3 < (int)local_34) {
          texture->field96_0x6c = uVar4 & 0xff;
        }
      }
    }
    else if (local_40 == 0x53495a45) {
      uVar4 = Get4__10CChunkFileFv(chunkFile);
      texture->field94_0x64 = uVar4;
      uVar4 = Get4__10CChunkFileFv(chunkFile);
      texture->field95_0x68 = uVar4;
      if ((texture->field94_0x64 == 0) || (texture->field95_0x68 == 0)) {
        Printf__7CSystemFPce
                  (&System,s_Error_width__d_height__d_801d7984,texture->field94_0x64,
                   texture->field95_0x68);
        PopChunk__10CChunkFileFv(chunkFile);
        return;
      }
    }
    else if (((int)local_40 < 0x53495a45) && (local_40 == 0x50414c54)) {
      if (texture->field_0x75 == '\0') {
        uVar1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                          (&Memory,local_34,stage,s_textureman_cpp_801d7974,0x178,0);
        *(undefined4 *)&texture->field_0x7c = uVar1;
        Get__10CChunkFileFPvl(chunkFile,*(undefined4 *)&texture->field_0x7c,local_34);
      }
      else {
        uVar1 = GetAddress__10CChunkFileFv(chunkFile);
        *(undefined4 *)&texture->field_0x7c = uVar1;
      }
      DCFlushRange(*(undefined4 *)&texture->field_0x7c,local_34);
    }
  }
  PopChunk__10CChunkFileFv(chunkFile);
  for (uVar4 = texture->field94_0x64; (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
  }
  for (uVar8 = texture->field95_0x68; (uVar8 & 1) == 0; uVar8 = uVar8 >> 1) {
  }
  if ((uVar4 != 1) || (uVar8 != 1)) {
    texture->field96_0x6c = 0;
  }
  if (*(short *)&texture->field_0x72 != -1) {
    return;
  }
  iVar3 = texture->field93_0x60;
  if ((iVar3 == 9) || (iVar3 == 8)) {
    GXInitTexObjCI(&texture->field_0x28,texture->field105_0x78,texture->field94_0x64 & 0xffff,
                   texture->field95_0x68 & 0xffff,iVar3,texture->field96_0x6c,texture->field96_0x6c,
                   0,0);
    iVar3 = *(int *)&texture->field_0x7c;
    uVar1 = 0x10;
    if (texture->field93_0x60 == 9) {
      uVar1 = 0x100;
    }
    GXInitTlutObj(&texture->field_0x48,iVar3,0,uVar1);
    uVar1 = 0x10;
    if (texture->field93_0x60 == 9) {
      uVar1 = 0x100;
    }
    iVar2 = 0x10;
    if (texture->field93_0x60 == 9) {
      iVar2 = 0x100;
    }
    GXInitTlutObj(&texture->field_0x54,iVar3 + iVar2 * 2,0,uVar1);
  }
  else {
    GXInitTexObj(&texture->field_0x28,texture->field105_0x78,texture->field94_0x64 & 0xffff,
                 texture->field95_0x68 & 0xffff,iVar3,texture->field96_0x6c,texture->field96_0x6c,
                 1 - texture->field101_0x74 >> 0x1f);
  }
  puStack_2c = (uint8_t *)(uint)texture->field101_0x74;
  if (puStack_2c < (uint8_t *)0x2) {
    return;
  }
  local_30 = (uint8_t *)0x43300000;
  GXInitTexObjLOD((double)FLOAT_8032fad8,
                  (double)((float)((double)CONCAT44(0x43300000,puStack_2c) - DOUBLE_8032fae0) -
                          FLOAT_8032fadc),(double)FLOAT_8032fad8,&texture->field_0x28,5,1,1,0,0);
  return;
}

