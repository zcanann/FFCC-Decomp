// Function: OSInitStopwatch
// Entry: 80180814
// Size: 44 bytes

void OSInitStopwatch(OSStopwatch *osStopwatch,char *name)

{
  osStopwatch->name = name;
  *(undefined4 *)((int)&osStopwatch->total + 4) = 0;
  *(undefined4 *)&osStopwatch->total = 0;
  osStopwatch->hits = 0;
  *(undefined4 *)((int)&osStopwatch->min + 4) = 0xffffffff;
  *(undefined4 *)&osStopwatch->min = 0;
  *(undefined4 *)((int)&osStopwatch->max + 4) = 0;
  *(undefined4 *)&osStopwatch->max = 0;
  return;
}

