// Function: __dt__8CMesMenuFv
// Entry: 8009e0fc
// Size: 128 bytes

CMenu * __dt__8CMesMenuFv(CMenu *param_1,short param_2)

{
  if (param_1 != (CMenu *)0x0) {
    (param_1->ref).vtable = &PTR_PTR_s_CMesMenu_8020f9d8;
    (**(code **)((int)(param_1->ref).vtable + 0x10))();
    __dt__4CMesFv(&param_1[3].ref.refCount,0xffffffff);
    __dt__5CMenuFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

