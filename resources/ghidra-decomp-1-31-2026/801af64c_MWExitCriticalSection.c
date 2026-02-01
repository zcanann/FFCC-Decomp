// Function: MWExitCriticalSection
// Entry: 801af64c
// Size: 36 bytes

void MWExitCriticalSection(undefined4 *param_1)

{
  OSRestoreInterrupts(*param_1);
  return;
}

