// Function: MixAudio__FPsPsUl
// Entry: 80104240
// Size: 852 bytes

void MixAudio__FPsPsUl(undefined2 *param_1,short *param_2,uint param_3)

{
  ushort uVar1;
  float fVar2;
  int iVar3;
  short *psVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_2 == (short *)0x0) {
    if (((SimpleControl._160_4_ == 0) || (SimpleControl._165_1_ != '\x01')) ||
       (SimpleControl._167_1_ == '\0')) {
      memset(param_1,0,param_3 << 2);
    }
    else {
      do {
        uVar5 = *(uint *)(&SimpleControl.field_0x14c + SimpleControl._364_4_ * 0xc);
        if (uVar5 == 0) {
          memset(param_1,0,param_3 << 2);
          return;
        }
        if (param_3 <= uVar5) {
          uVar5 = param_3;
        }
        psVar4 = *(short **)(&SimpleControl.field_0x148 + SimpleControl._364_4_ * 0xc);
        for (uVar6 = uVar5; uVar6 != 0; uVar6 = uVar6 - 1) {
          fVar2 = (float)SimpleControl._200_4_;
          if (SimpleControl._208_4_ != 0) {
            SimpleControl._208_4_ = SimpleControl._208_4_ + -1;
            fVar2 = (float)SimpleControl._196_4_ + (float)SimpleControl._204_4_;
          }
          SimpleControl._196_4_ = fVar2;
          uVar1 = *(ushort *)(&DAT_802111e8 + (int)(float)SimpleControl._196_4_ * 2);
          iVar3 = (int)((uint)uVar1 * (int)*psVar4) >> 0xf;
          if (iVar3 < -0x8000) {
            iVar3 = -0x8000;
          }
          if (0x7fff < iVar3) {
            iVar3 = 0x7fff;
          }
          *param_1 = (short)iVar3;
          iVar3 = (int)((uint)uVar1 * (int)psVar4[1]) >> 0xf;
          if (iVar3 < -0x8000) {
            iVar3 = -0x8000;
          }
          if (0x7fff < iVar3) {
            iVar3 = 0x7fff;
          }
          param_1[1] = (short)iVar3;
          param_1 = param_1 + 2;
          psVar4 = psVar4 + 2;
        }
        param_3 = param_3 - uVar5;
        *(uint *)(&SimpleControl.field_0x14c + SimpleControl._364_4_ * 0xc) =
             *(int *)(&SimpleControl.field_0x14c + SimpleControl._364_4_ * 0xc) - uVar5;
        *(short **)(&SimpleControl.field_0x148 + SimpleControl._364_4_ * 0xc) = psVar4;
        if ((*(int *)(&SimpleControl.field_0x14c + SimpleControl._364_4_ * 0xc) == 0) &&
           (SimpleControl._364_4_ = SimpleControl._364_4_ + 1, 2 < (int)SimpleControl._364_4_)) {
          SimpleControl._364_4_ = 0;
        }
      } while (param_3 != 0);
    }
  }
  else if (((SimpleControl._160_4_ == 0) || (SimpleControl._165_1_ != '\x01')) ||
          (SimpleControl._167_1_ == '\0')) {
    memcpy(param_1,param_2,param_3 << 2);
  }
  else {
    do {
      uVar5 = *(uint *)(&SimpleControl.field_0x14c + SimpleControl._364_4_ * 0xc);
      if (uVar5 == 0) {
        memcpy(param_1,param_2,param_3 << 2);
        return;
      }
      if (param_3 <= uVar5) {
        uVar5 = param_3;
      }
      psVar4 = *(short **)(&SimpleControl.field_0x148 + SimpleControl._364_4_ * 0xc);
      for (uVar6 = uVar5; uVar6 != 0; uVar6 = uVar6 - 1) {
        fVar2 = (float)SimpleControl._200_4_;
        if (SimpleControl._208_4_ != 0) {
          SimpleControl._208_4_ = SimpleControl._208_4_ + -1;
          fVar2 = (float)SimpleControl._196_4_ + (float)SimpleControl._204_4_;
        }
        SimpleControl._196_4_ = fVar2;
        uVar1 = *(ushort *)(&DAT_802111e8 + (int)(float)SimpleControl._196_4_ * 2);
        iVar3 = (int)*param_2 + ((int)((uint)uVar1 * (int)*psVar4) >> 0xf);
        if (iVar3 < -0x8000) {
          iVar3 = -0x8000;
        }
        if (0x7fff < iVar3) {
          iVar3 = 0x7fff;
        }
        *param_1 = (short)iVar3;
        iVar3 = (int)param_2[1] + ((int)((uint)uVar1 * (int)psVar4[1]) >> 0xf);
        if (iVar3 < -0x8000) {
          iVar3 = -0x8000;
        }
        if (0x7fff < iVar3) {
          iVar3 = 0x7fff;
        }
        param_1[1] = (short)iVar3;
        param_1 = param_1 + 2;
        param_2 = param_2 + 2;
        psVar4 = psVar4 + 2;
      }
      param_3 = param_3 - uVar5;
      *(uint *)(&SimpleControl.field_0x14c + SimpleControl._364_4_ * 0xc) =
           *(int *)(&SimpleControl.field_0x14c + SimpleControl._364_4_ * 0xc) - uVar5;
      *(short **)(&SimpleControl.field_0x148 + SimpleControl._364_4_ * 0xc) = psVar4;
      if ((*(int *)(&SimpleControl.field_0x14c + SimpleControl._364_4_ * 0xc) == 0) &&
         (SimpleControl._364_4_ = SimpleControl._364_4_ + 1, 2 < (int)SimpleControl._364_4_)) {
        SimpleControl._364_4_ = 0;
      }
    } while (param_3 != 0);
  }
  return;
}

