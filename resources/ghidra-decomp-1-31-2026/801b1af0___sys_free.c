// Function: __sys_free
// Entry: 801b1af0
// Size: 184 bytes

void __sys_free(undefined4 param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_8032ea90 == -1) {
    OSReport(s_GCN_Mem_Alloc_c___InitDefaultHea_801e6f48);
    OSReport(s_Metrowerks_CW_runtime_library_in_801e6f80);
    uVar1 = OSGetArenaLo();
    uVar2 = OSGetArenaHi();
    iVar3 = OSInitAlloc(uVar1,uVar2,1);
    OSSetArenaLo();
    OSCreateHeap(iVar3 + 0x1fU & 0xffffffe0,uVar2 & 0xffffffe0);
    OSSetCurrentHeap();
    OSSetArenaLo(uVar2 & 0xffffffe0);
  }
  OSFreeToHeap(DAT_8032ea90,param_1);
  return;
}

