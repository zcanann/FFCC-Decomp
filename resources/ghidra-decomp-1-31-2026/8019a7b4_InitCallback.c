// Function: InitCallback
// Entry: 8019a7b4
// Size: 112 bytes

void InitCallback(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  puVar2 = &DAT_80327540;
  if (param_1 != -0x7fcd8a90) {
    puVar2 = &DAT_80327650;
  }
  uVar3 = puVar2[0x20];
  DSPSendMailToDSP(0xff000000);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(uVar3);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  return;
}

