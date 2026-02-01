// Function: AmemGetLock__13CAmemCacheSetFv
// Entry: 8001d44c
// Size: 16 bytes

void AmemGetLock__13CAmemCacheSetFv(CAmemCacheSet *amemCacheSet)

{
  *(undefined4 *)&amemCacheSet->field_0x34 = *(undefined4 *)&amemCacheSet->field_0x38;
  *(undefined4 *)&amemCacheSet->field_0x30 = *(undefined4 *)&amemCacheSet->field_0x38;
  return;
}

