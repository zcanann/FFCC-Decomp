// Function: Get__12CMapKeyFrameFRiRiRf
// Entry: 80033a20
// Size: 552 bytes

/* WARNING: Removing unreachable block (ram,0x80033a64) */

undefined4
Get__12CMapKeyFrameFRiRiRf(CMapKeyFrame *mapKeyFrame,uint *param_2,uint *param_3,float *param_4)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  undefined4 uVar7;
  double dVar8;
  double local_28;
  
  if (*(char *)mapKeyFrame == '\x01') {
    local_28 = (double)(CONCAT44(0x43300000,mapKeyFrame->field5_0x8) ^ 0x80000000);
    dVar8 = (double)Spline1D__5CMathFifPfPfPf
                              ((float)(local_28 - DOUBLE_8032f9e8),-3.284857e-39,
                               mapKeyFrame->field2_0x2 - 1,mapKeyFrame->field17_0x20,
                               (float *)mapKeyFrame->field16_0x1c,*(float **)(mapKeyFrame + 1));
    *param_4 = (float)dVar8;
  }
  else {
    if (*(char *)mapKeyFrame != '\0') {
      *param_4 = FLOAT_8032f9a0;
      bVar1 = **(byte **)&mapKeyFrame->field_0x18;
      *param_3 = (uint)bVar1;
      *param_2 = (uint)bVar1;
      return 0;
    }
    local_28 = (double)(CONCAT44(0x43300000,mapKeyFrame->field5_0x8) ^ 0x80000000);
    dVar8 = (double)Line1D__5CMathFifPfPf
                              ((float)(local_28 - DOUBLE_8032f9e8),-3.284857e-39,
                               mapKeyFrame->field2_0x2 - 1,mapKeyFrame->field17_0x20,
                               (float *)mapKeyFrame->field16_0x1c);
    *param_4 = (float)dVar8;
  }
  dVar8 = DOUBLE_8032f9e8;
  fVar5 = FLOAT_8032f9e0;
  fVar4 = FLOAT_8032f9a0;
  fVar3 = FLOAT_8032f998;
  fVar2 = *param_4;
  if (FLOAT_8032f9a0 < fVar2) {
    local_28 = (double)(CONCAT44(0x43300000,(byte)mapKeyFrame->field_0x1 - 1) ^ 0x80000000);
    if (fVar2 < (float)(local_28 - DOUBLE_8032f9e8)) {
      *param_2 = (int)fVar2;
      *param_3 = (int)(fVar5 + *param_4);
      *param_4 = *param_4 - (float)((double)CONCAT44(0x43300000,*param_2 ^ 0x80000000) - dVar8);
      *param_2 = (uint)*(byte *)(*(int *)&mapKeyFrame->field_0x18 + *param_2);
      if (fVar4 == *param_4) {
        uVar7 = 0;
        *param_3 = *param_2;
      }
      else {
        uVar7 = 1;
        *param_3 = (uint)*(byte *)(*(int *)&mapKeyFrame->field_0x18 + *param_3);
      }
    }
    else {
      uVar7 = 0;
      uVar6 = (uint)*(byte *)(*(int *)&mapKeyFrame->field_0x18 + (uint)(byte)mapKeyFrame->field_0x1
                             + -1);
      *param_3 = uVar6;
      *param_2 = uVar6;
      *param_4 = fVar3;
    }
  }
  else {
    uVar7 = 0;
    bVar1 = **(byte **)&mapKeyFrame->field_0x18;
    *param_3 = (uint)bVar1;
    *param_2 = (uint)bVar1;
    *param_4 = fVar4;
  }
  return uVar7;
}

