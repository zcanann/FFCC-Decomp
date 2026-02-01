// Function: TRKInitializeIntDrivenUART
// Entry: 801ae338
// Size: 80 bytes

undefined4 TRKInitializeIntDrivenUART(void)

{
  undefined4 in_r6;
  
  (*DAT_8021d038)(in_r6,TRKEXICallBack);
  (*DAT_8021d050)();
  return 0;
}

