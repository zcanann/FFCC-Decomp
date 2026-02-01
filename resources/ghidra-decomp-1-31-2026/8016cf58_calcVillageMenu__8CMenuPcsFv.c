// Function: calcVillageMenu__8CMenuPcsFv
// Entry: 8016cf58
// Size: 580 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calcVillageMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  char *pcVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined2 uVar5;
  int iVar6;
  undefined auStack_88 [128];
  
  if (((menuPcs->field_0x16 != '\0') && (*(short *)&menuPcs->field_0x86c == 0)) &&
     (menuPcs->field_0x16 != '\0')) {
    if (Game.game.m_gameWork.m_menuStageMode == '\0') {
      pcVar2 = GetLangString__5CGameFv(&Game.game);
      sprintf(auStack_88,s_dvd__smenu_subfont_fnt_801e3020,pcVar2);
      loadFont__8CMenuPcsFiPcii(menuPcs,2,auStack_88,4,0xffffffff);
    }
    loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii
              (menuPcs,&PTR_s_world2_802159a4,8,1,&DAT_802159c8,0x60,9,3);
    uVar3 = __nw__FUlPQ27CMemory6CStagePci(0x48,MenuPcs._236_4_,s_cmake_cpp_801e3038,0xcb3);
    *(undefined4 *)&menuPcs->field_0x830 = uVar3;
    memset(*(undefined4 *)&menuPcs->field_0x830,0,0x48);
    strcpy(&s_CmakeInfo,0x8021ff68);
    *(undefined2 *)&menuPcs->field_0x86c = 1;
  }
  sVar1 = *(short *)&menuPcs->field_0x86c;
  if (sVar1 != 0) {
    if ((menuPcs->field_0x16 == '\0') && (sVar1 != 0)) {
      if (sVar1 != 0) {
        if ((Game.game.m_gameWork.m_menuStageMode == '\0') &&
           (piVar4 = *(int **)&menuPcs->field_0x108, piVar4 != (int *)0x0)) {
          iVar6 = piVar4[1];
          piVar4[1] = iVar6 + -1;
          if ((iVar6 + -1 == 0) && (piVar4 != (int *)0x0)) {
            (**(code **)(*piVar4 + 8))(piVar4,1);
          }
          *(undefined4 *)&menuPcs->field_0x108 = 0;
        }
        freeTexture__8CMenuPcsFiiii(menuPcs,8,1,0x60,9);
        if (*(int *)&menuPcs->field_0x830 != 0) {
          __dl__FPv();
          *(undefined4 *)&menuPcs->field_0x830 = 0;
        }
        *(undefined2 *)&menuPcs->field_0x86c = 0;
      }
    }
    else {
      iVar6 = *(int *)&menuPcs->field_0x830;
      if (*(short *)(iVar6 + 0x10) == 0) {
        if (*(short *)(iVar6 + 0x22) < 10) {
          uVar5 = 0;
          *(short *)(iVar6 + 0x22) = *(short *)(iVar6 + 0x22) + 1;
        }
        else {
          uVar5 = 1;
        }
      }
      else if (*(short *)(iVar6 + 0x10) == 1) {
        uVar5 = CmakeVillageCtrl__8CMenuPcsFv(menuPcs);
      }
      else if (*(short *)(iVar6 + 0x22) < 10) {
        uVar5 = 0;
        *(short *)(iVar6 + 0x22) = *(short *)(iVar6 + 0x22) + 1;
      }
      else {
        uVar5 = 1;
      }
      *(undefined2 *)(iVar6 + 0x2e) = uVar5;
    }
  }
  return;
}

