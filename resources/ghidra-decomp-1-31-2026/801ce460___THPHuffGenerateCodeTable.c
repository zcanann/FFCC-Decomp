// Function: __THPHuffGenerateCodeTable
// Entry: 801ce460
// Size: 104 bytes

void __THPHuffGenerateCodeTable(void)

{
  char *pcVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  
  iVar2 = DAT_8032f58c;
  pcVar1 = DAT_8032f588;
  uVar4 = 0;
  uVar5 = 0;
  cVar3 = *DAT_8032f588;
  while (pcVar1[uVar4 & 0xffff] != '\0') {
    for (; cVar3 == pcVar1[uVar4 & 0xffff]; uVar4 = uVar4 + 1) {
      *(short *)(iVar2 + (uVar4 & 0xffff) * 2) = (short)uVar5;
      uVar5 = uVar5 + 1;
    }
    uVar5 = (uVar5 & 0x7fff) << 1;
    cVar3 = cVar3 + '\x01';
  }
  return;
}

