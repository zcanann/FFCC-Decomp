// Function: CalcCenteringPos2__8CMenuPcsFPcff
// Entry: 8017ae70
// Size: 164 bytes

/* WARNING: Removing unreachable block (ram,0x8017aef4) */
/* WARNING: Removing unreachable block (ram,0x8017aeec) */
/* WARNING: Removing unreachable block (ram,0x8017ae88) */
/* WARNING: Removing unreachable block (ram,0x8017ae80) */

double CalcCenteringPos2__8CMenuPcsFPcff
                 (double param_1,double param_2,CMenuPcs *menuPcs,undefined4 param_4)

{
  CFont *font;
  double dVar1;
  
  font = *(CFont **)&menuPcs->field_0xf8;
  SetShadow__5CFontFi(font,1);
  SetMargin__5CFontFf((float)param_2,font);
  SetScaleX__5CFontFf((float)param_1,font);
  SetScaleY__5CFontFf(FLOAT_8033356c,font);
  dVar1 = (double)GetWidth__5CFontFPc(font,param_4);
  return -(double)(float)(dVar1 * (double)FLOAT_80333558 - (double)FLOAT_8033358c);
}

