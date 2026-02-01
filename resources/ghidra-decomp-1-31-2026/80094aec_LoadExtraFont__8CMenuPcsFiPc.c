// Function: LoadExtraFont__8CMenuPcsFiPc
// Entry: 80094aec
// Size: 208 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadExtraFont__8CMenuPcsFiPc(CMenuPcs *menuPcs,int param_2,undefined4 param_3)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  undefined auStack_118 [264];
  
  piVar1 = *(int **)(&menuPcs->field_0x100 + param_2 * 4);
  if (piVar1 != (int *)0x0) {
    iVar3 = piVar1[1];
    piVar1[1] = iVar3 + -1;
    if ((iVar3 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)(&menuPcs->field_0x100 + param_2 * 4) = 0;
  }
  pcVar2 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_118,s_dvd__smenu__s_fnt_801d9da0,pcVar2,param_3);
  loadFont__8CMenuPcsFiPcii(menuPcs,2,auStack_118,param_2 + 2,0xffffffff);
  return;
}

