// Function: DrawShadowFont__8CMenuPcsFP5CFontPcffii
// Entry: 8014764c
// Size: 220 bytes

/* WARNING: Removing unreachable block (ram,0x80147704) */
/* WARNING: Removing unreachable block (ram,0x801476fc) */
/* WARNING: Removing unreachable block (ram,0x80147664) */
/* WARNING: Removing unreachable block (ram,0x8014765c) */

void DrawShadowFont__8CMenuPcsFP5CFontPcffii
               (double param_1,double param_2,undefined4 param_3,CFont *param_4,undefined4 param_5,
               undefined4 param_6,undefined4 param_7)

{
  SetTlut__5CFontFi(param_4,param_7);
  SetPosX__5CFontFf((float)((double)FLOAT_80332934 + param_1),param_4);
  SetPosY__5CFontFf((float)((double)FLOAT_80332934 + param_2) - FLOAT_80332954,param_4);
  Draw__5CFontFPc(param_4,param_5);
  SetTlut__5CFontFi(param_4,param_6);
  SetPosX__5CFontFf((float)param_1,param_4);
  SetPosY__5CFontFf((float)(param_2 - (double)FLOAT_80332954),param_4);
  Draw__5CFontFPc(param_4,param_5);
  return;
}

