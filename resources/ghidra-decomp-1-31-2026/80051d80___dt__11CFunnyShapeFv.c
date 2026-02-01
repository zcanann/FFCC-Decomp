// Function: __dt__11CFunnyShapeFv
// Entry: 80051d80
// Size: 204 bytes

CFunnyShape * __dt__11CFunnyShapeFv(CFunnyShape *funnyShape,short param_2)

{
  int iVar1;
  CFunnyShape *pCVar2;
  
  if (funnyShape != (CFunnyShape *)0x0) {
    if (*(void **)&funnyShape->field_0x6010 != (void *)0x0) {
      __dla__FPv(*(void **)&funnyShape->field_0x6010);
      *(undefined4 *)&funnyShape->field_0x6010 = 0;
    }
    if (*(void **)(funnyShape->UnkBuff2 + 0xc) != (void *)0x0) {
      __dla__FPv(*(void **)(funnyShape->UnkBuff2 + 0xc));
      funnyShape->UnkBuff2[0xc] = '\0';
      funnyShape->UnkBuff2[0xd] = '\0';
      funnyShape->UnkBuff2[0xe] = '\0';
      funnyShape->UnkBuff2[0xf] = '\0';
    }
    iVar1 = 0;
    pCVar2 = funnyShape;
    do {
      if (*(void **)&pCVar2->field_0x6094 != (void *)0x0) {
        __dla__FPv(*(void **)&pCVar2->field_0x6094);
        *(undefined4 *)&pCVar2->field_0x6094 = 0;
      }
      if (*(int *)&pCVar2->field_0x6014 != 0) {
        __dl__FPv();
        *(undefined4 *)&pCVar2->field_0x6014 = 0;
      }
      if (*(int *)&pCVar2->field_0x6054 != 0) {
        __dl__FPv();
        *(undefined4 *)&pCVar2->field_0x6054 = 0;
      }
      iVar1 = iVar1 + 1;
      pCVar2 = (CFunnyShape *)(pCVar2->m_maybeTexture + 4);
    } while (iVar1 < 0x10);
    if (0 < param_2) {
      __dl__FPv(funnyShape);
    }
  }
  return funnyShape;
}

