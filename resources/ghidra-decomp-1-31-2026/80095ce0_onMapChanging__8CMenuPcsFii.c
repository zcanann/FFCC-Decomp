// Function: onMapChanging__8CMenuPcsFii
// Entry: 80095ce0
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onMapChanging__8CMenuPcsFii(CMenuPcs *menuPcs,int param_2)

{
  if (((param_2 == 0x21) && (Game.game.m_currentMapId != 0x21)) ||
     ((param_2 != 0x21 && (Game.game.m_currentMapId == 0x21)))) {
    changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(menuPcs,0xffffffff);
  }
  return;
}

