// Function: MakeArtItemName__5CGameFPcii
// Entry: 800141e0
// Size: 240 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 MakeArtItemName__5CGameFPcii(CGame *game,undefined4 param_2,int param_3,int param_4)

{
  uint8_t uVar1;
  bool bVar2;
  int iVar3;
  int32_t *piVar4;
  int32_t iVar5;
  undefined *puVar6;
  int32_t iVar7;
  
  if (param_4 < 2) {
    bVar2 = false;
    piVar4 = game->m_cFlatDataArr[1].m_table[0].index;
    iVar7 = piVar4[param_3 * 5];
    iVar5 = piVar4[param_3 * 5 + 1];
    iVar3 = strlen(iVar7);
    if (iVar3 != 0) {
      uVar1 = (game->m_gameWork).m_languageId;
      if ((uVar1 != '\x03') && (uVar1 != '\x04')) {
        bVar2 = true;
      }
    }
    puVar6 = &DAT_8032f674;
    if (bVar2) {
      puVar6 = &DAT_8032f670;
    }
    sprintf(param_2,&DAT_8032f678,iVar7,puVar6,iVar5);
  }
  else {
    if (param_4 < 2) {
      iVar5 = game->m_cFlatDataArr[1].m_table[0].index[param_3 * 5 + 1];
    }
    else {
      iVar5 = game->m_cFlatDataArr[1].m_table[0].index[param_3 * 5 + 3];
    }
    sprintf(param_2,s__d__s_8032f668,param_4,iVar5);
  }
  return param_2;
}

