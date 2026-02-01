// Function: CanCreateFromScript__9CGItemObjFv
// Entry: 80125e74
// Size: 56 bytes

uint CanCreateFromScript__9CGItemObjFv(void)

{
  uint uVar1;
  
  uVar1 = getNumFreeObject__13CFlatRuntime2Fi((CFlatRuntime2 *)&CFlat,5);
  return (-uVar1 & ~uVar1) >> 0x1f;
}

