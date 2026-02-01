// Function: __ct__9CMaterialFv
// Entry: 8003dd14
// Size: 176 bytes

CMaterial * __ct__9CMaterialFv(CMaterial *material)

{
  __ct__4CRefFv((CRef *)material);
  material->vtable = &PTR_PTR_s_CMaterial_801e9bd4;
  __construct_array(&material->field_0x4c,__ct__10CTexScrollFv,__dt__10CTexScrollFv,0x14,4);
  memset(material->unkObjOrBuffer,0,0x10);
  material->field126_0x9c = -1;
  material->field127_0xa0 = 4;
  material->field128_0xa1 = 1;
  material->field129_0xa2 = 0;
  material->field131_0xa4 = 0;
  material->field42_0x3c = 0;
  material->field43_0x40 = 0;
  material->field44_0x44 = 0;
  material->field45_0x48 = 0;
  material->field34_0x34 = 0;
  material->field35_0x35 = 0;
  material->field36_0x36 = 0;
  material->field132_0xa5 = 0;
  return material;
}

