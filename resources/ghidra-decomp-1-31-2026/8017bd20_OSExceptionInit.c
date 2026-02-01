// Function: OSExceptionInit
// Entry: 8017bd20
// Size: 640 bytes

/* WARNING: Removing unreachable block (ram,0x8017be90) */
/* WARNING: Removing unreachable block (ram,0x8017be94) */
/* WARNING: Removing unreachable block (ram,0x8017bed8) */

void OSExceptionInit(void)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  void *dstBuffer;
  uint uVar4;
  int *piVar5;
  
  uVar1 = DAT_8017c060;
  if (DAT_80000060 == 0) {
    DBPrintf(s_Installing_OSDBIntegrator_802168d0);
    memcpy(&DAT_80000060,__OSDBIntegrator,0x24);
    DCFlushRangeNoSync(&DAT_80000060,0x24);
    sync(0);
    ICInvalidateRange(&DAT_80000060,0x24);
  }
  piVar5 = &DAT_80216894;
  for (uVar4 = 0; (uVar4 & 0xff) < 0xf; uVar4 = uVar4 + 1) {
    if (((DAT_8032ef24 == (uint *)0x0) || (*DAT_8032ef24 < 2)) ||
       (iVar2 = __DBIsExceptionMarked(uVar4), iVar2 == 0)) {
      DAT_8017c060 = uVar1 | uVar4 & 0xff;
      iVar2 = __DBIsExceptionMarked(uVar4);
      if (iVar2 == 0) {
        puVar3 = &DAT_8017c050;
        iVar2 = 1;
        do {
          *puVar3 = 0x60000000;
          puVar3 = puVar3 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      else {
        DBPrintf(s_>>>_OSINIT__exception__d_vectore_8021691c,uVar4 & 0xff);
        memcpy(&DAT_8017c050,__OSDBJump,4);
      }
      dstBuffer = (void *)(*piVar5 + -0x80000000);
      memcpy(dstBuffer,OSExceptionVector,0x98);
      DCFlushRangeNoSync(dstBuffer,0x98);
      sync(0);
      ICInvalidateRange(dstBuffer,0x98);
    }
    else {
      DBPrintf(s_>>>_OSINIT__exception__d_command_802168ec,uVar4 & 0xff);
    }
    piVar5 = piVar5 + 1;
  }
  DAT_8032ef44 = &DAT_80003000;
  for (uVar4 = 0; (uVar4 & 0xff) < 0xf; uVar4 = uVar4 + 1) {
    __OSSetExceptionHandler(uVar4,OSDefaultExceptionHandler);
  }
  DAT_8017c060 = uVar1;
  DBPrintf(s_Exceptions_initialized____8021694c);
  return;
}

