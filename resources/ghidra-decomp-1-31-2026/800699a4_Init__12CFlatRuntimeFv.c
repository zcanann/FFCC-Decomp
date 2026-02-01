// Function: Init__12CFlatRuntimeFv
// Entry: 800699a4
// Size: 136 bytes

void Init__12CFlatRuntimeFv(CFlatRuntime *flatRuntime)

{
  undefined4 uVar1;
  void *pvVar2;
  
  uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))();
  pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x3000,uVar1,s_cflat_runtime_cpp_801d8ef8,0x2a);
  flatRuntime->m_variableValuesPtr = pvVar2;
  uVar1 = (**(code **)((int)flatRuntime->vtable + 0x44))(flatRuntime);
  pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x14880,uVar1,s_cflat_runtime_cpp_801d8ef8,0x2b);
  flatRuntime->m_workBasePtr = pvVar2;
  return;
}

