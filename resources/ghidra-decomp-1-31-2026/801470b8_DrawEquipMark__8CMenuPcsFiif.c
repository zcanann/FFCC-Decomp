// Function: DrawEquipMark__8CMenuPcsFiif
// Entry: 801470b8
// Size: 276 bytes

/* WARNING: Removing unreachable block (ram,0x801471ac) */
/* WARNING: Removing unreachable block (ram,0x801470c8) */

void DrawEquipMark__8CMenuPcsFiif(double param_1,CMenuPcs *menuPcs,uint param_3,uint param_4)

{
  undefined4 local_40;
  undefined4 local_3c;
  longlong local_38;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_38 = (longlong)(int)((double)FLOAT_80332940 * param_1);
  local_3c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332940 * param_1));
  local_40 = local_3c;
  GXSetChanMatColor(4,&local_40);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x2c);
  uStack_2c = param_3 ^ 0x80000000;
  uStack_24 = param_4 ^ 0x80000000;
  local_30 = 0x43300000;
  local_28 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80332938),
             (double)FLOAT_80332948,(double)FLOAT_80332948,(double)FLOAT_8033294c,
             (double)FLOAT_8033294c,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  return;
}

