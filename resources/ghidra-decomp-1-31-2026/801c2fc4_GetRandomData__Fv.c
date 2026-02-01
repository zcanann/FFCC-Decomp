// Function: GetRandomData__Fv
// Entry: 801c2fc4
// Size: 56 bytes

undefined GetRandomData__Fv(void)

{
  uint uVar1;
  
  uVar1 = (uint)DAT_8032f4a8;
  DAT_8032f4a8 = DAT_8032f4a8 + 1;
  return (&DAT_8021dcce)[uVar1];
}

