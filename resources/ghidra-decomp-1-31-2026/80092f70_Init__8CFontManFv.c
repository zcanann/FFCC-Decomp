// Function: Init__8CFontManFv
// Entry: 80092f70
// Size: 296 bytes

void Init__8CFontManFv(CFontMan *fontMan)

{
  float fVar1;
  float fVar2;
  CStage *pCVar3;
  CRef *ref;
  
  *(undefined4 *)&fontMan->field_0x8 = 0;
  pCVar3 = CreateStage__7CMemoryFUlPci(&Memory,0x8000,s_CFontMan_801d9cc4,0);
  *(CStage **)&fontMan->field_0x4 = pCVar3;
  ref = (CRef *)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                          (&Memory,0x1440,FontMan._4_4_,s_fontman_cpp_801d9cb8,0x3d,0);
  if (ref != (CRef *)0x0) {
    __ct__4CRefFv(ref);
    fVar1 = FLOAT_803306b8;
    ref->vtable = &PTR_PTR_s_CFont_8020edcc;
    fVar2 = FLOAT_803306c8;
    ref[7].vtable = (void *)0x0;
    ref[6].refCount = 0;
    ref[4].vtable = (void *)fVar1;
    ref[3].refCount = (int)fVar1;
    ref[3].vtable = (void *)fVar1;
    ref[2].refCount = (int)fVar1;
    *(byte *)&ref[4].refCount = *(byte *)&ref[4].refCount & 0x7f;
    ref[5].refCount = (int)fVar2;
    ref[5].vtable = (void *)fVar2;
    *(byte *)&ref[4].refCount = *(byte *)&ref[4].refCount & 0xf7;
    *(undefined *)&ref[6].vtable = 0xff;
    *(undefined *)((int)&ref[6].vtable + 1) = 0xff;
    *(undefined *)((int)&ref[6].vtable + 2) = 0xff;
    *(undefined *)((int)&ref[6].vtable + 3) = 0xff;
    *(byte *)&ref[4].refCount = *(byte *)&ref[4].refCount & 0xbf;
    *(byte *)&ref[4].refCount = *(byte *)&ref[4].refCount & 0xdf;
    *(undefined2 *)((int)&ref[1].refCount + 2) = 0;
  }
  *(CRef **)&fontMan->field_0x8 = ref;
  Create__5CFontFPvPQ27CMemory6CStage(*(CFont **)&fontMan->field_0x8,0,0);
  return;
}

