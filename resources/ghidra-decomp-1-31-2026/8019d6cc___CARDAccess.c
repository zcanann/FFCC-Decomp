// Function: __CARDAccess
// Entry: 8019d6cc
// Size: 152 bytes

undefined4 __CARDAccess(CARDControl *cardControl,char *fileName)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*fileName == -1) {
    uVar1 = 0xfffffffc;
  }
  else if ((cardControl->diskId == (DVDDiskId *)&DAT_80327760) ||
          ((iVar2 = memcmp(fileName,cardControl->diskId,4), iVar2 == 0 &&
           (iVar2 = memcmp(fileName + 4,cardControl->diskId->company,2), iVar2 == 0)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0xfffffff6;
  }
  return uVar1;
}

