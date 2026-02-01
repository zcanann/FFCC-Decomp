// Function: MusicMemoryFree__9CRedEntryFP14RedHistoryBANK
// Entry: 801c266c
// Size: 112 bytes

undefined4 MusicMemoryFree__9CRedEntryFP14RedHistoryBANK(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  WaveHistoryManager__9CRedEntryFii(param_1,0,(int)*(short *)(param_2[2] + 6));
  RedDelete__Fi(param_2[2]);
  uVar1 = param_2[3];
  param_2[3] = 0;
  param_2[2] = 0;
  param_2[1] = 0;
  *param_2 = 0xffffffff;
  return uVar1;
}

