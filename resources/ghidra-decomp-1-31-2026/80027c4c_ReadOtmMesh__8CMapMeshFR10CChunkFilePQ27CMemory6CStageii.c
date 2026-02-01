// Function: ReadOtmMesh__8CMapMeshFR10CChunkFilePQ27CMemory6CStageii
// Entry: 80027c4c
// Size: 2292 bytes

/* WARNING: Removing unreachable block (ram,0x80028524) */
/* WARNING: Removing unreachable block (ram,0x8002851c) */
/* WARNING: Removing unreachable block (ram,0x80027c64) */
/* WARNING: Removing unreachable block (ram,0x80027c5c) */

uint ReadOtmMesh__8CMapMeshFR10CChunkFilePQ27CMemory6CStageii
               (CMapMesh *mapMesh,CChunkFile *chunkFile,CStage *stage,int param_4,int param_5)

{
  ChunkScope *pCVar1;
  float fVar2;
  uint uVar3;
  float fVar4;
  uchar *puVar5;
  int iVar6;
  float *pfVar7;
  undefined uVar9;
  undefined2 uVar8;
  int32_t *piVar10;
  uchar **ppuVar11;
  int iVar12;
  int *piVar13;
  uint8_t *unaff_r25;
  uint uVar14;
  uint8_t *puVar15;
  int iVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  undefined local_118 [20];
  uint8_t *local_104;
  int32_t local_100;
  uint8_t *local_fc;
  uint8_t *local_f8;
  uint8_t *local_f4;
  uchar *local_f0;
  uchar *local_ec [42];
  
  local_118._16_4_ = chunkFile->m_scopeSize;
  ppuVar11 = &local_f0;
  piVar10 = &chunkFile->m_stackDepth;
  local_104 = (uint8_t *)chunkFile->m_lastChunkSize;
  local_100 = chunkFile->m_scopeOffset;
  local_fc = chunkFile->m_base;
  local_f8 = chunkFile->m_headerPtr;
  local_f4 = chunkFile->m_cursor;
  local_f0 = (uchar *)chunkFile->m_stackDepth;
  iVar16 = 0x14;
  do {
    pCVar1 = (ChunkScope *)(piVar10 + 1);
    piVar10 = piVar10 + 2;
    puVar5 = (uchar *)*piVar10;
    ppuVar11[1] = (uchar *)pCVar1->m_scopeSize;
    ppuVar11 = ppuVar11 + 2;
    *ppuVar11 = puVar5;
    iVar16 = iVar16 + -1;
  } while (iVar16 != 0);
  puVar15 = (uint8_t *)0x0;
  PushChunk__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
  while (iVar16 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                            ((CChunkFile *)(local_118 + 0x10),(CChunkFile *)local_118), iVar16 != 0)
  {
    if (local_118._0_4_ == 0x4e4f524d) {
      puVar15 = (uint8_t *)(local_118._12_4_ + ((uint)(puVar15 + 0x1f) & 0xffffffe0));
    }
    else if ((int)local_118._0_4_ < 0x4e4f524d) {
      if (local_118._0_4_ == 0x444c4844) {
        mapMesh->unkCount = (short)local_118._4_4_;
        puVar15 = (uint8_t *)
                  (((uint)(puVar15 + 0x1f) & 0xffffffe0) + (uint)(ushort)mapMesh->unkCount * 0x10);
        PushChunk__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        while (iVar16 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                  ((CChunkFile *)(local_118 + 0x10),(CChunkFile *)local_118),
              iVar16 != 0) {
          if (local_118._0_4_ == 0x444c5354) {
            Align__10CChunkFileFUl((CChunkFile *)(local_118 + 0x10),0x20);
            if (local_118._4_4_ != 0) {
              puVar15 = (uint8_t *)
                        (((uint)(puVar15 + 0x1f) & 0xffffffe0) +
                        (local_118._4_4_ + 0x1f & 0xffffffe0));
            }
            Align__10CChunkFileFUl((CChunkFile *)(local_118 + 0x10),0x20);
          }
        }
        PopChunk__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
      }
      else if ((int)local_118._0_4_ < 0x444c4844) {
        if (local_118._0_4_ == 0x434f4c52) {
          puVar15 = (uint8_t *)(local_118._12_4_ + ((uint)(puVar15 + 0x1f) & 0xffffffe0));
        }
      }
      else if (local_118._0_4_ == 0x4e425420) {
        puVar15 = (uint8_t *)(local_118._12_4_ + ((uint)(puVar15 + 0x1f) & 0xffffffe0));
      }
    }
    else if (local_118._0_4_ == 0x56455254) {
      puVar15 = (uint8_t *)(local_118._12_4_ + ((uint)(puVar15 + 0x1f) & 0xffffffe0));
    }
    else if (((int)local_118._0_4_ < 0x56455254) && (local_118._0_4_ == 0x55562020)) {
      puVar15 = (uint8_t *)(local_118._12_4_ + ((uint)(puVar15 + 0x1f) & 0xffffffe0));
    }
  }
  PopChunk__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
  local_118._16_4_ = chunkFile->m_scopeSize;
  ppuVar11 = &local_f0;
  uVar3 = (uint)(puVar15 + 0x1f) & 0xffffffe0;
  piVar10 = &chunkFile->m_stackDepth;
  local_104 = (uint8_t *)chunkFile->m_lastChunkSize;
  local_100 = chunkFile->m_scopeOffset;
  local_fc = chunkFile->m_base;
  local_f8 = chunkFile->m_headerPtr;
  local_f4 = chunkFile->m_cursor;
  local_f0 = (uchar *)chunkFile->m_stackDepth;
  iVar16 = 0x14;
  do {
    pCVar1 = (ChunkScope *)(piVar10 + 1);
    piVar10 = piVar10 + 2;
    puVar5 = (uchar *)*piVar10;
    ppuVar11[1] = (uchar *)pCVar1->m_scopeSize;
    ppuVar11 = ppuVar11 + 2;
    *ppuVar11 = puVar5;
    iVar16 = iVar16 + -1;
  } while (iVar16 != 0);
  DAT_8032ec98 = stage;
  PushChunk__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
  while (iVar16 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                            ((CChunkFile *)(local_118 + 0x10),(CChunkFile *)local_118), iVar16 != 0)
  {
    if (local_118._0_4_ == 0x4e4f524d) {
      iVar12 = 0;
      mapMesh->field1_0x2 = (short)((uint)local_118._12_4_ / 6);
      mapMesh->field15_0x30 = (uint)(unaff_r25 + 0x1f) & 0xffffffe0;
      unaff_r25 = (uint8_t *)(local_118._12_4_ + ((uint)(unaff_r25 + 0x1f) & 0xffffffe0));
      for (iVar16 = 0; iVar16 < (int)(uint)(ushort)mapMesh->field1_0x2; iVar16 = iVar16 + 1) {
        uVar8 = Get2__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        *(undefined2 *)(mapMesh->field15_0x30 + iVar12) = uVar8;
        uVar8 = Get2__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        *(undefined2 *)(mapMesh->field15_0x30 + iVar12 + 2) = uVar8;
        uVar8 = Get2__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        iVar6 = iVar12 + 4;
        iVar12 = iVar12 + 6;
        *(undefined2 *)(mapMesh->field15_0x30 + iVar6) = uVar8;
      }
    }
    else if ((int)local_118._0_4_ < 0x4e4f524d) {
      if (local_118._0_4_ == 0x434f4c52) {
        iVar12 = 0;
        mapMesh->field4_0x8 = (short)((uint)local_118._12_4_ >> 2);
        mapMesh->field18_0x3c = (uint)(unaff_r25 + 0x1f) & 0xffffffe0;
        unaff_r25 = (uint8_t *)(local_118._12_4_ + ((uint)(unaff_r25 + 0x1f) & 0xffffffe0));
        for (iVar16 = 0; iVar16 < (int)(uint)(ushort)mapMesh->field4_0x8; iVar16 = iVar16 + 1) {
          uVar9 = Get1__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
          *(undefined *)(mapMesh->field18_0x3c + iVar12) = uVar9;
          uVar9 = Get1__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
          *(undefined *)(mapMesh->field18_0x3c + iVar12 + 1) = uVar9;
          uVar9 = Get1__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
          *(undefined *)(mapMesh->field18_0x3c + iVar12 + 2) = uVar9;
          uVar9 = Get1__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
          *(undefined *)(mapMesh->field18_0x3c + iVar12 + 3) = uVar9;
          if (param_5 != 0) {
            *(char *)(mapMesh->field18_0x3c + iVar12) =
                 (char)((int)(uint)*(byte *)(mapMesh->field18_0x3c + iVar12) >> 1);
            *(char *)(mapMesh->field18_0x3c + iVar12 + 1) =
                 (char)((int)(uint)*(byte *)(mapMesh->field18_0x3c + iVar12 + 1) >> 1);
            *(char *)(mapMesh->field18_0x3c + iVar12 + 2) =
                 (char)((int)(uint)*(byte *)(mapMesh->field18_0x3c + iVar12 + 2) >> 1);
          }
          iVar12 = iVar12 + 4;
        }
      }
      else if ((int)local_118._0_4_ < 0x434f4c52) {
        if (local_118._0_4_ == 0x424f4646) {
          dVar17 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
          dVar18 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
          dVar19 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
          mapMesh->field6_0xc = (float)((double)mapMesh->field6_0xc - dVar17);
          mapMesh->field7_0x10 = (float)((double)mapMesh->field7_0x10 - dVar18);
          mapMesh->field8_0x14 = (float)((double)mapMesh->field8_0x14 - dVar19);
          mapMesh->field9_0x18 = (float)((double)mapMesh->field9_0x18 + dVar17);
          mapMesh->field10_0x1c = (float)((double)mapMesh->field10_0x1c + dVar18);
          mapMesh->field11_0x20 = (float)((double)mapMesh->field11_0x20 + dVar19);
        }
      }
      else if (local_118._0_4_ == 0x444c4844) {
        mapMesh->unkCount = (short)local_118._4_4_;
        if (param_4 == 0) {
          uVar14 = (uint)(unaff_r25 + 0x1f) & 0xffffffe0;
        }
        else {
          iVar16 = __nwa__FUlPQ27CMemory6CStagePci(uVar3,DAT_8032ec98,s_mapmesh_cpp_801d70b0,0x1d5);
          mapMesh->field13_0x28 = iVar16;
          uVar14 = mapMesh->field13_0x28;
        }
        mapMesh->field19_0x40 = uVar14;
        iVar16 = 0;
        unaff_r25 = (uint8_t *)(uVar14 + (uint)(ushort)mapMesh->unkCount * 0x10);
        for (iVar12 = 0; iVar12 < (int)(uint)(ushort)mapMesh->unkCount; iVar12 = iVar12 + 1) {
          iVar6 = iVar16 + 4;
          *(undefined4 *)(mapMesh->field19_0x40 + iVar16) = 0;
          iVar16 = iVar16 + 0x10;
          *(undefined4 *)(mapMesh->field19_0x40 + iVar6) = 0;
        }
        iVar16 = 0;
        PushChunk__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        while (iVar12 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                  ((CChunkFile *)(local_118 + 0x10),(CChunkFile *)local_118),
              iVar12 != 0) {
          if (local_118._0_4_ == 0x444c5354) {
            piVar13 = (int *)(mapMesh->field19_0x40 + iVar16);
            iVar16 = iVar16 + 0x10;
            uVar8 = Get2__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
            *(undefined2 *)(piVar13 + 2) = uVar8;
            *piVar13 = local_118._4_4_;
            Align__10CChunkFileFUl((CChunkFile *)(local_118 + 0x10),0x20);
            piVar13[1] = 0;
            if (*piVar13 != 0) {
              piVar13[1] = (uint)(unaff_r25 + 0x1f) & 0xffffffe0;
              if (param_4 == 0) {
                piVar13[3] = piVar13[1] - mapMesh->field12_0x24;
              }
              else {
                piVar13[3] = piVar13[1] - mapMesh->field13_0x28;
              }
              unaff_r25 = (uint8_t *)
                          (((uint)(unaff_r25 + 0x1f) & 0xffffffe0) +
                          (local_118._4_4_ + 0x1f & 0xffffffe0));
              memset(piVar13[1],0,*piVar13 + 0x1fU & 0xffffffe0);
              Get__10CChunkFileFPvl((CChunkFile *)(local_118 + 0x10),piVar13[1],*piVar13);
              DCFlushRange(piVar13[1],*piVar13 + 0x1fU & 0xffffffe0);
            }
            Align__10CChunkFileFUl((CChunkFile *)(local_118 + 0x10),0x20);
          }
        }
        PopChunk__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        DCFlushRange(mapMesh->field14_0x2c,(uint)(ushort)mapMesh->field0_0x0 * 0xc);
        DCFlushRange(mapMesh->field15_0x30,(uint)(ushort)mapMesh->field1_0x2 * 0xc);
        DCFlushRange(mapMesh->field16_0x34,(uint)(ushort)mapMesh->field2_0x4 * 0x12);
        DCFlushRange(mapMesh->field18_0x3c,(uint)(ushort)mapMesh->field4_0x8 * 0xc);
        DCFlushRange(mapMesh->field17_0x38,(uint)(ushort)mapMesh->field3_0x6 * 0xc);
      }
    }
    else if (local_118._0_4_ == 0x56455254) {
      iVar16 = __nwa__FUlPQ27CMemory6CStagePci(uVar3,DAT_8032ec98,s_mapmesh_cpp_801d70b0,0x13a);
      mapMesh->field12_0x24 = iVar16;
      fVar4 = FLOAT_8032f934;
      fVar2 = FLOAT_8032f930;
      iVar12 = 0;
      uVar14 = mapMesh->field12_0x24 + 0x1fU & 0xffffffe0;
      mapMesh->field0_0x0 = (short)((uint)local_118._12_4_ / 0xc);
      mapMesh->field14_0x2c = uVar14;
      mapMesh->field8_0x14 = fVar2;
      unaff_r25 = (uint8_t *)(local_118._12_4_ + uVar14);
      mapMesh->field7_0x10 = fVar2;
      mapMesh->field6_0xc = fVar2;
      mapMesh->field11_0x20 = fVar4;
      mapMesh->field10_0x1c = fVar4;
      mapMesh->field9_0x18 = fVar4;
      for (iVar16 = 0; iVar16 < (int)(uint)(ushort)mapMesh->field0_0x0; iVar16 = iVar16 + 1) {
        dVar17 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        *(float *)(mapMesh->field14_0x2c + iVar12) = (float)dVar17;
        dVar17 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        *(float *)(mapMesh->field14_0x2c + iVar12 + 4) = (float)dVar17;
        dVar17 = (double)GetF4__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        *(float *)(mapMesh->field14_0x2c + iVar12 + 8) = (float)dVar17;
        pfVar7 = (float *)(mapMesh->field14_0x2c + iVar12);
        fVar2 = *pfVar7;
        if (mapMesh->field6_0xc < fVar2) {
          fVar2 = mapMesh->field6_0xc;
        }
        mapMesh->field6_0xc = fVar2;
        fVar2 = pfVar7[1];
        if (mapMesh->field7_0x10 < fVar2) {
          fVar2 = mapMesh->field7_0x10;
        }
        mapMesh->field7_0x10 = fVar2;
        fVar2 = pfVar7[2];
        if (mapMesh->field8_0x14 < fVar2) {
          fVar2 = mapMesh->field8_0x14;
        }
        mapMesh->field8_0x14 = fVar2;
        fVar2 = *pfVar7;
        if (fVar2 < mapMesh->field9_0x18) {
          fVar2 = mapMesh->field9_0x18;
        }
        mapMesh->field9_0x18 = fVar2;
        fVar2 = pfVar7[1];
        if (fVar2 < mapMesh->field10_0x1c) {
          fVar2 = mapMesh->field10_0x1c;
        }
        mapMesh->field10_0x1c = fVar2;
        fVar2 = pfVar7[2];
        if (fVar2 < mapMesh->field11_0x20) {
          fVar2 = mapMesh->field11_0x20;
        }
        mapMesh->field11_0x20 = fVar2;
        iVar12 = iVar12 + 0xc;
      }
    }
    else if (((int)local_118._0_4_ < 0x56455254) && (local_118._0_4_ == 0x55562020)) {
      iVar16 = 0;
      mapMesh->field3_0x6 = (short)((uint)local_118._12_4_ >> 2);
      mapMesh->field17_0x38 = (uint)(unaff_r25 + 0x1f) & 0xffffffe0;
      unaff_r25 = (uint8_t *)(local_118._12_4_ + ((uint)(unaff_r25 + 0x1f) & 0xffffffe0));
      for (iVar12 = 0; iVar12 < (int)(uint)(ushort)mapMesh->field3_0x6; iVar12 = iVar12 + 1) {
        uVar8 = Get2__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        *(undefined2 *)(mapMesh->field17_0x38 + iVar16) = uVar8;
        uVar8 = Get2__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
        iVar6 = iVar16 + 2;
        iVar16 = iVar16 + 4;
        *(undefined2 *)(mapMesh->field17_0x38 + iVar6) = uVar8;
      }
    }
  }
  PopChunk__10CChunkFileFv((CChunkFile *)(local_118 + 0x10));
  return uVar3;
}

