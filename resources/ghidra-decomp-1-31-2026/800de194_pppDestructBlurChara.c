// Function: pppDestructBlurChara
// Entry: 800de194
// Size: 152 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructBlurChara(pppBlurChara *pppBlurChara,int param_2)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)
           ((int)(&pppBlurChara->field0_0x0 + 2) + *(int *)(*(int *)(param_2 + 0xc) + 8));
  handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl((CGObject *)puVar2[1],0);
  iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  *(undefined4 *)(iVar1 + 0x108) = 0;
  *(undefined4 *)(iVar1 + 0xe4) = 0;
  *(undefined4 *)(iVar1 + 0xe8) = 0;
  if ((CStage *)*puVar2 != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)*puVar2);
    *puVar2 = 0;
  }
  if ((CStage *)puVar2[2] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar2[2]);
    puVar2[2] = 0;
  }
  *(undefined4 *)(iVar1 + 0x9c) = puVar2[3];
  return;
}

