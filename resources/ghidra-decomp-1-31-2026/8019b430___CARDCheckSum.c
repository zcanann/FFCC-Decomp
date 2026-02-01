// Function: __CARDCheckSum
// Entry: 8019b430
// Size: 432 bytes

void __CARDCheckSum(ushort *ptr,uint length,short *checksum,short *checksumInv)

{
  ushort *puVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  
  *checksumInv = 0;
  uVar3 = ((int)length >> 1) + (uint)((int)length < 0 && (length & 1) != 0);
  *checksum = 0;
  if (0 < (int)uVar3) {
    uVar4 = uVar3 >> 3;
    if (uVar4 != 0) {
      do {
        *checksum = *checksum + *ptr;
        *checksumInv = *checksumInv + ~*ptr;
        *checksum = *checksum + ptr[1];
        *checksumInv = *checksumInv + ~ptr[1];
        *checksum = *checksum + ptr[2];
        *checksumInv = *checksumInv + ~ptr[2];
        *checksum = *checksum + ptr[3];
        *checksumInv = *checksumInv + ~ptr[3];
        *checksum = *checksum + ptr[4];
        *checksumInv = *checksumInv + ~ptr[4];
        *checksum = *checksum + ptr[5];
        *checksumInv = *checksumInv + ~ptr[5];
        *checksum = *checksum + ptr[6];
        *checksumInv = *checksumInv + ~ptr[6];
        *checksum = *checksum + ptr[7];
        puVar1 = ptr + 7;
        ptr = ptr + 8;
        *checksumInv = *checksumInv + ~*puVar1;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
      uVar3 = uVar3 & 7;
      if (uVar3 == 0) goto LAB_8019b5b4;
    }
    do {
      *checksum = *checksum + *ptr;
      uVar2 = *ptr;
      ptr = ptr + 1;
      *checksumInv = *checksumInv + ~uVar2;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
LAB_8019b5b4:
  if (*checksum == -1) {
    *checksum = 0;
  }
  if (*checksumInv == -1) {
    *checksumInv = 0;
    return;
  }
  return;
}

