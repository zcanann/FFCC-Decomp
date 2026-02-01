// Function: __dt__11CTexAnimSeqFv
// Entry: 80043d70
// Size: 124 bytes

CRef * __dt__11CTexAnimSeqFv(CRef *param_1,short param_2)

{
  if (param_1 != (CRef *)0x0) {
    param_1->vtable = &PTR_PTR_s_CTexAnimSeq_801e9c24;
    if ((void *)param_1[0x22].refCount != (void *)0x0) {
      __dla__FPv((void *)param_1[0x22].refCount);
      param_1[0x22].refCount = 0;
    }
    __dt__4CRefFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

