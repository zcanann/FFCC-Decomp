// Function: DVDConvertPathToEntrynum
// Entry: 80188308
// Size: 756 bytes

uint DVDConvertPathToEntrynum(char *param_1)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  char *unaff_r24;
  uint uVar12;
  char *pcVar13;
  int iVar14;
  
  pcVar11 = param_1;
  uVar12 = DAT_8032f070;
LAB_8018832c:
  while( true ) {
    while( true ) {
      cVar1 = *pcVar11;
      if (cVar1 == '\0') {
        return uVar12;
      }
      if (cVar1 != '/') break;
      uVar12 = 0;
      pcVar11 = pcVar11 + 1;
    }
    if (cVar1 != '.') break;
    cVar1 = pcVar11[1];
    if (cVar1 == '.') {
      if (pcVar11[2] != '/') {
        if (pcVar11[2] == '\0') {
          return *(uint *)(DAT_8032f064 + uVar12 * 0xc + 4);
        }
        break;
      }
      uVar12 = *(uint *)(DAT_8032f064 + uVar12 * 0xc + 4);
      pcVar11 = pcVar11 + 3;
    }
    else {
      if (cVar1 != '/') {
        if (cVar1 == '\0') {
          return uVar12;
        }
        break;
      }
      pcVar11 = pcVar11 + 2;
    }
  }
  pcVar13 = pcVar11;
  if (DAT_8032f074 == 0) {
    bVar3 = false;
    bVar4 = false;
LAB_80188430:
    cVar1 = *pcVar13;
    if ((cVar1 == '\0') || (cVar1 == '/')) goto LAB_80188448;
    if (cVar1 == '.') {
      if ((8 < (int)pcVar13 - (int)pcVar11) || (bVar3)) {
        bVar4 = true;
LAB_80188448:
        if ((bVar3) && (3 < (int)pcVar13 - (int)unaff_r24)) {
          bVar4 = true;
        }
        if (bVar4) {
          OSPanic(&DAT_8032ead8,0x17b,s_DVDConvertEntrynumToPath_possibl_80217470,param_1);
        }
        goto LAB_801884a8;
      }
      unaff_r24 = pcVar13 + 1;
      bVar3 = true;
    }
    else if (cVar1 == ' ') {
      bVar4 = true;
    }
    pcVar13 = pcVar13 + 1;
    goto LAB_80188430;
  }
  for (; (*pcVar13 != '\0' && (*pcVar13 != '/')); pcVar13 = pcVar13 + 1) {
  }
LAB_801884a8:
  cVar1 = *pcVar13;
  iVar14 = uVar12 * 0xc;
  uVar12 = uVar12 + 1;
LAB_801885b0:
  if (*(uint *)(iVar14 + DAT_8032f064 + 8) <= uVar12) {
    return 0xffffffff;
  }
  uVar8 = *(uint *)(DAT_8032f064 + uVar12 * 0xc);
  if (((uVar8 & 0xff000000) != 0) || (cVar1 == '\0')) {
    pcVar9 = (char *)(DAT_8032f068 + (uVar8 & 0xffffff));
    pcVar10 = pcVar11;
    do {
      if (*pcVar9 == '\0') {
        if ((*pcVar10 == '/') || (*pcVar10 == '\0')) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
        goto LAB_80188570;
      }
      cVar2 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      iVar5 = FUN_801b52a0((int)cVar2);
      cVar2 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      iVar6 = FUN_801b52a0((int)cVar2);
    } while (iVar6 == iVar5);
    bVar3 = false;
LAB_80188570:
    if (bVar3) goto LAB_801885cc;
  }
  puVar7 = (uint *)(DAT_8032f064 + uVar12 * 0xc);
  if ((*puVar7 & 0xff000000) == 0) {
    uVar12 = uVar12 + 1;
  }
  else {
    uVar12 = puVar7[2];
  }
  goto LAB_801885b0;
LAB_801885cc:
  if (cVar1 == '\0') {
    return uVar12;
  }
  pcVar11 = pcVar13 + 1;
  goto LAB_8018832c;
}

