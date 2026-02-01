// Function: MWEnterCriticalSection
// Entry: 801af670
// Size: 48 bytes

void MWEnterCriticalSection(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  *param_1 = uVar1;
  return;
}

