// Function: _RedAXCallback__Fv
// Entry: 801be5d0
// Size: 56 bytes

void _RedAXCallback__Fv(void)

{
  DAT_8032f3b8 = DAT_8032f3b8 + 1;
  EnvelopeKeyExecute__Fv();
  OSSignalSemaphore((OSSemaphore *)&DAT_8032d778);
  return;
}

