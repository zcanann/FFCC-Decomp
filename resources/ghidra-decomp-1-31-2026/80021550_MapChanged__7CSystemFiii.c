// Function: MapChanged__7CSystemFiii
// Entry: 80021550
// Size: 124 bytes

void MapChanged__7CSystemFiii
               (CSystem *system,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined *puVar1;
  
  for (puVar1 = *(undefined **)((int)&(system->m_stopwatch).max + 4);
      (int64_t *)puVar1 != &(system->m_stopwatch).total; puVar1 = *(undefined **)(puVar1 + 0x14)) {
    if (*(int *)(puVar1 + 0x20) == *(int *)(puVar1 + 0x1c) + 0x1c) {
      (**(code **)(**(int **)(puVar1 + 0x18) + 0x20))
                (*(int **)(puVar1 + 0x18),param_2,param_3,param_4);
    }
  }
  return;
}

