// Function: create__7CMapPcsFv
// Entry: 80035e20
// Size: 64 bytes

void create__7CMapPcsFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(undefined4 *)(param_1 + 0x180) = 1;
  *(undefined *)(param_1 + 0x184) = 0;
  Create__7CMapMngFv(&MapMng);
  return;
}

