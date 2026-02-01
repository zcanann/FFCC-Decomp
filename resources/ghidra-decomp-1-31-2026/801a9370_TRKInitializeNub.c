// Function: TRKInitializeNub
// Entry: 801a9370
// Size: 332 bytes

/* WARNING: Removing unreachable block (ram,0x801a93cc) */
/* WARNING: Removing unreachable block (ram,0x801a93e0) */
/* WARNING: Removing unreachable block (ram,0x801a93d8) */

int TRKInitializeNub(void)

{
  int iVar1;
  int iVar2;
  
  DAT_80328748 = 1;
  MWTRACE(1,s_Initialize_NUB_801e663c);
  usr_put_initialize();
  iVar1 = TRKInitializeEventQueue();
  if (iVar1 == 0) {
    iVar1 = TRKInitializeMessageBuffers();
  }
  if (iVar1 == 0) {
    iVar1 = TRKInitializeDispatcher();
  }
  InitializeProgramEndTrap();
  if (iVar1 == 0) {
    iVar1 = TRKInitializeSerialHandler();
  }
  if (iVar1 == 0) {
    iVar1 = TRKInitializeTarget();
  }
  if (iVar1 == 0) {
    iVar2 = TRKInitializeIntDrivenUART(0xe100,1,0,&DAT_8032f358);
    TRKTargetSetInputPendingPtr(DAT_8032f358);
    if (iVar2 != 0) {
      iVar1 = iVar2;
    }
  }
  return iVar1;
}

