// Function: SingleCalcFadeOut__8CMenuPcsFv
// Entry: 80148220
// Size: 708 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SingleCalcFadeOut__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float xS;
  double dVar1;
  CModel *model;
  short *psVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Mtx MStack_58;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  if (*(short *)(*(int *)&menuPcs->field_0x850 + 4) == 0) {
    PlaySe__6CSoundFiiii(&Sound,0xf,0x40,0x7f,0);
    memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(uint *)(iVar3 + 0x2c) =
         ~((int)~((int)*(short *)&menuPcs->field_0x864 - 8U |
                 8U - (int)*(short *)&menuPcs->field_0x864) >> 0x1f) & 10;
    *(undefined4 *)(iVar3 + 0x30) = 10;
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 0x6c) = 0;
    *(undefined4 *)(iVar3 + 0x70) = 10;
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 0xac) = 0;
    *(undefined4 *)(iVar3 + 0xb0) = 10;
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 0xec) = 0;
    *(undefined4 *)(iVar3 + 0xf0) = 10;
    **(undefined2 **)&menuPcs->field_0x850 = 4;
    *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 6) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 4) = 1;
  }
  iVar5 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar3 = (int)**(short **)&menuPcs->field_0x850;
  psVar2 = *(short **)&menuPcs->field_0x850 + 4;
  iVar4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  if (0 < iVar3) {
    do {
      dVar1 = DOUBLE_80332938;
      if (iVar4 < *(int *)(psVar2 + 0x12)) {
        *(float *)(psVar2 + 8) = FLOAT_80332934;
      }
      else if (iVar4 < *(int *)(psVar2 + 0x12) + *(int *)(psVar2 + 0x14)) {
        local_28 = 0x43300000;
        *(int *)(psVar2 + 0x10) = *(int *)(psVar2 + 0x10) + 1;
        uStack_24 = *(uint *)(psVar2 + 0x14) ^ 0x80000000;
        local_20 = 0x43300000;
        uStack_1c = *(uint *)(psVar2 + 0x10) ^ 0x80000000;
        *(float *)(psVar2 + 8) =
             (float)-((DOUBLE_80332980 / ((double)CONCAT44(0x43300000,uStack_24) - dVar1)) *
                      ((double)CONCAT44(0x43300000,uStack_1c) - dVar1) - DOUBLE_80332980);
      }
      else {
        iVar5 = iVar5 + 1;
        *(float *)(psVar2 + 8) = FLOAT_8033294c;
      }
      psVar2 = psVar2 + 0x20;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  model = *(CModel **)(*(int *)&menuPcs->field_0x774 + 0x168);
  if (model->m_animEnd <= model->m_time) {
    SetFrame__Q26CChara6CModelFf(FLOAT_8033294c,model);
  }
  else {
    AddFrame__Q26CChara6CModelFf((double)FLOAT_80332934,model);
  }
  iVar3 = (uint)*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e0) * 4;
  xS = *(float *)(&DAT_801dd708 + iVar3);
  PSMTXScale(xS,xS,xS,&MStack_58);
  MStack_58.value[1][3] = *(float *)(&DAT_801dd6f8 + iVar3);
  MStack_58.value[0][3] = FLOAT_8033294c;
  MStack_58.value[2][3] = FLOAT_8033294c;
  iVar3 = *(int *)(*(int *)&menuPcs->field_0x774 + 0x168);
  *(byte *)(iVar3 + 0x10c) = *(byte *)(iVar3 + 0x10c) & 0x7f | 0x80;
  SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(*(int *)&menuPcs->field_0x774 + 0x168),&MStack_58);
  CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x774 + 0x168));
  CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x774 + 0x168));
  if (**(short **)&menuPcs->field_0x850 == iVar5) {
    (*(short **)&menuPcs->field_0x850)[3] = 1;
  }
  return;
}

