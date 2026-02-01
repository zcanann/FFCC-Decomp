// Function: __dt__5CMenuFv
// Entry: 8009b448
// Size: 96 bytes

CMenu * __dt__5CMenuFv(CMenu *menu,short param_2)

{
  if (menu != (CMenu *)0x0) {
    (menu->ref).vtable = &PTR_PTR_s_CMenu_8020f974;
    __dt__4CRefFv(&menu->ref,0);
    if (0 < param_2) {
      __dl__FPv(menu);
    }
  }
  return menu;
}

