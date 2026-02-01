// Function: DrawFilter__8CMenuPcsFUcUcUcUc
// Entry: 800e9ba0
// Size: 236 bytes

void DrawFilter__8CMenuPcsFUcUcUcUc
               (CMenuPcs *menuPcs,undefined param_2,undefined param_3,undefined param_4,
               undefined param_5)

{
  undefined4 local_18;
  undefined4 local_14;
  
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(menuPcs,2);
  local_14 = CONCAT31(CONCAT21(CONCAT11(param_2,param_3),param_4),param_5);
  local_18 = local_14;
  GXSetChanMatColor(4,&local_18);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0xffffffff);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  GXBegin(0x80,0,4);
  DAT_cc008000 = FLOAT_803313dc;
  DAT_cc008000 = FLOAT_803313dc;
  DAT_cc008000 = FLOAT_803313dc;
  DAT_cc008000 = FLOAT_803313e0;
  DAT_cc008000 = FLOAT_803313dc;
  DAT_cc008000 = FLOAT_803313dc;
  DAT_cc008000 = FLOAT_803313e0;
  DAT_cc008000 = FLOAT_803313e4;
  DAT_cc008000 = FLOAT_803313dc;
  DAT_cc008000 = FLOAT_803313dc;
  DAT_cc008000 = FLOAT_803313e4;
  DAT_cc008000 = FLOAT_803313dc;
  return;
}

