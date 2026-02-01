// Function: ClearTextureData__11CFunnyShapeFv
// Entry: 80051020
// Size: 144 bytes

void ClearTextureData__11CFunnyShapeFv(CFunnyShape *funnyShape)

{
  int iVar1;
  
  iVar1 = 0;
  funnyShape->field_0x60d4 = 0;
  do {
    if (*(void **)&funnyShape->field_0x6094 != (void *)0x0) {
      __dla__FPv(*(void **)&funnyShape->field_0x6094);
      *(undefined4 *)&funnyShape->field_0x6094 = 0;
    }
    if (*(int *)&funnyShape->field_0x6014 != 0) {
      __dl__FPv();
      *(undefined4 *)&funnyShape->field_0x6014 = 0;
    }
    if (*(int *)&funnyShape->field_0x6054 != 0) {
      __dl__FPv();
      *(undefined4 *)&funnyShape->field_0x6054 = 0;
    }
    iVar1 = iVar1 + 1;
    funnyShape = (CFunnyShape *)(funnyShape->m_maybeTexture + 4);
  } while (iVar1 < 0x10);
  return;
}

