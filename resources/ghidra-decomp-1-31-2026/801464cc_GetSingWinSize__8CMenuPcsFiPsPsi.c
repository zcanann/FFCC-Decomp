// Function: GetSingWinSize__8CMenuPcsFiPsPsi
// Entry: 801464cc
// Size: 544 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GetSingWinSize__8CMenuPcsFiPsPsi
               (CMenuPcs *menuPcs,int param_2,short *param_3,short *param_4,int param_5)

{
  undefined *puVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  undefined *puVar8;
  CFont *font;
  double dVar9;
  
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80332934,font);
  SetShadow__5CFontFi(font,1);
  SetScale__5CFontFf(FLOAT_8032ea78,font);
  iVar5 = 0;
  iVar4 = AStar.m_bestPath.m_path._56_4_;
  if (param_5 == 0) {
    iVar4 = *(int *)(&DAT_80214a50 + param_2 * 0x14);
  }
  puVar7 = s_DynamicMessStr;
  puVar8 = &DAT_80214a50 + param_2 * 0x14;
  iVar6 = 0;
  do {
    if (iVar4 <= iVar6) {
      if (param_5 == 0) {
        iVar5 = iVar5 + -0x18;
      }
      else {
        iVar5 = iVar5 + 0x16;
      }
      uVar3 = (uint)(FLOAT_80332960 * FLOAT_8032ea78);
      if (FLOAT_8033294c <
          FLOAT_80332960 * FLOAT_8032ea78 -
          (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_80332938)) {
        uVar3 = uVar3 + 1;
      }
      iVar6 = iVar5 / (int)uVar3;
      if (iVar5 != iVar6 * uVar3) {
        iVar6 = iVar6 + 1;
      }
      sVar2 = (short)iVar6;
      if (param_5 == 0) {
        sVar2 = sVar2 + 3;
      }
      *param_3 = sVar2 * (short)uVar3 + 0x40;
      *param_4 = (short)iVar4 * ((short)uVar3 + 2) + 0x40;
      return;
    }
    puVar1 = puVar7;
    if (param_5 == 0) {
      sVar2 = *(short *)(puVar8 + 4);
      if (Game.game.m_gameWork.m_languageId == '\x03') {
        puVar1 = (&PTR_DAT_802143a0)[sVar2];
      }
      else if (Game.game.m_gameWork.m_languageId < 3) {
        if ((Game.game.m_gameWork.m_languageId == '\x01') ||
           (Game.game.m_gameWork.m_languageId == '\0')) {
LAB_801465f0:
          puVar1 = (&PTR_DAT_802141e0)[sVar2];
        }
        else {
          puVar1 = (&PTR_DAT_802142c0)[sVar2];
        }
      }
      else if (Game.game.m_gameWork.m_languageId == '\x05') {
        puVar1 = (&PTR_DAT_80214560)[sVar2];
      }
      else {
        if (4 < Game.game.m_gameWork.m_languageId) goto LAB_801465f0;
        puVar1 = (&PTR_DAT_80214480)[sVar2];
      }
    }
    dVar9 = (double)GetWidth__5CFontFPc(font,puVar1);
    if (iVar5 < (int)dVar9) {
      iVar5 = (int)dVar9;
    }
    puVar8 = puVar8 + 2;
    puVar7 = puVar7 + 0x80;
    iVar6 = iVar6 + 1;
  } while( true );
}

