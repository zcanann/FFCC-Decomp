// Function: TRKInitializeMessageBuffers
// Entry: 801a9cc8
// Size: 116 bytes

undefined4 TRKInitializeMessageBuffers(void)

{
  int iVar1;
  undefined *puVar2;
  
  puVar2 = &DAT_80328750;
  iVar1 = 0;
  do {
    TRKInitializeMutex(puVar2);
    TRKAcquireMutex(puVar2);
    *(undefined4 *)(puVar2 + 4) = 0;
    TRKReleaseMutex(puVar2);
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x890;
  } while (iVar1 < 3);
  return 0;
}

