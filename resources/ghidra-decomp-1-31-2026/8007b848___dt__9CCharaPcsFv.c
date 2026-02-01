// Function: __dt__9CCharaPcsFv
// Entry: 8007b848
// Size: 136 bytes

undefined4 * __dt__9CCharaPcsFv(undefined4 *param_1,short param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = &PTR_PTR_s_CCharaPcs_801fd2ec;
    __dt__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv((CPtrArray *)(param_1 + 0x29),0xffff);
    __dt__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv((CPtrArray *)(param_1 + 0x22),0xffff);
    __dt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)(param_1 + 0x1b),0xffff);
    __dt__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv((CPtrArray *)(param_1 + 0x14),0xffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

