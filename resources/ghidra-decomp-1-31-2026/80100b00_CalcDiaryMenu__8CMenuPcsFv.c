// Function: CalcDiaryMenu__8CMenuPcsFv
// Entry: 80100b00
// Size: 1616 bytes

/* WARNING: Removing unreachable block (ram,0x8010112c) */
/* WARNING: Removing unreachable block (ram,0x80100b10) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcDiaryMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  undefined *puVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  undefined8 local_48;
  double local_40;
  undefined8 local_38;
  double local_30;
  
  if (DAT_8032ee32 == '\0') {
    DAT_8032ee31 = 0;
    DAT_8032ee32 = '\x01';
  }
  uVar2 = -(int)(char)MemoryCardMan.m_currentSlot - 1U | (int)(char)MemoryCardMan.m_currentSlot + 1U
  ;
  uVar4 = -((int)uVar2 >> 0x1f);
  if (uVar4 != DAT_8032ee31) {
    if (2 < (uint)System.m_execParam) {
      pcVar3 = s_FALSE_803317f4;
      if (uVar4 != 0) {
        pcVar3 = &DAT_803317ec;
      }
      Printf__7CSystemFPce(&System,s_mount____s_801dc460,pcVar3);
    }
    DAT_8032ee31 = (byte)(uVar2 >> 0x1f);
  }
  WMChgMenu__8CMenuPcsFv(menuPcs);
  dVar8 = DOUBLE_80331408;
  if (menuPcs->field_0xd == '\0') {
    iVar6 = 4;
    puVar5 = &menuPcs->field_0x10;
    do {
      Calc__5CMenuFv(*(CMenu **)(puVar5 + 0x10c));
      iVar6 = iVar6 + 1;
      puVar5 = puVar5 + 4;
    } while (iVar6 < 6);
  }
  else {
    iVar6 = *(int *)&menuPcs->field_0x82c;
    switch(*(undefined2 *)(iVar6 + 0x1c)) {
    case 0:
      sVar1 = *(short *)(iVar6 + 0x10);
      if (sVar1 < 5) {
        if (sVar1 == 0) {
          uVar4 = (int)*(short *)(iVar6 + 0x22) - 10;
        }
        else if ((sVar1 < 1) || (3 < sVar1)) {
          uVar4 = -(int)*(short *)(iVar6 + 0x22);
        }
        else {
          uVar4 = 0;
        }
        *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
        iVar6 = *(int *)&menuPcs->field_0x820;
        local_48 = (double)(CONCAT44(0x43300000,
                                     (int)*(short *)(iVar6 + 8) + (int)*(short *)(iVar6 + 4)) ^
                           0x80000000);
        *(short *)(iVar6 + 0x20) = (short)(int)(FLOAT_803313e0 - (float)(local_48 - dVar8));
        if ((int)uVar4 < 0) {
          local_40 = (double)(CONCAT44(0x43300000,
                                       (int)*(short *)(*(int *)&menuPcs->field_0x820 + 8) +
                                       (int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^
                             0x80000000);
          dVar7 = (double)(float)(local_40 - dVar8);
          if (-0xb < (int)uVar4) {
            uVar2 = (int)uVar4 >> 0x1f;
            local_40 = (double)(CONCAT44(0x43300000,(uVar2 ^ uVar4) - uVar2) ^ 0x80000000);
            uVar2 = (uVar2 ^ uVar4) - uVar2;
            dVar8 = (double)(float)(dVar7 * DOUBLE_803314e8 * (local_40 - dVar8));
            if ((int)uVar2 < 0) {
              uVar2 = 0;
            }
            if (10 < (int)uVar2) {
              uVar2 = 10;
            }
            local_48 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
            dVar7 = (double)sin((double)(FLOAT_803314bc *
                                        (float)(local_48 - DOUBLE_80331408) * FLOAT_803316d4));
            dVar7 = (double)(float)(dVar8 * (double)(float)dVar7);
          }
          dVar8 = DOUBLE_80331408;
          local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)
                                      ) ^ 0x80000000);
          *(short *)(*(int *)&menuPcs->field_0x820 + 4) =
               (short)(int)((double)(float)(local_40 - DOUBLE_80331408) - dVar7);
          local_38 = (double)(CONCAT44(0x43300000,
                                       (int)*(short *)(*(int *)&menuPcs->field_0x820 + 0x20)) ^
                             0x80000000);
          *(short *)(*(int *)&menuPcs->field_0x820 + 0x20) =
               (short)(int)((double)(float)(local_38 - dVar8) + dVar7);
        }
        CalcMainMenuSub__8CMenuPcsFv(menuPcs);
      }
      break;
    case 1:
      calcWorld__8CMenuPcsFv(menuPcs);
      break;
    case 2:
      CalcMCardMenu__8CMenuPcsFv(menuPcs);
      break;
    case 3:
      if (*(short *)&menuPcs->field_0x868 == 0) {
        if (*(char *)(iVar6 + 0xc) == '\0') {
          *(undefined *)(*(int *)&menuPcs->field_0x824 + 0xc) = 1;
          *(undefined *)(*(int *)&menuPcs->field_0x824 + 0x40) = 1;
          *(undefined *)(*(int *)&menuPcs->field_0x824 + 0x74) = 1;
          *(undefined *)(*(int *)&menuPcs->field_0x824 + 0xa8) = 1;
          *(undefined *)(*(int *)&menuPcs->field_0x824 + 0xdc) = 1;
          *(undefined *)(*(int *)&menuPcs->field_0x824 + 0x110) = 1;
          *(undefined *)(*(int *)&menuPcs->field_0x824 + 0x144) = 1;
          *(undefined *)(*(int *)&menuPcs->field_0x824 + 0x178) = 1;
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
        }
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) < 5) {
          CalcCharaSelect__8CMenuPcsFv(menuPcs);
          dVar8 = DOUBLE_80331408;
          iVar6 = *(int *)&menuPcs->field_0x82c;
          sVar1 = *(short *)(iVar6 + 0x10);
          if (sVar1 == 0) {
            uVar4 = (int)*(short *)(iVar6 + 0x22) - 10;
          }
          else if ((sVar1 < 1) || (3 < sVar1)) {
            uVar4 = -(int)*(short *)(iVar6 + 0x22);
          }
          else {
            uVar4 = 0;
          }
          *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
          iVar6 = *(int *)&menuPcs->field_0x820;
          local_30 = (double)(CONCAT44(0x43300000,
                                       (int)*(short *)(iVar6 + 8) + (int)*(short *)(iVar6 + 4)) ^
                             0x80000000);
          *(short *)(iVar6 + 0x20) = (short)(int)(FLOAT_803313e0 - (float)(local_30 - dVar8));
          if ((int)uVar4 < 0) {
            local_30 = (double)(CONCAT44(0x43300000,
                                         (int)*(short *)(*(int *)&menuPcs->field_0x820 + 8) +
                                         (int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^
                               0x80000000);
            dVar7 = (double)(float)(local_30 - dVar8);
            if (-0xb < (int)uVar4) {
              uVar2 = (int)uVar4 >> 0x1f;
              local_30 = (double)(CONCAT44(0x43300000,(uVar2 ^ uVar4) - uVar2) ^ 0x80000000);
              uVar2 = (uVar2 ^ uVar4) - uVar2;
              dVar8 = (double)(float)(dVar7 * DOUBLE_803314e8 * (local_30 - dVar8));
              if ((int)uVar2 < 0) {
                uVar2 = 0;
              }
              if (10 < (int)uVar2) {
                uVar2 = 10;
              }
              local_38 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
              dVar7 = (double)sin((double)(FLOAT_803314bc *
                                          (float)(local_38 - DOUBLE_80331408) * FLOAT_803316d4));
              dVar7 = (double)(float)(dVar8 * (double)(float)dVar7);
            }
            dVar8 = DOUBLE_80331408;
            local_30 = (double)(CONCAT44(0x43300000,
                                         (int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^
                               0x80000000);
            *(short *)(*(int *)&menuPcs->field_0x820 + 4) =
                 (short)(int)((double)(float)(local_30 - DOUBLE_80331408) - dVar7);
            local_40 = (double)(CONCAT44(0x43300000,
                                         (int)*(short *)(*(int *)&menuPcs->field_0x820 + 0x20)) ^
                               0x80000000);
            *(short *)(*(int *)&menuPcs->field_0x820 + 0x20) =
                 (short)(int)((double)(float)(local_40 - dVar8) + dVar7);
          }
          sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
          if ((0 < sVar1) && (sVar1 < 4)) {
            CalcChara__8CMenuPcsFv(menuPcs);
          }
        }
      }
      else {
        CalcSingCMake__8CMenuPcsFv(menuPcs);
      }
      break;
    case 4:
      if (((*(short *)(iVar6 + 0x10) != 0) || (menuPcs->field_0x12 != '\0')) &&
         (*(short *)(iVar6 + 0x10) < 4)) {
        if (Game.game.m_gameWork.m_chaliceElement != *(int *)&menuPcs->field_0x84) {
          SetCrystalCageAttr__8CMenuPcsFv(menuPcs);
        }
        if (Game.game.m_gameWork.m_timerA != *(int *)&menuPcs->field_0x70) {
          SetManaWaterEffect__8CMenuPcsFv(menuPcs);
        }
        CalcFukidashi__8CMenuPcsFv(menuPcs);
        CalcPitcher__8CMenuPcsFv(menuPcs);
        CalcWMFrame__8CMenuPcsFv(menuPcs);
      }
      break;
    case 5:
      CalcLoadMenu__8CMenuPcsFv(menuPcs);
      break;
    case 6:
      CalcTitleMenu__8CMenuPcsFv(menuPcs);
      break;
    case 7:
      CalcOptionMenu__8CMenuPcsFv(menuPcs);
      break;
    case 8:
      CalcGoOutMenu__Fv();
      break;
    default:
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error_WM_menu_no_error___801dc424,s_wm_menu_cpp_801dc418,0x4c0)
        ;
      }
    }
    iVar6 = 4;
    puVar5 = &menuPcs->field_0x10;
    do {
      Calc__5CMenuFv(*(CMenu **)(puVar5 + 0x10c));
      iVar6 = iVar6 + 1;
      puVar5 = puVar5 + 4;
    } while (iVar6 < 6);
  }
  return;
}

