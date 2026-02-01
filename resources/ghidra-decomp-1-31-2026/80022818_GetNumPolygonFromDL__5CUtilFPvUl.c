// Function: GetNumPolygonFromDL__5CUtilFPvUl
// Entry: 80022818
// Size: 324 bytes

int GetNumPolygonFromDL__5CUtilFPvUl(CUtil *util,byte *param_2)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  
  bVar4 = true;
  iVar5 = 0;
LAB_80022950:
  do {
    if (!bVar4) {
      return iVar5;
    }
    bVar1 = *param_2;
    uVar2 = *(ushort *)(param_2 + 1);
    uVar7 = (uint)uVar2;
    param_2 = param_2 + 3;
    bVar6 = bVar1 & 0xf8;
    if (bVar6 == 0xa0) {
LAB_8002288c:
      bVar3 = true;
    }
    else {
      if (0x9f < bVar6) {
        if (bVar6 != 0xb0) {
          if (bVar6 < 0xb0) {
            if (bVar6 == 0xa8) goto LAB_8002288c;
          }
          else if (bVar6 == 0xb8) goto LAB_8002288c;
          goto LAB_80022894;
        }
        goto LAB_8002288c;
      }
      if (bVar6 == 0x90) goto LAB_8002288c;
      if (bVar6 < 0x90) {
        if (bVar6 == 0x80) goto LAB_8002288c;
      }
      else if (bVar6 == 0x98) goto LAB_8002288c;
LAB_80022894:
      bVar3 = false;
    }
    if (bVar3) {
      if (bVar6 == 0x90) {
        iVar5 = iVar5 + uVar7 / 3;
      }
      else if (bVar6 == 0x98) {
        iVar5 = uVar7 + iVar5 + -2;
      }
      if ((bVar1 & 7) != 2) {
        if (uVar7 != 0) {
          uVar8 = (uint)(uVar2 >> 3);
          if (uVar2 >> 3 != 0) {
            do {
              param_2 = param_2 + 0x40;
              uVar8 = uVar8 - 1;
            } while (uVar8 != 0);
            uVar7 = uVar7 & 7;
            if ((uVar2 & 7) == 0) goto LAB_80022950;
          }
          do {
            param_2 = param_2 + 8;
            uVar7 = uVar7 - 1;
          } while (uVar7 != 0);
        }
        goto LAB_80022950;
      }
      if (uVar7 != 0) {
        uVar8 = (uint)(uVar2 >> 3);
        if (uVar2 >> 3 != 0) {
          do {
            param_2 = param_2 + 0x50;
            uVar8 = uVar8 - 1;
          } while (uVar8 != 0);
          uVar7 = uVar7 & 7;
          if ((uVar2 & 7) == 0) goto LAB_80022950;
        }
        do {
          param_2 = param_2 + 10;
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
      }
      goto LAB_80022950;
    }
    bVar4 = false;
  } while( true );
}

