// Function: DrawFont__8CMenuPcsFii8_GXColoriPcff
// Entry: 8017ad50
// Size: 240 bytes

/* WARNING: Removing unreachable block (ram,0x8017ae24) */
/* WARNING: Removing unreachable block (ram,0x8017ad60) */

void DrawFont__8CMenuPcsFii8_GXColoriPcff
               (double param_1,double param_2,int param_3,uint param_4,uint param_5,
               undefined4 *param_6,undefined4 param_7,undefined4 param_8)

{
  CFont *font;
  undefined4 local_48 [2];
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  font = *(CFont **)(param_3 + 0xf8);
  SetMargin__5CFontFf((float)param_2,font);
  SetShadow__5CFontFi(font,1);
  SetScale__5CFontFf((float)param_1,font);
  DrawInit__5CFontFv(font);
  SetTlut__5CFontFi(font,param_7);
  local_48[0] = *param_6;
  SetColor__5CFontF8_GXColor(font,local_48);
  uStack_3c = param_4 ^ 0x80000000;
  local_40 = 0x43300000;
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80333640),font);
  uStack_34 = param_5 ^ 0x80000000;
  local_38 = 0x43300000;
  SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80333640),font);
  Draw__5CFontFPc(font,param_8);
  return;
}

