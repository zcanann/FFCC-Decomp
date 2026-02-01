// Function: ReadOtmHit__7CMapHitFR10CChunkFile
// Entry: 800266f0
// Size: 1608 bytes

/* WARNING: Removing unreachable block (ram,0x80026d1c) */
/* WARNING: Removing unreachable block (ram,0x80026d14) */
/* WARNING: Removing unreachable block (ram,0x80026d0c) */
/* WARNING: Removing unreachable block (ram,0x80026d04) */
/* WARNING: Removing unreachable block (ram,0x80026cfc) */
/* WARNING: Removing unreachable block (ram,0x80026720) */
/* WARNING: Removing unreachable block (ram,0x80026718) */
/* WARNING: Removing unreachable block (ram,0x80026710) */
/* WARNING: Removing unreachable block (ram,0x80026708) */
/* WARNING: Removing unreachable block (ram,0x80026700) */

undefined4 ReadOtmHit__7CMapHitFR10CChunkFile(CMapHit *mapHit,CChunkFile *chunkFile)

{
  float fVar1;
  float fVar2;
  ushort uVar3;
  undefined4 uVar4;
  CMapHitFace *pCVar5;
  undefined uVar9;
  undefined2 uVar8;
  float *pfVar6;
  int iVar7;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  uint32_t local_88;
  int32_t local_84;
  int local_80;
  
  PushChunk__10CChunkFileFv(chunkFile);
  while (iVar7 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)&local_88), iVar7 != 0) {
    if (local_88 == 0x48495456) {
      mapHit->m_vertexCount = (uint16_t)local_84;
      pfVar11 = (float *)__nwa__FUlPQ27CMemory6CStagePci
                                   ((uint)mapHit->m_vertexCount * 0xc,MapMng._0_4_,
                                    s_maphit_cpp_801d7088,0x143);
      mapHit->m_vertices = pfVar11;
      iVar13 = 0;
      for (iVar7 = 0; fVar2 = FLOAT_8032f8cc, iVar7 < (int)(uint)mapHit->m_vertexCount;
          iVar7 = iVar7 + 1) {
        dVar14 = (double)GetF4__10CChunkFileFv(chunkFile);
        *(float *)((int)mapHit->m_vertices + iVar13) = (float)dVar14;
        dVar14 = (double)GetF4__10CChunkFileFv(chunkFile);
        *(float *)((int)mapHit->m_vertices + iVar13 + 4) = (float)dVar14;
        dVar14 = (double)GetF4__10CChunkFileFv(chunkFile);
        *(float *)((int)mapHit->m_vertices + iVar13 + 8) = (float)dVar14;
        fVar2 = (mapHit->m_positionMin).x;
        pfVar11 = (float *)((int)mapHit->m_vertices + iVar13);
        fVar1 = *pfVar11;
        if (fVar2 < fVar1) {
          fVar1 = fVar2;
        }
        (mapHit->m_positionMin).x = fVar1;
        fVar2 = (mapHit->m_positionMin).y;
        fVar1 = pfVar11[1];
        if (fVar2 < fVar1) {
          fVar1 = fVar2;
        }
        (mapHit->m_positionMin).y = fVar1;
        fVar2 = (mapHit->m_positionMin).z;
        fVar1 = pfVar11[2];
        if (fVar2 < fVar1) {
          fVar1 = fVar2;
        }
        (mapHit->m_positionMin).z = fVar1;
        fVar2 = (mapHit->m_positionMax).x;
        fVar1 = *pfVar11;
        if (fVar1 < fVar2) {
          fVar1 = fVar2;
        }
        (mapHit->m_positionMax).x = fVar1;
        fVar2 = (mapHit->m_positionMax).y;
        fVar1 = pfVar11[1];
        if (fVar1 < fVar2) {
          fVar1 = fVar2;
        }
        (mapHit->m_positionMax).y = fVar1;
        fVar2 = (mapHit->m_positionMax).z;
        fVar1 = pfVar11[2];
        if (fVar1 < fVar2) {
          fVar1 = fVar2;
        }
        (mapHit->m_positionMax).z = fVar1;
        iVar13 = iVar13 + 0xc;
      }
      (mapHit->m_positionMin).x = (mapHit->m_positionMin).x - FLOAT_8032f8cc;
      (mapHit->m_positionMin).y = (mapHit->m_positionMin).y - fVar2;
      (mapHit->m_positionMin).z = (mapHit->m_positionMin).z - fVar2;
      (mapHit->m_positionMax).x = (mapHit->m_positionMax).x + fVar2;
      (mapHit->m_positionMax).y = (mapHit->m_positionMax).y + fVar2;
      (mapHit->m_positionMax).z = (mapHit->m_positionMax).z + fVar2;
    }
    else if ((int)local_88 < 0x48495456) {
      if (local_88 == 0x48495446) {
        mapHit->m_faceCount = (uint16_t)local_84;
        uVar3 = mapHit->m_faceCount;
        uVar4 = __nwa__FUlPQ27CMemory6CStagePci
                          ((uint)uVar3 * 0x50 + 0x10,MapMng._0_4_,s_maphit_cpp_801d7088,0x159);
        pCVar5 = (CMapHitFace *)
                 __construct_new_array(uVar4,__ct__11CMapHitFaceFv,0,0x50,(uint)uVar3);
        mapHit->m_faces = pCVar5;
        dVar17 = (double)FLOAT_8032f8d0;
        iVar13 = 0;
        dVar18 = (double)FLOAT_8032f8f8;
        dVar19 = (double)FLOAT_8032f8f4;
        dVar14 = DOUBLE_8032f900;
        for (iVar7 = 0; iVar7 < (int)(uint)mapHit->m_faceCount; iVar7 = iVar7 + 1) {
          Align__10CChunkFileFUl(chunkFile,4);
          pfVar12 = (float *)(&mapHit->m_faces->field_0x0 + iVar13);
          dVar15 = (double)GetF4__10CChunkFileFv(chunkFile);
          *pfVar12 = (float)dVar15;
          dVar15 = (double)GetF4__10CChunkFileFv(chunkFile);
          pfVar12[1] = (float)dVar15;
          dVar15 = (double)GetF4__10CChunkFileFv(chunkFile);
          pfVar12[2] = (float)dVar15;
          dVar15 = (double)GetF4__10CChunkFileFv(chunkFile);
          pfVar12[3] = (float)dVar15;
          uVar9 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(pfVar12 + 0x11) = uVar9;
          uVar9 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)pfVar12 + 0x45) = uVar9;
          uVar9 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)pfVar12 + 0x46) = uVar9;
          uVar9 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)pfVar12 + 0x47) = uVar9;
          *(undefined *)((int)pfVar12 + 0x4e) = 0;
          *(undefined *)((int)pfVar12 + 0x4f) = 0;
          pfVar11 = pfVar12;
          for (iVar10 = 0; iVar10 < (int)(uint)*(byte *)((int)pfVar12 + 0x46); iVar10 = iVar10 + 1)
          {
            pfVar11[0xc] = (float)dVar17;
            pfVar11[0xb] = (float)dVar17;
            pfVar11 = pfVar11 + 2;
          }
          if (local_80 == 0) {
            if (System.m_execParam != 0) {
              Printf__7CSystemFPce(&System,&DAT_801d7094);
            }
            Align__10CChunkFileFUl(chunkFile,4);
            for (iVar10 = 0; iVar10 < (int)(uint)*(byte *)((int)pfVar12 + 0x46); iVar10 = iVar10 + 1
                ) {
              GetF4__10CChunkFileFv(chunkFile);
              GetF4__10CChunkFileFv(chunkFile);
            }
            pfVar12[10] = FLOAT_8032f8d0;
          }
          else if (local_80 == 1) {
            if (System.m_execParam != 0) {
              Printf__7CSystemFPce(&System,&DAT_801d7094);
            }
            dVar15 = (double)GetF4__10CChunkFileFv(chunkFile);
            pfVar12[10] = (float)dVar15;
            Align__10CChunkFileFUl(chunkFile,4);
          }
          else {
            dVar15 = (double)GetF4__10CChunkFileFv(chunkFile);
            pfVar12[10] = (float)dVar15;
            Align__10CChunkFileFUl(chunkFile,4);
            dVar15 = (double)FLOAT_8032f8f4;
            pfVar11 = pfVar12;
            for (iVar10 = 0; iVar10 < (int)(uint)*(byte *)((int)pfVar12 + 0x46); iVar10 = iVar10 + 1
                ) {
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              pfVar11[0xb] = (float)(dVar15 * dVar16);
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              pfVar11[0xc] = (float)(dVar15 * dVar16);
              pfVar11 = pfVar11 + 2;
            }
          }
          pfVar11 = pfVar12;
          for (iVar10 = 0; iVar10 < (int)(uint)*(byte *)((int)pfVar12 + 0x46); iVar10 = iVar10 + 1)
          {
            uVar8 = Get2__10CChunkFileFv(chunkFile);
            *(undefined2 *)(pfVar11 + 0x12) = uVar8;
            pfVar6 = mapHit->m_vertices + (uint)*(ushort *)(pfVar11 + 0x12) * 3;
            fVar2 = *pfVar6;
            if (pfVar12[4] < fVar2) {
              fVar2 = pfVar12[4];
            }
            pfVar12[4] = fVar2;
            fVar2 = pfVar6[1];
            if (pfVar12[5] < fVar2) {
              fVar2 = pfVar12[5];
            }
            pfVar12[5] = fVar2;
            fVar2 = pfVar6[2];
            if (pfVar12[6] < fVar2) {
              fVar2 = pfVar12[6];
            }
            pfVar12[6] = fVar2;
            fVar2 = *pfVar6;
            if (fVar2 < pfVar12[7]) {
              fVar2 = pfVar12[7];
            }
            pfVar12[7] = fVar2;
            fVar2 = pfVar6[1];
            if (fVar2 < pfVar12[8]) {
              fVar2 = pfVar12[8];
            }
            pfVar12[8] = fVar2;
            fVar2 = pfVar6[2];
            if (fVar2 < pfVar12[9]) {
              fVar2 = pfVar12[9];
            }
            pfVar12[9] = fVar2;
            pfVar11 = (float *)((int)pfVar11 + 2);
          }
          iVar13 = iVar13 + 0x50;
          pfVar12[10] = (float)((double)pfVar12[10] * dVar18);
          pfVar12[4] = pfVar12[4] - (float)(dVar19 + (double)pfVar12[10]);
          pfVar12[5] = pfVar12[5] - (float)(dVar19 + (double)pfVar12[10]);
          pfVar12[6] = pfVar12[6] - (float)(dVar19 + (double)pfVar12[10]);
          pfVar12[7] = pfVar12[7] + (float)(dVar19 + (double)pfVar12[10]);
          pfVar12[8] = pfVar12[8] + (float)(dVar19 + (double)pfVar12[10]);
          pfVar12[9] = pfVar12[9] + (float)(dVar19 + (double)pfVar12[10]);
          pfVar12[10] = (float)(dVar14 - (double)pfVar12[10]);
        }
      }
    }
    else if (local_88 == 0x4e414d45) {
      uVar4 = GetString__10CChunkFileFv(chunkFile);
      AttachMapHit__7CMapMngFP7CMapHitPc(&MapMng,mapHit,uVar4);
    }
  }
  PopChunk__10CChunkFileFv(chunkFile);
  return 1;
}

