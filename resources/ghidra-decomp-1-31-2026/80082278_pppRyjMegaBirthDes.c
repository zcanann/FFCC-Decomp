// Function: pppRyjMegaBirthDes
// Entry: 80082278
// Size: 124 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRyjMegaBirthDes(pppRyjMegaBirth *pppRyjMegaBirth,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  if (*(CStage **)(&pppRyjMegaBirth->field_0xbc + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppRyjMegaBirth->field_0xbc + iVar1));
    *(undefined4 *)(&pppRyjMegaBirth->field_0xbc + iVar1) = 0;
  }
  if (*(CStage **)(&pppRyjMegaBirth->field_0xc0 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppRyjMegaBirth->field_0xc0 + iVar1));
    *(undefined4 *)(&pppRyjMegaBirth->field_0xc0 + iVar1) = 0;
  }
  if (*(CStage **)(&pppRyjMegaBirth->field_0xc4 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppRyjMegaBirth->field_0xc4 + iVar1));
    *(undefined4 *)(&pppRyjMegaBirth->field_0xc4 + iVar1) = 0;
  }
  return;
}

