// Function: Init__6CCharaFv
// Entry: 80073a0c
// Size: 200 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Init__6CCharaFv(int param_1)

{
  CStage *pCVar1;
  undefined4 uVar2;
  
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0xc0000,s_CChara_80330220,0);
  *(CStage **)(param_1 + 0x2058) = pCVar1;
  *(undefined4 *)(param_1 + 0x205c) = 0;
  uVar2 = __nwa__FUlPQ27CMemory6CStagePci(0x58000,Chara._8280_4_,s_chara_cpp_801d90c8,0x3f);
  *(undefined4 *)(param_1 + 0x2068) = uVar2;
  uVar2 = __nwa__FUlPQ27CMemory6CStagePci(0x58000,Chara._8280_4_,s_chara_cpp_801d90c8,0x40);
  *(undefined4 *)(param_1 + 0x2070) = uVar2;
  *(undefined4 *)(param_1 + 0x2060) = 1;
  *(int *)(param_1 + 0x2060) = 1 - *(int *)(param_1 + 0x2060);
  *(undefined4 *)(param_1 + *(int *)(param_1 + 0x2060) * 8 + 0x2064) = 0;
  *(undefined4 *)(param_1 + 0x2074) = 0;
  return;
}

