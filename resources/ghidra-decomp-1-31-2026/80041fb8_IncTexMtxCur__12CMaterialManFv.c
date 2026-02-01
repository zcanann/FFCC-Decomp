// Function: IncTexMtxCur__12CMaterialManFv
// Entry: 80041fb8
// Size: 20 bytes

int IncTexMtxCur__12CMaterialManFv(CMaterialMan *materialMan)

{
  int iVar1;
  
  iVar1 = *(int *)&materialMan->field_0x120;
  *(int *)&materialMan->field_0x120 = iVar1 + 3;
  return iVar1;
}

