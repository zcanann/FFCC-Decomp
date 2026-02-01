// Function: Create__Q26CChara5CNodeFR10CChunkFilePQ26CChara6CModelQ36CChara5CNode4TYPEPQ27CMemory6CStage
// Entry: 8006fef0
// Size: 484 bytes

void Create__Q26CChara5CNodeFR10CChunkFilePQ26CChara6CModelQ36CChara5CNode4TYPEPQ27CMemory6CStage
               (CNode *node,CChunkFile *chunkFile,CModel *model,int nodeType,CStage *stage)

{
  float xS;
  uint16_t uVar3;
  uint8_t uVar4;
  undefined4 uVar1;
  CNodeCRefData *source;
  int iVar2;
  double dVar5;
  uint32_t local_28;
  
  node->m_refData = model->m_data->m_nodeRef + model->m_data->m_nodeCount;
  node->m_refData->m_index = (uint16_t)model->m_data->m_nodeCount;
  node->m_refData->m_type = (uint8_t)nodeType;
  node->m_refData->m_dynParamIndex = 0xff;
  node->m_refData->m_bindFlags = '\0';
  PushChunk__10CChunkFileFv(chunkFile);
  while (iVar2 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)&local_28), iVar2 != 0) {
    if (local_28 == 0x494e464f) {
      uVar3 = Get4__10CChunkFileFv(chunkFile);
      node->m_refData->m_parentIndex = uVar3;
      uVar4 = Get4__10CChunkFileFv(chunkFile);
      node->m_refData->m_childCount = uVar4;
      uVar3 = Get4__10CChunkFileFv(chunkFile);
      node->m_refData->m_childBankOffset = uVar3;
      uVar4 = Get4__10CChunkFileFv(chunkFile);
      node->m_refData->m_useParentLenX = uVar4;
    }
    else if (local_28 == 0x42494e46) {
      uVar4 = Get4__10CChunkFileFv(chunkFile);
      node->m_refData->m_bindFlags = uVar4;
      dVar5 = (double)GetF4__10CChunkFileFv(chunkFile);
      node->m_refData->m_boneLen = (float)dVar5;
    }
    else if (local_28 == 0x4e414d45) {
      uVar1 = GetString__10CChunkFileFv(chunkFile);
      strcpy(node->m_refData->m_name,uVar1);
    }
    else if (local_28 == 0x4e414d32) {
      uVar1 = GetString__10CChunkFileFv(chunkFile);
      strcpy(node->m_refData->m_name2,uVar1);
    }
    else if (local_28 == 0x5446524d) {
      Get__10CChunkFileFPvl(chunkFile,node->m_refData,0x30);
      source = node->m_refData;
      if (source->m_parentIndex == 0xffff) {
        xS = model->m_data->m_baseScale;
        PSMTXScaleApply(xS,xS,xS,&source->m_localMtx,&source->m_localMtx);
      }
    }
    else if (local_28 == 0x4d494458) {
      uVar4 = Get4__10CChunkFileFv(chunkFile);
      node->m_refData->m_displayIndex = uVar4;
    }
  }
  PopChunk__10CChunkFileFv(chunkFile);
  return;
}

