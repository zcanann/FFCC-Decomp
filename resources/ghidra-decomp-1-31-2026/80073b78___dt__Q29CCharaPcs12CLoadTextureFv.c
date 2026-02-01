// Function: __dt__Q29CCharaPcs12CLoadTextureFv
// Entry: 80073b78
// Size: 164 bytes

CRef * __dt__Q29CCharaPcs12CLoadTextureFv(CRef *param_1,short param_2)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 != (CRef *)0x0) {
    param_1->vtable = &PTR_PTR_s_CCharaPcs_CLoadTexture_801fd290;
    piVar1 = (int *)param_1[3].refCount;
    if (piVar1 != (int *)0x0) {
      iVar2 = piVar1[1];
      piVar1[1] = iVar2 + -1;
      if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      param_1[3].refCount = 0;
    }
    __dt__4CRefFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

