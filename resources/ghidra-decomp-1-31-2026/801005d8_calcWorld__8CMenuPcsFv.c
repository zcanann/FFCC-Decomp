// Function: calcWorld__8CMenuPcsFv
// Entry: 801005d8
// Size: 1320 bytes

/* WARNING: Removing unreachable block (ram,0x80100ae0) */
/* WARNING: Removing unreachable block (ram,0x80100ad8) */
/* WARNING: Removing unreachable block (ram,0x801005f0) */
/* WARNING: Removing unreachable block (ram,0x801005e8) */

void calcWorld__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  CModel *pCVar8;
  int iVar9;
  CCharaPcsCHandle *pCVar10;
  double dVar11;
  double dVar12;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  Mtx MStack_5c;
  
  *(undefined4 *)(*(int *)&menuPcs->field_0x83c + 4) =
       *(undefined4 *)(*(int *)&menuPcs->field_0x83c + 8);
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 8) == '\0') {
    PlaySe__6CSoundFiiii(&Sound,0x138b,0x40,0x7f,0);
    SetAnim__Q29CCharaPcs7CHandleFiiiii
              (*(CCharaPcsCHandle **)&menuPcs->field_0x778,0,0xffffffff,0xffffffff,0xffffffff,0);
    *(undefined4 *)(*(int *)&menuPcs->field_0x83c + 8) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 1;
  }
  pCVar10 = *(CCharaPcsCHandle **)&menuPcs->field_0x778;
  iVar9 = *(int *)&menuPcs->field_0x82c;
  pCVar8 = pCVar10->m_model;
  sVar2 = *(short *)(iVar9 + 0x10);
  dVar11 = (double)pCVar8->m_animEnd;
  dVar12 = (double)pCVar8->m_time;
  if (sVar2 == 1) {
    if (dVar11 <= dVar12) {
      if (9 < *(short *)(iVar9 + 0x22)) {
        SetAnim__Q29CCharaPcs7CHandleFiiiii(pCVar10,1,0xffffffff,0xffffffff,0xffffffff,0);
        *(undefined4 *)(*(int *)&menuPcs->field_0x83c + 8) = 1;
        local_68 = 2;
        local_64 = 0;
        local_60 = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,4,3,&local_68,(CStack *)0x0);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 2;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      }
    }
    else {
      AddFrame__Q26CChara6CModelFf((double)FLOAT_80331698,pCVar8);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    }
  }
  else if (sVar2 == 2) {
    iVar9 = (int)(char)menuPcs->field_0xe;
    if (iVar9 == 0) {
      if (dVar11 <= dVar12) {
        SetAnim__Q29CCharaPcs7CHandleFiiiii(pCVar10,1,0xffffffff,0xffffffff,0xffffffff,0);
        *(undefined4 *)(*(int *)&menuPcs->field_0x83c + 8) = 1;
      }
      else {
        AddFrame__Q26CChara6CModelFf((double)FLOAT_80331698,pCVar8);
      }
    }
    else {
      if (iVar9 == 1) {
        PlaySe__6CSoundFiiii(&Sound,0x138c,0x40,0x7f,0);
        iVar9 = 2;
      }
      else if (iVar9 == 2) {
        PlaySe__6CSoundFiiii(&Sound,0x138c,0x40,0x7f,0);
        iVar9 = 3;
      }
      else if (iVar9 == 3) {
        PlaySe__6CSoundFiiii(&Sound,0x138c,0x40,0x7f,0);
        iVar9 = 4;
      }
      else if (iVar9 == 4) {
        PlaySe__6CSoundFiiii(&Sound,0x138c,0x40,0x7f,0);
        iVar9 = 5;
      }
      else if (iVar9 == 5) {
        PlaySe__6CSoundFiiii(&Sound,0x138d,0x40,0x7f,0);
        iVar9 = 6;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 3;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      }
      if (iVar9 != *(int *)(*(int *)&menuPcs->field_0x83c + 8)) {
        SetAnim__Q29CCharaPcs7CHandleFiiiii
                  (*(CCharaPcsCHandle **)&menuPcs->field_0x778,iVar9,0xffffffff,0xffffffff,
                   0xffffffff,0);
        *(int *)(*(int *)&menuPcs->field_0x83c + 8) = iVar9;
        if (iVar9 == 0) {
          pCVar8 = *(CModel **)(*(int *)&menuPcs->field_0x778 + 0x168);
          fVar1 = pCVar8->m_animEnd;
          dVar11 = (double)fVar1;
          SetFrame__Q26CChara6CModelFf(fVar1,pCVar8);
        }
      }
      menuPcs->field_0xe = 0;
    }
  }
  else if ((sVar2 == 3) && (9 < *(short *)(iVar9 + 0x22))) {
    if (dVar11 <= dVar12) {
      SetAnim__Q29CCharaPcs7CHandleFiiiii(pCVar10,0,0xffffffff,0xffffffff,0xffffffff,0);
      *(undefined4 *)(*(int *)&menuPcs->field_0x83c + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 10;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 4;
      PlaySe__6CSoundFiiii(&Sound,0x32,0x40,0x7f,0);
    }
    else {
      AddFrame__Q26CChara6CModelFf((double)FLOAT_80331698,pCVar8);
    }
  }
  else if (sVar2 == 4) {
    if (*(short *)(iVar9 + 0x18) == 0) {
      *(undefined2 *)(iVar9 + 0x20) = *(undefined2 *)(iVar9 + 0x1e);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0;
    }
    else {
      *(short *)(iVar9 + 0x18) = *(short *)(iVar9 + 0x18) + -1;
    }
  }
  iVar9 = *(int *)&menuPcs->field_0x814;
  *(undefined2 *)(iVar9 + 0x58) = 0;
  fVar1 = FLOAT_803313dc;
  *(undefined2 *)(iVar9 + 0x5a) = 0;
  fVar3 = FLOAT_80331598;
  *(undefined2 *)(iVar9 + 0x5c) = 0x280;
  fVar4 = FLOAT_803315d4;
  *(undefined2 *)(iVar9 + 0x5e) = 0x1c0;
  fVar5 = FLOAT_803317e0;
  *(float *)(iVar9 + 0x60) = fVar1;
  fVar6 = FLOAT_803317e4;
  *(float *)(iVar9 + 100) = fVar1;
  fVar7 = FLOAT_803317e8;
  *(float *)(iVar9 + 0x68) = fVar3;
  fVar3 = FLOAT_803314bc;
  *(undefined4 *)(iVar9 + 0x50) = 1;
  *(float *)(iVar9 + 0x84) = fVar4;
  *(float *)(iVar9 + 0x88) = fVar4;
  *(float *)(iVar9 + 0x8c) = fVar4;
  *(float *)(iVar9 + 0x6c) = fVar1;
  *(float *)(iVar9 + 0x70) = fVar5;
  *(float *)(iVar9 + 0x74) = fVar6;
  *(float *)(iVar9 + 0x78) = fVar7;
  *(float *)(iVar9 + 0x7c) = fVar1;
  *(float *)(iVar9 + 0x80) = fVar1;
  PSMTXRotRad(fVar3 * *(float *)(iVar9 + 0x78),&MStack_5c,0x78);
  MStack_5c.value[0][3] = *(float *)(iVar9 + 0x6c);
  MStack_5c.value[1][3] = *(float *)(iVar9 + 0x70);
  MStack_5c.value[2][3] = *(float *)(iVar9 + 0x74);
  PSMTXScaleApply(*(float *)(iVar9 + 0x84),*(float *)(iVar9 + 0x88),*(float *)(iVar9 + 0x8c),
                  &MStack_5c,&MStack_5c);
  SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(*(int *)&menuPcs->field_0x778 + 0x168),&MStack_5c);
  CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x778 + 0x168));
  CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x778 + 0x168));
  iVar9 = *(int *)&menuPcs->field_0x82c;
  if ((*(short *)(iVar9 + 0x10) != 1) || (dVar12 < dVar11)) {
    if ((*(short *)(iVar9 + 0x10) == 3) && (*(short *)(iVar9 + 0x22) < 10)) {
      *(short *)(iVar9 + 0x22) = *(short *)(iVar9 + 0x22) + 1;
    }
  }
  else if (*(short *)(iVar9 + 0x22) < 10) {
    *(short *)(iVar9 + 0x22) = *(short *)(iVar9 + 0x22) + 1;
  }
  return;
}

