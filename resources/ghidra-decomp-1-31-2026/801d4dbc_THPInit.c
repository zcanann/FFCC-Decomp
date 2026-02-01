// Function: THPInit
// Entry: 801d4dbc
// Size: 160 bytes

undefined4 THPInit(void)

{
  OSRegisterVersion(DAT_8032ec38);
  DAT_8032e380 = 0xe0000000;
  DAT_8032e384 = 0xe0002000;
  DAT_8032e388 = 0xe0002800;
  DAT_8032e38c = 0xe0000000;
  DAT_8032e390 = 0xe0002800;
  DAT_8032e394 = 0xe0003200;
  DAT_8032f5f4 = 1;
  return 1;
}

