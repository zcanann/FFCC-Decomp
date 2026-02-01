// Function: DVDSetAutoInvalidation
// Entry: 8018aba4
// Size: 16 bytes

undefined4 DVDSetAutoInvalidation(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8032eae4;
  DAT_8032eae4 = param_1;
  return uVar1;
}

