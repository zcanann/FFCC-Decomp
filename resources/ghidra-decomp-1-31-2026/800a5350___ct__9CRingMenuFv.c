// Function: __ct__9CRingMenuFv
// Entry: 800a5350
// Size: 60 bytes

CRingMenu * __ct__9CRingMenuFv(CRingMenu *ringMenu)

{
  __ct__5CMenuFv(&ringMenu->menuBase);
  (ringMenu->menuBase).ref.vtable = &vtable_CRingMenu;
  return ringMenu;
}

