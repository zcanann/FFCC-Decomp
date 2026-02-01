// Function: CalcCenteringPos__8CMenuPcsFPcP5CFont
// Entry: 8017ae40
// Size: 48 bytes

double CalcCenteringPos__8CMenuPcsFPcP5CFont(CMenuPcs *menuPcs,undefined4 param_2,CFont *font)

{
  double dVar1;
  
  dVar1 = (double)GetWidth__5CFontFPc(font,param_2);
  return -(double)(float)(dVar1 * (double)FLOAT_80333558 - (double)FLOAT_8033358c);
}

