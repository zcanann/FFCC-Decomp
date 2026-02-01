// Function: pppDestructYmMegaBirthShpTail2
// Entry: 8008c9a0
// Size: 124 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2 *pppYmMegaBirthShpTail2,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  if (*(CStage **)(&pppYmMegaBirthShpTail2->field_0xbc + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppYmMegaBirthShpTail2->field_0xbc + iVar1));
    *(undefined4 *)(&pppYmMegaBirthShpTail2->field_0xbc + iVar1) = 0;
  }
  if (*(CStage **)(&pppYmMegaBirthShpTail2->field_0xc0 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppYmMegaBirthShpTail2->field_0xc0 + iVar1));
    *(undefined4 *)(&pppYmMegaBirthShpTail2->field_0xc0 + iVar1) = 0;
  }
  if (*(CStage **)(&pppYmMegaBirthShpTail2->field_0xc4 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppYmMegaBirthShpTail2->field_0xc4 + iVar1));
    *(undefined4 *)(&pppYmMegaBirthShpTail2->field_0xc4 + iVar1) = 0;
  }
  return;
}

