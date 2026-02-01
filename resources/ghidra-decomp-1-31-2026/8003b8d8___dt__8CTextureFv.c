// Function: __dt__8CTextureFv
// Entry: 8003b8d8
// Size: 176 bytes

CTexture * __dt__8CTextureFv(CTexture *texture,short param_2)

{
  if (texture != (CTexture *)0x0) {
    texture->vtable = &PTR_PTR_s_CTexture_801e9b78;
    if (texture->field_0x75 == '\0') {
      if ((void *)texture->field105_0x78 != (void *)0x0) {
        __dla__FPv((void *)texture->field105_0x78);
        texture->field105_0x78 = 0;
      }
      if (*(void **)&texture->field_0x7c != (void *)0x0) {
        __dla__FPv(*(void **)&texture->field_0x7c);
        *(undefined4 *)&texture->field_0x7c = 0;
      }
    }
    else {
      texture->field105_0x78 = 0;
      *(undefined4 *)&texture->field_0x7c = 0;
    }
    __dt__4CRefFv((CRef *)texture,0);
    if (0 < param_2) {
      __dl__FPv(texture);
    }
  }
  return texture;
}

