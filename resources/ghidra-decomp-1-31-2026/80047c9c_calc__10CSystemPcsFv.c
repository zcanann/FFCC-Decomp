// Function: calc__10CSystemPcsFv
// Entry: 80047c9c
// Size: 188 bytes

void calc__10CSystemPcsFv(void)

{
  ushort uVar2;
  int iVar1;
  
  if (Pad._452_4_ == 0) {
    uVar2 = *(ushort *)
             (&Pad.field_0x36 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
  }
  else {
    uVar2 = 0;
  }
  if ((uVar2 & 0x1000) == 0) {
    if ((uVar2 & 0x100) == 0) {
      if (((uVar2 & 0x800) == 0) && ((uVar2 & 0x40) != 0)) {
        iVar1 = Pad._448_4_ + 1;
        if (iVar1 == 0) {
          iVar1 = Pad._448_4_ + 2;
        }
        Pad._448_4_ = iVar1;
        if (3 < iVar1) {
          Pad._448_4_ = 0xffffffff;
        }
      }
    }
    else {
      Add__11CDbgMenuPcsFv(0x80306708);
    }
  }
  return;
}

