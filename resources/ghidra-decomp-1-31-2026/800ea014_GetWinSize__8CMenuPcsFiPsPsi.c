// Function: GetWinSize__8CMenuPcsFiPsPsi
// Entry: 800ea014
// Size: 316 bytes

void GetWinSize__8CMenuPcsFiPsPsi
               (CMenuPcs *menuPcs,undefined4 param_2,short *param_3,short *param_4,
               undefined4 param_5)

{
  int iVar1;
  int *piVar2;
  short sVar3;
  char *pcVar4;
  int iVar5;
  int *piVar6;
  CFont *font;
  int iVar7;
  double dVar8;
  
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_803313e8,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_803313e8,font);
  iVar1 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,param_5);
  iVar7 = 0;
  piVar2 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,param_2);
  iVar5 = 0;
  piVar6 = piVar2;
  while( true ) {
    if (*piVar2 <= iVar5) break;
    pcVar4 = *(char **)(iVar1 + *(short *)(piVar6 + 1) * 4);
    if (pcVar4 != (char *)0x0) {
      if (*pcVar4 == '$') {
        pcVar4 = pcVar4 + 1;
      }
      dVar8 = (double)GetWidth__5CFontFPc(font,pcVar4);
      if (iVar7 < (int)dVar8) {
        iVar7 = (int)dVar8;
      }
    }
    piVar6 = (int *)((int)piVar6 + 2);
    iVar5 = iVar5 + 1;
  }
  iVar1 = iVar7 / 0x16 + (iVar7 >> 0x1f);
  sVar3 = (short)iVar1 - (short)(iVar1 >> 0x1f);
  if (iVar7 != (iVar1 - (iVar1 >> 0x1f)) * 0x16) {
    sVar3 = sVar3 + 1;
  }
  *param_3 = (sVar3 + 2) * 0x16 + 0x40;
  *param_4 = (short)*piVar2 * 0x1e + 0x40;
  return;
}

