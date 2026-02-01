// Function: GBAJoyBoot
// Entry: 801a8734
// Size: 72 bytes

void GBAJoyBoot(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = GBAJoyBootAsync();
  if (iVar1 == 0) {
    __GBASync(param_1);
  }
  return;
}

