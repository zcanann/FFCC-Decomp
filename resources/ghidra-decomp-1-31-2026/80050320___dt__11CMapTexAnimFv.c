// Function: __dt__11CMapTexAnimFv
// Entry: 80050320
// Size: 220 bytes

CRef * __dt__11CMapTexAnimFv(CRef *param_1,short param_2)

{
  if (param_1 != (CRef *)0x0) {
    param_1->vtable = &PTR_PTR_s_CMapTexAnim_801ea9a4;
    __dl__FPv(param_1[4].vtable);
    param_1[4].vtable = (void *)0x0;
    if (param_1 != (CRef *)0xffffffdc) {
      if (param_1[7].refCount != 0) {
        __dl__FPv();
        param_1[7].refCount = 0;
      }
      if (param_1[8].vtable != (void *)0x0) {
        __dl__FPv();
        param_1[8].vtable = (void *)0x0;
      }
      if (param_1[8].refCount != 0) {
        __dl__FPv();
        param_1[8].refCount = 0;
      }
      if (param_1[9].vtable != (void *)0x0) {
        __dl__FPv();
        param_1[9].vtable = (void *)0x0;
      }
    }
    __dt__4CRefFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

