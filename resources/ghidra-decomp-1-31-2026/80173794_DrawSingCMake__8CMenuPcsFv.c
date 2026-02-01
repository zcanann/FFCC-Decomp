// Function: DrawSingCMake__8CMenuPcsFv
// Entry: 80173794
// Size: 1040 bytes

/* WARNING: Removing unreachable block (ram,0x80173b88) */
/* WARNING: Removing unreachable block (ram,0x80173b80) */
/* WARNING: Removing unreachable block (ram,0x801737ac) */
/* WARNING: Removing unreachable block (ram,0x801737a4) */

void DrawSingCMake__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  undefined4 local_50;
  undefined4 local_4c;
  undefined8 local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  iVar3 = *(int *)&menuPcs->field_0x82c;
  switch(*(undefined2 *)(iVar3 + 0x16)) {
  case 0:
    uVar2 = (int)*(short *)(iVar3 + 0x22) - 1;
    if ((int)uVar2 < 0) {
      uVar2 = 0;
    }
    if (*(short *)(iVar3 + 0x10) == 0) {
      local_48 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
      dVar5 = (double)(float)(DOUBLE_80333268 * (local_48 - DOUBLE_803332d0));
    }
    else if (*(short *)(iVar3 + 0x10) == 1) {
      dVar5 = (double)FLOAT_80333258;
    }
    else {
      local_48 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
      dVar5 = (double)(float)-(DOUBLE_80333268 * (local_48 - DOUBLE_803332d0) - DOUBLE_80333270);
    }
    DrawWMFrame0__8CMenuPcsFif(dVar5,menuPcs,1);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_48 = (double)(longlong)(int)((double)FLOAT_80333240 * dVar5);
    local_50 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80333240 * dVar5));
    local_4c = local_50;
    GXSetChanMatColor(4,&local_4c);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3f);
    dVar5 = (double)FLOAT_80333254;
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar5,(double)FLOAT_803332d8,(double)FLOAT_803332dc,(double)FLOAT_803332e0,dVar5,
               dVar5,(double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_803332e4,(double)FLOAT_803332d8,(double)FLOAT_803332dc,
               (double)FLOAT_803332e0,(double)FLOAT_80333254,(double)FLOAT_80333254,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,8);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x40);
    dVar6 = (double)FLOAT_80333254;
    dVar5 = DOUBLE_803332d0;
    for (uVar2 = 0x20; (int)uVar2 < 0x260; uVar2 = uVar2 + uVar4) {
      uVar4 = 0x20;
      if ((int)(0x260 - uVar2) < 0x20) {
        uVar4 = 0x260 - uVar2;
      }
      uStack_3c = uVar4 ^ 0x80000000;
      local_48 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
      local_40 = 0x43300000;
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)(local_48 - dVar5),(double)FLOAT_803332d8,
                 (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - dVar5),
                 (double)FLOAT_803332e0,dVar6,dVar6,(double)FLOAT_80333258,(double)FLOAT_80333258,
                 &MenuPcs,0);
    }
    iVar3 = *(int *)&menuPcs->field_0x82c;
    if ((*(short *)(iVar3 + 0x2e) == 0) || (*(short *)(iVar3 + 0x10) != 0)) {
      if ((*(short *)(iVar3 + 0x2e) != 0) && (*(short *)(iVar3 + 0x10) == 2)) {
        *(undefined2 *)&menuPcs->field_0x86a = 999;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x20) = 0xffff;
      }
    }
    else {
      *(short *)(iVar3 + 0x16) = *(short *)(iVar3 + 0x16) + 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = 0;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
    }
    break;
  case 1:
    CmakeNameDraw__8CMenuPcsFv(menuPcs);
    break;
  case 2:
    CmakeSexDraw__8CMenuPcsFv(menuPcs);
    break;
  case 3:
    CmakeTribeDraw__8CMenuPcsFv(menuPcs);
    break;
  case 4:
    CmakeJobDraw__8CMenuPcsFv(menuPcs);
    break;
  case 5:
    CmakeResultDraw__8CMenuPcsFv(menuPcs);
    break;
  case 6:
    CmakeResultDraw1__8CMenuPcsFv(menuPcs);
  }
  iVar3 = *(int *)&menuPcs->field_0x82c;
  if (*(short *)(iVar3 + 0x2e) == 0) {
    return;
  }
  if (*(short *)(iVar3 + 0x10) < 2) {
    *(short *)(iVar3 + 0x10) = *(short *)(iVar3 + 0x10) + 1;
    goto LAB_80173b68;
  }
  DAT_8032ef10 = (int)*(short *)(iVar3 + 0x16);
  iVar3 = *(int *)&menuPcs->field_0x82c;
  sVar1 = *(short *)(iVar3 + 0x16);
  if (sVar1 == 6) {
    *(short *)(iVar3 + 0x16) = *(short *)(iVar3 + 0x26) + 1;
LAB_80173b38:
    iVar3 = *(int *)&menuPcs->field_0x82c;
    if (*(short *)(iVar3 + 0x16) == 0) {
      *(undefined2 *)(iVar3 + 0x10) = 2;
    }
    else {
      *(undefined2 *)(iVar3 + 0x10) = 0;
    }
  }
  else {
    if (*(short *)(iVar3 + 0x1e) < 0) {
      if (sVar1 != 0) {
        if (sVar1 == 5) {
          *(undefined2 *)(iVar3 + 0x16) = 6;
        }
        else {
          *(short *)(iVar3 + 0x16) = sVar1 + -1;
        }
      }
      goto LAB_80173b38;
    }
    if (sVar1 != 5) {
      *(short *)(iVar3 + 0x16) = sVar1 + 1;
      goto LAB_80173b38;
    }
    *(undefined2 *)(iVar3 + 0x16) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 2;
  }
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
LAB_80173b68:
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
  return;
}

