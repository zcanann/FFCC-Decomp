// Function: DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
// Entry: 801475bc
// Size: 144 bytes

/* WARNING: Removing unreachable block (ram,0x8014762c) */
/* WARNING: Removing unreachable block (ram,0x80147624) */
/* WARNING: Removing unreachable block (ram,0x801475d4) */
/* WARNING: Removing unreachable block (ram,0x801475cc) */

void DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
               (double param_1,double param_2,undefined4 param_3,CFont *font,undefined4 param_5,
               undefined4 param_6)

{
  SetTlut__5CFontFi(font,param_6);
  SetPosX__5CFontFf((float)param_1,font);
  SetPosY__5CFontFf((float)(param_2 - (double)FLOAT_80332954),font);
  Draw__5CFontFPc(font,param_5);
  return;
}

