// Function: DrawFont2__8CMenuPcsFii8_GXColoriPcfff
// Entry: 8017ac40
// Size: 272 bytes

/* WARNING: Removing unreachable block (ram,0x8017ad34) */
/* WARNING: Removing unreachable block (ram,0x8017ad2c) */
/* WARNING: Removing unreachable block (ram,0x8017ac58) */
/* WARNING: Removing unreachable block (ram,0x8017ac50) */

void DrawFont2__8CMenuPcsFii8_GXColoriPcfff
               (double param_1,double param_2,double param_3,int param_4,uint param_5,uint param_6,
               undefined4 *param_7,undefined4 param_8,undefined4 param_9)

{
  CFont *font;
  undefined4 local_58 [2];
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  font = *(CFont **)(param_4 + 0xf8);
  SetMargin__5CFontFf((float)param_3,font);
  SetShadow__5CFontFi(font,1);
  SetScaleX__5CFontFf((float)param_1,font);
  SetScaleY__5CFontFf((float)param_2,font);
  DrawInit__5CFontFv(font);
  SetTlut__5CFontFi(font,param_8);
  local_58[0] = *param_7;
  SetColor__5CFontF8_GXColor(font,local_58);
  uStack_4c = param_5 ^ 0x80000000;
  local_50 = 0x43300000;
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80333640),font);
  uStack_44 = param_6 ^ 0x80000000;
  local_48 = 0x43300000;
  SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80333640),font);
  Draw__5CFontFPc(font,param_9);
  return;
}

