// Function: _ExecuteCommand__Fv
// Entry: 801bdbd0
// Size: 120 bytes

void _ExecuteCommand__Fv(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = DAT_8032f3d8;
  piVar2 = DAT_8032f3dc;
  while (piVar1 != piVar2) {
    if (*piVar2 != 0) {
      (*(code *)*piVar2)(piVar2 + 1);
    }
    piVar2 = piVar2 + 8;
    if (piVar2 == DAT_8032f3d4 + 0x800) {
      piVar2 = DAT_8032f3d4;
    }
  }
  DAT_8032f3dc = piVar2;
  return;
}

