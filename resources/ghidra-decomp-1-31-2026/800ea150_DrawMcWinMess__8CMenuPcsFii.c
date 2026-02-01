// Function: DrawMcWinMess__8CMenuPcsFii
// Entry: 800ea150
// Size: 932 bytes

/* WARNING: Removing unreachable block (ram,0x800ea4d8) */
/* WARNING: Removing unreachable block (ram,0x800ea4d0) */
/* WARNING: Removing unreachable block (ram,0x800ea4c8) */
/* WARNING: Removing unreachable block (ram,0x800ea170) */
/* WARNING: Removing unreachable block (ram,0x800ea168) */
/* WARNING: Removing unreachable block (ram,0x800ea160) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawMcWinMess__8CMenuPcsFii(CMenuPcs *menuPcs,int param_2,int param_3)

{
  bool bVar1;
  short sVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  CFont *font;
  double dVar12;
  double dVar13;
  double in_f30;
  double dVar14;
  undefined auStack_108 [4];
  undefined4 local_104;
  undefined auStack_100 [128];
  double local_80;
  double local_78;
  undefined4 local_70;
  uint uStack_6c;
  
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_803313e8,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_803313e8,font);
  DrawInit__5CFontFv(font);
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_108,0xff,0xff,0xff,0xff);
  local_104 = *puVar3;
  SetColor__5CFontF8_GXColor(font,&local_104);
  SetTlut__5CFontFi(font,0x23);
  iVar4 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,param_3);
  iVar9 = Game.game.m_gameWork.m_languageId - 1;
  piVar5 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,param_2);
  if (param_2 != 0) {
    iVar8 = 0;
    piVar11 = piVar5;
    for (iVar10 = 0; iVar10 < *piVar5; iVar10 = iVar10 + 1) {
      pcVar7 = *(char **)(iVar4 + *(short *)(piVar11 + 1) * 4);
      if (pcVar7 != (char *)0x0) {
        if (*pcVar7 == '$') {
          pcVar7 = pcVar7 + 1;
        }
        dVar13 = (double)GetWidth__5CFontFPc(font,pcVar7);
        iVar6 = (int)dVar13;
        local_80 = (double)(longlong)iVar6;
        if (iVar8 < iVar6) {
          iVar8 = iVar6;
        }
      }
      piVar11 = (int *)((int)piVar11 + 2);
    }
    local_80 = (double)(CONCAT44(0x43300000,(*(short **)&menuPcs->field_0x848)[2] - iVar8) ^
                       0x80000000);
    local_78 = (double)(CONCAT44(0x43300000,(int)**(short **)&menuPcs->field_0x848) ^ 0x80000000);
    in_f30 = (double)(float)((local_80 - DOUBLE_80331408) * DOUBLE_803313f8 +
                            (local_78 - DOUBLE_80331408));
  }
  dVar14 = (double)FLOAT_80331404;
  local_78 = (double)(CONCAT44(0x43300000,*(short *)(*(int *)&menuPcs->field_0x848 + 2) + 0x20) ^
                     0x80000000);
  dVar13 = local_78 - DOUBLE_80331408;
  piVar11 = piVar5;
  for (iVar8 = 0; dVar13 = (double)(float)dVar13, iVar8 < *piVar5; iVar8 = iVar8 + 1) {
    sVar2 = *(short *)(piVar11 + 1);
    iVar10 = strlen(*(undefined4 *)(iVar4 + sVar2 * 4));
    if (iVar10 != 0) {
      pcVar7 = *(char **)(iVar4 + sVar2 * 4);
      bVar1 = *pcVar7 != '$';
      if (bVar1) {
        strcpy(auStack_100);
      }
      else {
        strcpy(auStack_100,pcVar7 + 1);
      }
      if ((param_2 == 0) || (!bVar1)) {
        dVar12 = (double)GetWidth__5CFontFPc(font,auStack_100);
        local_78 = (double)(longlong)(int)dVar12;
        uStack_6c = (int)**(short **)&menuPcs->field_0x848 ^ 0x80000000;
        local_80 = (double)(CONCAT44(0x43300000,
                                     (int)(*(short **)&menuPcs->field_0x848)[2] - (int)dVar12) ^
                           0x80000000);
        local_70 = 0x43300000;
        in_f30 = (double)(float)((local_80 - DOUBLE_80331408) * DOUBLE_803313f8 +
                                ((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408));
      }
      SetPosX__5CFontFf((float)in_f30,font);
      SetPosY__5CFontFf((float)dVar13,font);
      if (param_3 == 0) {
        if ((param_2 == 0) ||
           (iVar10 = strstr(auStack_100,(&PTR_s_Slot_A_80210d54)[iVar9]), iVar10 == 0)) {
          pcVar7 = (char *)strstr(auStack_100,&DAT_80331400);
          if (pcVar7 != (char *)0x0) {
            *pcVar7 = *pcVar7 + '\x02';
            pcVar7[1] = pcVar7[1] + '\x02';
          }
        }
        else {
          iVar6 = strlen((&PTR_s_Slot_A_80210d54)[iVar9]);
          *(char *)(iVar10 + iVar6 + -1) =
               *(char *)(iVar10 + iVar6 + -1) + (char)(menuPcs->m_mcCtrl).m_cardChannel;
        }
      }
      else {
        iVar10 = strstr(auStack_100,(&PTR_s_Data_1_80210d68)[iVar9]);
        if (iVar10 != 0) {
          iVar6 = strlen((&PTR_s_Data_1_80210d68)[iVar9]);
          *(char *)(iVar10 + iVar6 + -1) =
               *(char *)(iVar10 + iVar6 + -1) + (char)(menuPcs->m_mcCtrl).m_saveIndex;
        }
      }
      Draw__5CFontFPc(font,auStack_100);
    }
    dVar13 = dVar13 + dVar14;
    piVar11 = (int *)((int)piVar11 + 2);
  }
  DrawInit__8CMenuPcsFv(menuPcs);
  return;
}

