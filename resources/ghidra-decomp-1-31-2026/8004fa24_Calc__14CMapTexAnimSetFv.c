// Function: Calc__14CMapTexAnimSetFv
// Entry: 8004fa24
// Size: 104 bytes

void Calc__14CMapTexAnimSetFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (iVar1 = 0; iVar1 < *(short *)(param_1 + 8); iVar1 = iVar1 + 1) {
    Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet
              (*(undefined4 *)(iVar2 + 0xc),*(CMaterialSet **)(param_1 + 0x10c),
               *(CTextureSet **)(param_1 + 0x110));
    iVar2 = iVar2 + 4;
  }
  return;
}

