// Function: ClearAnmData__11CFunnyShapeFv
// Entry: 800510b0
// Size: 96 bytes

void ClearAnmData__11CFunnyShapeFv(CFunnyShape *funnyShape)

{
  if (*(void **)(funnyShape->UnkBuff2 + 0xc) != (void *)0x0) {
    __dla__FPv(*(void **)(funnyShape->UnkBuff2 + 0xc));
    funnyShape->UnkBuff2[0xc] = '\0';
    funnyShape->UnkBuff2[0xd] = '\0';
    funnyShape->UnkBuff2[0xe] = '\0';
    funnyShape->UnkBuff2[0xf] = '\0';
  }
  memset(funnyShape,0,0x30);
  memset(funnyShape->UnkBuff2,0,0x10);
  return;
}

