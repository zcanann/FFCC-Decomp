// Function: OSStartStopwatch
// Entry: 80180840
// Size: 60 bytes

void OSStartStopwatch(OSStopwatch *osStopwatch)

{
  int64_t iVar1;
  
  osStopwatch->running = 1;
  iVar1 = OSGetTime();
  osStopwatch->last = iVar1;
  return;
}

