// Function: GetModelNo__8CMenuPcsFiii
// Entry: 800f2018
// Size: 28 bytes

int GetModelNo__8CMenuPcsFiii(CMenuPcs *menuPcs,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = param_2 * 200 + 100;
  if (param_4 != 0) {
    iVar1 = param_2 * 200 + 200;
  }
  return iVar1 + param_3;
}

