// Function: AmemGetFreeSize__13CAmemCacheSetFv
// Entry: 8001c630
// Size: 16 bytes

int AmemGetFreeSize__13CAmemCacheSetFv(CAmemCacheSet *amemCacheSet)

{
  return *(int *)&amemCacheSet->field_0x2c - *(int *)&amemCacheSet->field_0x30;
}

