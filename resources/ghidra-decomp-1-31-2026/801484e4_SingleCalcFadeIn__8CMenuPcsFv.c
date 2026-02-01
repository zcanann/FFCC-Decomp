// Function: SingleCalcFadeIn__8CMenuPcsFv
// Entry: 801484e4
// Size: 744 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SingleCalcFadeIn__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float xS;
  double dVar1;
  int iVar2;
  CModel *model;
  short *psVar3;
  int iVar4;
  int iVar5;
  Mtx MStack_58;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  if (*(short *)(*(int *)&menuPcs->field_0x850 + 4) == 0) {
    PlaySe__6CSoundFiiii(&Sound,0xe,0x40,0x7f,0);
    memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
    iVar2 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar2 + 0x2c) = 0;
    *(undefined4 *)(iVar2 + 0x30) = 10;
    iVar2 = *(int *)&menuPcs->field_0x850;
    *(uint *)(iVar2 + 0x6c) =
         ~((int)~((int)*(short *)&menuPcs->field_0x864 - 8U |
                 8U - (int)*(short *)&menuPcs->field_0x864) >> 0x1f) & 10;
    *(undefined4 *)(iVar2 + 0x70) = 10;
    iVar2 = *(int *)&menuPcs->field_0x850;
    *(uint *)(iVar2 + 0xac) =
         ~((int)~((int)*(short *)&menuPcs->field_0x864 - 8U |
                 8U - (int)*(short *)&menuPcs->field_0x864) >> 0x1f) & 10;
    *(undefined4 *)(iVar2 + 0xb0) = 10;
    iVar2 = *(int *)&menuPcs->field_0x850;
    *(uint *)(iVar2 + 0xec) =
         ~((int)~((int)*(short *)&menuPcs->field_0x864 - 8U |
                 8U - (int)*(short *)&menuPcs->field_0x864) >> 0x1f) & 10;
    *(undefined4 *)(iVar2 + 0xf0) = 10;
    **(undefined2 **)&menuPcs->field_0x850 = 4;
    *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 6) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 4) = 1;
  }
  iVar5 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar2 = (int)**(short **)&menuPcs->field_0x850;
  psVar3 = *(short **)&menuPcs->field_0x850 + 4;
  iVar4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  if (0 < iVar2) {
    do {
      dVar1 = DOUBLE_80332938;
      if (*(int *)(psVar3 + 0x12) <= iVar4) {
        if (iVar4 < *(int *)(psVar3 + 0x12) + *(int *)(psVar3 + 0x14)) {
          local_28 = 0x43300000;
          *(int *)(psVar3 + 0x10) = *(int *)(psVar3 + 0x10) + 1;
          uStack_24 = *(uint *)(psVar3 + 0x14) ^ 0x80000000;
          local_20 = 0x43300000;
          uStack_1c = *(uint *)(psVar3 + 0x10) ^ 0x80000000;
          *(float *)(psVar3 + 8) =
               (float)((DOUBLE_80332980 / ((double)CONCAT44(0x43300000,uStack_24) - dVar1)) *
                      ((double)CONCAT44(0x43300000,uStack_1c) - dVar1));
        }
        else {
          iVar5 = iVar5 + 1;
          *(float *)(psVar3 + 8) = FLOAT_80332934;
        }
      }
      psVar3 = psVar3 + 0x20;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  model = *(CModel **)(*(int *)&menuPcs->field_0x774 + 0x168);
  if (model->m_animEnd <= model->m_time) {
    SetFrame__Q26CChara6CModelFf(FLOAT_8033294c,model);
  }
  else {
    AddFrame__Q26CChara6CModelFf((double)FLOAT_80332934,model);
  }
  iVar2 = (uint)*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e0) * 4;
  xS = *(float *)(&DAT_801dd708 + iVar2);
  PSMTXScale(xS,xS,xS,&MStack_58);
  MStack_58.value[1][3] = *(float *)(&DAT_801dd6f8 + iVar2);
  MStack_58.value[0][3] = FLOAT_8033294c;
  MStack_58.value[2][3] = FLOAT_8033294c;
  iVar2 = *(int *)(*(int *)&menuPcs->field_0x774 + 0x168);
  *(byte *)(iVar2 + 0x10c) = *(byte *)(iVar2 + 0x10c) & 0x7f | 0x80;
  SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(*(int *)&menuPcs->field_0x774 + 0x168),&MStack_58);
  CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x774 + 0x168));
  CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x774 + 0x168));
  if (**(short **)&menuPcs->field_0x850 == iVar5) {
    (*(short **)&menuPcs->field_0x850)[3] = 1;
  }
  return;
}

