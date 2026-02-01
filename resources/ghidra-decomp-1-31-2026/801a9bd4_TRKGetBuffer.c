// Function: TRKGetBuffer
// Entry: 801a9bd4
// Size: 44 bytes

undefined * TRKGetBuffer(int param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)0x0;
  if ((-1 < param_1) && (param_1 < 3)) {
    puVar1 = &DAT_80328750 + param_1 * 0x890;
  }
  return puVar1;
}

