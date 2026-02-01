// Function: __DVDStoreErrorCode
// Entry: 8018b480
// Size: 124 bytes

void __DVDStoreErrorCode(uint param_1)

{
  char cVar2;
  int iVar1;
  char cVar3;
  
  if (param_1 == 0x1234567) {
    cVar2 = -1;
  }
  else if (param_1 == 0x1234568) {
    cVar2 = -2;
  }
  else {
    cVar3 = (char)(param_1 >> 0x18);
    cVar2 = ErrorCode2Num(param_1 & 0xffffff);
    if (5 < param_1 >> 0x18) {
      cVar3 = '\x06';
    }
    cVar2 = cVar2 + cVar3 * '\x1e';
  }
  iVar1 = __OSLockSramEx();
  *(char *)(iVar1 + 0x24) = cVar2;
  __OSUnlockSramEx(1);
  return;
}

