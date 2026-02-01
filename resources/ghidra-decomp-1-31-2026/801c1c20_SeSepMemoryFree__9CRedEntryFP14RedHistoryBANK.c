// Function: SeSepMemoryFree__9CRedEntryFP14RedHistoryBANK
// Entry: 801c1c20
// Size: 156 bytes

undefined4 SeSepMemoryFree__9CRedEntryFP14RedHistoryBANK(undefined4 param_1,undefined4 *param_2)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  
  bVar1 = *(byte *)(param_2[2] + 0x12);
  bVar2 = *(byte *)(param_2[2] + 0x11);
  RedDelete__Fi(param_2[2]);
  SeSepHistoryDelete__9CRedEntryFi(param_1,param_2[1]);
  uVar3 = param_2[3];
  param_2[3] = 0;
  param_2[2] = 0;
  *param_2 = 0xffffffff;
  WaveHistoryManager__9CRedEntryFii(param_1,0,(uint)bVar2 + (uint)bVar1 * 0x100);
  return uVar3;
}

