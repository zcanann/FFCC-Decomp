// Function: drawWorld__8CMenuPcsFv
// Entry: 800fc0b0
// Size: 324 bytes

void drawWorld__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  undefined *puVar2;
  
  if (menuPcs->field_0xd == '\0') {
    iVar1 = 4;
    puVar2 = &menuPcs->field_0x10;
    do {
      Draw__5CMenuFv(*(CMenuPcs **)(puVar2 + 0x10c));
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 4;
    } while (iVar1 < 6);
  }
  else {
    switch(*(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c)) {
    case 0:
      DrawMainMenu__8CMenuPcsFv();
      break;
    case 1:
      DrawDiaryMenu__8CMenuPcsFv();
      break;
    case 2:
      DrawMCardMenu__8CMenuPcsFv();
      break;
    case 3:
      if (*(short *)&menuPcs->field_0x868 == 0) {
        DrawCMakeMenu__8CMenuPcsFv();
      }
      else {
        DrawSingCMake__8CMenuPcsFv();
      }
      break;
    case 4:
      DrawMoveMenu__8CMenuPcsFv();
      break;
    case 5:
      DrawLoadMenu__8CMenuPcsFv();
      break;
    case 6:
      DrawTitleMenu__8CMenuPcsFv();
      break;
    case 7:
      DrawOptionMenu__8CMenuPcsFv(menuPcs);
      break;
    case 8:
      DrawGoOutMenu__Fv();
      break;
    default:
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error_WM_menu_no_error___801dc424,s_wm_menu_cpp_801dc418,0xc59)
        ;
      }
    }
    iVar1 = 4;
    puVar2 = &menuPcs->field_0x10;
    do {
      Draw__5CMenuFv(*(CMenuPcs **)(puVar2 + 0x10c));
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 4;
    } while (iVar1 < 6);
    DrawInit__8CMenuPcsFv(menuPcs);
  }
  return;
}

