// Function: pppLoadPmd__8CPartMngFPCc
// Entry: 80059238
// Size: 912 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 pppLoadPmd__8CPartMngFPCc(CPartMng *partMng,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  pppModelSt *ppVar3;
  int16_t iVar4;
  uint uVar5;
  pppModelSt *ppVar6;
  int iVar7;
  undefined auStack_1c8 [4];
  undefined local_1c4 [32];
  CChunkFile aCStack_1a4 [3];
  CChunkFile aCStack_e8 [4];
  
  sprintf(StrTmp,s__s_pmd_8032fe30,param_2);
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_ReadPmd_fn__s_801d82d0,StrTmp);
  }
  iVar1 = pppPartInit__8CPartMngFv(partMng,StrTmp,auStack_1c8,0,0);
  if (iVar1 == 0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_CAN_NOT_READ__s________801d82a8,StrTmp);
    }
    uVar2 = 0;
  }
  else {
    if (partMng->m_pppModelStArr == (pppModelSt *)0x0) {
      ppVar3 = (pppModelSt *)
               __nw__FUlPQ27CMemory6CStagePci
                         (0x6c00,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0xca9);
      if (ppVar3 != (pppModelSt *)0x0) {
        __construct_array(ppVar3,__ct__10pppModelStFv,__dt__10pppModelStFv,0x6c,0x100);
        iVar7 = 8;
        ppVar6 = ppVar3;
        do {
          ppVar6->m_isUsed = '\0';
          ppVar6[1].m_isUsed = '\0';
          ppVar6[2].m_isUsed = '\0';
          ppVar6[3].m_isUsed = '\0';
          ppVar6[4].m_isUsed = '\0';
          ppVar6[5].m_isUsed = '\0';
          ppVar6[6].m_isUsed = '\0';
          ppVar6[7].m_isUsed = '\0';
          ppVar6[8].m_isUsed = '\0';
          ppVar6[9].m_isUsed = '\0';
          ppVar6[10].m_isUsed = '\0';
          ppVar6[0xb].m_isUsed = '\0';
          ppVar6[0xc].m_isUsed = '\0';
          ppVar6[0xd].m_isUsed = '\0';
          ppVar6[0xe].m_isUsed = '\0';
          ppVar6[0xf].m_isUsed = '\0';
          ppVar6[0x10].m_isUsed = '\0';
          ppVar6[0x11].m_isUsed = '\0';
          ppVar6[0x12].m_isUsed = '\0';
          ppVar6[0x13].m_isUsed = '\0';
          ppVar6[0x14].m_isUsed = '\0';
          ppVar6[0x15].m_isUsed = '\0';
          ppVar6[0x16].m_isUsed = '\0';
          ppVar6[0x17].m_isUsed = '\0';
          ppVar6[0x18].m_isUsed = '\0';
          ppVar6[0x19].m_isUsed = '\0';
          ppVar6[0x1a].m_isUsed = '\0';
          ppVar6[0x1b].m_isUsed = '\0';
          ppVar6[0x1c].m_isUsed = '\0';
          ppVar6[0x1d].m_isUsed = '\0';
          ppVar6[0x1e].m_isUsed = '\0';
          ppVar6[0x1f].m_isUsed = '\0';
          ppVar6 = ppVar6 + 0x20;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      partMng->m_pppModelStArr = ppVar3;
    }
    __ct__10CChunkFileFv(aCStack_e8);
    SetBuf__10CChunkFileFPv(aCStack_e8,iVar1);
    while (iVar1 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             (aCStack_e8,(CChunkFile *)(local_1c4 + 0x10)), iVar1 != 0) {
      PushChunk__10CChunkFileFv(aCStack_e8);
      if ((uint8_t *)local_1c4._16_4_ == (uint8_t *)0x52534554) {
        ppVar6 = partMng->m_pppModelStArr;
        ppVar3 = (pppModelSt *)0x0;
        while (iVar1 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (aCStack_e8,(CChunkFile *)local_1c4), iVar1 != 0) {
          if (local_1c4._0_4_ == 0x5253444d) {
            if (ppVar3 != (pppModelSt *)0x0) {
              __ct__10CChunkFileFv(aCStack_1a4);
              uVar2 = GetAddress__10CChunkFileFv(aCStack_e8);
              SetBuf__10CChunkFileFPv(aCStack_1a4,uVar2);
              uVar2 = pppReadRsd__8CPartMngFR10CChunkFileP10pppModelSt(&PartMng,aCStack_1a4,ppVar3);
              Ptr2Off__8CMapMeshFv(ppVar3);
              iVar4 = SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi
                                ((CAmemCacheSet *)CAMemCacheSet,(ppVar3->m_mapMesh).field12_0x24,
                                 uVar2,1,1);
              ppVar3->m_cacheId = iVar4;
              if ((ppVar3->m_mapMesh).field12_0x24 != 0) {
                __dl__FPv();
                (ppVar3->m_mapMesh).field12_0x24 = 0;
              }
              ppVar3->m_refCount = ppVar3->m_refCount + 1;
              ppVar3 = (pppModelSt *)0x0;
            }
          }
          else if (((int)local_1c4._0_4_ < 0x5253444d) && (local_1c4._0_4_ == 0x4e414d45)) {
            uVar2 = GetString__10CChunkFileFv(aCStack_e8);
            uVar5 = 0;
            ppVar3 = ppVar6;
            do {
              if ((ppVar3->m_isUsed != '\0') && (iVar1 = strcmp(ppVar3->m_name,uVar2), iVar1 == 0))
              goto LAB_8005948c;
              uVar5 = uVar5 + 1;
              ppVar3 = ppVar3 + 1;
            } while (uVar5 < 0x100);
            ppVar3 = (pppModelSt *)0x0;
LAB_8005948c:
            if (ppVar3 == (pppModelSt *)0x0) {
              iVar1 = 0;
              iVar7 = 0x100;
              ppVar3 = ppVar6;
              do {
                if (ppVar3->m_isUsed == '\0') {
                  ppVar3 = ppVar6 + iVar1;
                  goto LAB_800594d4;
                }
                ppVar3 = ppVar3 + 1;
                iVar1 = iVar1 + 1;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
              ppVar3 = (pppModelSt *)0x0;
LAB_800594d4:
              ppVar3->m_refCount = 0;
              ppVar3->m_isUsed = '\x01';
              strcpy(ppVar3->m_name,uVar2);
            }
            else {
              ppVar3 = (pppModelSt *)0x0;
            }
          }
        }
      }
      PopChunk__10CChunkFileFv(aCStack_e8);
    }
    uVar2 = 1;
  }
  return uVar2;
}

