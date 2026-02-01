// Function: GetSmithItem__8CMenuPcsFi
// Entry: 80145ff4
// Size: 412 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint GetSmithItem__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  uint32_t uVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  uVar3 = Game.game.m_scriptFoodBase[0];
  GetItemType__8CMenuPcsFii(menuPcs,param_2,1);
  uVar1 = *(ushort *)(uVar3 + 0x3e0);
  uVar4 = uVar1 & 3;
  iVar6 = Game.game.unkCFlatData0[2] + param_2 * 0x48;
  uVar5 = (uint)*(ushort *)(iVar6 + (uVar1 & 3) * 2 + 0x38);
  if (uVar5 != 0) {
    uVar8 = 0x10;
    uVar2 = *(ushort *)(Game.game.unkCFlatData0[2] + uVar5 * 0x48 + 4);
    uVar7 = 1 << (*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e0) & 3);
    if (*(short *)(Game.game.m_scriptFoodBase[0] + 0x3e2) != 0) {
      uVar8 = 0x20;
    }
    if (((uVar2 & 0xf) == 0) || ((uVar2 & 0x30) == 0)) {
      if ((uVar2 & 0xf) == 0) {
        uVar7 = -(uVar2 & 0x30 & uVar8) >> 0x1f;
      }
      else {
        uVar7 = -(uVar2 & 0xf & uVar7) >> 0x1f;
      }
    }
    else if (((uVar2 & 0xf & uVar7) == 0) || ((uVar2 & 0x30 & uVar8) == 0)) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
    }
    if (uVar7 != 0) {
      return uVar5;
    }
  }
  if ((((((uVar1 & 3) == 0) || (uVar5 = (uint)*(ushort *)(iVar6 + 0x38), uVar5 == 0)) &&
       ((uVar4 == 1 || (uVar5 = (uint)*(ushort *)(iVar6 + 0x3a), uVar5 == 0)))) &&
      ((uVar4 == 2 || (uVar5 = (uint)*(ushort *)(iVar6 + 0x3c), uVar5 == 0)))) &&
     ((uVar4 == 3 || (uVar5 = (uint)*(ushort *)(iVar6 + 0x3e), uVar5 == 0)))) {
    uVar5 = 0xffffffff;
  }
  return uVar5;
}

