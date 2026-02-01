// Function: CARDCreateAsync
// Entry: 8019dd48
// Size: 544 bytes

int CARDCreateAsync(int32_t param_1,undefined4 param_2,uint param_3,CARDFileInfo *param_4,
                   code *param_5)

{
  uint uVar1;
  int iVar2;
  CARDDir *pCVar3;
  ushort uVar4;
  CARDDir *cardDir;
  ushort uVar5;
  CARDControl *local_2c [2];
  
  uVar1 = strlen(param_2);
  if (uVar1 < 0x21) {
    iVar2 = __CARDGetControlBlock(param_1,local_2c);
    if (-1 < iVar2) {
      if ((param_3 == 0) ||
         (param_3 != (param_3 / (uint)local_2c[0]->sectorSize) * local_2c[0]->sectorSize)) {
        iVar2 = -0x80;
      }
      else {
        uVar5 = 0xffff;
        pCVar3 = (CARDDir *)__CARDGetDirBlock(local_2c[0]);
        cardDir = pCVar3;
        for (uVar4 = 0; uVar4 < 0x7f; uVar4 = uVar4 + 1) {
          if (cardDir->gameName[0] == 0xff) {
            if (uVar5 == 0xffff) {
              uVar5 = uVar4;
            }
          }
          else {
            iVar2 = memcmp(cardDir,local_2c[0]->diskId,4);
            if (((iVar2 == 0) &&
                (iVar2 = memcmp(cardDir->company,local_2c[0]->diskId->company,2), iVar2 == 0)) &&
               (iVar2 = __CARDCompareFileName(cardDir,param_2), iVar2 != 0)) {
              iVar2 = __CARDPutControlBlock(local_2c[0],0xfffffff9);
              return iVar2;
            }
          }
          cardDir = cardDir + 1;
        }
        if (uVar5 == 0xffff) {
          iVar2 = __CARDPutControlBlock(local_2c[0],0xfffffff8);
        }
        else {
          iVar2 = __CARDGetFatBlock(local_2c[0]);
          if (local_2c[0]->sectorSize * (uint)*(ushort *)(iVar2 + 6) < param_3) {
            iVar2 = __CARDPutControlBlock(local_2c[0],0xfffffff7);
          }
          else {
            if (param_5 == (code *)0x0) {
              param_5 = __CARDDefaultApiCallback;
            }
            local_2c[0]->apiCallback = param_5;
            local_2c[0]->freeNo = uVar5;
            pCVar3[uVar5].length = (uint16_t)(param_3 / (uint)local_2c[0]->sectorSize);
            strncpy(pCVar3[uVar5].fileName,param_2,0x20);
            local_2c[0]->fileInfo = param_4;
            param_4->chan = param_1;
            param_4->fileNo = (uint)uVar5;
            iVar2 = __CARDAllocBlock(param_1,param_3 / (uint)local_2c[0]->sectorSize,
                                     CreateCallbackFat);
            if (iVar2 < 0) {
              iVar2 = __CARDPutControlBlock(local_2c[0],iVar2);
            }
          }
        }
      }
    }
  }
  else {
    iVar2 = -0xc;
  }
  return iVar2;
}

