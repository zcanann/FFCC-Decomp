// Function: create__12CMiniGamePcsFv
// Entry: 8012b0d4
// Size: 172 bytes

void create__12CMiniGamePcsFv(int param_1)

{
  *(undefined *)(param_1 + 0x1348) = 0;
  *(undefined *)(param_1 + 0x1350) = 0;
  *(undefined4 *)(param_1 + 0x1354) = 0;
  *(undefined4 *)(param_1 + 0x135c) = 0;
  *(undefined *)(param_1 + 0x134a) = 0;
  *(undefined *)(param_1 + 0x134b) = 0xf;
  *(undefined *)(param_1 + 0x649c) = 0;
  *(undefined *)(param_1 + 0x134c) = 0;
  if ((*(byte *)(param_1 + 0x134b) & 1) != 0) {
    *(char *)(param_1 + 0x134c) = *(char *)(param_1 + 0x134c) + '\x01';
  }
  if ((*(byte *)(param_1 + 0x134b) & 2) != 0) {
    *(char *)(param_1 + 0x134c) = *(char *)(param_1 + 0x134c) + '\x01';
  }
  if ((*(byte *)(param_1 + 0x134b) & 4) != 0) {
    *(char *)(param_1 + 0x134c) = *(char *)(param_1 + 0x134c) + '\x01';
  }
  if ((*(byte *)(param_1 + 0x134b) & 8) == 0) {
    return;
  }
  *(char *)(param_1 + 0x134c) = *(char *)(param_1 + 0x134c) + '\x01';
  return;
}

