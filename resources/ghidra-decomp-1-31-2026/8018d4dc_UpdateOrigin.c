// Function: UpdateOrigin
// Entry: 8018d4dc
// Size: 420 bytes

void UpdateOrigin(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_1 * 0xc;
  uVar1 = DAT_8032eb24 & 0x700;
  if (uVar1 == 0x400) goto LAB_8018d604;
  if (uVar1 < 0x400) {
    if (uVar1 == 0x200) {
      (&DAT_8030cca4)[iVar2] = (&DAT_8030cca4)[iVar2] & 0xf0;
      (&DAT_8030cca5)[iVar2] = (&DAT_8030cca5)[iVar2] & 0xf0;
      (&DAT_8030cca6)[iVar2] = (&DAT_8030cca6)[iVar2] & 0xf0;
      (&DAT_8030cca7)[iVar2] = (&DAT_8030cca7)[iVar2] & 0xf0;
      goto LAB_8018d604;
    }
    if (0x1ff < uVar1) goto LAB_8018d604;
    if (uVar1 == 0x100) {
      (&DAT_8030cca4)[iVar2] = (&DAT_8030cca4)[iVar2] & 0xf0;
      (&DAT_8030cca5)[iVar2] = (&DAT_8030cca5)[iVar2] & 0xf0;
      (&DAT_8030cca8)[iVar2] = (&DAT_8030cca8)[iVar2] & 0xf0;
      (&DAT_8030cca9)[iVar2] = (&DAT_8030cca9)[iVar2] & 0xf0;
      goto LAB_8018d604;
    }
    if ((0xff < uVar1) || (uVar1 != 0)) goto LAB_8018d604;
  }
  else if (uVar1 != 0x600) {
    if (uVar1 < 0x600) {
      if (uVar1 != 0x500) goto LAB_8018d604;
    }
    else if (uVar1 != 0x700) goto LAB_8018d604;
  }
  (&DAT_8030cca6)[iVar2] = (&DAT_8030cca6)[iVar2] & 0xf0;
  (&DAT_8030cca7)[iVar2] = (&DAT_8030cca7)[iVar2] & 0xf0;
  (&DAT_8030cca8)[iVar2] = (&DAT_8030cca8)[iVar2] & 0xf0;
  (&DAT_8030cca9)[iVar2] = (&DAT_8030cca9)[iVar2] & 0xf0;
LAB_8018d604:
  (&DAT_8030cca2)[iVar2] = (&DAT_8030cca2)[iVar2] + -0x80;
  (&DAT_8030cca3)[iVar2] = (&DAT_8030cca3)[iVar2] + -0x80;
  (&DAT_8030cca4)[iVar2] = (&DAT_8030cca4)[iVar2] + -0x80;
  (&DAT_8030cca5)[iVar2] = (&DAT_8030cca5)[iVar2] + -0x80;
  if ((((DAT_8032eb20 & 0x80000000U >> param_1) != 0) && ('@' < (char)(&DAT_8030cca2)[iVar2])) &&
     (uVar1 = SIGetType(), (uVar1 & 0xffff0000) == 0x9000000)) {
    (&DAT_8030cca2)[iVar2] = 0;
  }
  return;
}

