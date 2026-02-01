// Function: __dt__14CMapObjAtrMimeFv
// Entry: 8002c04c
// Size: 292 bytes

undefined4 * __dt__14CMapObjAtrMimeFv(undefined4 *param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    iVar2 = 0;
    *param_1 = &PTR_PTR_s_CMapObjAtrMime_801e88fc;
    for (iVar1 = 0; iVar1 < (int)(uint)*(byte *)(param_1 + 2); iVar1 = iVar1 + 1) {
      if (*(int *)(param_1[3] + iVar2) != 0) {
        __dl__FPv();
        *(undefined4 *)(param_1[3] + iVar2) = 0;
      }
      iVar2 = iVar2 + 4;
    }
    if (param_1[3] != 0) {
      __dl__FPv();
      param_1[3] = 0;
    }
    if (param_1 != (undefined4 *)0xffffffec) {
      if (param_1[0xb] != 0) {
        __dl__FPv();
        param_1[0xb] = 0;
      }
      if (param_1[0xc] != 0) {
        __dl__FPv();
        param_1[0xc] = 0;
      }
      if (param_1[0xd] != 0) {
        __dl__FPv();
        param_1[0xd] = 0;
      }
      if (param_1[0xe] != 0) {
        __dl__FPv();
        param_1[0xe] = 0;
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

