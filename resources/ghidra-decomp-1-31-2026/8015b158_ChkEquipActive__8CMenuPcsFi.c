// Function: ChkEquipActive__8CMenuPcsFi
// Entry: 8015b158
// Size: 268 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint ChkEquipActive__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  uint32_t uVar1;
  short *psVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = Game.game.m_scriptFoodBase[0];
  psVar2 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
  iVar4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
  if ((param_2 < 0) || (*psVar2 <= param_2)) {
    uVar3 = 0;
  }
  else if (param_2 == 0) {
    if (iVar4 < 3) {
      uVar3 = 0;
    }
    else {
      uVar3 = (uint)(int)*(short *)(uVar1 + iVar4 * 2 + 0xac) >> 0x1f ^ 1;
    }
  }
  else {
    iVar5 = (int)*(short *)(uVar1 + psVar2[param_2] * 2 + 0xb6);
    uVar3 = ChkEquipPossible__8CMenuPcsFi(menuPcs,iVar5);
    if (((uVar3 & 0xff) != 0) && (iVar5 = GetEquipType__8CMenuPcsFi(menuPcs,iVar5), iVar5 != iVar4))
    {
      uVar3 = 0;
    }
  }
  return uVar3;
}

