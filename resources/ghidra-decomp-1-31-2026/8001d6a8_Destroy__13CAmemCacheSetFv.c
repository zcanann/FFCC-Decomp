// Function: Destroy__13CAmemCacheSetFv
// Entry: 8001d6a8
// Size: 72 bytes

void Destroy__13CAmemCacheSetFv(CAmemCacheSet *amemCacheSet)

{
  if (*(int *)&amemCacheSet->field_0x58 != 0) {
    __destroy_new_array(*(int *)&amemCacheSet->field_0x58,__dt__10CAmemCacheFv);
    *(undefined4 *)&amemCacheSet->field_0x58 = 0;
  }
  return;
}

