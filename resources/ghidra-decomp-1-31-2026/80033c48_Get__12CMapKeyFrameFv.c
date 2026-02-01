// Function: Get__12CMapKeyFrameFv
// Entry: 80033c48
// Size: 196 bytes

/* WARNING: Removing unreachable block (ram,0x80033c70) */

double Get__12CMapKeyFrameFv(CMapKeyFrame *mapKeyFrame)

{
  double dVar1;
  
  if (*(char *)mapKeyFrame == '\x01') {
    dVar1 = (double)Spline1D__5CMathFifPfPfPf
                              ((float)((double)CONCAT44(0x43300000,
                                                        mapKeyFrame->field5_0x8 ^ 0x80000000) -
                                      DOUBLE_8032f9e8),-3.284857e-39,mapKeyFrame->field2_0x2 - 1,
                               mapKeyFrame->field17_0x20,(float *)mapKeyFrame->field16_0x1c,
                               *(float **)(mapKeyFrame + 1));
  }
  else if (*(char *)mapKeyFrame == '\0') {
    dVar1 = (double)Line1D__5CMathFifPfPf
                              ((float)((double)CONCAT44(0x43300000,
                                                        mapKeyFrame->field5_0x8 ^ 0x80000000) -
                                      DOUBLE_8032f9e8),-3.284857e-39,mapKeyFrame->field2_0x2 - 1,
                               mapKeyFrame->field17_0x20,(float *)mapKeyFrame->field16_0x1c);
  }
  else {
    dVar1 = (double)FLOAT_8032f9a0;
  }
  return dVar1;
}

