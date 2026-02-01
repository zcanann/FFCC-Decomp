// Function: IsFifoOver__8CGraphicFv
// Entry: 80019388
// Size: 64 bytes

undefined IsFifoOver__8CGraphicFv(void)

{
  undefined4 uVar1;
  undefined local_18;
  undefined uStack_17;
  undefined uStack_16;
  undefined uStack_15;
  undefined auStack_14 [4];
  undefined auStack_10 [16];
  
  uVar1 = GXGetCPUFifo();
  GXGetFifoStatus(uVar1,auStack_14,&uStack_15,auStack_10,&uStack_16,&uStack_17,&local_18);
  return local_18;
}

