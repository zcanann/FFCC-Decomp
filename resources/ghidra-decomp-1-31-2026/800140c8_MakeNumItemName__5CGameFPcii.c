// Function: MakeNumItemName__5CGameFPcii
// Entry: 800140c8
// Size: 124 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 MakeNumItemName__5CGameFPcii(CGame *game,undefined4 param_2,int param_3,int param_4)

{
  int32_t iVar1;
  
  if (param_4 < 2) {
    iVar1 = game->m_cFlatDataArr[1].m_table[0].index[param_3 * 5 + 1];
  }
  else {
    iVar1 = game->m_cFlatDataArr[1].m_table[0].index[param_3 * 5 + 3];
  }
  sprintf(param_2,s__d__s_8032f668,param_4,iVar1);
  return param_2;
}

