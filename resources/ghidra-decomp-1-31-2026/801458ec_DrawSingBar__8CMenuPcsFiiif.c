// Function: DrawSingBar__8CMenuPcsFiiif
// Entry: 801458ec
// Size: 920 bytes

/* WARNING: Removing unreachable block (ram,0x80145c68) */
/* WARNING: Removing unreachable block (ram,0x801458fc) */

void DrawSingBar__8CMenuPcsFiiif
               (double param_1,undefined4 param_2,uint param_3,uint param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 local_68;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_68 = (double)(longlong)(int)((double)FLOAT_80332940 * param_1);
  local_6c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332940 * param_1));
  local_70 = local_6c;
  GXSetChanMatColor(4,&local_70);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x53);
  uStack_5c = param_3 ^ 0x80000000;
  uStack_54 = param_4 ^ 0x80000000;
  local_60 = 0x43300000;
  local_58 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332938),
             (double)FLOAT_80332944,(double)FLOAT_80332948,(double)FLOAT_8033294c,
             (double)FLOAT_8033294c,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  uStack_4c = param_3 + 0x60 ^ 0x80000000;
  local_50 = 0x43300000;
  uStack_44 = param_4 ^ 0x80000000;
  local_48 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332938),
             (double)FLOAT_80332944,(double)FLOAT_80332948,(double)FLOAT_8033294c,
             (double)FLOAT_8033294c,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,8);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x54);
  uStack_3c = param_3 + 0x10 ^ 0x80000000;
  local_40 = 0x43300000;
  uStack_34 = param_4 ^ 0x80000000;
  local_38 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80332938),
             (double)FLOAT_80332950,(double)FLOAT_80332948,(double)FLOAT_8033294c,
             (double)FLOAT_8033294c,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  if (param_5 < 0x29) {
    iVar3 = 0x59;
  }
  else if (param_5 < 0x3d) {
    iVar3 = 0x57;
  }
  else {
    iVar3 = 0x55;
  }
  iVar1 = param_5 / 10 + (param_5 >> 0x1f);
  iVar2 = iVar1 - (iVar1 >> 0x1f);
  if (param_5 != (iVar1 - (iVar1 >> 0x1f)) * 10) {
    iVar2 = iVar2 + 1;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar3);
  uStack_34 = param_3 + 0x10 ^ 0x80000000;
  param_4 = param_4 + 8;
  uStack_3c = param_4 ^ 0x80000000;
  local_38 = 0x43300000;
  local_40 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332938),
             (double)FLOAT_80332954,(double)FLOAT_80332930,(double)FLOAT_8033294c,
             (double)FLOAT_8033294c,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  uStack_4c = param_4 ^ 0x80000000;
  uStack_44 = (iVar2 * 8 + param_3 + 0x10) - 4 ^ 0x80000000;
  local_48 = 0x43300000;
  local_50 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80332938),
             (double)FLOAT_80332954,(double)FLOAT_80332930,(double)FLOAT_8033294c,
             (double)FLOAT_8033294c,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,8);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar3 + 1);
  uStack_5c = param_4 ^ 0x80000000;
  uStack_54 = param_3 + 0x14 ^ 0x80000000;
  local_60 = 0x43300000;
  local_58 = 0x43300000;
  local_68 = (double)CONCAT44(0x43300000,iVar2 * 8 - 8U ^ 0x80000000);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80332938),
             (double)(float)(local_68 - DOUBLE_80332938),(double)FLOAT_80332930,
             (double)FLOAT_8033294c,(double)FLOAT_8033294c,(double)FLOAT_80332934,
             (double)FLOAT_80332934,&MenuPcs,0);
  return;
}

