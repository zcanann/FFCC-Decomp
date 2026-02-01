// Function: BeginFrame__8CGraphicFv
// Entry: 80019724
// Size: 268 bytes

void BeginFrame__8CGraphicFv(CGraphic *graphic)

{
  bool bVar1;
  ushort uVar3;
  uint uVar2;
  double dVar4;
  
  GXSetZMode(1,3,1);
  GXSetColorUpdate(1);
  dVar4 = (double)FLOAT_8032f6c0;
  GXSetViewport(dVar4,dVar4,
                (double)(float)((double)CONCAT44(0x43300000,
                                                 (uint)*(ushort *)
                                                        (*(int *)&graphic->field_0x71e0 + 4)) -
                               DOUBLE_8032f6d8),
                (double)(float)((double)CONCAT44(0x43300000,
                                                 (uint)*(ushort *)
                                                        (*(int *)&graphic->field_0x71e0 + 6)) -
                               DOUBLE_8032f6d8),dVar4,(double)FLOAT_8032f6c4);
  GXInvalidateVtxCache();
  GXInvalidateTexAll();
  bVar1 = false;
  if (Pad._452_4_ == 0) {
    if (Pad._448_4_ == -1) goto LAB_800197c8;
  }
  bVar1 = true;
LAB_800197c8:
  if (bVar1) {
    uVar3 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar3 = Pad._54_2_;
  }
  if ((uVar3 & 2) != 0) {
    uVar2 = countLeadingZeros(*(undefined4 *)&graphic->field_0x7354);
    *(uint *)&graphic->field_0x7354 = uVar2 >> 5 & 0xff;
  }
  return;
}

