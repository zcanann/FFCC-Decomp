// Function: calc__11CGraphicPcsFv
// Entry: 800475b0
// Size: 200 bytes

/* WARNING: Removing unreachable block (ram,0x800475fc) */
/* WARNING: Removing unreachable block (ram,0x80047610) */
/* WARNING: Removing unreachable block (ram,0x80047658) */

void calc__11CGraphicPcsFv(int param_1)

{
  if ((0 < *(int *)(param_1 + 4)) &&
     (*(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1, *(int *)(param_1 + 4) == 0)) {
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  if ((0 < *(int *)(param_1 + 0x5c)) &&
     (*(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + -1, *(int *)(param_1 + 0x5c) == 0)) {
    *(undefined4 *)(param_1 + 0x74) = 0;
  }
  if (0 < *(int *)(param_1 + 0x88)) {
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + -1;
    if (*(int *)(param_1 + 0x88) == 0) {
      *(undefined4 *)(param_1 + 0xa0) = 0;
      return;
    }
    return;
  }
  return;
}

