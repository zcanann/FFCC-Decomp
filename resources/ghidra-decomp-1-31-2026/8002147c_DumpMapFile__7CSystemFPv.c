// Function: DumpMapFile__7CSystemFPv
// Entry: 8002147c
// Size: 56 bytes

CSystem * DumpMapFile__7CSystemFPv(CSystem *system)

{
  undefined4 in_r4;
  
  OSInitStopwatch(&system->m_stopwatch,in_r4);
  OSResetStopwatch(&system->m_stopwatch);
  return system;
}

