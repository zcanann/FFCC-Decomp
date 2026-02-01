// Function: __dt__8CMonWorkFv
// Entry: 8009e9b4
// Size: 92 bytes

CMonWork * __dt__8CMonWorkFv(CMonWork *monWork,short param_2)

{
  if (monWork != (CMonWork *)0x0) {
    (monWork->gObjWork).vtable = &PTR_PTR_s_CMonWork_8020fa0c;
    if (monWork != (CMonWork *)0x0) {
      (monWork->gObjWork).vtable = &PTR_PTR_s_CGObjWork_8020faa8;
    }
    if (0 < param_2) {
      __dl__FPv(monWork);
    }
  }
  return monWork;
}

