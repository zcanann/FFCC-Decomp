// Function: CARDCheckExAsync
// Entry: 8019bdb4
// Size: 1424 bytes

int CARDCheckExAsync(undefined4 param_1,undefined4 *param_2,code *param_3)

{
  ushort *puVar1;
  uint uVar2;
  bool bVar3;
  byte bVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  ushort uVar9;
  undefined4 uVar8;
  void *pvVar10;
  ushort *puVar11;
  short *psVar12;
  uint16_t *puVar13;
  uint8_t *puVar14;
  uint16_t *puVar15;
  ushort uVar16;
  uint16_t uVar17;
  int iVar18;
  uint local_40;
  uint local_3c;
  int local_38 [4];
  CARDControl *local_28 [3];
  
  bVar4 = 0;
  bVar5 = false;
  bVar3 = false;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  iVar6 = __CARDGetControlBlock(param_1,local_28);
  if (-1 < iVar6) {
    iVar6 = VerifyID(local_28[0]);
    if (iVar6 < 0) {
      iVar6 = __CARDPutControlBlock(local_28[0],iVar6);
    }
    else {
      iVar6 = VerifyDir(local_28[0],&local_40);
      iVar7 = VerifyFAT(local_28[0],&local_3c);
      if (iVar6 + iVar7 < 2) {
        pvVar10 = local_28[0]->workArea;
        local_38[2] = (int)pvVar10 + 0x2000;
        local_38[0] = (int)pvVar10 + 0x6000;
        local_38[3] = (int)pvVar10 + 0x4000;
        local_38[1] = (int)pvVar10 + 0x8000;
        if (iVar6 + iVar7 == 1) {
          if (local_28[0]->currentDir == (CARDDir *)0x0) {
            local_28[0]->currentDir = (CARDDir *)local_38[local_40 + 2];
            memcpy((void *)local_38[local_40 + 2],local_38[(local_40 ^ 1) + 2],0x2000);
            bVar5 = true;
          }
          else {
            local_28[0]->currentFat = (uint16_t *)local_38[local_3c];
            memcpy((void *)local_38[local_3c],local_38[local_3c ^ 1],0x2000);
            bVar4 = 1;
          }
        }
        iVar7 = local_38[local_3c ^ 1];
        memset(iVar7,0,0x2000);
        iVar18 = 0x7f;
        iVar6 = 0;
        do {
          puVar14 = local_28[0]->currentDir->gameName + iVar6;
          if (*puVar14 != 0xff) {
            uVar9 = *(ushort *)(puVar14 + 0x36);
            for (uVar16 = 0; (uVar9 != 0xffff && (uVar16 < *(ushort *)(puVar14 + 0x38)));
                uVar16 = uVar16 + 1) {
              uVar2 = (uint)uVar9;
              if ((uVar2 < 5) ||
                 ((local_28[0]->cBlock <= uVar2 ||
                  (uVar9 = *(short *)(iVar7 + uVar2 * 2) + 1, *(ushort *)(iVar7 + uVar2 * 2) = uVar9
                  , 1 < uVar9)))) {
                iVar6 = __CARDPutControlBlock(local_28[0],0xfffffffa);
                return iVar6;
              }
              uVar9 = local_28[0]->currentFat[uVar2];
            }
            if ((uVar16 != *(ushort *)(puVar14 + 0x38)) || (uVar9 != 0xffff)) {
              iVar6 = __CARDPutControlBlock(local_28[0],0xfffffffa);
              return iVar6;
            }
          }
          iVar6 = iVar6 + 0x40;
          iVar18 = iVar18 + -1;
        } while (iVar18 != 0);
        psVar12 = (short *)(iVar7 + 10);
        uVar17 = 0;
        iVar6 = 10;
        for (uVar9 = 5; uVar9 < local_28[0]->cBlock; uVar9 = uVar9 + 1) {
          puVar11 = (ushort *)((int)local_28[0]->currentFat + iVar6);
          uVar16 = *puVar11;
          if (*psVar12 == 0) {
            if (uVar16 != 0) {
              *puVar11 = 0;
              bVar3 = true;
            }
            uVar17 = uVar17 + 1;
          }
          else if (((uVar16 < 5) || (local_28[0]->cBlock <= uVar16)) && (uVar16 != 0xffff)) {
            iVar6 = __CARDPutControlBlock(local_28[0],0xfffffffa);
            return iVar6;
          }
          iVar6 = iVar6 + 2;
          psVar12 = psVar12 + 1;
        }
        if (uVar17 != local_28[0]->currentFat[3]) {
          local_28[0]->currentFat[3] = uVar17;
          bVar3 = true;
        }
        if (bVar3) {
          puVar13 = local_28[0]->currentFat;
          puVar13[1] = 0;
          puVar15 = puVar13 + 1;
          puVar11 = puVar13 + 2;
          *puVar13 = 0;
          iVar6 = 0x1ff;
          do {
            *puVar13 = *puVar13 + *puVar11;
            *puVar15 = *puVar15 + ~*puVar11;
            *puVar13 = *puVar13 + puVar11[1];
            *puVar15 = *puVar15 + ~puVar11[1];
            *puVar13 = *puVar13 + puVar11[2];
            *puVar15 = *puVar15 + ~puVar11[2];
            *puVar13 = *puVar13 + puVar11[3];
            *puVar15 = *puVar15 + ~puVar11[3];
            *puVar13 = *puVar13 + puVar11[4];
            *puVar15 = *puVar15 + ~puVar11[4];
            *puVar13 = *puVar13 + puVar11[5];
            *puVar15 = *puVar15 + ~puVar11[5];
            *puVar13 = *puVar13 + puVar11[6];
            *puVar15 = *puVar15 + ~puVar11[6];
            *puVar13 = *puVar13 + puVar11[7];
            puVar1 = puVar11 + 7;
            puVar11 = puVar11 + 8;
            *puVar15 = *puVar15 + ~*puVar1;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          iVar6 = 6;
          do {
            *puVar13 = *puVar13 + *puVar11;
            uVar9 = *puVar11;
            puVar11 = puVar11 + 1;
            *puVar15 = *puVar15 + ~uVar9;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          if (*puVar13 == 0xffff) {
            *puVar13 = 0;
          }
          if (*puVar15 == 0xffff) {
            *puVar15 = 0;
          }
        }
        memcpy((void *)local_38[local_3c ^ 1],local_38[local_3c],0x2000);
        if (bVar5) {
          if (param_2 != (undefined4 *)0x0) {
            *param_2 = 0x2000;
          }
          iVar6 = __CARDUpdateDir(param_1,param_3);
        }
        else if ((bool)(bVar4 | bVar3)) {
          if (param_2 != (undefined4 *)0x0) {
            *param_2 = 0x2000;
          }
          iVar6 = __CARDUpdateFatBlock(param_1,local_28[0]->currentFat,param_3);
        }
        else {
          __CARDPutControlBlock(local_28[0],0);
          if (param_3 != (code *)0x0) {
            uVar8 = OSDisableInterrupts();
            (*param_3)(param_1,0);
            OSRestoreInterrupts(uVar8);
          }
          iVar6 = 0;
        }
      }
      else {
        iVar6 = __CARDPutControlBlock(local_28[0],0xfffffffa);
      }
    }
  }
  return iVar6;
}

