// Function: __ct__11CTexAnimSetFv
// Entry: 80044a9c
// Size: 76 bytes

CTexAnimSet * __ct__11CTexAnimSetFv(CTexAnimSet *texAnimSet)

{
  __ct__4CRefFv((CRef *)texAnimSet);
  (texAnimSet->texAnims).vtable = &PTR_PTR_s_CTexAnimSet_801e9c6c;
  __ct__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)&(texAnimSet->texAnims).size);
  *(float *)&texAnimSet->field_0x24 = FLOAT_8032fb38;
  return texAnimSet;
}

