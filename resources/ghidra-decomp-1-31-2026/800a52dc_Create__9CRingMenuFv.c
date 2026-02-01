// Function: Create__9CRingMenuFv
// Entry: 800a52dc
// Size: 116 bytes

CRingMenu * Create__9CRingMenuFv(CRingMenu *ringMenu,short param_2)

{
  if (ringMenu != (CRingMenu *)0x0) {
    (ringMenu->menuBase).ref.vtable = &vtable_CRingMenu;
    (**(code **)((int)(ringMenu->menuBase).ref.vtable + 0x10))();
    __dt__5CMenuFv(&ringMenu->menuBase,0);
    if (0 < param_2) {
      __dl__FPv(ringMenu);
    }
  }
  return ringMenu;
}

