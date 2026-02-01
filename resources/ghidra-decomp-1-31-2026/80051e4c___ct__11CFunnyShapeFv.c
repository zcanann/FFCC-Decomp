// Function: __ct__11CFunnyShapeFv
// Entry: 80051e4c
// Size: 236 bytes

CFunnyShape * __ct__11CFunnyShapeFv(CFunnyShape *funnyShape)

{
  CFunnyShape *pCVar1;
  int iVar2;
  
  *(undefined4 *)&funnyShape->field_0x6010 = 0;
  memset(funnyShape,0,0x6000);
  memset(funnyShape->UnkBuff2,0,0x10);
  memset(funnyShape->UnkBuffA,0,0x10);
  memset(funnyShape->UnkBuff3,0,0x40);
  iVar2 = 2;
  pCVar1 = funnyShape;
  do {
    *(undefined4 *)&pCVar1->field_0x6094 = 0;
    *(undefined4 *)&pCVar1->field_0x6014 = 0;
    *(undefined4 *)&pCVar1->field_0x6054 = 0;
    *(undefined4 *)&pCVar1->field_0x6098 = 0;
    *(undefined4 *)&pCVar1->field_0x6018 = 0;
    *(undefined4 *)&pCVar1->field_0x6058 = 0;
    *(undefined4 *)&pCVar1->field_0x609c = 0;
    *(undefined4 *)&pCVar1->field_0x601c = 0;
    *(undefined4 *)&pCVar1->field_0x605c = 0;
    *(undefined4 *)&pCVar1->field_0x60a0 = 0;
    *(undefined4 *)&pCVar1->field_0x6020 = 0;
    *(undefined4 *)&pCVar1->field_0x6060 = 0;
    *(undefined4 *)&pCVar1->field_0x60a4 = 0;
    *(undefined4 *)&pCVar1->field_0x6024 = 0;
    *(undefined4 *)&pCVar1->field_0x6064 = 0;
    *(undefined4 *)&pCVar1->field_0x60a8 = 0;
    *(undefined4 *)&pCVar1->field_0x6028 = 0;
    *(undefined4 *)&pCVar1->field_0x6068 = 0;
    *(undefined4 *)&pCVar1->field_0x60ac = 0;
    *(undefined4 *)&pCVar1->field_0x602c = 0;
    *(undefined4 *)&pCVar1->field_0x606c = 0;
    *(undefined4 *)&pCVar1->field_0x60b0 = 0;
    *(undefined4 *)&pCVar1->field_0x6030 = 0;
    *(undefined4 *)&pCVar1->field_0x6070 = 0;
    pCVar1 = (CFunnyShape *)(pCVar1->m_maybeTexture + 0x20);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  funnyShape->field_0x60d4 = 0;
  return funnyShape;
}

