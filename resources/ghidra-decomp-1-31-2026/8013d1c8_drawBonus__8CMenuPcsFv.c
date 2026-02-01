// Function: drawBonus__8CMenuPcsFv
// Entry: 8013d1c8
// Size: 216 bytes

void drawBonus__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  ClearZBufferRect__5CUtilFffff
            ((double)FLOAT_80331eac,(double)FLOAT_80331eac,(double)FLOAT_80331fb8,
             (double)FLOAT_80331fbc,&DAT_8032ec70);
  if (System.m_execParam != 0) {
    Printf__7CSystemFPce
              (&System,s_draw_Bonus___d__801dd5c0,
               (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c));
  }
  switch(*(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c)) {
  case 0:
    DrawResultOpenAnim__8CMenuPcsFv(menuPcs);
    break;
  case 1:
    DrawResultCountAnim__8CMenuPcsFv(menuPcs);
    break;
  case 2:
    DrawResultCloseAnim__8CMenuPcsFv(menuPcs);
    break;
  case 3:
    DrawSelectOpenAnim__8CMenuPcsFv(menuPcs);
    break;
  case 4:
    DrawSelectOpenAnim__8CMenuPcsFv(menuPcs);
    break;
  case 5:
    DrawSelectOpenAnim__8CMenuPcsFv(menuPcs);
  }
  return;
}

