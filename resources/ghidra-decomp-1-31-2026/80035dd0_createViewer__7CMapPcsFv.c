// Function: createViewer__7CMapPcsFv
// Entry: 80035dd0
// Size: 80 bytes

void createViewer__7CMapPcsFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(undefined4 *)(param_1 + 0x180) = 1;
  *(undefined *)(param_1 + 0x184) = 0;
  Create__7CMapMngFv(&MapMng);
  *(undefined4 *)(param_1 + 0x17c) = 1;
  return;
}

