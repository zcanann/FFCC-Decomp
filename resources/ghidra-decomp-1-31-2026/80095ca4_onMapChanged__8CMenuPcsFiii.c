// Function: onMapChanged__8CMenuPcsFiii
// Entry: 80095ca4
// Size: 60 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onMapChanged__8CMenuPcsFiii(CMenuPcs *menuPcs)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(0x21 - Game.game.m_currentMapId);
  changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(menuPcs,uVar1 >> 5);
  return;
}

