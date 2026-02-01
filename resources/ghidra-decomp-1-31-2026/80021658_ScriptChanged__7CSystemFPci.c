// Function: ScriptChanged__7CSystemFPci
// Entry: 80021658
// Size: 140 bytes

void ScriptChanged__7CSystemFPci(CSystem *system,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  
  for (puVar1 = *(undefined **)((int)&(system->m_stopwatch).max + 4);
      (int64_t *)puVar1 != &(system->m_stopwatch).total; puVar1 = *(undefined **)(puVar1 + 0x14)) {
    if (*(int *)(puVar1 + 0x20) == *(int *)(puVar1 + 0x1c) + 0x1c) {
      (**(code **)(**(int **)(puVar1 + 0x18) + 0x18))(*(int **)(puVar1 + 0x18),param_2,param_3);
    }
  }
  return;
}

