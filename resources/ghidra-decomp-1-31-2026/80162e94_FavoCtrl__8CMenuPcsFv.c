// Function: FavoCtrl__8CMenuPcsFv
// Entry: 80162e94
// Size: 400 bytes

int FavoCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  
  bVar1 = false;
  if (Pad._452_4_ == 0) {
    if (Pad._448_4_ != -1) goto LAB_80162ed0;
  }
  else {
LAB_80162ed0:
    bVar1 = true;
  }
  if (bVar1) {
    uVar2 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar2 = Pad._8_2_;
  }
  if (uVar2 == 0) {
    iVar3 = 0;
  }
  else if ((uVar2 & 0x20) == 0) {
    if ((uVar2 & 0x40) == 0) {
      if ((uVar2 & 0x100) == 0) {
        if ((uVar2 & 0x200) != 0) {
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          iVar3 = 1;
          goto LAB_80162ff8;
        }
      }
      else {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
      iVar3 = 0;
    }
    else {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
      PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
      iVar3 = 1;
    }
  }
  else {
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
    PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
    iVar3 = 1;
  }
LAB_80162ff8:
  if (iVar3 != 0) {
    FavoInit0__8CMenuPcsFv(menuPcs);
  }
  return iVar3;
}

