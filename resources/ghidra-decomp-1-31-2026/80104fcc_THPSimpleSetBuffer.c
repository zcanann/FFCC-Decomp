// Function: THPSimpleSetBuffer
// Entry: 80104fcc
// Size: 424 bytes

undefined4 THPSimpleSetBuffer(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  if ((SimpleControl._160_4_ != 0) && (SimpleControl._164_1_ == '\0')) {
    if (SimpleControl._165_1_ == '\x01') {
      return 0;
    }
    uVar1 = SimpleControl._128_4_ * SimpleControl._132_4_ + 0x1f & 0xffffffe0;
    uVar2 = ((uint)(SimpleControl._128_4_ * SimpleControl._132_4_) >> 2) + 0x1f & 0xffffffe0;
    SimpleControl._308_4_ = param_1;
    DCInvalidateRange(param_1,uVar1);
    param_1 = param_1 + uVar1;
    SimpleControl._312_4_ = param_1;
    DCInvalidateRange(param_1,uVar2);
    param_1 = param_1 + uVar2;
    SimpleControl._316_4_ = param_1;
    DCInvalidateRange(param_1,uVar2);
    SimpleControl._212_4_ = param_1 + uVar2;
    SimpleControl._220_4_ = 0;
    uVar1 = SimpleControl._68_4_ + 0x1f & 0xffffffe0;
    SimpleControl._224_4_ = SimpleControl._212_4_ + uVar1;
    SimpleControl._236_4_ = SimpleControl._224_4_ + uVar1;
    SimpleControl._248_4_ = SimpleControl._236_4_ + uVar1;
    SimpleControl._260_4_ = SimpleControl._248_4_ + uVar1;
    SimpleControl._272_4_ = SimpleControl._260_4_ + uVar1;
    SimpleControl._284_4_ = SimpleControl._272_4_ + uVar1;
    SimpleControl._296_4_ = SimpleControl._284_4_ + uVar1;
    SimpleControl._232_4_ = 0;
    SimpleControl._244_4_ = 0;
    SimpleControl._256_4_ = 0;
    SimpleControl._268_4_ = 0;
    SimpleControl._280_4_ = 0;
    SimpleControl._292_4_ = 0;
    iVar3 = SimpleControl._296_4_ + uVar1;
    SimpleControl._304_4_ = 0;
    SimpleControl._156_4_ = iVar3;
    if (SimpleControl._167_1_ != '\0') {
      uVar1 = SimpleControl._72_4_ * 4 + 0x1fU & 0xffffffe0;
      SimpleControl._336_4_ = iVar3 + uVar1;
      SimpleControl._332_4_ = 0;
      SimpleControl._348_4_ = SimpleControl._336_4_ + uVar1;
      SimpleControl._344_4_ = 0;
      SimpleControl._156_4_ = SimpleControl._348_4_ + uVar1;
      SimpleControl._356_4_ = 0;
      SimpleControl._324_4_ = iVar3;
      SimpleControl._328_4_ = iVar3;
      SimpleControl._340_4_ = SimpleControl._336_4_;
      SimpleControl._352_4_ = SimpleControl._348_4_;
    }
  }
  return 1;
}

