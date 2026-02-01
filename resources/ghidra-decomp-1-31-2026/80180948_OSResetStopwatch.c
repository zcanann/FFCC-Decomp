// Function: OSResetStopwatch
// Entry: 80180948
// Size: 40 bytes

void OSResetStopwatch(OSStopwatch *stopwatch)

{
  *(undefined4 *)((int)&stopwatch->total + 4) = 0;
  *(undefined4 *)&stopwatch->total = 0;
  stopwatch->hits = 0;
  *(undefined4 *)((int)&stopwatch->min + 4) = 0xffffffff;
  *(undefined4 *)&stopwatch->min = 0;
  *(undefined4 *)((int)&stopwatch->max + 4) = 0;
  *(undefined4 *)&stopwatch->max = 0;
  return;
}

