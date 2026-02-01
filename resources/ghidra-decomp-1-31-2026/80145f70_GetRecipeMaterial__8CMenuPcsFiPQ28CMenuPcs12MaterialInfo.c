// Function: GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo
// Entry: 80145f70
// Size: 132 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo
               (CMenuPcs *menuPcs,int param_2,undefined2 *param_3)

{
  int iVar1;
  
  GetItemType__8CMenuPcsFii(menuPcs,param_2,1);
  iVar1 = Game.game.unkCFlatData0[2] + param_2 * 0x48;
  *param_3 = *(undefined2 *)(iVar1 + 0x26);
  param_3[3] = *(undefined2 *)(iVar1 + 0x2c);
  param_3[1] = *(undefined2 *)(iVar1 + 0x28);
  param_3[4] = *(undefined2 *)(iVar1 + 0x2e);
  param_3[2] = *(undefined2 *)(iVar1 + 0x2a);
  param_3[5] = *(undefined2 *)(iVar1 + 0x30);
  return;
}

