// Function: DrawSingleCrescent__8CMenuPcsFff
// Entry: 801487cc
// Size: 292 bytes

/* WARNING: Removing unreachable block (ram,0x801488d8) */
/* WARNING: Removing unreachable block (ram,0x801488d0) */
/* WARNING: Removing unreachable block (ram,0x801487e4) */
/* WARNING: Removing unreachable block (ram,0x801487dc) */

void DrawSingleCrescent__8CMenuPcsFff(double param_1,double param_2,CMenuPcs *menuPcs)

{
  double in_f30;
  double in_f31;
  double in_ps30_1;
  double in_ps31_1;
  undefined4 local_30;
  undefined4 local_2c;
  longlong local_28;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  DrawInit__8CMenuPcsFv(menuPcs);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_28 = (longlong)(int)((double)FLOAT_80332940 * param_2);
  local_2c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332940 * param_2));
  local_30 = local_2c;
  GXSetChanMatColor(4,&local_30);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x21);
  DrawRect__8CMenuPcsFUlfffffffff
            (-(double)(float)((double)FLOAT_803329ac * param_1 - (double)FLOAT_803329bc),
             (double)FLOAT_80332948,(double)FLOAT_803329ac,(double)FLOAT_803329b0,
             (double)FLOAT_8033294c,(double)FLOAT_8033294c,param_1,(double)FLOAT_80332934,&MenuPcs,0
            );
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803329b4,(double)FLOAT_80332948,(double)FLOAT_803329ac,
             (double)FLOAT_803329b0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,param_1,
             (double)FLOAT_80332934,&MenuPcs,8);
  return;
}

