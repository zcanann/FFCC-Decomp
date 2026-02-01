// Function: __dt__12CFlatRuntimeFv
// Entry: 80069a2c
// Size: 104 bytes

CFlatRuntime * __dt__12CFlatRuntimeFv(CFlatRuntime *flatRuntime,short param_2)

{
  if (flatRuntime != (CFlatRuntime *)0x0) {
    flatRuntime->vtable = &PTR_PTR_s_CFlatRuntime_801fc9f0;
    (**(code **)((int)flatRuntime->vtable + 0x10))();
    if (0 < param_2) {
      __dl__FPv(flatRuntime);
    }
  }
  return flatRuntime;
}

