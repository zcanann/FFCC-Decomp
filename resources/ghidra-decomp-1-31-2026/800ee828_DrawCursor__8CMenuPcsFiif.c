// Function: DrawCursor__8CMenuPcsFiif
// Entry: 800ee828
// Size: 256 bytes

/* WARNING: Removing unreachable block (ram,0x800ee908) */
/* WARNING: Removing unreachable block (ram,0x800ee838) */

void DrawCursor__8CMenuPcsFiif(double param_1,CMenuPcs *menuPcs,uint param_3,uint param_4)

{
  undefined4 local_40;
  undefined4 local_3c;
  longlong local_38;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_38 = (longlong)(int)((double)FLOAT_80331458 * param_1);
  local_3c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331458 * param_1));
  local_40 = local_3c;
  GXSetChanMatColor(4,&local_40);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0);
  uStack_2c = param_3 ^ 0x80000000;
  uStack_24 = param_4 ^ 0x80000000;
  local_30 = 0x43300000;
  local_28 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80331408),
             (double)(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80331408),
             (double)FLOAT_80331410,(double)FLOAT_80331410,(double)FLOAT_803313dc,
             (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
  return;
}

