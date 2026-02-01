// Function: THPSimpleDrawCurrentFrame
// Entry: 80104594
// Size: 152 bytes

undefined4
THPSimpleDrawCurrentFrame
          (undefined4 param_1,short param_2,short param_3,short param_4,short param_5)

{
  undefined4 uVar1;
  
  if ((int)SimpleControl._320_4_ < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    THPGXYuv2RgbSetup();
    THPGXYuv2RgbDraw(SimpleControl._308_4_,SimpleControl._312_4_,SimpleControl._316_4_,(int)param_2,
                     (int)param_3,(int)(short)SimpleControl._128_4_,
                     (int)(short)SimpleControl._132_4_,(int)param_4,(int)param_5);
    THPGXRestore();
    uVar1 = SimpleControl._320_4_;
  }
  return uVar1;
}

