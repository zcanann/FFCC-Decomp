// Function: SingleDrawCtrl__8CMenuPcsFv
// Entry: 801478cc
// Size: 1156 bytes

/* WARNING: Removing unreachable block (ram,0x80147d34) */
/* WARNING: Removing unreachable block (ram,0x80147d2c) */
/* WARNING: Removing unreachable block (ram,0x801478e4) */
/* WARNING: Removing unreachable block (ram,0x801478dc) */

void SingleDrawCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  double dVar6;
  double dVar7;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  DrawInit__8CMenuPcsFv(menuPcs);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_58 = 0xffffffff;
  local_54 = 0xffffffff;
  GXSetChanMatColor(4,&local_54);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x20);
  dVar6 = (double)FLOAT_8033294c;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar6,dVar6,(double)FLOAT_803329a4,(double)FLOAT_80332928,dVar6,dVar6,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  dVar6 = (double)FLOAT_8033294c;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar6,(double)FLOAT_803329a8,(double)FLOAT_803329a4,(double)FLOAT_80332928,dVar6,dVar6,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,4);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x28);
  dVar7 = (double)FLOAT_8033294c;
  uVar4 = 0x20;
  dVar6 = DOUBLE_80332938;
  for (uVar3 = 0x40; (int)uVar3 < 0x180; uVar3 = uVar3 + uVar4) {
    if ((int)(0x180 - uVar3) < (int)uVar4) {
      uVar4 = 0x180 - uVar3;
    }
    uStack_4c = uVar3 ^ 0x80000000;
    uStack_44 = uVar4 ^ 0x80000000;
    local_50 = 0x43300000;
    local_48 = 0x43300000;
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar7,(double)(float)((double)CONCAT44(0x43300000,uStack_4c) - dVar6),
               (double)FLOAT_803329a4,
               (double)(float)((double)CONCAT44(0x43300000,uStack_44) - dVar6),dVar7,dVar7,
               (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  }
  if (*(short *)&menuPcs->field_0x864 != 8) {
    DrawInit__8CMenuPcsFv(menuPcs);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_5c = 0xffffffff;
    GXSetChanMatColor(4,&local_5c);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x21);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_8033292c,(double)FLOAT_80332948,(double)FLOAT_803329ac,
               (double)FLOAT_803329b0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
               (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_803329b4,(double)FLOAT_80332948,(double)FLOAT_803329ac,
               (double)FLOAT_803329b0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
               (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,8);
    DrawSingleStat__8CMenuPcsFf((double)FLOAT_80332934,menuPcs);
    DrawSingleHelpWim__8CMenuPcsFf((double)FLOAT_80332934,menuPcs);
  }
  if (DAT_8032eebc != 0) {
    switch(*(undefined2 *)&menuPcs->field_0x864) {
    case 0:
      CmdDraw__8CMenuPcsFv(menuPcs);
      break;
    case 1:
      ItemDraw__8CMenuPcsFv(menuPcs);
      break;
    case 2:
      EquipDraw__8CMenuPcsFv(menuPcs);
      break;
    case 3:
      ArtiDraw__8CMenuPcsFv(menuPcs);
      break;
    case 4:
      TmpArtiDraw__8CMenuPcsFv(menuPcs);
      break;
    case 5:
      MoneyDraw__8CMenuPcsFv(menuPcs);
      break;
    case 6:
      FavoDraw__8CMenuPcsFv(menuPcs);
      break;
    case 7:
      CompaDraw__8CMenuPcsFv(menuPcs);
      break;
    case 8:
      LetterDraw__8CMenuPcsFv(menuPcs);
      break;
    case 9:
      MLstDraw__8CMenuPcsFv(menuPcs);
    }
    iVar2 = *(int *)&menuPcs->field_0x82c;
    if (*(short *)(iVar2 + 0x2e) != 0) {
      if (*(short *)(iVar2 + 0x10) < 2) {
        *(short *)(iVar2 + 0x10) = *(short *)(iVar2 + 0x10) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = 0;
      }
      else {
        sVar5 = 0;
        if (*(char *)(iVar2 + 0xd) == '\0') {
          sVar1 = *(short *)&menuPcs->field_0x864;
          if (sVar1 == 9) {
            *(undefined2 *)&menuPcs->field_0x864 = *(undefined2 *)(iVar2 + 0x26);
          }
          else if ((sVar1 == 8) && (-1 < DAT_8032eec4)) {
            *(short *)&menuPcs->field_0x864 = (short)DAT_8032eec4;
          }
          else if ((sVar1 == 8) || (DAT_8032eec4 < 0)) {
            if (*(short *)(iVar2 + 0x1e) < 1) {
              *(short *)&menuPcs->field_0x864 = *(short *)&menuPcs->field_0x864 + -1;
              if (*(short *)&menuPcs->field_0x864 < 0) {
                *(undefined2 *)&menuPcs->field_0x864 = 8;
              }
            }
            else {
              *(short *)&menuPcs->field_0x864 = *(short *)&menuPcs->field_0x864 + 1;
              if (8 < *(short *)&menuPcs->field_0x864) {
                *(undefined2 *)&menuPcs->field_0x864 = 0;
              }
            }
          }
          else {
            *(undefined2 *)&menuPcs->field_0x864 = 8;
          }
        }
        else {
          sVar1 = *(short *)&menuPcs->field_0x864;
          if (sVar1 == 9) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 6) = 1;
          }
          else {
            *(undefined2 *)&menuPcs->field_0x864 = 9;
            sVar5 = sVar1;
          }
        }
        memset(*(undefined4 *)&menuPcs->field_0x82c,0,0x48);
        FLOAT_8032ea78 = FLOAT_803329b8;
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = sVar5;
      }
    }
  }
  return;
}

