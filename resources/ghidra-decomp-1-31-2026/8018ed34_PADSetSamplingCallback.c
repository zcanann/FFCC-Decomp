// Function: PADSetSamplingCallback
// Entry: 8018ed34
// Size: 84 bytes

undefined4 PADSetSamplingCallback(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8032f154;
  DAT_8032f154 = param_1;
  if (param_1 == 0) {
    SIUnregisterPollingHandler(SamplingHandler);
  }
  else {
    SIRegisterPollingHandler(SamplingHandler);
  }
  return uVar1;
}

