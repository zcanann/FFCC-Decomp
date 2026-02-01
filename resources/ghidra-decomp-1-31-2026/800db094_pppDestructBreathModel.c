// Function: pppDestructBreathModel
// Entry: 800db094
// Size: 248 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructBreathModel(pppBreathModel *pppBreathModel,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = **(int **)(param_2 + 0xc);
  if (*(CStage **)(&pppBreathModel->field_0xb0 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppBreathModel->field_0xb0 + iVar1));
    *(undefined4 *)(&pppBreathModel->field_0xb0 + iVar1) = 0;
  }
  if (*(CStage **)(&pppBreathModel->field_0xb4 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppBreathModel->field_0xb4 + iVar1));
    *(undefined4 *)(&pppBreathModel->field_0xb4 + iVar1) = 0;
  }
  if (*(CStage **)(&pppBreathModel->field_0xb8 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppBreathModel->field_0xb8 + iVar1));
    *(undefined4 *)(&pppBreathModel->field_0xb8 + iVar1) = 0;
  }
  iVar3 = *(int *)(&pppBreathModel->field_0xbc + iVar1);
  if (iVar3 != 0) {
    for (iVar2 = 0; iVar2 < *(short *)(&pppBreathModel->field_0xd4 + iVar1); iVar2 = iVar2 + 1) {
      if (*(CStage **)(iVar3 + 4) != (CStage *)0x0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(iVar3 + 4));
        *(undefined4 *)(iVar3 + 4) = 0;
      }
      if (*(CStage **)(iVar3 + 8) != (CStage *)0x0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(iVar3 + 8));
        *(undefined4 *)(iVar3 + 8) = 0;
      }
      iVar3 = iVar3 + 0x5c;
    }
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppBreathModel->field_0xbc + iVar1));
    *(undefined4 *)(&pppBreathModel->field_0xbc + iVar1) = 0;
  }
  return;
}

