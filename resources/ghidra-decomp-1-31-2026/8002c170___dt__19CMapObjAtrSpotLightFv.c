// Function: __dt__19CMapObjAtrSpotLightFv
// Entry: 8002c170
// Size: 316 bytes

undefined4 * __dt__19CMapObjAtrSpotLightFv(undefined4 *param_1,short param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = &PTR_PTR_s_CMapObjAtrSpotLight_801e8914;
    if (param_1 != (undefined4 *)0xffffff18) {
      if (param_1[0x40] != 0) {
        __dl__FPv();
        param_1[0x40] = 0;
      }
      if (param_1[0x41] != 0) {
        __dl__FPv();
        param_1[0x41] = 0;
      }
      if (param_1[0x42] != 0) {
        __dl__FPv();
        param_1[0x42] = 0;
      }
      if (param_1[0x43] != 0) {
        __dl__FPv();
        param_1[0x43] = 0;
      }
    }
    if (param_1 != (undefined4 *)0xffffff40) {
      if (param_1[0x36] != 0) {
        __dl__FPv();
        param_1[0x36] = 0;
      }
      if (param_1[0x37] != 0) {
        __dl__FPv();
        param_1[0x37] = 0;
      }
      if (param_1[0x38] != 0) {
        __dl__FPv();
        param_1[0x38] = 0;
      }
      if (param_1[0x39] != 0) {
        __dl__FPv();
        param_1[0x39] = 0;
      }
    }
    if (param_1 != (undefined4 *)0x0) {
      *param_1 = &PTR_PTR_s_CMapObjAtr_801e8950;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

