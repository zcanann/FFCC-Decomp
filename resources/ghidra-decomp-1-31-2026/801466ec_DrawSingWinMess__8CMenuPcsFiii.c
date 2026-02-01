// Function: DrawSingWinMess__8CMenuPcsFiii
// Entry: 801466ec
// Size: 1008 bytes

/* WARNING: Removing unreachable block (ram,0x80146ac0) */
/* WARNING: Removing unreachable block (ram,0x80146ab8) */
/* WARNING: Removing unreachable block (ram,0x80146ab0) */
/* WARNING: Removing unreachable block (ram,0x8014670c) */
/* WARNING: Removing unreachable block (ram,0x80146704) */
/* WARNING: Removing unreachable block (ram,0x801466fc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawSingWinMess__8CMenuPcsFiii(CMenuPcs *menuPcs,int param_2,uint param_3,int param_4)

{
  int iVar1;
  short sVar2;
  undefined *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  short *psVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  CFont *font;
  int iVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined auStack_118 [4];
  undefined4 local_114;
  undefined auStack_110 [128];
  double local_90;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  longlong local_78;
  undefined4 local_70;
  uint uStack_6c;
  
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80332934,font);
  SetShadow__5CFontFi(font,1);
  SetScale__5CFontFf(FLOAT_8032ea78,font);
  DrawInit__5CFontFv(font);
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_118,0xff,0xff,0xff,0xff);
  local_114 = *puVar4;
  SetColor__5CFontF8_GXColor(font,&local_114);
  iVar8 = 0;
  iVar14 = AStar.m_bestPath.m_path._56_4_;
  if (param_4 == 0) {
    iVar14 = *(int *)(&DAT_80214a50 + param_2 * 0x14);
  }
  puVar10 = s_DynamicMessStr;
  puVar11 = &DAT_80214a50 + param_2 * 0x14;
  puVar12 = puVar10;
  puVar13 = puVar11;
  for (iVar9 = 0; iVar9 < iVar14; iVar9 = iVar9 + 1) {
    puVar3 = puVar12;
    if (param_4 == 0) {
      sVar2 = *(short *)(puVar13 + 4);
      if (Game.game.m_gameWork.m_languageId == '\x03') {
        puVar3 = (&PTR_DAT_802143a0)[sVar2];
      }
      else if (Game.game.m_gameWork.m_languageId < 3) {
        if ((Game.game.m_gameWork.m_languageId == '\x01') ||
           (Game.game.m_gameWork.m_languageId == '\0')) {
LAB_80146864:
          puVar3 = (&PTR_DAT_802141e0)[sVar2];
        }
        else {
          puVar3 = (&PTR_DAT_802142c0)[sVar2];
        }
      }
      else if (Game.game.m_gameWork.m_languageId == '\x05') {
        puVar3 = (&PTR_DAT_80214560)[sVar2];
      }
      else {
        if (4 < Game.game.m_gameWork.m_languageId) goto LAB_80146864;
        puVar3 = (&PTR_DAT_80214480)[sVar2];
      }
    }
    dVar15 = (double)GetWidth__5CFontFPc(font,puVar3);
    iVar1 = (int)dVar15;
    local_90 = (double)(longlong)iVar1;
    if (iVar8 < iVar1) {
      iVar8 = iVar1;
    }
    puVar13 = puVar13 + 2;
    puVar12 = puVar12 + 0x80;
  }
  psVar6 = *(short **)&menuPcs->field_0x848;
  uVar7 = (uint)(FLOAT_80332960 * FLOAT_8032ea78);
  local_78 = (longlong)(int)uVar7;
  uStack_84 = (int)*psVar6 ^ 0x80000000;
  local_90 = (double)(CONCAT44(0x43300000,psVar6[2] - iVar8) ^ 0x80000000);
  uStack_7c = (int)psVar6[1] + 0x20U ^ 0x80000000;
  uStack_6c = uVar7 ^ 0x80000000;
  local_88 = 0x43300000;
  local_80 = 0x43300000;
  dVar16 = (double)(float)((local_90 - DOUBLE_80332938) * DOUBLE_80332968 +
                          ((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80332938));
  dVar15 = (double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80332938;
  if (FLOAT_8033294c <
      FLOAT_80332960 * FLOAT_8032ea78 -
      (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80332938)) {
    uVar7 = uVar7 + 1;
  }
  uVar7 = uVar7 + 3 ^ 0x80000000;
  iVar8 = 0;
  dVar17 = DOUBLE_80332938;
  do {
    local_70 = 0x43300000;
    dVar15 = (double)(float)dVar15;
    if (iVar14 <= iVar8) {
      DrawInit__8CMenuPcsFv(menuPcs);
      return;
    }
    uVar5 = param_3 & 1 << iVar8;
    SetTlut__5CFontFi(font,((int)(-uVar5 | uVar5) >> 0x1f) + 8);
    puVar12 = puVar10;
    if (param_4 == 0) {
      sVar2 = *(short *)(puVar11 + 4);
      if (Game.game.m_gameWork.m_languageId == '\x03') {
        puVar12 = (&PTR_DAT_802143a0)[sVar2];
      }
      else if (Game.game.m_gameWork.m_languageId < 3) {
        if ((Game.game.m_gameWork.m_languageId == '\x01') ||
           (Game.game.m_gameWork.m_languageId == '\0')) {
LAB_80146a24:
          puVar12 = (&PTR_DAT_802141e0)[sVar2];
        }
        else {
          puVar12 = (&PTR_DAT_802142c0)[sVar2];
        }
      }
      else if (Game.game.m_gameWork.m_languageId == '\x05') {
        puVar12 = (&PTR_DAT_80214560)[sVar2];
      }
      else {
        if (4 < Game.game.m_gameWork.m_languageId) goto LAB_80146a24;
        puVar12 = (&PTR_DAT_80214480)[sVar2];
      }
    }
    iVar9 = strlen(puVar12);
    if (iVar9 != 0) {
      strcpy(auStack_110,puVar12);
      SetPosX__5CFontFf((float)dVar16,font);
      SetPosY__5CFontFf((float)(dVar15 - (double)FLOAT_80332954),font);
      Draw__5CFontFPc(font,auStack_110);
    }
    puVar11 = puVar11 + 2;
    puVar10 = puVar10 + 0x80;
    iVar8 = iVar8 + 1;
    dVar15 = dVar15 + (double)(float)((double)CONCAT44(0x43300000,uVar7) - dVar17);
    uStack_6c = uVar7;
  } while( true );
}

