// Function: UpdateIconOffsets
// Entry: 8019e9a0
// Size: 504 bytes

void UpdateIconOffsets(CARDDir *cardDir,CARDStat *cardStat)

{
  bool bVar1;
  uint uVar2;
  byte bVar4;
  uint32_t uVar3;
  uint uVar5;
  CARDStat *pCVar6;
  uint32_t uVar7;
  int iVar8;
  
  uVar7 = cardDir->iconAddr;
  if (uVar7 == 0xffffffff) {
    cardStat->bannerFormat = '\0';
    uVar7 = 0;
    cardStat->iconFormat = 0;
    cardStat->iconSpeed = 0;
  }
  bVar1 = false;
  bVar4 = cardDir->bannerFormat & 3;
  if (bVar4 == 2) {
    cardStat->offsetBanner = uVar7;
    uVar7 = uVar7 + 0x1800;
    cardStat->offsetBannerTlut = 0xffffffff;
  }
  else if ((bVar4 < 2) && ((cardDir->bannerFormat & 3) != 0)) {
    cardStat->offsetBanner = uVar7;
    uVar3 = uVar7 + 0xc00;
    uVar7 = uVar7 + 0xe00;
    cardStat->offsetBannerTlut = uVar3;
  }
  else {
    cardStat->offsetBanner = 0xffffffff;
    cardStat->offsetBannerTlut = 0xffffffff;
  }
  iVar8 = 2;
  uVar5 = 0;
  pCVar6 = cardStat;
  do {
    uVar2 = (int)(uint)cardDir->iconFormat >> (uVar5 & 0x3f) & 3;
    if (uVar2 == 2) {
      pCVar6->offsetIcon[0] = uVar7;
      uVar7 = uVar7 + 0x800;
    }
    else if ((uVar2 < 2) && (uVar2 != 0)) {
      pCVar6->offsetIcon[0] = uVar7;
      bVar1 = true;
      uVar7 = uVar7 + 0x400;
    }
    else {
      pCVar6->offsetIcon[0] = 0xffffffff;
    }
    uVar2 = (int)(uint)cardDir->iconFormat >> (uVar5 + 2 & 0x3f) & 3;
    if (uVar2 == 2) {
      pCVar6->offsetIcon[1] = uVar7;
      uVar7 = uVar7 + 0x800;
    }
    else if ((uVar2 < 2) && (uVar2 != 0)) {
      pCVar6->offsetIcon[1] = uVar7;
      bVar1 = true;
      uVar7 = uVar7 + 0x400;
    }
    else {
      pCVar6->offsetIcon[1] = 0xffffffff;
    }
    uVar2 = (int)(uint)cardDir->iconFormat >> (uVar5 + 4 & 0x3f) & 3;
    if (uVar2 == 2) {
      pCVar6->offsetIcon[2] = uVar7;
      uVar7 = uVar7 + 0x800;
    }
    else if ((uVar2 < 2) && (uVar2 != 0)) {
      pCVar6->offsetIcon[2] = uVar7;
      bVar1 = true;
      uVar7 = uVar7 + 0x400;
    }
    else {
      pCVar6->offsetIcon[2] = 0xffffffff;
    }
    uVar2 = (int)(uint)cardDir->iconFormat >> (uVar5 + 6 & 0x3f) & 3;
    if (uVar2 == 2) {
      pCVar6->offsetIcon[3] = uVar7;
      uVar7 = uVar7 + 0x800;
    }
    else if ((uVar2 < 2) && (uVar2 != 0)) {
      pCVar6->offsetIcon[3] = uVar7;
      bVar1 = true;
      uVar7 = uVar7 + 0x400;
    }
    else {
      pCVar6->offsetIcon[3] = 0xffffffff;
    }
    uVar5 = uVar5 + 8;
    pCVar6 = (CARDStat *)(pCVar6->fileName + 0x10);
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  if (bVar1) {
    cardStat->offsetIconTlut = uVar7;
    uVar7 = uVar7 + 0x200;
  }
  else {
    cardStat->offsetIconTlut = 0xffffffff;
  }
  cardStat->offsetData = uVar7;
  return;
}

