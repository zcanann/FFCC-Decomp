// Function: Create__5CFontFPvPQ27CMemory6CStage
// Entry: 80092aa4
// Size: 648 bytes

void Create__5CFontFPvPQ27CMemory6CStage(CFont *font,undefined *param_2,CStage *stage)

{
  short sVar1;
  undefined2 uVar5;
  void *pvVar2;
  CFont *pCVar3;
  CTexture *texture;
  int iVar4;
  ushort *puVar6;
  undefined local_e8 [212];
  
  sVar1 = 0;
  if ((param_2 == (undefined *)0x0) && (stage == (CStage *)0x0)) {
    sVar1 = 1;
  }
  font->field7_0xe = sVar1;
  if (font->field7_0xe != 0) {
    param_2 = &DAT_801fe080;
  }
  __ct__10CChunkFileFPv((CChunkFile *)(local_e8 + 0x10),param_2);
  while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8), iVar4 != 0) {
    if (local_e8._0_4_ == 0x464f4e54) {
      PushChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
      while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                               ((CChunkFile *)(local_e8 + 0x10),(CChunkFile *)local_e8), iVar4 != 0)
      {
        if (local_e8._0_4_ == 0x494e464f) {
          uVar5 = Get4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
          *(undefined2 *)&font->field_0x8 = uVar5;
          uVar5 = Get4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
          *(undefined2 *)&font->field_0xa = uVar5;
          uVar5 = Get4__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
          *(undefined2 *)&font->field_0xc = uVar5;
        }
        else if ((int)local_e8._0_4_ < 0x494e464f) {
          if (local_e8._0_4_ == 0x44415441) {
            if (font->field7_0xe == 0) {
              pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                         (local_e8._12_4_,stage,s_fontman_cpp_801d9cb8,0xcf);
              font->field27_0x38 = pvVar2;
              Get__10CChunkFileFPvl
                        ((CChunkFile *)(local_e8 + 0x10),font->field27_0x38,local_e8._12_4_);
            }
            else {
              pvVar2 = (void *)GetAddress__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
              font->field27_0x38 = pvVar2;
            }
            puVar6 = (ushort *)font->field27_0x38;
            iVar4 = 0x20;
            pCVar3 = font;
            do {
              *(ushort **)&pCVar3->field_0x3c = puVar6;
              puVar6 = puVar6 + (uint)*puVar6 * 4 + 1;
              *(ushort **)&pCVar3->field_0x40 = puVar6;
              puVar6 = puVar6 + (uint)*puVar6 * 4 + 1;
              *(ushort **)&pCVar3->field_0x44 = puVar6;
              puVar6 = puVar6 + (uint)*puVar6 * 4 + 1;
              *(ushort **)&pCVar3->field_0x48 = puVar6;
              puVar6 = puVar6 + (uint)*puVar6 * 4 + 1;
              *(ushort **)&pCVar3->field_0x4c = puVar6;
              puVar6 = puVar6 + (uint)*puVar6 * 4 + 1;
              *(ushort **)&pCVar3->field_0x50 = puVar6;
              puVar6 = puVar6 + (uint)*puVar6 * 4 + 1;
              *(ushort **)&pCVar3->field_0x54 = puVar6;
              puVar6 = puVar6 + (uint)*puVar6 * 4 + 1;
              *(ushort **)&pCVar3->field_0x58 = puVar6;
              pCVar3 = (CFont *)&pCVar3->margin;
              puVar6 = puVar6 + (uint)*puVar6 * 4 + 1;
              iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
          }
        }
        else if (local_e8._0_4_ == 0x54585452) {
          texture = (CTexture *)
                    __nw__8CTextureFUlPQ27CMemory6CStagePci
                              (0x80,FontMan._4_4_,s_fontman_cpp_801d9cb8,0xdf);
          if (texture != (CTexture *)0x0) {
            texture = (CTexture *)__ct__8CTextureFv(texture);
          }
          font->texturePtr = texture;
          Create__8CTextureFR10CChunkFilePQ27CMemory6CStageP13CAmemCacheSetii
                    (font->texturePtr,local_e8 + 0x10,stage,0,0,
                     (byte)(-(uint)(ushort)font->field7_0xe >> 0x1f));
        }
      }
      PopChunk__10CChunkFileFv((CChunkFile *)(local_e8 + 0x10));
    }
  }
  return;
}

