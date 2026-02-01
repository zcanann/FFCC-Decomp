// Function: __dt__12CCaravanWorkFv
// Entry: 800a2b9c
// Size: 92 bytes

CCaravanWork * __dt__12CCaravanWorkFv(CCaravanWork *caravanWork,short param_2)

{
  if (caravanWork != (CCaravanWork *)0x0) {
    (caravanWork->gObjWork).vtable = &PTR_PTR_s_CCaravanWork_8020fa98;
    if (caravanWork != (CCaravanWork *)0x0) {
      (caravanWork->gObjWork).vtable = &PTR_PTR_s_CGObjWork_8020faa8;
    }
    if (0 < param_2) {
      __dl__FPv(caravanWork);
    }
  }
  return caravanWork;
}

