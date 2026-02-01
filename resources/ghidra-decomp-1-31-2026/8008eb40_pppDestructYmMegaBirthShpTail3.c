// Function: pppDestructYmMegaBirthShpTail3
// Entry: 8008eb40
// Size: 124 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3 *pppYmMegaBirthShpTail3,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  if (*(CStage **)(&pppYmMegaBirthShpTail3->field_0xbc + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppYmMegaBirthShpTail3->field_0xbc + iVar1));
    *(undefined4 *)(&pppYmMegaBirthShpTail3->field_0xbc + iVar1) = 0;
  }
  if (*(CStage **)(&pppYmMegaBirthShpTail3->field_0xc0 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppYmMegaBirthShpTail3->field_0xc0 + iVar1));
    *(undefined4 *)(&pppYmMegaBirthShpTail3->field_0xc0 + iVar1) = 0;
  }
  if (*(CStage **)(&pppYmMegaBirthShpTail3->field_0xc4 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppYmMegaBirthShpTail3->field_0xc4 + iVar1));
    *(undefined4 *)(&pppYmMegaBirthShpTail3->field_0xc4 + iVar1) = 0;
  }
  return;
}

