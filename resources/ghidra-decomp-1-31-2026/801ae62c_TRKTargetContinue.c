// Function: TRKTargetContinue
// Entry: 801ae62c
// Size: 52 bytes

undefined4 TRKTargetContinue(void)

{
  TRKTargetSetStopped(0);
  UnreserveEXI2Port();
  TRKSwapAndGo();
  ReserveEXI2Port();
  return 0;
}

