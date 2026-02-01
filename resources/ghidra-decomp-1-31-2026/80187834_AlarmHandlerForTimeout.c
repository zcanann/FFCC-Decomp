// Function: AlarmHandlerForTimeout
// Entry: 80187834
// Size: 112 bytes

void AlarmHandlerForTimeout(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  code *pcVar2;
  undefined auStack_2d0 [716];
  
  __OSMaskInterrupts(0x400);
  OSClearContext(auStack_2d0);
  OSSetCurrentContext(auStack_2d0);
  pcVar2 = DAT_8032f020;
  bVar1 = DAT_8032f020 != (code *)0x0;
  DAT_8032f020 = (code *)0x0;
  if (bVar1) {
    (*pcVar2)(0x10);
  }
  OSClearContext(auStack_2d0);
  OSSetCurrentContext(param_2);
  return;
}

