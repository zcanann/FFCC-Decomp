// Function: ?GetWeaponAttrib__12CCaravanWorkFi
// Entry: 8009f6ac
// Size: 132 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int32_t _GetWeaponAttrib__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  int iVar1;
  int32_t iVar2;
  
  iVar1 = _GetCmdListItem__12CCaravanWorkFi(caravanWork,param_2);
  if ((iVar1 < 0) || (2 < iVar1)) {
    iVar1 = _DelCmdListAndItem__12CCaravanWorkFii(caravanWork,param_2);
    iVar2 = Game.game.m_cFlatDataArr[1].m_table[0].index[iVar1 * 5 + 4];
  }
  else {
    iVar2 = GetSkillStr__8CMenuPcsFi(&MenuPcs,iVar1);
  }
  return iVar2;
}

