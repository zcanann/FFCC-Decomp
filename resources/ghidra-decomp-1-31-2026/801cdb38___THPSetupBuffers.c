// Function: __THPSetupBuffers
// Entry: 801cdb38
// Size: 68 bytes

void __THPSetupBuffers(void)

{
  DAT_8032e398 = DAT_8032f5ec + 0x1fU & 0xffffffe0;
  DAT_8032e39c = DAT_8032e398 + 0x80;
  DAT_8032e3a0 = DAT_8032e398 + 0x100;
  DAT_8032e3a4 = DAT_8032e398 + 0x180;
  DAT_8032e3a8 = DAT_8032e398 + 0x200;
  DAT_8032e3ac = DAT_8032e398 + 0x280;
  return;
}

