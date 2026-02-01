// Function: pppInitData__FP12_pppDataHeadP7pppProgi
// Entry: 80054d88
// Size: 804 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppInitData__FP12_pppDataHeadP7pppProgi(_pppDataHead *pppDataHead,pppProg *pppProg,int param_3)

{
  uint32_t uVar1;
  void *dstBuffer;
  undefined2 uVar4;
  int iVar2;
  undefined4 uVar3;
  int iVar5;
  int iVar6;
  uint32_t uVar7;
  int *piVar8;
  uint uVar9;
  pppModelSt *ppVar10;
  undefined2 *puVar11;
  int iVar12;
  
  pppDataHead->m_cacheChunks = (int)&pppDataHead->m_version + pppDataHead->m_cacheChunks;
  pppDataHead->m_modelNames = (int)&pppDataHead->m_version + pppDataHead->m_modelNames;
  pppDataHead->m_shapeNames = (int)&pppDataHead->m_version + pppDataHead->m_shapeNames;
  pppDataHead->m_shapeGroups = (int)&pppDataHead->m_version + pppDataHead->m_shapeGroups;
  piVar8 = (int *)pppDataHead->m_cacheChunks;
  uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                    ((uint)pppDataHead->m_cacheChunkCount << 3,PartPcs.m_usbStreamData.m_stageLoad,
                     s_pppPart_cpp_801d81f8,0x620);
  pppDataHead->m_cacheChunks = uVar1;
  iVar12 = 0;
  for (iVar6 = 0; iVar6 < (int)(uint)pppDataHead->m_cacheChunkCount; iVar6 = iVar6 + 1) {
    iVar5 = *piVar8;
    iVar2 = piVar8[1] - iVar5;
    dstBuffer = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                  (iVar2,PartPcs.m_usbStreamData.m_stageLoad,s_pppPart_cpp_801d81f8,
                                   0x626);
    memcpy(dstBuffer,(int)&pppDataHead->m_version + iVar5,iVar2);
    uVar4 = SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi
                      ((CAmemCacheSet *)CAMemCacheSet,dstBuffer,iVar2,2,param_3);
    *(undefined2 *)(pppDataHead->m_cacheChunks + iVar12) = uVar4;
    __dl__FPv(dstBuffer);
    piVar8 = piVar8 + 1;
    iVar12 = iVar12 + 8;
  }
  uVar7 = pppDataHead->m_modelNames;
  uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                    ((uint)pppDataHead->m_modelCount << 2,PartPcs.m_usbStreamData.m_stageLoad,
                     s_pppPart_cpp_801d81f8,0x636);
  pppDataHead->m_modelNames = uVar1;
  iVar12 = 0;
  for (iVar6 = 0; iVar6 < (int)(uint)pppDataHead->m_modelCount; iVar6 = iVar6 + 1) {
    uVar9 = 0;
    ppVar10 = PartMng.m_pppModelStArr;
    do {
      if ((ppVar10->m_isUsed != '\0') && (iVar5 = strcmp(ppVar10->m_name,uVar7), iVar5 == 0))
      goto LAB_80054f04;
      uVar9 = uVar9 + 1;
      ppVar10 = ppVar10 + 1;
    } while (uVar9 < 0x100);
    ppVar10 = (pppModelSt *)0x0;
LAB_80054f04:
    uVar7 = uVar7 + 0x20;
    *(pppModelSt **)(pppDataHead->m_modelNames + iVar12) = ppVar10;
    iVar5 = *(int *)(pppDataHead->m_modelNames + iVar12);
    iVar12 = iVar12 + 4;
    *(short *)(iVar5 + 100) = *(short *)(iVar5 + 100) + 1;
  }
  uVar7 = pppDataHead->m_shapeNames;
  uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                    ((uint)pppDataHead->m_shapeCount << 2,PartPcs.m_usbStreamData.m_stageLoad,
                     s_pppPart_cpp_801d81f8,0x643);
  pppDataHead->m_shapeNames = uVar1;
  iVar6 = 0;
  iVar12 = 0;
  do {
    if ((int)(uint)pppDataHead->m_shapeCount <= iVar6) {
      puVar11 = (undefined2 *)pppDataHead->m_shapeGroups;
      uVar1 = __nwa__FUlPQ27CMemory6CStagePci
                        ((uint)pppDataHead->m_shapeGroupCount << 3,
                         PartPcs.m_usbStreamData.m_stageLoad,s_pppPart_cpp_801d81f8,0x651);
      pppDataHead->m_shapeGroups = uVar1;
      iVar12 = 0;
      for (iVar6 = 0; iVar6 < (int)(uint)pppDataHead->m_shapeGroupCount; iVar6 = iVar6 + 1) {
        *(undefined2 *)(pppDataHead->m_shapeGroups + iVar12) = *puVar11;
        *(undefined2 *)(pppDataHead->m_shapeGroups + iVar12 + 2) = puVar11[1];
        uVar3 = __nwa__FUlPQ27CMemory6CStagePci
                          ((int)(short)puVar11[1] << 1,PartPcs.m_usbStreamData.m_stageLoad,
                           s_pppPart_cpp_801d81f8,0x656);
        *(undefined4 *)(pppDataHead->m_shapeGroups + iVar12 + 4) = uVar3;
        *(int *)(puVar11 + 2) = (int)&pppDataHead->m_version + *(int *)(puVar11 + 2);
        memcpy(*(void **)(pppDataHead->m_shapeGroups + iVar12 + 4),*(undefined4 *)(puVar11 + 2),
               (int)(short)puVar11[1] << 1);
        iVar12 = iVar12 + 8;
        puVar11 = puVar11 + 4;
      }
      return;
    }
    uVar9 = 0;
    iVar5 = PartMng.m_usbEdit._0_4_;
    do {
      if ((*(char *)(iVar5 + 0x2a) != '\0') && (iVar2 = strcmp(iVar5 + 8,uVar7), iVar2 == 0))
      goto LAB_80054fb0;
      uVar9 = uVar9 + 1;
      iVar5 = iVar5 + 0x2c;
    } while (uVar9 < 0x100);
    iVar5 = 0;
LAB_80054fb0:
    uVar7 = uVar7 + 0x20;
    iVar6 = iVar6 + 1;
    *(int *)(pppDataHead->m_shapeNames + iVar12) = iVar5;
    iVar5 = *(int *)(pppDataHead->m_shapeNames + iVar12);
    iVar12 = iVar12 + 4;
    *(short *)(iVar5 + 0x28) = *(short *)(iVar5 + 0x28) + 1;
  } while( true );
}

