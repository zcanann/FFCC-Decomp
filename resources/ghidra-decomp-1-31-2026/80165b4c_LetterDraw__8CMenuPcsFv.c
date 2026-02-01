// Function: LetterDraw__8CMenuPcsFv
// Entry: 80165b4c
// Size: 56 bytes

void LetterDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) == 0) {
    LetterListDraw__8CMenuPcsFv();
  }
  else {
    LetterMessDraw__8CMenuPcsFv();
  }
  return;
}

