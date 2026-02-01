// Function: SamplingHandler
// Entry: 8018ecd4
// Size: 96 bytes

void SamplingHandler(undefined4 param_1,undefined4 param_2)

{
  undefined auStack_2d0 [716];
  
  if (DAT_8032f154 != (code *)0x0) {
    OSClearContext(auStack_2d0);
    OSSetCurrentContext(auStack_2d0);
    (*DAT_8032f154)();
    OSClearContext(auStack_2d0);
    OSSetCurrentContext(param_2);
  }
  return;
}

