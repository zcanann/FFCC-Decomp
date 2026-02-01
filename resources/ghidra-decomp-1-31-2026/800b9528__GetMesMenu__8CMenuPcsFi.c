// Function: ?GetMesMenu__8CMenuPcsFi
// Entry: 800b9528
// Size: 16 bytes

undefined4 _GetMesMenu__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  return *(undefined4 *)(&menuPcs->field_0x10c + param_2 * 4);
}

