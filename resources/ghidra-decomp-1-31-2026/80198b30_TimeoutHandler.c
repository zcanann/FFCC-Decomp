// Function: TimeoutHandler
// Entry: 80198b30
// Size: 164 bytes

void TimeoutHandler(undefined *param_1)

{
  code *pcVar1;
  int *piVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  piVar2 = &DAT_80327540;
  if (param_1 != &DAT_80327620) {
    uVar3 = 1;
    piVar2 = &DAT_80327650;
    if (param_1 != (undefined *)0x80327730) {
      uVar3 = 2;
      piVar2 = &DAT_80327650;
    }
  }
  if (*piVar2 != 0) {
    EXISetExiCallback(uVar3,0);
    pcVar1 = (code *)piVar2[0x33];
    if (pcVar1 != (code *)0x0) {
      piVar2[0x33] = 0;
      (*pcVar1)(uVar3,0xfffffffb);
    }
  }
  return;
}

