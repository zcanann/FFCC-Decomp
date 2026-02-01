// Function: __CARDCompareFileName
// Entry: 8019d664
// Size: 104 bytes

undefined4 __CARDCompareFileName(CARDDir *cardDir,uint8_t *fileName)

{
  uint8_t uVar1;
  uint8_t uVar2;
  uint8_t *puVar3;
  int iVar4;
  
  puVar3 = cardDir->fileName;
  iVar4 = 0x20;
  do {
    iVar4 = iVar4 + -1;
    if (iVar4 < 0) {
      if (*fileName == '\0') {
        return 1;
      }
      return 0;
    }
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    uVar2 = *fileName;
    fileName = fileName + 1;
    if (uVar1 != uVar2) {
      return 0;
    }
  } while (uVar2 != '\0');
  return 1;
}

