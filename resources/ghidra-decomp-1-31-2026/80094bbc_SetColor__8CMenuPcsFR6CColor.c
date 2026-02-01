// Function: SetColor__8CMenuPcsFR6CColor
// Entry: 80094bbc
// Size: 48 bytes

void SetColor__8CMenuPcsFR6CColor(CMenuPcs *menuPcs,undefined4 *param_2)

{
  undefined4 local_8 [2];
  
  local_8[0] = *param_2;
  GXSetChanMatColor(4,local_8);
  return;
}

