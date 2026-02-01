// Function: __dt__11CTexAnimSetFv
// Entry: 80044a24
// Size: 120 bytes

CTexAnimSet * __dt__11CTexAnimSetFv(CTexAnimSet *texAnimSet,short param_2)

{
  if (texAnimSet != (CTexAnimSet *)0x0) {
    (texAnimSet->texAnims).vtable = &PTR_PTR_s_CTexAnimSet_801e9c6c;
    ReleaseAndRemoveAll__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)&(texAnimSet->texAnims).size);
    __dt__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)&(texAnimSet->texAnims).size,0xffff);
    __dt__4CRefFv((CRef *)texAnimSet,0);
    if (0 < param_2) {
      __dl__FPv(texAnimSet);
    }
  }
  return texAnimSet;
}

