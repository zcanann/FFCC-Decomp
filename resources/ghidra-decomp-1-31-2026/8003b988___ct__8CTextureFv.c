// Function: __ct__8CTextureFv
// Entry: 8003b988
// Size: 100 bytes

CTexture * __ct__8CTextureFv(CTexture *texture)

{
  __ct__4CRefFv((CRef *)texture);
  texture->vtable = &PTR_PTR_s_CTexture_801e9b78;
  texture->field101_0x74 = 0;
  texture->field105_0x78 = 0;
  *(undefined4 *)&texture->field_0x7c = 0;
  texture->field_0x70 = 0;
  texture->field_0x71 = 0;
  texture->field_0x8 = 0;
  *(undefined2 *)&texture->field_0x72 = 0xffff;
  texture->field_0x75 = 0;
  return texture;
}

