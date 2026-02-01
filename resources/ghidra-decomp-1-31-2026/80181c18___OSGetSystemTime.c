// Function: __OSGetSystemTime
// Entry: 80181c18
// Size: 100 bytes

longlong __OSGetSystemTime(void)

{
  longlong lVar1;
  undefined4 uVar2;
  longlong lVar3;
  
  uVar2 = OSDisableInterrupts();
  lVar3 = OSGetTime();
  lVar1 = CONCAT44(DAT_800030d8,DAT_800030dc);
  OSRestoreInterrupts(uVar2);
  return lVar3 + lVar1;
}

