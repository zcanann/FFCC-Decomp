// Function: __dt__13CFlatRuntime2Fv
// Entry: 8006e0b0
// Size: 124 bytes

CFlatRuntime2 * __dt__13CFlatRuntime2Fv(CFlatRuntime2 *flatRuntime2,short param_2)

{
  if (flatRuntime2 != (CFlatRuntime2 *)0x0) {
    (flatRuntime2->flatRuntimeBase).vtable = &PTR_PTR_s_CFlatRuntime2_801fcc14;
    AfterFrame__12CFlatRuntimeFi(&flatRuntime2->flatRuntimeBase,1);
    __dt__9CFlatDataFv((CFlatData *)&flatRuntime2->field_0xcf20,0xffff);
    __dt__12CFlatRuntimeFv(&flatRuntime2->flatRuntimeBase,0);
    if (0 < param_2) {
      __dl__FPv(flatRuntime2);
    }
  }
  return flatRuntime2;
}

