// Function: __OSInitSystemCall
// Entry: 80180990
// Size: 100 bytes

void __OSInitSystemCall(void)

{
  memcpy(&DAT_80000c00,SystemCallVector,0x1c);
  DCFlushRangeNoSync(&DAT_80000c00,0x100);
  sync(0);
  ICInvalidateRange(&DAT_80000c00,0x100);
  return;
}

