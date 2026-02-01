// Function: ArtiCtrlCur__8CMenuPcsFv
// Entry: 8015fa28
// Size: 812 bytes

undefined4 ArtiCtrlCur__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  bool bVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar3 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar3 = Pad._8_2_;
  }
  bVar2 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar2 = true;
  }
  if (bVar2) {
    uVar4 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar4 = Pad._20_2_;
  }
  if (uVar4 == 0) {
    return 0;
  }
  iVar5 = *(int *)&menuPcs->field_0x82c;
  if ((uVar4 & 8) == 0) {
    if ((uVar4 & 4) != 0) {
      iVar6 = iVar5 + *(short *)(iVar5 + 0x30) * 2;
      sVar1 = *(short *)(iVar6 + 0x26);
      if (sVar1 < 7) {
        *(short *)(iVar6 + 0x26) = sVar1 + 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      else if ((int)*(short *)(iVar5 + 0x34) + (int)sVar1 < 0x48) {
        *(short *)(iVar5 + 0x34) = *(short *)(iVar5 + 0x34) + 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      else {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
    }
  }
  else {
    iVar6 = iVar5 + *(short *)(iVar5 + 0x30) * 2;
    sVar1 = *(short *)(iVar6 + 0x26);
    if (sVar1 == 0) {
      if (*(short *)(iVar5 + 0x34) == 0) {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
      else {
        *(short *)(iVar5 + 0x34) = *(short *)(iVar5 + 0x34) + -1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      *(short *)(iVar6 + 0x26) = sVar1 + -1;
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
  }
  if ((uVar4 & 0xc) == 0) {
    if ((uVar3 & 0x20) != 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
      PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
      return 1;
    }
    if ((uVar3 & 0x40) != 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
      PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
      return 1;
    }
    if ((uVar3 & 0x100) == 0) {
      if ((uVar3 & 0x200) != 0) {
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
        PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        return 1;
      }
    }
    else {
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
  }
  return 0;
}

