// Function: __ct__12CMaterialSetFv
// Entry: 8003d998
// Size: 88 bytes

CMaterialSet * __ct__12CMaterialSetFv(CMaterialSet *materialSet)

{
  __ct__4CRefFv((CRef *)materialSet);
  materialSet->vtable = &PTR_PTR_s_CMaterialSet_801e9bbc;
  __ct__22CPtrArray<P9CMaterial>Fv(&materialSet->materials);
  SetStage__22CPtrArray<P9CMaterial>FPQ27CMemory6CStage(&materialSet->materials,MaterialMan._536_4_)
  ;
  return materialSet;
}

