// Function: MakeArtsItemNames__5CGameFPci
// Entry: 80014144
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 MakeArtsItemNames__5CGameFPci(CGame *game,undefined4 param_2,int param_3)

{
  uint8_t uVar1;
  bool bVar2;
  int32_t *piVar3;
  int iVar4;
  undefined *puVar5;
  int32_t iVar6;
  int32_t iVar7;
  
  bVar2 = false;
  piVar3 = game->m_cFlatDataArr[1].m_table[0].index;
  iVar7 = piVar3[param_3 * 5 + 2];
  iVar6 = piVar3[param_3 * 5 + 3];
  iVar4 = strlen(iVar7);
  if (iVar4 != 0) {
    uVar1 = (game->m_gameWork).m_languageId;
    if ((uVar1 != '\x03') && (uVar1 != '\x04')) {
      bVar2 = true;
    }
  }
  puVar5 = &DAT_8032f674;
  if (bVar2) {
    puVar5 = &DAT_8032f670;
  }
  sprintf(param_2,&DAT_8032f678,iVar7,puVar5,iVar6);
  return param_2;
}

