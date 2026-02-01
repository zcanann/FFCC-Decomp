// Function: DrawListPosMark__8CMenuPcsFfff
// Entry: 8014735c
// Size: 240 bytes

/* WARNING: Removing unreachable block (ram,0x80147434) */
/* WARNING: Removing unreachable block (ram,0x8014742c) */
/* WARNING: Removing unreachable block (ram,0x80147424) */
/* WARNING: Removing unreachable block (ram,0x8014737c) */
/* WARNING: Removing unreachable block (ram,0x80147374) */
/* WARNING: Removing unreachable block (ram,0x8014736c) */

void DrawListPosMark__8CMenuPcsFfff(double param_1,double param_2,double param_3)

{
  double in_f29;
  double in_f30;
  double in_f31;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  undefined4 local_40;
  undefined4 local_3c;
  float local_28;
  float fStack_24;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  local_28 = (float)in_f29;
  fStack_24 = (float)in_ps29_1;
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_3c = 0xffffffff;
  local_40 = 0xffffffff;
  GXSetChanMatColor(4,&local_40);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x2e);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)FLOAT_80332990 + param_1),(double)(float)(param_2 + param_3),
             (double)FLOAT_80332930,(double)FLOAT_80332930,(double)FLOAT_80332994,
             (double)FLOAT_80332998,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  return;
}

