// Function: __dt__Q29CMaterial25@class$529materialman_cppFv
// Entry: 8003c49c
// Size: 100 bytes

CMaterial * __dt__Q29CMaterial25_class_529materialman_cppFv(CMaterial *material,short param_2)

{
  if ((material != (CMaterial *)0x0) &&
     (__destroy_arr(material->unkObjOrBuffer + 8,__dt__10CTexScrollFv,0x14,4), 0 < param_2)) {
    __dl__FPv(material);
  }
  return material;
}

