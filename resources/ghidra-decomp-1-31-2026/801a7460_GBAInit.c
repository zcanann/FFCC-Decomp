// Function: GBAInit
// Entry: 801a7460
// Size: 164 bytes

void GBAInit(void)

{
  uint uVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  
  puVar4 = &DAT_80328320;
  iVar2 = 0;
  uVar1 = DAT_800000f8 / 500000;
  puVar3 = &DAT_80328220;
  do {
    *(uint *)(puVar4 + 0x34) = uVar1 * 0x3c >> 3;
    *(undefined4 *)(puVar4 + 0x30) = 0;
    OSInitThreadQueue(puVar4 + 0x24);
    iVar2 = iVar2 + 1;
    *(undefined **)(puVar4 + 0xf8) = puVar3;
    puVar4 = puVar4 + 0x100;
    puVar3 = puVar3 + 0x40;
  } while (iVar2 < 4);
  OSInitAlarm();
  DSPInit();
  DAT_8032f350 = 0;
  OSRegisterResetFunction(&PTR_OnReset_8021cb38);
  return;
}

