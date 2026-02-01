// Function: SingLifeInit__8CMenuPcsFi
// Entry: 80145710
// Size: 40 bytes

void SingLifeInit__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if ((0 < *(int *)&menuPcs->field_0x874) && (param_2 == 0)) {
    *(undefined4 *)&menuPcs->field_0x874 = 10;
    return;
  }
  *(int *)&menuPcs->field_0x874 = param_2;
  return;
}

