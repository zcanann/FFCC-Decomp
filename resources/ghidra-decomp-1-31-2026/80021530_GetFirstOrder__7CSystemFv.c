// Function: GetFirstOrder__7CSystemFv
// Entry: 80021530
// Size: 32 bytes

undefined * GetFirstOrder__7CSystemFv(CSystem *system)

{
  undefined *puVar1;
  
  puVar1 = *(undefined **)((int)&(system->m_stopwatch).max + 4);
  if ((int64_t *)puVar1 == &(system->m_stopwatch).total) {
    return (undefined *)0x0;
  }
  return puVar1;
}

