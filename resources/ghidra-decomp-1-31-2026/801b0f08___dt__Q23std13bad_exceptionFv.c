// Function: __dt__Q23std13bad_exceptionFv
// Entry: 801b0f08
// Size: 92 bytes

undefined4 * __dt__Q23std13bad_exceptionFv(undefined4 *param_1,short param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = &PTR_PTR_s_std_bad_exception_8021d148;
    if (param_1 != (undefined4 *)0x0) {
      *param_1 = &PTR_PTR_s_std_exception_8021d060;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

