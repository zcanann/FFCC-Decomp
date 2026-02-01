// Function: EXIIntrruptHandler
// Entry: 80182f48
// Size: 200 bytes

void EXIIntrruptHandler(short param_1,undefined4 param_2)

{
  int iVar1;
  code *pcVar2;
  undefined auStack_2e0 [724];
  
  iVar1 = (param_1 + -9) / 3;
  (&DAT_cc006800)[iVar1 * 5] = (&DAT_cc006800)[iVar1 * 5] & 0x7f5 | 2;
  pcVar2 = (code *)FatalContext[iVar1 * 0x10 + 0x297];
  if (pcVar2 != (code *)0x0) {
    OSClearContext(auStack_2e0);
    OSSetCurrentContext(auStack_2e0);
    (*pcVar2)(iVar1,param_2);
    OSClearContext(auStack_2e0);
    OSSetCurrentContext(param_2);
  }
  return;
}

