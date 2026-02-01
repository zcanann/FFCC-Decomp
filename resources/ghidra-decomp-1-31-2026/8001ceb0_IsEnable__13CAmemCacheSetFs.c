// Function: IsEnable__13CAmemCacheSetFs
// Entry: 8001ceb0
// Size: 32 bytes

uint IsEnable__13CAmemCacheSetFs(CAmemCacheSet *amemCacheSet,short param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(*(int *)&amemCacheSet->field_0x58 + param_2 * 0x1c);
  return (-uVar1 | uVar1) >> 0x1f;
}

