// Function: DrawCmakeTitle__8CMenuPcsFiff
// Entry: 80173258
// Size: 724 bytes

/* WARNING: Removing unreachable block (ram,0x80173504) */
/* WARNING: Removing unreachable block (ram,0x801734fc) */
/* WARNING: Removing unreachable block (ram,0x80173270) */
/* WARNING: Removing unreachable block (ram,0x80173268) */

void DrawCmakeTitle__8CMenuPcsFiff(double param_1,double param_2,CMenuPcs *menuPcs,int param_4)

{
  uint uVar1;
  undefined4 uVar2;
  double dVar3;
  undefined4 local_70;
  undefined4 local_6c;
  longlong local_68;
  undefined8 local_60;
  longlong local_58;
  undefined4 local_50;
  undefined *puStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_68 = (longlong)(int)((double)FLOAT_80333240 * param_2);
  local_6c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80333240 * param_2));
  local_70 = local_6c;
  GXSetChanMatColor(4,&local_70);
  uVar2 = 0x3b;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar2 = 0x62;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar2);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80333390,(double)FLOAT_803332dc,(double)FLOAT_80333394,
             (double)FLOAT_8033327c,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80333398,(double)FLOAT_803332dc,(double)FLOAT_80333394,
             (double)FLOAT_8033327c,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,8);
  uVar2 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar2 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar2);
  dVar3 = (double)FLOAT_803333a8;
  local_50 = 0x43300000;
  uVar1 = (uint)(-(double)(float)(dVar3 * param_1 - dVar3) * DOUBLE_80333298 + DOUBLE_803333a0);
  local_60 = (double)(longlong)(int)uVar1;
  puStack_4c = (undefined *)(uVar1 ^ 0x80000000);
  local_58 = (longlong)local_60;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803333ac,
             (double)(float)((double)CONCAT44(0x43300000,puStack_4c) - DOUBLE_803332d0),
             (double)FLOAT_803333b0,dVar3,(double)FLOAT_80333254,(double)FLOAT_80333284,
             (double)FLOAT_80333258,param_1,&MenuPcs,0);
  if (DOUBLE_80333270 <= param_1) {
    uVar2 = 0x3e;
    if (*(short *)&menuPcs->field_0x86c != 0) {
      uVar2 = 0x65;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar2);
    puStack_4c = &DAT_80000116;
    local_50 = 0x43300000;
    uStack_34 = param_4 * 0x18 ^ 0x80000000;
    local_60 = (double)CONCAT44(0x43300000,uVar1 ^ 0x80000000);
    uStack_44 = (uint)((4503601774854422.0 - DOUBLE_803332d0) + DOUBLE_803333b8);
    local_58 = (longlong)(int)uStack_44;
    local_48 = 0x43300000;
    uStack_3c = (uint)((local_60 - DOUBLE_803332d0) + DOUBLE_803333c0);
    local_68 = (longlong)(int)uStack_3c;
    local_40 = 0x43300000;
    uStack_44 = uStack_44 ^ 0x80000000;
    uStack_3c = uStack_3c ^ 0x80000000;
    local_38 = 0x43300000;
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_803332d0),
               (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_803332d0),
               (double)FLOAT_803333c8,(double)FLOAT_803332d8,(double)FLOAT_80333254,
               (double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_803332d0),
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  return;
}

