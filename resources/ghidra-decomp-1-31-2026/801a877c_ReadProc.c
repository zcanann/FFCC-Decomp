// Function: ReadProc
// Entry: 801a877c
// Size: 96 bytes

void ReadProc(int param_1)

{
  param_1 = param_1 * 0x100;
  if (*(int *)(&DAT_80328340 + param_1) == 0) {
    memcpy(*(void **)(&DAT_80328338 + param_1),&DAT_80328325 + param_1,4);
    **(byte **)(&DAT_80328334 + param_1) = (&DAT_80328329)[param_1] & 0x3a;
  }
  return;
}

