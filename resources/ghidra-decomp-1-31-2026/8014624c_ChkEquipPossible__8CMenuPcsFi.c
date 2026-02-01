// Function: ChkEquipPossible__8CMenuPcsFi
// Entry: 8014624c
// Size: 192 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint ChkEquipPossible__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0x10;
  uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + param_2 * 0x48 + 4);
  uVar2 = 1 << (*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e0) & 3);
  if (*(short *)(Game.game.m_scriptFoodBase[0] + 0x3e2) != 0) {
    uVar3 = 0x20;
  }
  if ((uVar1 & 0xf) != 0) {
    if ((uVar1 & 0x30) != 0) {
      if (((uVar1 & 0xf & uVar2) == 0) || ((uVar1 & 0x30 & uVar3) == 0)) {
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
      goto LAB_801462fc;
    }
  }
  if ((uVar1 & 0xf) == 0) {
    uVar2 = -(uVar1 & 0x30 & uVar3) >> 0x1f;
  }
  else {
    uVar2 = -(uVar1 & 0xf & uVar2) >> 0x1f;
  }
LAB_801462fc:
  return -uVar2 >> 0x1f;
}

