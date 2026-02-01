// Function: setSize__21CPtrArray<P8CTexture>FUl
// Entry: 8003c09c
// Size: 240 bytes

undefined4 setSize__21CPtrArray<P8CTexture>FUl(CPtrArray *ptrArray,uint size)

{
  void **dstBuffer;
  
  if (ptrArray->size < size) {
    if (ptrArray->size == 0) {
      ptrArray->size = ptrArray->defaultSize;
    }
    else {
      if (ptrArray->growCapacity == 0) {
        Printf__7CSystemFPce(&System,&DAT_801d79d8);
      }
      ptrArray->size = ptrArray->size << 1;
    }
    dstBuffer = (void **)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                                   (&Memory,ptrArray->size << 2,ptrArray->stage,
                                    s_collection_ptrarray_h_801d79f4,0xfa,0);
    if (dstBuffer == (void **)0x0) {
      return 0;
    }
    if (ptrArray->items != (void **)0x0) {
      memcpy(dstBuffer,ptrArray->items,ptrArray->numItems << 2);
    }
    if (ptrArray->items != (void **)0x0) {
      __dla__FPv(ptrArray->items);
      ptrArray->items = (void **)0x0;
    }
    ptrArray->items = dstBuffer;
  }
  return 1;
}

