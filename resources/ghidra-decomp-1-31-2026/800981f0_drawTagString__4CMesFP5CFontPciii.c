// Function: drawTagString__4CMesFP5CFontPciii
// Entry: 800981f0
// Size: 380 bytes

/* WARNING: Removing unreachable block (ram,0x80098278) */

uint drawTagString__4CMesFP5CFontPciii
               (CFont *font,byte *param_2,int param_3,int param_4,uint param_5)

{
  byte bVar1;
  float fVar2;
  bool bVar3;
  byte *pbVar4;
  uint uVar5;
  double dVar6;
  undefined8 local_48;
  undefined8 local_40;
  
  uVar5 = 0;
  bVar3 = true;
  fVar2 = font->posX;
  while (bVar3) {
    bVar1 = *param_2;
    pbVar4 = param_2 + 1;
    if (bVar1 == 0) {
      bVar3 = false;
      param_2 = pbVar4;
    }
    else if (bVar1 == 0xff) {
      param_2 = param_2 + 2;
      if (*pbVar4 == 0xa1) {
        bVar3 = false;
      }
      else if ((*pbVar4 == 0xa0) && (param_4 != 0)) {
        local_48 = (double)CONCAT44(0x43300000,(int)fVar2 ^ 0x80000000);
        SetPosX__5CFontFf((float)(local_48 - DOUBLE_80330878),font);
        local_40 = (double)CONCAT44(0x43300000,param_5 ^ 0x80000000);
        SetPosY__5CFontFf((float)(local_40 - DOUBLE_80330878) +
                          font->posY +
                          (float)((double)CONCAT44(0x43300000,(uint)*(ushort *)&font->field_0xa) -
                                 DOUBLE_80330880) * font->scaleY,font);
      }
    }
    else {
      if (param_3 != 0) {
        Draw__5CFontFUs(font,(uint)bVar1);
      }
      dVar6 = (double)GetWidth__5CFontFUs(font,(uint)bVar1);
      uVar5 = (uint)((double)(float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) -
                                    DOUBLE_80330878) + dVar6);
      param_2 = pbVar4;
    }
  }
  return uVar5;
}

