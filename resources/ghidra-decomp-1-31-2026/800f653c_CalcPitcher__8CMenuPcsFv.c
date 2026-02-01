// Function: CalcPitcher__8CMenuPcsFv
// Entry: 800f653c
// Size: 512 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcPitcher__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  uint uVar9;
  int iVar10;
  Mtx MStack_a8;
  Mtx MStack_78;
  Mtx MStack_48;
  undefined4 local_18;
  uint uStack_14;
  
  fVar1 = FLOAT_803313e8;
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if ((sVar2 != 0) && (sVar2 < 3)) {
    iVar10 = *(int *)&menuPcs->field_0x814;
    *(undefined4 *)(iVar10 + 400) = 1;
    fVar3 = FLOAT_803313dc;
    *(undefined2 *)(iVar10 + 0x198) = 0x140;
    fVar4 = FLOAT_803314a4;
    *(undefined2 *)(iVar10 + 0x19a) = 0xe0;
    fVar6 = FLOAT_80331748;
    *(undefined2 *)(iVar10 + 0x19c) = 0x140;
    fVar7 = FLOAT_8033174c;
    *(undefined2 *)(iVar10 + 0x19e) = 0xe0;
    fVar8 = FLOAT_80331750;
    *(float *)(iVar10 + 0x1a0) = fVar3;
    fVar5 = FLOAT_803315d0;
    *(float *)(iVar10 + 0x1a4) = fVar3;
    fVar3 = FLOAT_80331754;
    *(float *)(iVar10 + 0x1a8) = fVar4;
    *(float *)(iVar10 + 0x1ac) = fVar6;
    *(float *)(iVar10 + 0x1b0) = fVar7;
    *(float *)(iVar10 + 0x1b4) = fVar8;
    *(float *)(iVar10 + 0x1b8) = fVar5;
    *(float *)(iVar10 + 0x1bc) = *(float *)(iVar10 + 0x1bc) + fVar3;
    PSMTXScale(fVar1,fVar1,fVar1,&MStack_48);
    PSMTXRotRad(*(float *)(iVar10 + 0x1b8),&MStack_78,0x78);
    PSMTXRotRad(*(float *)(iVar10 + 0x1bc),&MStack_a8,0x79);
    PSMTXConcat(&MStack_78,&MStack_a8,&MStack_78);
    MStack_78.value[0][3] = *(float *)(iVar10 + 0x1ac);
    MStack_78.value[1][3] = *(float *)(iVar10 + 0x1b0);
    MStack_78.value[2][3] = *(float *)(iVar10 + 0x1b4);
    PSMTXConcat(&MStack_78,&MStack_48,&MStack_48);
    local_18 = 0x43300000;
    uVar9 = (uint)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
    sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
    uStack_14 = uVar9 ^ 0x80000000;
    fVar1 = (float)(DOUBLE_803314e8 * ((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80331408));
    if ((sVar2 == 1) && ((int)uVar9 < 10)) {
      *(float *)(*(int *)(*(int *)&menuPcs->field_0x788 + 0x168) + 0x9c) = fVar1;
    }
    else if ((sVar2 == 2) && (menuPcs->field_0x13 != '\0')) {
      *(float *)(*(int *)(*(int *)&menuPcs->field_0x788 + 0x168) + 0x9c) =
           (float)(DOUBLE_80331420 - (double)fVar1);
    }
    else {
      *(float *)(*(int *)(*(int *)&menuPcs->field_0x788 + 0x168) + 0x9c) = FLOAT_803313e8;
    }
    SetMatrix__Q26CChara6CModelFPA4_f
              (*(CModel **)(*(int *)&menuPcs->field_0x788 + 0x168),&MStack_48);
    *(int *)(*(int *)(*(int *)&menuPcs->field_0x788 + 0x168) + 0x98) =
         (int)(char)(&DAT_80331380)[Game.game.m_gameWork.m_timerA];
    CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x788 + 0x168));
    CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x788 + 0x168));
  }
  return;
}

