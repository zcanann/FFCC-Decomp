// Function: __dt__Q28CTexAnim8CRefDataFv
// Entry: 80043dec
// Size: 184 bytes

CTexAnimCRefData * __dt__Q28CTexAnim8CRefDataFv(CTexAnimCRefData *refData,short param_2)

{
  int *piVar1;
  int iVar2;
  
  if (refData != (CTexAnimCRefData *)0x0) {
    *(undefined ***)refData = &PTR_PTR_s_CTexAnim_CRefData_801e9c3c;
    piVar1 = *(int **)(refData + 0x108);
    if (piVar1 != (int *)0x0) {
      iVar2 = piVar1[1];
      piVar1[1] = iVar2 + -1;
      if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)(refData + 0x108) = 0;
    }
    ReleaseAndRemoveAll__25CPtrArray<P11CTexAnimSeq>Fv((CPtrArray *)(refData + 0x110));
    __dt__25CPtrArray<P11CTexAnimSeq>Fv((CPtrArray *)(refData + 0x110),0xffff);
    __dt__4CRefFv((CRef *)refData,0);
    if (0 < param_2) {
      __dl__FPv(refData);
    }
  }
  return refData;
}

