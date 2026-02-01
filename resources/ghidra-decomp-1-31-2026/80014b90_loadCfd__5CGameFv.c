// Function: loadCfd__5CGameFv
// Entry: 80014b90
// Size: 364 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadCfd__5CGameFv(CGame *game)

{
  CFileCHandle *fileHandle;
  int iVar1;
  CGame *pCVar2;
  undefined **ppuVar3;
  undefined *local_148 [4];
  undefined *local_138;
  undefined *local_134;
  undefined auStack_130 [268];
  
  ppuVar3 = &PTR_s_dvd__scft_param_cfd_801e8344;
  iVar1 = 0;
  pCVar2 = game;
  do {
    local_148[0] = PTR_DAT_801d60b0;
    local_148[1] = PTR_DAT_801d60b4;
    local_148[2] = PTR_DAT_801d60b8;
    local_148[3] = PTR_DAT_801d60bc;
    local_138 = PTR_DAT_801d60c0;
    local_134 = PTR_DAT_801d60c4;
    sprintf(auStack_130,*ppuVar3,local_148[Game.game.m_gameWork.m_languageId]);
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_130,0,0);
    if (fileHandle != (CFileCHandle *)0x0) {
      Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      Create__9CFlatDataFPv(pCVar2->m_cFlatDataArr,File.m_readBuffer);
      Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    }
    iVar1 = iVar1 + 1;
    pCVar2 = (CGame *)(pCVar2->m_caravanWorkArr[0].m_inventoryItems + 0x17);
    ppuVar3 = ppuVar3 + 1;
  } while (iVar1 < 4);
  game->unkCFlatData0[0] = (uint32_t)game->m_cFlatDataArr[0].m_data[0].m_data;
  game->unkCFlatData0[1] = (uint32_t)game->m_cFlatDataArr[0].m_data[1].m_data;
  game->unkCFlatData0[2] = (uint32_t)game->m_cFlatDataArr[0].m_data[2].m_data;
  game->unkCFlatData0[3] = (uint32_t)game->m_cFlatDataArr[2].m_data[0].m_data;
  game->unk_flat3_field_8_0xc7dc = (uint32_t)game->m_cFlatDataArr[3].m_data[0].m_data;
  game->unk_flat3_field_1C_0xc7d8 = (uint32_t)game->m_cFlatDataArr[3].m_data[1].m_data;
  game->unk_flat3_count_0xc7d4 = game->m_cFlatDataArr[3].m_data[1].m_size / 0x1a;
  game->unk_flat3_field_30_0xc7e0 = (uint32_t)game->m_cFlatDataArr[3].m_data[2].m_data;
  game->m_bossArtifactBase = (uint32_t)game->m_cFlatDataArr[3].m_data[3].m_data;
  return;
}

