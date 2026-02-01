// Function: __dt__9CMaterialFv
// Entry: 8003dc38
// Size: 220 bytes

CMaterial * __dt__9CMaterialFv(CMaterial *material,short param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  CMaterial *pCVar4;
  
  if (material != (CMaterial *)0x0) {
    iVar3 = 0;
    material->vtable = &PTR_PTR_s_CMaterial_801e9bd4;
    pCVar4 = material;
    while( true ) {
      if ((int)(uint)*(ushort *)&material->field_0x18 <= iVar3) break;
      piVar1 = (int *)pCVar4->field42_0x3c;
      if (piVar1 != (int *)0x0) {
        iVar2 = piVar1[1];
        piVar1[1] = iVar2 + -1;
        if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
          (**(code **)(*piVar1 + 8))(piVar1,1);
        }
        pCVar4->field42_0x3c = 0;
      }
      pCVar4 = (CMaterial *)&pCVar4->field_0x4;
      iVar3 = iVar3 + 1;
    }
    if (material != (CMaterial *)0xffffffc4) {
      __destroy_arr(&material->field_0x4c,__dt__10CTexScrollFv,0x14,4);
    }
    __dt__4CRefFv((CRef *)material,0);
    if (0 < param_2) {
      __dl__FPv(material);
    }
  }
  return material;
}

