// Function: OSStopStopwatch
// Entry: 8018087c
// Size: 204 bytes

void OSStopStopwatch(OSStopwatch *osStopwatch)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined8 uVar5;
  
  if (osStopwatch->running != 0) {
    uVar5 = OSGetTime();
    uVar2 = *(uint *)((int)&osStopwatch->last + 4);
    uVar4 = (uint)uVar5 - uVar2;
    uVar3 = *(uint *)((int)&osStopwatch->total + 4);
    uVar2 = (int)((ulonglong)uVar5 >> 0x20) -
            ((uint)((uint)uVar5 < uVar2) + *(int *)&osStopwatch->last);
    iVar1 = *(int *)&osStopwatch->total;
    *(uint *)((int)&osStopwatch->total + 4) = uVar3 + uVar4;
    *(uint *)&osStopwatch->total = iVar1 + uVar2 + CARRY4(uVar3,uVar4);
    osStopwatch->running = 0;
    osStopwatch->hits = osStopwatch->hits + 1;
    if ((*(uint *)&osStopwatch->max ^ 0x80000000) <
        (uint)(*(uint *)((int)&osStopwatch->max + 4) < uVar4) + (uVar2 ^ 0x80000000)) {
      *(uint *)((int)&osStopwatch->max + 4) = uVar4;
      *(uint *)&osStopwatch->max = uVar2;
    }
    if ((uVar2 ^ 0x80000000) <
        (uint)(uVar4 < *(uint *)((int)&osStopwatch->min + 4)) +
        (*(uint *)&osStopwatch->min ^ 0x80000000)) {
      *(uint *)((int)&osStopwatch->min + 4) = uVar4;
      *(uint *)&osStopwatch->min = uVar2;
    }
  }
  return;
}

