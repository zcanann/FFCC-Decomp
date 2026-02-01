// Function: Draw__10CMapShadowFv
// Entry: 8004c808
// Size: 192 bytes

void Draw__10CMapShadowFv(CMapShadow *mapShadow)

{
  int iVar1;
  Vec VStack_38;
  Vec local_2c;
  Vec local_20;
  Vec local_14;
  
  iVar1 = *(int *)&mapShadow->field_0xc;
  local_14.x = *(float *)(iVar1 + 0xc4);
  local_14.y = *(float *)(iVar1 + 0xd4);
  local_14.z = *(float *)(iVar1 + 0xe4);
  iVar1 = *(int *)&mapShadow->field_0x14;
  local_20.x = *(float *)(iVar1 + 0xc4);
  local_20.y = *(float *)(iVar1 + 0xd4);
  local_20.z = *(float *)(iVar1 + 0xe4);
  iVar1 = *(int *)&mapShadow->field_0x10;
  local_2c.x = *(float *)(iVar1 + 0xc4);
  local_2c.y = *(float *)(iVar1 + 0xd4);
  local_2c.z = *(float *)(iVar1 + 0xe4);
  PSVECSubtract(&local_20,&local_14,&local_20);
  PSVECSubtract(&local_2c,&local_14,&VStack_38);
  C_MTXLookAt((Mtx *)&mapShadow->field_0x18,&local_14,&local_20,&local_2c);
  PSMTXConcat((Mtx *)&mapShadow->field_0x48,(Mtx *)&mapShadow->field_0x18,
              (Mtx *)&mapShadow->field_0x78);
  return;
}

