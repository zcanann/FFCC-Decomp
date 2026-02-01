// Function: SingMenuInit__8CMenuPcsFv
// Entry: 8014a214
// Size: 1128 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SingMenuInit__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  double dVar8;
  double dVar9;
  CCharaPcsCHandle *pCVar10;
  undefined4 uVar11;
  int iVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_singmenu_cpp_801de8d4,0x5c2);
  DestroyTempBuffer__8CGraphicFv(&Graphic);
  *(undefined4 *)&menuPcs->field_0xf4 = Graphic._8_4_;
  memset(&menuPcs->field_0x85c,0,8);
  *(undefined4 *)&menuPcs->field_0x774 = 0;
  pCVar10 = (CCharaPcsCHandle *)MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    pCVar10 = (CCharaPcsCHandle *)MenuPcs._244_4_;
  }
  pCVar10 = (CCharaPcsCHandle *)
            __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                      (0x194,pCVar10,s_singmenu_cpp_801de8d4,0x5cd);
  if (pCVar10 != (CCharaPcsCHandle *)0x0) {
    pCVar10 = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(pCVar10);
  }
  *(CCharaPcsCHandle **)&menuPcs->field_0x774 = pCVar10;
  Add__Q29CCharaPcs7CHandleFv(*(CCharaPcsCHandle **)&menuPcs->field_0x774);
  uVar11 = GetModelNo__8CMenuPcsFiii
                     (menuPcs,(uint)*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e0),
                      (uint)*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e4),
                      (uint)*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e2));
  LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
            (*(undefined4 *)&menuPcs->field_0x774,0,uVar11,0,0,0xffffffff,0,0);
  *(uint *)(*(int *)&menuPcs->field_0x774 + 8) =
       *(uint *)(*(int *)&menuPcs->field_0x774 + 8) | 0x300141;
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x774,s_stand_80332a24,0,1,0,
             ((uint)(*(CCharaPcsCHandle **)&menuPcs->field_0x774)->m_charaNo / 100) * 100,0xffffffff
             ,0);
  SetAnim__Q29CCharaPcs7CHandleFiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x774,0,0xffffffff,0xffffffff,0xffffffff,0);
  uVar11 = MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar11 = MenuPcs._244_4_;
  }
  uVar11 = __nwa__FUlPQ27CMemory6CStagePci(0x50,uVar11,s_singmenu_cpp_801de8d4,0x5dd);
  *(undefined4 *)&menuPcs->field_0x814 = uVar11;
  fVar3 = FLOAT_8033294c;
  fVar2 = FLOAT_80332934;
  iVar12 = *(int *)&menuPcs->field_0x814;
  iVar1 = (int)FLOAT_80332950;
  *(float *)(iVar12 + 0x24) = FLOAT_8033294c;
  fVar5 = FLOAT_803329d4;
  *(float *)(iVar12 + 0x20) = fVar3;
  fVar6 = FLOAT_803329ec;
  *(float *)(iVar12 + 0x1c) = fVar3;
  dVar13 = (double)FLOAT_80332a48;
  *(float *)(iVar12 + 0x30) = fVar3;
  dVar14 = (double)FLOAT_803329f4;
  *(float *)(iVar12 + 0x2c) = fVar3;
  dVar4 = DOUBLE_80332968;
  *(float *)(iVar12 + 0x28) = fVar3;
  dVar15 = (double)FLOAT_803329f0;
  *(float *)(iVar12 + 0x3c) = fVar2;
  dVar8 = DOUBLE_80332a30;
  *(float *)(iVar12 + 0x38) = fVar2;
  fVar7 = FLOAT_80332a2c;
  *(float *)(iVar12 + 0x34) = fVar2;
  dVar9 = DOUBLE_80332a38;
  **(undefined4 **)&menuPcs->field_0x814 = 0;
  dVar15 = (double)(float)(dVar15 * dVar4 + dVar15) - DOUBLE_80332a40;
  *(undefined4 *)(*(int *)&menuPcs->field_0x814 + 4) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x814 + 8) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x814 + 10) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x814 + 0xc) = 0x280;
  *(undefined2 *)(*(int *)&menuPcs->field_0x814 + 0xe) = 0x1c0;
  *(float *)(*(int *)&menuPcs->field_0x814 + 0x10) = fVar3;
  *(float *)(*(int *)&menuPcs->field_0x814 + 0x14) = fVar3;
  *(float *)(*(int *)&menuPcs->field_0x814 + 0x18) = fVar7;
  *(undefined4 *)(*(int *)&menuPcs->field_0x814 + 0x40) = 0;
  *(undefined4 *)(*(int *)&menuPcs->field_0x814 + 0x44) = 0;
  *(undefined4 *)(*(int *)&menuPcs->field_0x814 + 0x48) = 0x280;
  *(undefined4 *)(*(int *)&menuPcs->field_0x814 + 0x4c) = 0x1c0;
  *(short *)(*(int *)&menuPcs->field_0x814 + 8) =
       (short)(int)((double)(float)((double)(float)(dVar8 + dVar14 * dVar4 + (double)(fVar5 + fVar6)
                                                   ) - dVar9) - dVar8);
  *(short *)(*(int *)&menuPcs->field_0x814 + 10) = (short)(int)dVar15;
  *(int *)(*(int *)&menuPcs->field_0x814 + 0x40) = (int)(dVar13 + (double)(fVar5 + fVar6));
  *(int *)(*(int *)&menuPcs->field_0x814 + 0x44) = iVar1;
  *(undefined4 *)(*(int *)&menuPcs->field_0x814 + 0x48) = 0x48;
  *(undefined4 *)(*(int *)&menuPcs->field_0x814 + 0x4c) = 0x58;
  uVar11 = MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar11 = MenuPcs._244_4_;
  }
  uVar11 = __nw__FUlPQ27CMemory6CStagePci(0x1008,uVar11,s_singmenu_cpp_801de8d4,0x605);
  *(undefined4 *)&menuPcs->field_0x850 = uVar11;
  memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
  uVar11 = MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar11 = MenuPcs._244_4_;
  }
  uVar11 = __nw__FUlPQ27CMemory6CStagePci(0x48,uVar11,s_singmenu_cpp_801de8d4,0x609);
  *(undefined4 *)&menuPcs->field_0x82c = uVar11;
  memset(*(undefined4 *)&menuPcs->field_0x82c,0,0x48);
  uVar11 = MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar11 = MenuPcs._244_4_;
  }
  uVar11 = __nw__FUlPQ27CMemory6CStagePci(0xc,uVar11,s_singmenu_cpp_801de8d4,0x60d);
  *(undefined4 *)&menuPcs->field_0x848 = uVar11;
  memset(*(undefined4 *)&menuPcs->field_0x848,0,0xc);
  *(undefined2 *)&menuPcs->field_0x866 = 0;
  if (-1 < DAT_8032eec4) {
    *(undefined2 *)&menuPcs->field_0x864 = 8;
    DAT_8032eec4 = -1;
  }
  FLOAT_8032ea78 = FLOAT_803329b8;
  *(undefined4 *)&menuPcs->field_0x874 = 0xffffffff;
  menuPcs->field_0x872 = 1;
  menuPcs->field_0x85a = 1;
  return;
}

