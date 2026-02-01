// Function: DrawCharaBase__8CMenuPcsFv
// Entry: 800f31b8
// Size: 460 bytes

/* WARNING: Removing unreachable block (ram,0x800f3368) */
/* WARNING: Removing unreachable block (ram,0x800f3360) */
/* WARNING: Removing unreachable block (ram,0x800f31d0) */
/* WARNING: Removing unreachable block (ram,0x800f31c8) */

void DrawCharaBase__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  double dVar6;
  double dVar7;
  undefined4 local_50;
  undefined4 local_4c;
  undefined8 local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  iVar2 = *(int *)&menuPcs->field_0x82c;
  sVar1 = *(short *)(iVar2 + 0x10);
  if (sVar1 != 0) {
    if (sVar1 == 1) {
      local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar2 + 0x22)) ^ 0x80000000);
      dVar6 = (double)(float)(DOUBLE_803316c0 * (local_48 - DOUBLE_80331408));
    }
    else if (sVar1 == 2) {
      dVar6 = (double)FLOAT_80331668;
    }
    else {
      local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar2 + 0x22)) ^ 0x80000000);
      dVar6 = (double)(float)-(DOUBLE_803316c0 * (local_48 - DOUBLE_80331408) - DOUBLE_80331448);
    }
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_48 = (double)(longlong)(int)(DOUBLE_80331508 * dVar6);
    local_4c = CONCAT31(0xffffff,(char)(int)(DOUBLE_80331508 * dVar6));
    local_50 = local_4c;
    GXSetChanMatColor(4,&local_50);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x29);
    dVar7 = (double)FLOAT_803313dc;
    iVar2 = 0;
    uVar4 = 0x22;
    dVar6 = DOUBLE_80331408;
    do {
      iVar3 = 0;
      uVar5 = 0x1c;
      do {
        uStack_3c = uVar4;
        if (iVar2 != 0) {
          uStack_3c = uVar4 + 8;
        }
        uStack_3c = uStack_3c ^ 0x80000000;
        local_48 = (double)CONCAT44(0x43300000,uVar5 ^ 0x80000000);
        local_40 = 0x43300000;
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)(local_48 - dVar6),
                   (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - dVar6),
                   (double)FLOAT_803316c8,(double)FLOAT_803316cc,dVar7,dVar7,(double)FLOAT_803313e8,
                   (double)FLOAT_803313e8,&MenuPcs,0);
        iVar3 = iVar3 + 1;
        uVar5 = uVar5 + 0x90;
      } while (iVar3 < 4);
      iVar2 = iVar2 + 1;
      uVar4 = uVar4 + 0xb8;
    } while (iVar2 < 2);
  }
  return;
}

