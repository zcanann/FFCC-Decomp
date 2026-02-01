// Function: THPSimpleLoadStop
// Entry: 80104b20
// Size: 232 bytes

undefined4 THPSimpleLoadStop(void)

{
  undefined4 uVar1;
  
  if ((SimpleControl._160_4_ == 0) || (SimpleControl._165_1_ != '\0')) {
    uVar1 = 0;
  }
  else {
    SimpleControl._164_1_ = 0;
    if (SimpleControl._176_4_ != 0) {
      DVDCancel(&SimpleControl);
      SimpleControl._176_4_ = 0;
    }
    uVar1 = 1;
    SimpleControl._220_4_ = 0;
    SimpleControl._232_4_ = 0;
    SimpleControl._244_4_ = 0;
    SimpleControl._256_4_ = 0;
    SimpleControl._268_4_ = 0;
    SimpleControl._280_4_ = 0;
    SimpleControl._292_4_ = 0;
    SimpleControl._304_4_ = 0;
    SimpleControl._332_4_ = 0;
    SimpleControl._344_4_ = 0;
    SimpleControl._356_4_ = 0;
    SimpleControl._320_4_ = 0xffffffff;
    SimpleControl._168_4_ = SimpleControl._100_4_;
    SimpleControl._188_4_ = SimpleControl._84_4_;
    SimpleControl._184_4_ = 0;
    SimpleControl._192_4_ = 0;
    SimpleControl._172_4_ = 0;
    SimpleControl._180_4_ = 0;
    SimpleControl._360_4_ = 0;
    SimpleControl._364_4_ = 0;
    SimpleControl._196_4_ = SimpleControl._200_4_;
    SimpleControl._208_4_ = 0;
  }
  return uVar1;
}

