// Function: DrawDiaryBase__8CMenuPcsFif
// Entry: 8017352c
// Size: 616 bytes

/* WARNING: Removing unreachable block (ram,0x80173778) */
/* WARNING: Removing unreachable block (ram,0x80173770) */
/* WARNING: Removing unreachable block (ram,0x80173544) */
/* WARNING: Removing unreachable block (ram,0x8017353c) */

void DrawDiaryBase__8CMenuPcsFif(double param_1,CMenuPcs *menuPcs,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  undefined4 local_70;
  undefined4 local_6c;
  longlong local_68;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_68 = (longlong)(int)((double)FLOAT_80333240 * param_1);
  local_6c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80333240 * param_1));
  local_70 = local_6c;
  GXSetChanMatColor(4,&local_70);
  uVar1 = countLeadingZeros(param_3);
  uVar2 = 0x3f;
  if ((uVar1 >> 5 & 0xff) != 0) {
    uVar2 = 0x35;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar2);
  uVar4 = 0x150;
  if ((uVar1 >> 5 & 0xff) != 0) {
    uVar4 = 0x180;
  }
  uStack_54 = uVar4 ^ 0x80000000;
  uStack_5c = 0x80000018;
  dVar5 = (double)FLOAT_80333254;
  local_60 = 0x43300000;
  local_58 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar5,(double)(float)(4503601774854168.0 - DOUBLE_803332d0),(double)FLOAT_803332dc,
             (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_803332d0),dVar5,dVar5,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  uStack_44 = uVar4 ^ 0x80000000;
  uStack_4c = 0x80000018;
  local_50 = 0x43300000;
  local_48 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803332e4,(double)(float)(4503601774854168.0 - DOUBLE_803332d0),
             (double)FLOAT_803332dc,
             (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_803332d0),
             (double)FLOAT_80333254,(double)FLOAT_80333254,(double)FLOAT_80333258,
             (double)FLOAT_80333258,&MenuPcs,8);
  uVar2 = 0x40;
  if ((uVar1 >> 5 & 0xff) != 0) {
    uVar2 = 0x36;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar2);
  dVar6 = (double)FLOAT_80333254;
  dVar5 = DOUBLE_803332d0;
  for (uVar1 = 0x20; (int)uVar1 < 0x260; uVar1 = uVar1 + uVar3) {
    uVar3 = 0x20;
    if ((int)(0x260 - uVar1) < 0x20) {
      uVar3 = 0x260 - uVar1;
    }
    uStack_44 = uVar1 ^ 0x80000000;
    uStack_54 = uVar3 ^ 0x80000000;
    local_48 = 0x43300000;
    uStack_4c = 0x80000018;
    local_50 = 0x43300000;
    local_58 = 0x43300000;
    local_60 = 0x43300000;
    uStack_5c = uVar4 ^ 0x80000000;
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_44) - dVar5),
               (double)(float)(4503601774854168.0 - dVar5),
               (double)(float)((double)CONCAT44(0x43300000,uStack_54) - dVar5),
               (double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar5),dVar6,dVar6,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  return;
}

