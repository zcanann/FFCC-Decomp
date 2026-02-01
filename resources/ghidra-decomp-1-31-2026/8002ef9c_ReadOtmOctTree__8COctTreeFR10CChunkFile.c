// Function: ReadOtmOctTree__8COctTreeFR10CChunkFile
// Entry: 8002ef9c
// Size: 952 bytes

undefined4 ReadOtmOctTree__8COctTreeFR10CChunkFile(COctTree *octTree,CChunkFile *chunkFile)

{
  void *pvVar1;
  undefined2 uVar5;
  undefined4 uVar2;
  COctNode *pCVar3;
  undefined uVar8;
  short sVar6;
  ushort uVar7;
  int iVar4;
  COctNode **ppCVar9;
  int iVar10;
  COctNode *unaff_r28;
  uint uVar11;
  uint uVar12;
  double dVar13;
  uint32_t local_38;
  
  *(undefined *)((int)&octTree->vtable + 1) = 0;
  PushChunk__10CChunkFileFv(chunkFile);
  do {
    do {
      while( true ) {
        while( true ) {
          while( true ) {
            iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                              (chunkFile,(CChunkFile *)&local_38);
            if (iVar4 == 0) {
              PopChunk__10CChunkFileFv(chunkFile);
              return 1;
            }
            if (local_38 != 0x4f424a4e) break;
            uVar11 = Get2__10CChunkFileFv(chunkFile);
            octTree->field2_0x8 = MapMng.mapObjArr + (uVar11 & 0xffff);
            pvVar1 = octTree->field2_0x8;
            if (*(char *)((int)pvVar1 + 0x1e) == '\x04') {
              *(undefined *)((int)pvVar1 + 0x15) = 0xff;
              *(undefined *)((int)octTree->field2_0x8 + 0x14) = 0xff;
              *(undefined *)((int)octTree->field2_0x8 + 0x22) = 0;
            }
            else if (*(char *)((int)pvVar1 + 0x1e) == '\x03') {
              *(undefined *)((int)pvVar1 + 0x22) = 0;
            }
          }
          if (0x4f424a4d < (int)local_38) break;
          if (local_38 == 0x4e4f444e) {
            uVar5 = Get2__10CChunkFileFv(chunkFile);
            *(undefined2 *)((int)&octTree->vtable + 2) = uVar5;
            if ((*(char *)((int)octTree->field2_0x8 + 0x1e) != '\x01') &&
               (2 < (uint)System.m_execParam)) {
              Printf__7CSystemFPce
                        (&System,s__________________________________801d7268,
                         *(undefined2 *)((int)&octTree->vtable + 2));
            }
            uVar11 = (uint)*(ushort *)((int)&octTree->vtable + 2);
            uVar2 = __nwa__FUlPQ27CMemory6CStagePci
                              (uVar11 * 0x4c + 0x10,MapMng._0_4_,s_mapocttree_cpp_801d72ec,0x59);
            pCVar3 = (COctNode *)__construct_new_array(uVar2,__ct__8COctNodeFv,0,0x4c,uVar11);
            octTree->rootNode = pCVar3;
          }
          else if (((int)local_38 < 0x4e4f444e) && (local_38 == 0x494e464f)) {
            uVar8 = Get1__10CChunkFileFv(chunkFile);
            *(undefined *)((int)&octTree->vtable + 1) = uVar8;
          }
        }
        if (local_38 != 0x54595045) break;
        uVar8 = Get2__10CChunkFileFv(chunkFile);
        *(undefined *)&octTree->vtable = uVar8;
      }
    } while ((0x54595044 < (int)local_38) || (local_38 != 0x54524545));
    PushChunk__10CChunkFileFv(chunkFile);
    while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             (chunkFile,(CChunkFile *)&local_38), iVar4 != 0) {
      if (local_38 == 0x4e4f4445) {
        PushChunk__10CChunkFileFv(chunkFile);
LAB_8002f2e8:
        iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk(chunkFile,(CChunkFile *)&local_38)
        ;
        if (iVar4 != 0) {
          if (local_38 == 0x43484c44) {
            iVar10 = 0;
            iVar4 = 0;
            pCVar3 = unaff_r28;
            do {
              uVar7 = Get2__10CChunkFileFv(chunkFile);
              if (uVar7 != 0xffff) {
                iVar10 = iVar10 + 1;
                pCVar3->children[0] = octTree->rootNode + uVar7;
                pCVar3 = (COctNode *)&(pCVar3->boundsMin).y;
              }
              iVar4 = iVar4 + 1;
            } while (iVar4 < 8);
            ppCVar9 = unaff_r28->children + iVar10 + -7;
            uVar11 = 8 - iVar10;
            if (iVar10 < 8) {
              uVar12 = uVar11 >> 3;
              if (uVar12 != 0) {
                do {
                  ppCVar9[7] = (COctNode *)0x0;
                  ppCVar9[8] = (COctNode *)0x0;
                  ppCVar9[9] = (COctNode *)0x0;
                  ppCVar9[10] = (COctNode *)0x0;
                  ppCVar9[0xb] = (COctNode *)0x0;
                  ppCVar9[0xc] = (COctNode *)0x0;
                  ppCVar9[0xd] = (COctNode *)0x0;
                  ppCVar9[0xe] = (COctNode *)0x0;
                  ppCVar9 = ppCVar9 + 8;
                  uVar12 = uVar12 - 1;
                } while (uVar12 != 0);
                uVar11 = uVar11 & 7;
                if (uVar11 == 0) goto LAB_8002f2e8;
              }
              do {
                ppCVar9[7] = (COctNode *)0x0;
                ppCVar9 = ppCVar9 + 1;
                uVar11 = uVar11 - 1;
              } while (uVar11 != 0);
            }
          }
          else if ((int)local_38 < 0x43484c44) {
            if (local_38 == 0x424f4e44) {
              dVar13 = (double)GetF4__10CChunkFileFv(chunkFile);
              (unaff_r28->boundsMin).x = (float)dVar13;
              dVar13 = (double)GetF4__10CChunkFileFv(chunkFile);
              (unaff_r28->boundsMin).y = (float)dVar13;
              dVar13 = (double)GetF4__10CChunkFileFv(chunkFile);
              (unaff_r28->boundsMin).z = (float)dVar13;
              dVar13 = (double)GetF4__10CChunkFileFv(chunkFile);
              (unaff_r28->boundsMax).x = (float)dVar13;
              dVar13 = (double)GetF4__10CChunkFileFv(chunkFile);
              (unaff_r28->boundsMax).y = (float)dVar13;
              dVar13 = (double)GetF4__10CChunkFileFv(chunkFile);
              (unaff_r28->boundsMax).z = (float)dVar13;
            }
          }
          else if (local_38 == 0x4f424a20) {
            uVar11 = Get2__10CChunkFileFv(chunkFile);
            unaff_r28 = octTree->rootNode + (uVar11 & 0xffff);
            sVar6 = Get2__10CChunkFileFv(chunkFile);
            unaff_r28->meshIndex = sVar6;
            sVar6 = Get2__10CChunkFileFv(chunkFile);
            unaff_r28->_meshIndex2 = sVar6;
          }
          goto LAB_8002f2e8;
        }
        PopChunk__10CChunkFileFv(chunkFile);
      }
    }
    PopChunk__10CChunkFileFv(chunkFile);
  } while( true );
}

