// Function: CalcSingleCMakeChara__8CMenuPcsFv
// Entry: 8016cd3c
// Size: 400 bytes

void CalcSingleCMakeChara__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  Mtx MStack_a8;
  Mtx MStack_78;
  Mtx MStack_48;
  
  iVar5 = (int)*(short *)&menuPcs->field_0x86a;
  iVar4 = *(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar5 * 4) + 0x168);
  puVar6 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar5 * 0x50 + 0xa00);
  if ((iVar4 == 0) || (*(int *)(iVar4 + 0xb0) == 0)) {
    *puVar6 = 0;
  }
  else {
    iVar4 = *(int *)&menuPcs->field_0x824 + iVar5 * 0x34;
    if (*(char *)(iVar4 + 0xc) == '\x01') {
      puVar6[0xb] = FLOAT_8033325c;
      SetAnim__8CMenuPcsFi(menuPcs,(int)*(short *)&menuPcs->field_0x86a);
      *(undefined *)(iVar4 + 0xc) = 0;
    }
    *puVar6 = 1;
    fVar2 = FLOAT_80333260;
    fVar1 = FLOAT_80333254;
    if (**(int **)(&menuPcs->field_0x7f4 + iVar5 * 4) != 3) {
      puVar6[7] = FLOAT_80333254;
      fVar3 = FLOAT_80333264;
      puVar6[8] = fVar2;
      puVar6[9] = fVar1;
      puVar6[0xd] = fVar3;
      puVar6[0xe] = fVar3;
      puVar6[0xf] = fVar3;
      PSMTXScale((float)puVar6[0xd],(float)puVar6[0xe],(float)puVar6[0xf],&MStack_48);
      PSMTXRotRad((float)puVar6[10],&MStack_78,0x78);
      PSMTXRotRad((float)puVar6[0xb],&MStack_a8,0x79);
      PSMTXConcat(&MStack_78,&MStack_a8,&MStack_78);
      MStack_78.value[0][3] = (float)puVar6[7];
      MStack_78.value[1][3] = (float)puVar6[8];
      MStack_78.value[2][3] = (float)puVar6[9];
      PSMTXConcat(&MStack_78,&MStack_48,&MStack_48);
      SetMatrix__Q26CChara6CModelFPA4_f
                (*(CModel **)(*(int *)(&menuPcs->field_0x7f4 + iVar5 * 4) + 0x168),&MStack_48);
      CalcMatrix__Q26CChara6CModelFv
                (*(undefined4 *)(*(int *)(&menuPcs->field_0x7f4 + iVar5 * 4) + 0x168));
      CalcSkin__Q26CChara6CModelFv
                (*(undefined4 *)(*(int *)(&menuPcs->field_0x7f4 + iVar5 * 4) + 0x168));
      PCAnimCtrl__8CMenuPcsFv(menuPcs);
    }
  }
  return;
}

