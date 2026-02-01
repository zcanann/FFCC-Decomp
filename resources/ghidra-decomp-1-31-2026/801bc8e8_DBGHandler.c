// Function: DBGHandler
// Entry: 801bc8e8
// Size: 48 bytes

void DBGHandler(short param_1)

{
  DAT_cc003000 = 0x1000;
  if (DAT_8032f3a4 != (code *)0x0) {
    (*DAT_8032f3a4)((int)param_1);
  }
  return;
}

