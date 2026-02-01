// Function: __ct__8CMesMenuFv
// Entry: 8009e17c
// Size: 68 bytes

CMenu * __ct__8CMesMenuFv(CMenu *param_1)

{
  __ct__5CMenuFv(param_1);
  (param_1->ref).vtable = &PTR_PTR_s_CMesMenu_8020f9d8;
  __ct__4CMesFv(&param_1[3].ref.refCount);
  return param_1;
}

