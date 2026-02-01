// Function: Init__12CMaterialManFv
// Entry: 80043a28
// Size: 80 bytes

void Init__12CMaterialManFv(int param_1)

{
  CStage *pCVar1;
  
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x20000,s_CMaterial_material_801d7a48,0);
  *(CStage **)(param_1 + 0x218) = pCVar1;
  *(undefined *)(param_1 + 0x204) = 0x30;
  return;
}

