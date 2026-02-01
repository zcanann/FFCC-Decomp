// Function: __dt__14CMapTexAnimSetFv
// Entry: 800335d0
// Size: 188 bytes

CRef * __dt__14CMapTexAnimSetFv(CRef *param_1,short param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  CRef *pCVar4;
  
  if (param_1 != (CRef *)0x0) {
    iVar3 = 0;
    param_1->vtable = &PTR_PTR_s_CMapTexAnimSet_801e896c;
    pCVar4 = param_1;
    while( true ) {
      if (*(short *)&param_1[1].vtable <= iVar3) break;
      piVar1 = (int *)pCVar4[1].refCount;
      if (piVar1 != (int *)0x0) {
        iVar2 = piVar1[1];
        piVar1[1] = iVar2 + -1;
        if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
          (**(code **)(*piVar1 + 8))(piVar1,1);
        }
        pCVar4[1].refCount = 0;
      }
      pCVar4 = (CRef *)&pCVar4->refCount;
      iVar3 = iVar3 + 1;
    }
    __dt__4CRefFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

