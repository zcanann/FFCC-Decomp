// Function: CalcHeart__8CMesMenuFv
// Entry: 8009bcec
// Size: 496 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcHeart__8CMesMenuFv(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint32_t uVar4;
  
  uVar4 = Game.game.m_scriptFoodBase[*(int *)(param_1 + 0x18)];
  if (uVar4 == 0) {
    return;
  }
  uVar1 = (uint)*(ushort *)(uVar4 + 0x1c);
  iVar2 = uVar1 * 6;
  if (*(int *)(param_1 + 0x3dac) < iVar2) {
    *(int *)(param_1 + 0x3dac) = iVar2;
  }
  else if (iVar2 < *(int *)(param_1 + 0x3dac)) {
    *(uint *)(param_1 + 0x3dac) = uVar1 * 6;
  }
  iVar2 = *(int *)(param_1 + 0x3da8);
  if (iVar2 < *(int *)(param_1 + 0x3dac)) {
    iVar2 = iVar2 / 0xc + (iVar2 >> 0x1f);
    iVar2 = param_1 + (iVar2 - (iVar2 >> 0x1f)) * 4;
    if (*(int *)(iVar2 + 0x3db0) == 0) {
      *(undefined4 *)(iVar2 + 0x3db0) = 0x10;
    }
    iVar3 = *(int *)(param_1 + 0x3da8) + 2;
    iVar2 = *(int *)(param_1 + 0x3dac);
    if (iVar3 < *(int *)(param_1 + 0x3dac)) {
      iVar2 = iVar3;
    }
    *(int *)(param_1 + 0x3da8) = iVar2;
  }
  else if (*(int *)(param_1 + 0x3dac) < iVar2) {
    *(uint *)(param_1 + 0x3da8) = iVar2 - 2U & ~((int)(iVar2 - 2U) >> 0x1f);
    iVar2 = *(int *)(param_1 + 0x3da8) / 0xc + (*(int *)(param_1 + 0x3da8) >> 0x1f);
    iVar2 = param_1 + (iVar2 - (iVar2 >> 0x1f)) * 4;
    if (*(int *)(iVar2 + 0x3dd0) == 0) {
      *(undefined4 *)(iVar2 + 0x3dd0) = 0x10;
    }
    if (*(int *)(param_1 + 0x3df0) == 0) {
      *(undefined4 *)(param_1 + 0x3df0) = 0x10;
    }
  }
  iVar3 = 2;
  iVar2 = param_1;
  do {
    uVar1 = *(int *)(iVar2 + 0x3db0) - 1;
    *(uint *)(iVar2 + 0x3db0) = uVar1 & ~((int)uVar1 >> 0x1f);
    uVar1 = *(int *)(iVar2 + 0x3dd0) - 1;
    *(uint *)(iVar2 + 0x3dd0) = uVar1 & ~((int)uVar1 >> 0x1f);
    uVar1 = *(int *)(iVar2 + 0x3db4) - 1;
    *(uint *)(iVar2 + 0x3db4) = uVar1 & ~((int)uVar1 >> 0x1f);
    uVar1 = *(int *)(iVar2 + 0x3dd4) - 1;
    *(uint *)(iVar2 + 0x3dd4) = uVar1 & ~((int)uVar1 >> 0x1f);
    uVar1 = *(int *)(iVar2 + 0x3db8) - 1;
    *(uint *)(iVar2 + 0x3db8) = uVar1 & ~((int)uVar1 >> 0x1f);
    uVar1 = *(int *)(iVar2 + 0x3dd8) - 1;
    *(uint *)(iVar2 + 0x3dd8) = uVar1 & ~((int)uVar1 >> 0x1f);
    uVar1 = *(int *)(iVar2 + 0x3dbc) - 1;
    *(uint *)(iVar2 + 0x3dbc) = uVar1 & ~((int)uVar1 >> 0x1f);
    uVar1 = *(int *)(iVar2 + 0x3ddc) - 1;
    *(uint *)(iVar2 + 0x3ddc) = uVar1 & ~((int)uVar1 >> 0x1f);
    iVar2 = iVar2 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar1 = *(int *)(param_1 + 0x3df0) - 1;
  *(uint *)(param_1 + 0x3df0) = uVar1 & ~((int)uVar1 >> 0x1f);
  return;
}

