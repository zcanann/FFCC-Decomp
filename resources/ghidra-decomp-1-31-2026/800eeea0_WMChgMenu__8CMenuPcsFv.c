// Function: WMChgMenu__8CMenuPcsFv
// Entry: 800eeea0
// Size: 3480 bytes

/* WARNING: Removing unreachable block (ram,0x800efc1c) */
/* WARNING: Removing unreachable block (ram,0x800eeeb0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void WMChgMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  char cVar1;
  short sVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  byte bVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  double dVar15;
  double dVar16;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  Mtx MStack_70;
  double local_40;
  double local_38;
  
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x20) != 0) {
    iVar14 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c);
    DAT_8032ee1c = 1;
    iVar8 = *(int *)&menuPcs->field_0x82c;
    sVar2 = *(short *)(iVar8 + 0x20);
    if (sVar2 == 2) {
      cVar1 = menuPcs->field_0xd;
      if (cVar1 == '\x01') {
        *(undefined2 *)(iVar8 + 0x1c) = 0;
      }
      else if (cVar1 == '\x02') {
        *(undefined2 *)(iVar8 + 0x1c) = 5;
      }
      else if (cVar1 == '\x03') {
        DAT_8032ee1c = 1;
        if (iVar14 == 6) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x20) = 0;
          return;
        }
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c) = 6;
      }
      else if (cVar1 == '\x04') {
        *(undefined2 *)(iVar8 + 0x1c) = 4;
      }
      else {
        *(undefined2 *)(iVar8 + 0x1c) = 1;
      }
    }
    else if (iVar14 == 0) {
      if (sVar2 == 1) {
        sVar2 = *(short *)(iVar8 + 0x26);
        if (sVar2 == 0) {
          *(undefined2 *)(iVar8 + 0x1c) = 3;
        }
        else if (sVar2 == 1) {
          *(undefined2 *)(iVar8 + 0x1c) = 1;
          memset(*(undefined4 *)&menuPcs->field_0x83c,0,0x10);
        }
        else if (sVar2 == 2) {
          *(undefined2 *)(iVar8 + 0x1c) = 8;
        }
        else if (sVar2 == 3) {
          *(undefined2 *)(iVar8 + 0x1c) = 7;
        }
        else {
          *(undefined2 *)(iVar8 + 0x1c) = 2;
        }
      }
      else {
        *(undefined2 *)(iVar8 + 0x1c) = 4;
      }
    }
    else if (iVar14 == 1) {
      *(undefined2 *)(iVar8 + 0x1c) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 1;
    }
    else if (iVar14 == 8) {
      *(undefined2 *)(iVar8 + 0x1c) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 2;
    }
    else if (iVar14 == 7) {
      *(undefined2 *)(iVar8 + 0x1c) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 3;
    }
    else if (iVar14 == 2) {
      *(undefined2 *)(iVar8 + 0x1c) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 4;
    }
    else if (iVar14 == 5) {
      if (sVar2 == 1) {
        *(undefined2 *)(iVar8 + 0x1c) = 0;
        menuPcs->field_0xd = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
        local_7c = 1;
        local_78 = 1;
        local_74 = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,4,3,&local_7c,(CStack *)0x0);
      }
      else if (sVar2 == -1) {
        DAT_8032ee1c = 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c) = 6;
        local_88 = 1;
        local_84 = 0;
        local_80 = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,4,3,&local_88,(CStack *)0x0);
      }
    }
    else if (iVar14 == 6) {
      *(undefined2 *)(iVar8 + 0x1c) = 0;
    }
    else if (sVar2 == 1) {
      if (*(short *)(iVar8 + 0x1c) < 8) {
        *(short *)(iVar8 + 0x1c) = *(short *)(iVar8 + 0x1c) + 1;
      }
      else {
        menuPcs->field_0xd = 0;
      }
    }
    else if (sVar2 == -1) {
      sVar2 = *(short *)(iVar8 + 0x1c);
      if (sVar2 < 1) {
        menuPcs->field_0xd = 0;
      }
      else if (sVar2 == 3) {
        *(undefined2 *)(iVar8 + 0x1c) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
      }
      else {
        *(short *)(iVar8 + 0x1c) = sVar2 + -1;
      }
    }
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) != 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
    }
    fVar6 = FLOAT_803315b0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    fVar5 = FLOAT_803313e8;
    fVar4 = FLOAT_803313dc;
    local_40 = (double)(longlong)(int)fVar6;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
    dVar16 = DOUBLE_803313f8;
    dVar15 = (double)FLOAT_80331430;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 0;
    local_38 = (double)(longlong)(int)(dVar15 * dVar16);
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 10) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 0;
    *(float *)(*(int *)&menuPcs->field_0x82c + 4) = fVar5;
    **(float **)&menuPcs->field_0x82c = fVar4;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
    **(undefined2 **)&menuPcs->field_0x848 = (short)(int)fVar6;
    *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)(int)(dVar15 * dVar16);
    *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 4) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 6) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
    menuPcs->field_0x86e = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 6) = 0x10;
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 8) = 0xe8;
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 10) = 0x168;
    *(float *)(*(int *)&menuPcs->field_0x820 + 0xc) = fVar4;
    *(float *)(*(int *)&menuPcs->field_0x820 + 0x10) = fVar4;
    *(float *)(*(int *)&menuPcs->field_0x820 + 0x14) = fVar5;
    *(float *)(*(int *)&menuPcs->field_0x820 + 0x18) = fVar5;
    *(undefined4 *)(*(int *)&menuPcs->field_0x820 + 0x1c) = 0;
    iVar8 = *(int *)&menuPcs->field_0x820;
    *(undefined2 *)(iVar8 + 0x20) = *(undefined2 *)(iVar8 + 4);
    *(undefined2 *)(iVar8 + 0x22) = *(undefined2 *)(iVar8 + 6);
    *(undefined2 *)(iVar8 + 0x24) = *(undefined2 *)(iVar8 + 8);
    *(undefined2 *)(iVar8 + 0x26) = *(undefined2 *)(iVar8 + 10);
    *(undefined4 *)(iVar8 + 0x28) = *(undefined4 *)(iVar8 + 0xc);
    *(undefined4 *)(iVar8 + 0x2c) = *(undefined4 *)(iVar8 + 0x10);
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x14);
    *(undefined4 *)(iVar8 + 0x34) = *(undefined4 *)(iVar8 + 0x18);
    *(undefined4 *)(iVar8 + 0x38) = *(undefined4 *)(iVar8 + 0x1c);
    iVar8 = *(int *)&menuPcs->field_0x820;
    *(short *)(iVar8 + 0x20) = 0x280 - (*(short *)(iVar8 + 8) + *(short *)(iVar8 + 4));
    *(undefined4 *)(*(int *)&menuPcs->field_0x820 + 0x38) = 8;
    if ((((iVar14 == 3) && (Game.game.m_gameWork.m_menuStageMode != '\0')) &&
        (-1 < *(short *)&menuPcs->field_0x86a)) && (*(short *)&menuPcs->field_0x86a < 8)) {
      *(undefined2 *)&menuPcs->field_0x868 = 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c) = 3;
    }
    else if (((iVar14 == 3) && (Game.game.m_gameWork.m_menuStageMode != '\0')) &&
            (7 < *(short *)&menuPcs->field_0x86a)) {
      *(undefined2 *)&menuPcs->field_0x868 = 0;
      *(undefined2 *)&menuPcs->field_0x86a = 0xffff;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c) = 3;
    }
    else {
      *(undefined2 *)&menuPcs->field_0x868 = 0;
      *(undefined2 *)&menuPcs->field_0x86a = 0xffff;
    }
    iVar8 = 0;
    *(undefined2 *)&menuPcs->field_0x870 = 0;
    sVar2 = *(short *)(*(float **)&menuPcs->field_0x82c + 7);
    if (sVar2 == 4) {
      **(float **)&menuPcs->field_0x82c = FLOAT_80331440;
    }
    else if (sVar2 < 4) {
      if (sVar2 == 0) {
        iVar11 = -0x7fde1140;
        iVar12 = 4;
        do {
          if (Game.game.m_caravanWorkArr[*(short *)(*(int *)&menuPcs->field_0x82c + iVar8 + 0x36)].
              m_shopState == 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + iVar8 + 0x36) = 0xffff;
          }
          if (Game.game.m_caravanWorkArr[*(short *)(*(int *)&menuPcs->field_0x82c + iVar8 + 0x3e)].
              m_shopState == 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + iVar8 + 0x3e) = 0xffff;
          }
          iVar13 = *(int *)(iVar11 + 0x20);
          if (Game.game.m_caravanWorkArr[iVar13].m_shopState == 0) {
            *(undefined4 *)(iVar11 + 0x20) = 0xffffffff;
          }
          if (Game.game.m_caravanWorkArr[iVar13].m_shopBusyFlag != '\0') {
            *(undefined4 *)(iVar11 + 0x20) = 0xffffffff;
          }
          fVar4 = FLOAT_8033151c;
          dVar16 = DOUBLE_80331408;
          iVar8 = iVar8 + 2;
          iVar11 = iVar11 + 4;
          iVar12 = iVar12 + -1;
        } while (iVar12 != 0);
        local_38 = (double)(CONCAT44(0x43300000,
                                     (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26)) ^
                           0x80000000);
        *(float *)&menuPcs->field_0x78 = -(FLOAT_8033151c * (float)(local_38 - DOUBLE_80331408));
        local_40 = (double)(CONCAT44(0x43300000,
                                     (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26)) ^
                           0x80000000);
        *(float *)&menuPcs->field_0x7c = -(fVar4 * (float)(local_40 - dVar16));
        menuPcs->field_0x80 = 0;
      }
      else if ((-1 < sVar2) && (2 < sVar2)) {
        iVar11 = 0;
        dVar16 = (double)FLOAT_80331664;
        iVar12 = 0;
        iVar13 = *(int *)&menuPcs->field_0x814 + 0xa00;
        do {
          *(undefined *)(*(int *)&menuPcs->field_0x824 + iVar8 + 0xc) = 1;
          iVar3 = iVar12 * 4;
          *(float *)(iVar13 + 0x2c) = (float)dVar16;
          iVar9 = *(int *)&menuPcs->field_0x828 + iVar11;
          *(undefined2 *)(iVar9 + 6) = *(undefined2 *)(iVar9 + 4);
          iVar9 = IsModelLoaded__Q29CCharaPcs7CHandleFi
                            (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar3),1);
          if (iVar9 != 0) {
            PSMTXIdentity(&MStack_70);
            SetMatrix__Q26CChara6CModelFPA4_f
                      (*(CModel **)(*(int *)(&menuPcs->field_0x7f4 + iVar3) + 0x168),&MStack_70);
            CalcMatrix__Q26CChara6CModelFv
                      (*(undefined4 *)(*(int *)(&menuPcs->field_0x7f4 + iVar3) + 0x168));
            CalcSkin__Q26CChara6CModelFv
                      (*(undefined4 *)(*(int *)(&menuPcs->field_0x7f4 + iVar3) + 0x168));
          }
          iVar12 = iVar12 + 1;
          iVar11 = iVar11 + 0x10;
          iVar13 = iVar13 + 0x50;
          iVar8 = iVar8 + 0x34;
        } while (iVar12 < 8);
        iVar8 = 0;
        do {
          ClrCmakeInfo__8GbaQueueFi(&GbaQue,iVar8);
          iVar8 = iVar8 + 1;
        } while (iVar8 < 4);
      }
    }
    else if (sVar2 == 7) {
      GetOptionData__8CMenuPcsFv(menuPcs);
    }
    switch(iVar14) {
    case 0:
      iVar8 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar8 + 0x1c) == 4) {
        Game.game.m_gameWork.m_wmBackupParams[0] = (int32_t)*(short *)(iVar8 + 0x3e);
        Game.game.m_gameWork.m_wmBackupParams[1] = (int32_t)*(short *)(iVar8 + 0x40);
        Game.game.m_gameWork.m_wmBackupParams[2] = (int32_t)*(short *)(iVar8 + 0x42);
        Game.game.m_gameWork.m_wmBackupParams[3] = (int32_t)*(short *)(iVar8 + 0x44);
        menuPcs->field_0x10 = 1;
        menuPcs->field_0x12 = 0;
        menuPcs->field_0x13 = 0;
      }
      else {
        memset(*(undefined4 *)&menuPcs->field_0x828,0,0x80);
        bVar7 = 0;
        iVar8 = 0;
        iVar11 = 0;
        iVar12 = 2;
        do {
          *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0xc) = 0;
          *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0xb) = 0;
          *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 10) = 0;
          sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + iVar11 + 0x3e);
          if (sVar2 < 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x828 + iVar8 + 4) = 0xffff;
          }
          else {
            *(short *)(*(int *)&menuPcs->field_0x828 + iVar8 + 4) = sVar2;
            bVar7 = bVar7 | (byte)(1 << (int)sVar2);
          }
          *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x1c) = 0;
          *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x1b) = 0;
          *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x1a) = 0;
          sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + iVar11 + 0x40);
          if (sVar2 < 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x14) = 0xffff;
          }
          else {
            *(short *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x14) = sVar2;
            bVar7 = bVar7 | (byte)(1 << (int)sVar2);
          }
          iVar8 = iVar8 + 0x20;
          iVar11 = iVar11 + 4;
          iVar12 = iVar12 + -1;
        } while (iVar12 != 0);
        iVar8 = 0;
        iVar11 = 4;
        do {
          if (*(short *)(*(int *)&menuPcs->field_0x828 + iVar8 + 4) < 0) {
            iVar12 = 0;
            uVar10 = (uint)(char)bVar7;
            if (((((uVar10 & 1) != 0) && (iVar12 = 1, (uVar10 & 2) != 0)) &&
                (iVar12 = 2, (uVar10 & 4) != 0)) &&
               (((iVar12 = 3, (uVar10 & 8) != 0 && (iVar12 = 4, (uVar10 & 0x10) != 0)) &&
                ((iVar12 = 5, (uVar10 & 0x20) != 0 &&
                 ((iVar12 = 6, (uVar10 & 0x40) != 0 && (iVar12 = 7, (uVar10 & 0x80) != 0)))))))) {
              iVar12 = 8;
            }
            *(short *)(*(int *)&menuPcs->field_0x828 + iVar8 + 4) = (short)iVar12;
            bVar7 = bVar7 | (byte)(1 << iVar12);
          }
          iVar12 = *(int *)&menuPcs->field_0x828 + iVar8;
          iVar8 = iVar8 + 0x10;
          *(undefined2 *)(iVar12 + 6) = *(undefined2 *)(iVar12 + 4);
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
      }
      break;
    case 1:
      memset(*(undefined4 *)&menuPcs->field_0x83c,0,0x10);
      menuPcs->field_0x11 = 0;
      break;
    case 3:
      if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 4) {
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 10) == '\0') {
          Game.game.m_gameWork.m_wmBackupParams[0] = -1;
        }
        else {
          Game.game.m_gameWork.m_wmBackupParams[0] =
               (int32_t)*(short *)(*(int *)&menuPcs->field_0x828 + 4);
        }
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x3e) =
             (short)Game.game.m_gameWork.m_wmBackupParams[0];
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x1a) == '\0') {
          Game.game.m_gameWork.m_wmBackupParams[1] = -1;
        }
        else {
          Game.game.m_gameWork.m_wmBackupParams[1] =
               (int32_t)*(short *)(*(int *)&menuPcs->field_0x828 + 0x14);
        }
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x40) =
             (short)Game.game.m_gameWork.m_wmBackupParams[1];
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x2a) == '\0') {
          Game.game.m_gameWork.m_wmBackupParams[2] = -1;
        }
        else {
          Game.game.m_gameWork.m_wmBackupParams[2] =
               (int32_t)*(short *)(*(int *)&menuPcs->field_0x828 + 0x24);
        }
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x42) =
             (short)Game.game.m_gameWork.m_wmBackupParams[2];
        if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x3a) == '\0') {
          Game.game.m_gameWork.m_wmBackupParams[3] = -1;
        }
        else {
          Game.game.m_gameWork.m_wmBackupParams[3] =
               (int32_t)*(short *)(*(int *)&menuPcs->field_0x828 + 0x34);
        }
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x44) =
             (short)Game.game.m_gameWork.m_wmBackupParams[3];
        menuPcs->field_0x10 = 1;
        menuPcs->field_0x12 = 0;
        menuPcs->field_0x13 = 0;
      }
      break;
    case 4:
      PlaySe__6CSoundFiiii(&Sound,0x31,0x40,0x7f,0);
      menuPcs->field_0x10 = 0;
      memset(*(undefined4 *)&menuPcs->field_0x828,0,0x80);
      bVar7 = 0;
      iVar8 = 0;
      iVar11 = 0;
      iVar12 = 2;
      do {
        *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0xc) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0xb) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 10) = 0;
        sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + iVar11 + 0x3e);
        if (sVar2 < 0) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x828 + iVar8 + 4) = 0xffff;
        }
        else {
          *(short *)(*(int *)&menuPcs->field_0x828 + iVar8 + 4) = sVar2;
          bVar7 = bVar7 | (byte)(1 << (int)sVar2);
        }
        *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x1c) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x1b) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x1a) = 0;
        sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + iVar11 + 0x40);
        if (sVar2 < 0) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x14) = 0xffff;
        }
        else {
          *(short *)(*(int *)&menuPcs->field_0x828 + iVar8 + 0x14) = sVar2;
          bVar7 = bVar7 | (byte)(1 << (int)sVar2);
        }
        iVar8 = iVar8 + 0x20;
        iVar11 = iVar11 + 4;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
      iVar8 = 0;
      iVar11 = 4;
      do {
        if (*(short *)(*(int *)&menuPcs->field_0x828 + iVar8 + 4) < 0) {
          iVar12 = 0;
          uVar10 = (uint)(char)bVar7;
          if ((((((uVar10 & 1) != 0) && (iVar12 = 1, (uVar10 & 2) != 0)) &&
               (iVar12 = 2, (uVar10 & 4) != 0)) &&
              ((iVar12 = 3, (uVar10 & 8) != 0 && (iVar12 = 4, (uVar10 & 0x10) != 0)))) &&
             ((iVar12 = 5, (uVar10 & 0x20) != 0 &&
              ((iVar12 = 6, (uVar10 & 0x40) != 0 && (iVar12 = 7, (uVar10 & 0x80) != 0)))))) {
            iVar12 = 8;
          }
          *(short *)(*(int *)&menuPcs->field_0x828 + iVar8 + 4) = (short)iVar12;
          bVar7 = bVar7 | (byte)(1 << iVar12);
        }
        iVar12 = *(int *)&menuPcs->field_0x828 + iVar8;
        iVar8 = iVar8 + 0x10;
        *(undefined2 *)(iVar12 + 6) = *(undefined2 *)(iVar12 + 4);
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x20) == 2) &&
       (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 4)) {
      menuPcs->field_0x10 = 1;
      menuPcs->field_0x12 = 0;
      menuPcs->field_0x13 = 0;
    }
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x20) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0;
    sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1c);
    if (sVar2 == 6) {
      MapMng._141707_1_ = 0;
    }
    else if ((iVar14 == 6) && (sVar2 != 6)) {
      MapMng._141707_1_ = 1;
    }
  }
  return;
}

