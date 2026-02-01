// Function: __dt__Q26CChara5CAnimFv
// Entry: 800bfd44
// Size: 156 bytes

CRef * __dt__Q26CChara5CAnimFv(CRef *param_1,short param_2)

{
  if (param_1 != (CRef *)0x0) {
    param_1->vtable = &PTR_PTR_s_CChara_CAnim_80210534;
    if (param_1[2].refCount != 0) {
      __destroy_new_array(param_1[2].refCount,__dt__Q26CChara9CAnimNodeFv);
      param_1[2].refCount = 0;
    }
    if (param_1[4].vtable != (void *)0x0) {
      __dla__FPv(param_1[4].vtable);
      param_1[4].vtable = (void *)0x0;
    }
    __dt__4CRefFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

