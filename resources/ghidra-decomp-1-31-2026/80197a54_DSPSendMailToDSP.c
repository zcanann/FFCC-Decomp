// Function: DSPSendMailToDSP
// Entry: 80197a54
// Size: 20 bytes

void DSPSendMailToDSP(undefined4 param_1)

{
  DAT_cc005000 = (short)((uint)param_1 >> 0x10);
  DAT_cc005002 = (short)param_1;
  return;
}

