// Function: __AXProcessAux
// Entry: 80191d28
// Size: 572 bytes

void __AXProcessAux(void)

{
  undefined4 *local_30;
  int local_2c;
  int local_28;
  undefined4 *local_24;
  int local_20;
  int local_1c;
  undefined4 *local_18;
  int local_14;
  int local_10;
  int local_c;
  
  DAT_8032f200 = &DAT_8030cde0 + DAT_8032f210 * 0x1e0;
  DAT_8032f204 = &DAT_8030cde0 + DAT_8032f214 * 0x1e0;
  DAT_8032f208 = &DAT_8030e460 + DAT_8032f210 * 0x1e0;
  DAT_8032f20c = &DAT_8030e460 + DAT_8032f214 * 0x1e0;
  if (DAT_8032f1f0 != (code *)0x0) {
    if (DAT_8032f238 == 2) {
      local_c = DAT_8032f220 * 0x780;
      local_18 = &DAT_8030cde0 + DAT_8032f220 * 0x1e0;
      local_14 = local_c + -0x7fcf2fa0;
      local_10 = local_c + -0x7fcf2d20;
      local_c = local_c + -0x7fcf16a0;
      DCInvalidateRange(local_18,0x780);
      DCInvalidateRange(local_c,0x280);
      (*DAT_8032f1f0)(&local_18,DAT_8032f1f8);
      DCFlushRangeNoSync(local_18,0x780);
      DCFlushRangeNoSync(local_c,0x280);
    }
    else {
      local_24 = &DAT_8030cde0 + DAT_8032f220 * 0x1e0;
      local_20 = DAT_8032f220 * 0x780 + -0x7fcf2fa0;
      local_1c = DAT_8032f220 * 0x780 + -0x7fcf2d20;
      DCInvalidateRange(local_24,0x780);
      (*DAT_8032f1f0)(&local_24,DAT_8032f1f8);
      DCFlushRangeNoSync(local_24,0x780);
    }
  }
  if ((DAT_8032f1f4 != (code *)0x0) && (DAT_8032f238 != 2)) {
    local_30 = &DAT_8030e460 + DAT_8032f220 * 0x1e0;
    local_2c = DAT_8032f220 * 0x780 + -0x7fcf1920;
    local_28 = DAT_8032f220 * 0x780 + -0x7fcf16a0;
    DCInvalidateRange(local_30,0x780);
    (*DAT_8032f1f4)(&local_30,DAT_8032f1fc);
    DCFlushRangeNoSync(local_30,0x780);
  }
  DAT_8032f210 = (DAT_8032f210 + 1) % 3;
  DAT_8032f214 = (DAT_8032f214 + 1) % 3;
  DAT_8032f218 = DAT_8032f218 + 1 & 1;
  DAT_8032f21c = DAT_8032f21c + 1 & 1;
  DAT_8032f220 = (DAT_8032f220 + 1) % 3;
  return;
}

