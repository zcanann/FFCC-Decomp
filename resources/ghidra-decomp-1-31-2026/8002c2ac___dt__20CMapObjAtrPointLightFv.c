// Function: __dt__20CMapObjAtrPointLightFv
// Entry: 8002c2ac
// Size: 316 bytes

undefined4 * __dt__20CMapObjAtrPointLightFv(undefined4 *param_1,short param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = &PTR_PTR_s_CMapObjAtrPointLight_801e892c;
    if (param_1 != (undefined4 *)0xffffff34) {
      if (param_1[0x39] != 0) {
        __dl__FPv();
        param_1[0x39] = 0;
      }
      if (param_1[0x3a] != 0) {
        __dl__FPv();
        param_1[0x3a] = 0;
      }
      if (param_1[0x3b] != 0) {
        __dl__FPv();
        param_1[0x3b] = 0;
      }
      if (param_1[0x3c] != 0) {
        __dl__FPv();
        param_1[0x3c] = 0;
      }
    }
    if (param_1 != (undefined4 *)0xffffff5c) {
      if (param_1[0x2f] != 0) {
        __dl__FPv();
        param_1[0x2f] = 0;
      }
      if (param_1[0x30] != 0) {
        __dl__FPv();
        param_1[0x30] = 0;
      }
      if (param_1[0x31] != 0) {
        __dl__FPv();
        param_1[0x31] = 0;
      }
      if (param_1[0x32] != 0) {
        __dl__FPv();
        param_1[0x32] = 0;
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

