// Function: destroy__9CSoundPcsFv
// Entry: 800d8774
// Size: 80 bytes

void destroy__9CSoundPcsFv(void)

{
  CancelLoadWaveASync__6CSoundFv(&Sound);
  StopStream__6CSoundFv(&Sound);
  StopAndFreeAllSe__6CSoundFi(&Sound,1);
  FreeBlock__6CSoundFv(&Sound);
  return;
}

