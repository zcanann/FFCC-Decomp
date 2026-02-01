// Function: pppRyjMegaBirthModelDes
// Entry: 800841e4
// Size: 124 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRyjMegaBirthModelDes(pppRyjMegaBirthModel *pppRyjMegaBirthModel,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  if (*(CStage **)(&pppRyjMegaBirthModel->field_0x8c + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppRyjMegaBirthModel->field_0x8c + iVar1));
    *(undefined4 *)(&pppRyjMegaBirthModel->field_0x8c + iVar1) = 0;
  }
  if (*(CStage **)(&pppRyjMegaBirthModel->field_0x90 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppRyjMegaBirthModel->field_0x90 + iVar1));
    *(undefined4 *)(&pppRyjMegaBirthModel->field_0x90 + iVar1) = 0;
  }
  if (*(CStage **)(&pppRyjMegaBirthModel->field_0x94 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppRyjMegaBirthModel->field_0x94 + iVar1));
    *(undefined4 *)(&pppRyjMegaBirthModel->field_0x94 + iVar1) = 0;
  }
  return;
}

