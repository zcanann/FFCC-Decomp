// Function: memcpy
// Entry: 800054f4
// Size: 80 bytes

void memcpy(void *dstBuffer,void *srcBuffer,int count)

{
  undefined *puVar1;
  int iVar2;
  undefined *puVar3;
  
  if (dstBuffer <= srcBuffer) {
    puVar1 = (undefined *)((int)srcBuffer + -1);
    puVar3 = (undefined *)((int)dstBuffer + -1);
    iVar2 = count + 1;
    while( true ) {
      iVar2 = iVar2 + -1;
      if (iVar2 == 0) break;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
      *puVar3 = *puVar1;
    }
    return;
  }
  puVar1 = (undefined *)((int)srcBuffer + count);
  puVar3 = (undefined *)((int)dstBuffer + count);
  iVar2 = count + 1;
  while( true ) {
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) break;
    puVar1 = puVar1 + -1;
    puVar3 = puVar3 + -1;
    *puVar3 = *puVar1;
  }
  return;
}

