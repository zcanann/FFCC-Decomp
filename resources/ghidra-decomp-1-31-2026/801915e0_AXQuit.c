// Function: AXQuit
// Entry: 801915e0
// Size: 52 bytes

void AXQuit(void)

{
  __AXAllocQuit();
  __AXVPBQuit();
  __AXSPBQuit();
  __AXAuxQuit();
  __AXClQuit();
  __AXOutQuit();
  return;
}

