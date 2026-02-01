// Function: Init__10CRedMemoryFiiii
// Entry: 801c0528
// Size: 160 bytes

void Init__10CRedMemoryFiiii
               (undefined4 param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  DAT_8032f498 = param_3 + -0x4000;
  DAT_8032f4a4 = param_2 + 0x2000;
  DAT_8032f490 = param_2 + 0x4000;
  DAT_8032f4a0 = param_2;
  memset(param_2,0,0x2000);
  memset(DAT_8032f4a4,0,0x2000);
  DAT_8032f494 = param_4;
  DAT_8032f49c = param_5;
  return;
}

