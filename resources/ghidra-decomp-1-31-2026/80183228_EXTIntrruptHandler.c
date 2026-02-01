// Function: EXTIntrruptHandler
// Entry: 80183228
// Size: 208 bytes

void EXTIntrruptHandler(short param_1,undefined4 param_2)

{
  int iVar1;
  code *pcVar2;
  undefined auStack_2d8 [712];
  
  iVar1 = (param_1 + -0xb) / 3;
  __OSMaskInterrupts(0x500000 >> iVar1 * 3);
  pcVar2 = (code *)FatalContext[iVar1 * 0x10 + 0x299];
  FatalContext[iVar1 * 0x10 + 0x29a] = FatalContext[iVar1 * 0x10 + 0x29a] & 0xfffffff7;
  if (pcVar2 != (code *)0x0) {
    OSClearContext(auStack_2d8);
    OSSetCurrentContext(auStack_2d8);
    FatalContext[iVar1 * 0x10 + 0x299] = 0;
    (*pcVar2)(iVar1,param_2);
    OSClearContext(auStack_2d8);
    OSSetCurrentContext(param_2);
  }
  return;
}

