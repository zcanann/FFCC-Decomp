// Function: TRKInterruptHandlerEnableInterrupts
// Entry: 801abe5c
// Size: 84 bytes

void TRKInterruptHandlerEnableInterrupts(void)

{
  sync(0);
  sync(0);
  TRKPostInterruptEvent
            (DAT_8032a130,DAT_8032a134,DAT_8032a138,DAT_8032a13c,DAT_8032a140,DAT_8032a144,
             DAT_8032a148,DAT_8032a14c);
  return;
}

