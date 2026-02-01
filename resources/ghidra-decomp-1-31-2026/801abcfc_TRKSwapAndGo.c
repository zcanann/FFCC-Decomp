// Function: TRKSwapAndGo
// Entry: 801abcfc
// Size: 156 bytes

void TRKSwapAndGo(undefined2 param_1)

{
  undefined4 in_MSR;
  undefined4 in_SRR0;
  undefined4 in_SRR1;
  
  DAT_8021cfdc._0_2_ = param_1;
  DAT_8021cfd4 = in_SRR0;
  DAT_8021cfe1 = 1;
  returnFromInterrupt(in_MSR,in_SRR1);
  return;
}

