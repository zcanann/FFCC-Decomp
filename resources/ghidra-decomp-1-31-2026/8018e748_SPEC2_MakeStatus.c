// Function: SPEC2_MakeStatus
// Entry: 8018e748
// Size: 1016 bytes

void SPEC2_MakeStatus(int param_1,ushort *param_2,undefined4 *param_3)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  char cVar5;
  
  *param_2 = (ushort)((uint)*param_3 >> 0x10) & 0x3fff;
  *(char *)(param_2 + 1) = (char)((uint)*param_3 >> 8);
  *(char *)((int)param_2 + 3) = (char)*param_3;
  uVar3 = DAT_8032eb24 & 0x700;
  if (uVar3 == 0x400) {
    *(char *)(param_2 + 2) = (char)((uint)param_3[1] >> 0x18);
    *(char *)((int)param_2 + 5) = (char)((uint)param_3[1] >> 0x10);
    *(undefined *)(param_2 + 3) = 0;
    *(undefined *)((int)param_2 + 7) = 0;
    *(char *)(param_2 + 4) = (char)((uint)param_3[1] >> 8);
    *(char *)((int)param_2 + 9) = (char)param_3[1];
    goto LAB_8018e954;
  }
  if (uVar3 < 0x400) {
    if (uVar3 == 0x200) {
      *(byte *)(param_2 + 2) = (byte)((uint)param_3[1] >> 0x18) & 0xf0;
      *(byte *)((int)param_2 + 5) = (byte)((uint)param_3[1] >> 0x14) & 0xf0;
      *(byte *)(param_2 + 3) = (byte)((uint)param_3[1] >> 0x10) & 0xf0;
      *(byte *)((int)param_2 + 7) = (byte)((uint)param_3[1] >> 0xc) & 0xf0;
      *(char *)(param_2 + 4) = (char)((uint)param_3[1] >> 8);
      *(char *)((int)param_2 + 9) = (char)param_3[1];
      goto LAB_8018e954;
    }
    if (0x1ff < uVar3) {
      if (uVar3 == 0x300) {
        *(char *)(param_2 + 2) = (char)((uint)param_3[1] >> 0x18);
        *(char *)((int)param_2 + 5) = (char)((uint)param_3[1] >> 0x10);
        *(char *)(param_2 + 3) = (char)((uint)param_3[1] >> 8);
        *(char *)((int)param_2 + 7) = (char)param_3[1];
        *(undefined *)(param_2 + 4) = 0;
        *(undefined *)((int)param_2 + 9) = 0;
      }
      goto LAB_8018e954;
    }
    if (uVar3 == 0x100) {
      *(byte *)(param_2 + 2) = (byte)((uint)param_3[1] >> 0x18) & 0xf0;
      *(byte *)((int)param_2 + 5) = (byte)((uint)param_3[1] >> 0x14) & 0xf0;
      *(char *)(param_2 + 3) = (char)((uint)param_3[1] >> 0x10);
      *(char *)((int)param_2 + 7) = (char)((uint)param_3[1] >> 8);
      *(byte *)(param_2 + 4) = (byte)param_3[1] & 0xf0;
      *(char *)((int)param_2 + 9) = (char)(param_3[1] << 4);
      goto LAB_8018e954;
    }
    if ((0xff < uVar3) || (uVar3 != 0)) goto LAB_8018e954;
  }
  else if (uVar3 != 0x600) {
    if (uVar3 < 0x600) {
      if (uVar3 != 0x500) goto LAB_8018e954;
    }
    else if (uVar3 != 0x700) goto LAB_8018e954;
  }
  *(char *)(param_2 + 2) = (char)((uint)param_3[1] >> 0x18);
  *(char *)((int)param_2 + 5) = (char)((uint)param_3[1] >> 0x10);
  *(byte *)(param_2 + 3) = (byte)((uint)param_3[1] >> 8) & 0xf0;
  *(byte *)((int)param_2 + 7) = (byte)((uint)param_3[1] >> 4) & 0xf0;
  *(byte *)(param_2 + 4) = (byte)param_3[1] & 0xf0;
  *(char *)((int)param_2 + 9) = (char)(param_3[1] << 4);
LAB_8018e954:
  param_1 = param_1 * 0xc;
  *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + -0x80;
  *(char *)((int)param_2 + 3) = *(char *)((int)param_2 + 3) + -0x80;
  *(char *)(param_2 + 2) = *(char *)(param_2 + 2) + -0x80;
  *(char *)((int)param_2 + 5) = *(char *)((int)param_2 + 5) + -0x80;
  cVar1 = (&DAT_8030cca2)[param_1];
  cVar5 = *(char *)(param_2 + 1);
  if (cVar1 < '\x01') {
    if ((cVar1 < '\0') && ((char)(cVar1 + '\x7f') < cVar5)) {
      cVar5 = cVar1 + '\x7f';
    }
  }
  else if (cVar5 < (char)(cVar1 + -0x80)) {
    cVar5 = cVar1 + -0x80;
  }
  *(char *)(param_2 + 1) = cVar5 - cVar1;
  cVar1 = (&DAT_8030cca3)[param_1];
  cVar5 = *(char *)((int)param_2 + 3);
  if (cVar1 < '\x01') {
    if ((cVar1 < '\0') && ((char)(cVar1 + '\x7f') < cVar5)) {
      cVar5 = cVar1 + '\x7f';
    }
  }
  else if (cVar5 < (char)(cVar1 + -0x80)) {
    cVar5 = cVar1 + -0x80;
  }
  *(char *)((int)param_2 + 3) = cVar5 - cVar1;
  cVar1 = (&DAT_8030cca4)[param_1];
  cVar5 = *(char *)(param_2 + 2);
  if (cVar1 < '\x01') {
    if ((cVar1 < '\0') && ((char)(cVar1 + '\x7f') < cVar5)) {
      cVar5 = cVar1 + '\x7f';
    }
  }
  else if (cVar5 < (char)(cVar1 + -0x80)) {
    cVar5 = cVar1 + -0x80;
  }
  *(char *)(param_2 + 2) = cVar5 - cVar1;
  cVar1 = (&DAT_8030cca5)[param_1];
  cVar5 = *(char *)((int)param_2 + 5);
  if (cVar1 < '\x01') {
    if ((cVar1 < '\0') && ((char)(cVar1 + '\x7f') < cVar5)) {
      cVar5 = cVar1 + '\x7f';
    }
  }
  else if (cVar5 < (char)(cVar1 + -0x80)) {
    cVar5 = cVar1 + -0x80;
  }
  *(char *)((int)param_2 + 5) = cVar5 - cVar1;
  bVar2 = (&DAT_8030cca6)[param_1];
  bVar4 = *(byte *)(param_2 + 3);
  if (*(byte *)(param_2 + 3) < bVar2) {
    bVar4 = bVar2;
  }
  *(byte *)(param_2 + 3) = bVar4 - bVar2;
  bVar2 = (&DAT_8030cca7)[param_1];
  bVar4 = *(byte *)((int)param_2 + 7);
  if (*(byte *)((int)param_2 + 7) < bVar2) {
    bVar4 = bVar2;
  }
  *(byte *)((int)param_2 + 7) = bVar4 - bVar2;
  return;
}

