// Function: pppDesScreenBreak
// Entry: 8012d870
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDesScreenBreak(pppScreenBreak *pppScreenBreak,int param_2)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(param_2 + 0xc) + 8);
  handle = (CCharaPcsCHandle *)
           GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
  iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0xf0) = 0;
    *(undefined4 *)(iVar1 + 0xfc) = 0;
    *(undefined4 *)(iVar1 + 0xf4) = 0;
    *(undefined4 *)(iVar1 + 0xe4) = 0;
    *(undefined4 *)(iVar1 + 0xe8) = 0;
    *(undefined4 *)(iVar1 + 0xec) = 0;
  }
  if (*(CStage **)(&pppScreenBreak->field_0x8c + iVar2) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppScreenBreak->field_0x8c + iVar2));
    *(undefined4 *)(&pppScreenBreak->field_0x8c + iVar2) = 0;
  }
  if (*(CStage **)(&pppScreenBreak->field_0x90 + iVar2) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppScreenBreak->field_0x90 + iVar2));
    *(undefined4 *)(&pppScreenBreak->field_0x90 + iVar2) = 0;
  }
  return;
}

