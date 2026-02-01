// Function: DisableIndMtx__5CUtilFv
// Entry: 80024444
// Size: 100 bytes

void DisableIndMtx__5CUtilFv(void)

{
  undefined auStack_18 [24];
  
  GXSetNumIndStages(0);
  memset(auStack_18,0,0x18);
  GXSetIndTexMtx(1,auStack_18,1);
  GXSetIndTexMtx(2,auStack_18,1);
  GXSetIndTexMtx(3,auStack_18,1);
  return;
}

